#include <iostream>
#include <opencv2/opencv.hpp>

// kernel
__global__ void __apply(const uint8_t *pic, uint32_t *histogram) {
  int32_t i = blockIdx.x;
  int32_t j = threadIdx.x;
  int32_t n_col = blockDim.x;
  int32_t n_row = gridDim.x;
  uint32_t pixel_current = i * n_col + j;
  __syncthreads();
  atomicAdd(histogram+pic[pixel_current],1);
  //histogram[pic[pixel_current]]+=1;
  __syncthreads();
}

__host__ void histogram_grayscale(const uint8_t *h_pic, uint32_t *h_histogram, size_t n_row, size_t n_col) {
  // перенос картинки и вывода
  size_t size = sizeof(uint8_t) * n_row * n_col;
  uint8_t *d_pic;
  cudaMalloc(&d_pic, size);
  cudaMemcpy(d_pic, h_pic, size, cudaMemcpyHostToDevice);
  size_t size_hist = sizeof(uint32_t)*256;
  uint32_t* d_histogram;
  cudaMalloc(&d_histogram, size_hist);
  cudaMemset(d_histogram, 0, size_hist);


  //__apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_pic_filter, d_filter, sum_filter, n_row_filter, n_col_filter);
  __apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_histogram);

  if (n_col>1024)
	printf("Big picture. Remake separate threads. Not build histogram");
  cudaMemcpy(h_histogram, d_histogram, size_hist, cudaMemcpyDeviceToHost);
  cudaDeviceSynchronize();
  cudaFree(d_pic);
  cudaFree(d_histogram);
}