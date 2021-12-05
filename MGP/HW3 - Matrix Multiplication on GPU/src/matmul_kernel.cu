#include <stdio.h>
#include <iostream>
#include <chrono>
#include <assert.h>
#include "matmul.h"
using namespace std;

void allocateDeviceMemory(void** M, int size)
{
  cudaError_t err = cudaMalloc(M, size);
  assert(err==cudaSuccess);
}

void deallocateDeviceMemory(void* M)
{
  cudaError_t err = cudaFree(M);
  assert(err==cudaSuccess);
}

void matmul_ref(const int* const matrixA, const int* const matrixB,
                int* const matrixC, const int n) {
  // You can assume matrixC is initialized with zero
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        matrixC[i * n + j] += matrixA[i * n + k] * matrixB[k * n + j];
}

#define TILE_WIDTH 32
__global__ void MatrixMulKernel(const int* M, const int* N, int* const P, int Width) {
  __shared__ int subTileM[TILE_WIDTH][TILE_WIDTH];
  __shared__ int subTileN[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x; int by = blockIdx.y;
  int tx = threadIdx.x; int ty = threadIdx.y;

  int Row = by * TILE_WIDTH + ty;
  int Col = bx * TILE_WIDTH + tx;
  int Pvalue = 0;

  for (int m = 0; m < (Width)/(TILE_WIDTH); m++) {
    if (Row < Width && m * TILE_WIDTH + tx < Width) subTileM[ty][tx] = M[Row * Width + m * TILE_WIDTH + tx];
    else subTileM[ty][tx] = 0;
    
    if (Col < Width && m * TILE_WIDTH + ty < Width) subTileN[ty][tx] = N[(m * TILE_WIDTH + ty) * Width + Col];
    else subTileN[ty][tx] = 0;
    __syncthreads();

    for (int k = 0; k < TILE_WIDTH; k++) { 
      Pvalue += subTileM[ty][k] * subTileN[k][tx];
    }
    __syncthreads();
  }

  if (Row < Width && Col < Width) P[Row * Width + Col] = Pvalue;
}

void matmul_optimized(const int* const matrixA, const int* const matrixB,
                      int* const matrixC, const int* const d_A, const int* const d_B,  int* const d_C, const int n) {

  // TODO: Implement your CUDA code
  int* device_A = (int *)d_A;
  int* device_B = (int *)d_B;
  int size = n * n * sizeof(int);
  cudaMemcpy(device_A, matrixA, size, cudaMemcpyHostToDevice);
  cudaMemcpy(device_B, matrixB, size, cudaMemcpyHostToDevice);

  dim3 dimGrid(n/TILE_WIDTH, n/TILE_WIDTH, 1);
  dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
  MatrixMulKernel<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, n);

  // copy the matrix multiplication result
  cudaMemcpy(matrixC, d_C, size, cudaMemcpyDeviceToHost);
  return;
}

