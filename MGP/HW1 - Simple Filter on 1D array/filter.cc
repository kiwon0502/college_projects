#include <stdlib.h>
// #include <cstdio>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

float *array_in;
float *array_out_serial;
float *array_out_parallel;

void parallel_filter(int tid, int amount) {
  for (int i=0; i<amount; i++) {
    int idx = tid * amount + i;
    array_out_parallel[idx] = (array_in[idx] + array_in[idx+1] * 2 + array_in[idx+2]) / 4;
  }
  return;
}

void parallel_filter_2(int start, int remain) {
  for (int i= 0; i<(remain); i++) {
    int idx = start + i;
    array_out_parallel[idx] = (array_in[idx] + array_in[idx+1] * 2 + array_in[idx+2]) / 4;
  }
  return;
}

int main(int argc, char** argv) 
{
  if(argc < 2) std::cout<<"Usage : ./filter num_items"<<std::endl;
  int N = atoi(argv[1]);
  int NT = 32;                  // number of threads
  int p = (N-2)/NT;             // size of array that one thread calculates
  int r = (N-2)%NT;             // size of array that the last thread calculates

  //0. Initialize
  const int FILTER_SIZE=3;
  const float k[FILTER_SIZE] = {0.25, 0.5, 0.25};
  array_in = new float[N];
  array_out_serial = new float[N];
  array_out_parallel = new float[N];

  {
    std::chrono::duration<double> diff;
    auto start = std::chrono::steady_clock::now();
    for(int i=0;i<N;i++) {
      array_in[i] = i;
    }
    auto end = std::chrono::steady_clock::now();
    diff = end-start;
    std::cout<<"init took "<<diff.count()<<" sec"<<std::endl;
  }

  {
    //1. Serial
    std::chrono::duration<double> diff;
    auto start = std::chrono::steady_clock::now();
    for(int i=0;i<N-2;i++) {
      for(int j=0;j<FILTER_SIZE;j++) {
        array_out_serial[i] += array_in[i+j] * k[j];
      }
    }
    auto end = std::chrono::steady_clock::now();
    diff = end-start;
    std::cout<<"serial 1D filter took "<<diff.count()<<" sec"<<std::endl;
  }

  {
    //2. parallel 1D filter
    std::chrono::duration<double> diff;
    auto start = std::chrono::steady_clock::now();
    /* TODO: put your own parallelized 1D filter here */
    /****************/
    std::vector<std::thread> threads;
    for (int t=0; t<NT; t++) {
      threads.push_back(std::thread(parallel_filter, t, p));
    }
    if (r!=0) {
      threads.push_back(std::thread(parallel_filter_2, NT * p, r));
    }
    for (auto& thread: threads) {
      thread.join();
    }
    /****************/
    /* TODO: put your own parallelized 1D filter here */
    auto end = std::chrono::steady_clock::now();
    diff = end-start;
    std::cout<<"parallel 1D filter took "<<diff.count()<<" sec"<<std::endl;

    int error_counts=0;
    const float epsilon = 0.01;
    for(int i=0;i<N;i++) {
      float err= std::abs(array_out_serial[i] - array_out_parallel[i]);
      if(err > epsilon) {
        error_counts++;
        if(error_counts < 5) {
          std::cout<<"ERROR at "<<i<<": Serial["<<i<<"] = "<<array_out_serial[i]<<" Parallel["<<i<<"] = "<<array_out_parallel[i]<<std::endl;
          std::cout<<"err: "<<err<<std::endl;
        }
      }
    }

    if(error_counts==0) {
      std::cout<<"PASS"<<std::endl;
    } else {
      std::cout<<"There are "<<error_counts<<" errors"<<std::endl;
    }

  }
  return 0;
}
