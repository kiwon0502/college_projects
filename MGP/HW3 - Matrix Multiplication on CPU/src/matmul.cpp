/*#include "matmul.h"
#include <cstring>
#include <omp.h>

void matmul_ref(const int* const matrixA, const int* const matrixB,
                int* const matrixC, const int n) {
  // You can assume matrixC is initialized with zero
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        matrixC[i * n + j] += matrixA[i * n + k] * matrixB[k * n + j];
}

void matmul_optimized(const int* const matrixA, const int* const matrixB,
                      int* const matrixC, const int n) {    // n : 2048 or 4096
  // TODO: Implement your code
  // int tid;
  int blockSize = 16; // L1$ 12x32x1024, 4x32x1024 for each array, 32x1024 floats, about 181^2
  // float temp[block];
  // double sum,C,y,t;

  int* transB = new int[n * n];
  #pragma omp parallel for 
  for (int i=0; i<n; i++)
  for (int j=0; j<n; j++) {
    transB[i*n + j] = matrixB[j*n + i];
  }
  int blockSize = 16;
  #pragma omp parallel for
  for(int bi=0; bi<n; bi+=blockSize)
    for(int bj=0; bj<n; bj+=blockSize)
        for(int bk=0; bk<n; bk+=blockSize)
            for(int i=0; i<blockSize; i++)
                for(int j=0; j<blockSize; j++)
                    for(int k=0; k<blockSize; k++)
                        matrixC[(bi+i) * n + (bj+j)] += matrixA[(bi+i) * n + (bk+k)] * matrixB[(bk+k) * n + (bj+j)];
  // for (int jj=0; jj<n; jj+=block)
  // for (int ii=0; ii<n; ii+=block)
  // for (int k=0; k<n; k++) {
  //   for(int j=jj; j<(((jj+block)>n)?n:(jj+block)); j++) {
  //     sum=0.0f; C=0.0f;
  //     for(int i=ii; i<(((ii+block)>n)?n:(ii+block)); i++) {
  //       y = matrixA[k*n + i] * transB[j*n + i] - C;
  //       t = sum + y;
  //       C = (t-sum) - y;
  //       sum = t;
  //     }
  //     //temp[j]+=(sum-C);
  //     temp[j] += sum - C;
  //   }
  //   memcpy(&matrixC[k*n +jj], &temp[0], sizeof(float)*(((jj+block)>n)?(n-jj):block)); // jj=49 N=50 block=10, N-
  // } 
}*/

#include "matmul.h"
#include <omp.h>

void matmul_ref(const int* const matrixA, const int* const matrixB,
                int* const matrixC, const int n) {
  // You can assume matrixC is initialized with zero
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        matrixC[i * n + j] += matrixA[i * n + k] * matrixB[k * n + j];
}

void NestedLoopTranspositionPlan(int* const plan, const int n, const int TILE) {
  // Number of complete tiles in each dimension
  const int wTiles = n / TILE;
  int i = 0;
  // Tiled plan
  for (int j = 1; j < wTiles; j++)
  for (int k = 0; k < j; k++) {
    plan[2*i + 0] = j*TILE; // Value of ii
    plan[2*i + 1] = k*TILE; // Value of jj
    i++;
  }
}

void matmul_optimized(const int* const matrixA, const int* const matrixB,
                      int* const matrixC, const int n) {
  // TODO: Implement your code

  int* transB = new int[n * n];
  #pragma omp parallel for 
  for (int i=0; i<n; i++)
  for (int j=0; j<n; j++) {
    transB[i*n + j] = matrixB[j*n + i];
  }



  const int TILE = 32;
  const int blockSize = 32;
  const int wTiles = n / TILE; // Complete tiles in each dimens.
  const int nTilesParallel = wTiles*(wTiles - 1)/2; // # of complete tiles under the main diag.
  int* transB = new int[n * n];
  int* plan = new int[nTilesParallel*2];
  NestedLoopTranspositionPlan(plan, n, TILE);
  #pragma omp parallel // Start of parallel region
  {
  #pragma omp for schedule(guided)
    for (int k = 0; k < nTilesParallel; k++) { // Parallel loop over body tiles
        const int ii = plan[2*k + 0]; // Top column of the tile (planned)
        const int jj = plan[2*k + 1]; // Left row of the tile (planned)

        for (int j = jj; j < jj+TILE; j++)  // Tile transposition microkernel:
        #pragma simd // Ensure automatic vectorization
        for (int i = ii; i < ii+TILE; i++) {
            transB[i*n + j] = matrixB[j*n + i]; // Swap matrix elements
            transB[j*n + i] = matrixB[i*n + j]; //
        }
    } // End of main parallel for-loop

    #pragma omp for schedule(static)
    for (int ii = 0; ii < n; ii += TILE) { // Transposing tiles on the main diagonal:
        const int jj = ii;
        for (int j = jj; j < jj+TILE; j++) // Diagonal tile transposition microkernel:
        #pragma simd // Ensure automatic vectorization
        for (int i = ii; i < ii+TILE; i++) { // Avoid duplicate swaps
            transB[i*n + j] = matrixB[j*n + i]; // transB[i][j] = A[j][i]
            transB[j*n + i] = matrixB[i*n + j]; // transB[j][i] = A[i][j]
        }
    }
  }

  #pragma omp parallel for
  for (int bj = 0; bj < n; bj += blockSize) {
    for (int bi = 0; bi < n; bi += blockSize) {
      for (int bk = 0; bk < n; bk += blockSize) {
        for (int i = 0; i < blockSize; i++) {
          for (int j = 0; j < blockSize; j++) {
            int sum = 0;
            for (int k =0; k < blockSize; k++) {
              sum += matrixA[(bi + i)*n + (bk + k)] * transB[(bj + j)*n + (bk + k)];
            }
            matrixC[(bi + i)*n + (bj + j)] += sum;
          }
        }
      }
    }
  }
}