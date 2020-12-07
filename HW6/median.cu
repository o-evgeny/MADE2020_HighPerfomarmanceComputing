#include <iostream>
#include <opencv2/opencv.hpp>

// kernel
__global__ void __apply(const uint8_t *pic, uint8_t *pic_filter, int32_t n_row_window, int32_t n_col_window) {
  int32_t i = blockIdx.x;
  int32_t j = threadIdx.x;
  int32_t n_col = blockDim.x;
  int32_t n_row = gridDim.x;
  uint32_t pixel_current = i * n_col + j;
  // края не размываю
  if (((i - n_row_window) < 0) |
	  ((i + n_row_window+2) > n_row) |
	  ((j - n_col_window) < 0) |
	  ((j + n_col_window+2) > n_col)) {
	pic_filter[pixel_current] = pic[pixel_current];
	return;
  }
  //median от window
  uint32_t map_pixel_to_count[256];
  memset(map_pixel_to_count, 0 ,sizeof(uint32_t)*256);
  for(int window_row=0;window_row<n_row_window;++window_row)
	for (int window_col=0;window_col<n_col_window;++window_col){
	  map_pixel_to_count[pic[(i+window_row-n_row_window/2)*n_col+(j+window_col-n_row_window/2)]]+=1;
	}
  uint32_t tmp=0;
  uint8_t pixel_median;
  uint32_t half_count_element_window = (n_row_window*n_col_window)/2;
  for(pixel_median=0;pixel_median!=255;++pixel_median){
	tmp+=map_pixel_to_count[pixel_median];
	if(tmp>half_count_element_window)
		break;
  }
  pic_filter[pixel_current]=pixel_median;
  __syncthreads();
}

__host__ void filter_median_grayscale(const uint8_t *h_pic, uint8_t *h_pic_filter, size_t n_row, size_t n_col) {
  // задание шаблона
  int32_t n_row_filter = 3;
  int32_t n_col_filter = 3;

  // перенос картинки и вывода
  size_t size = sizeof(uint8_t) * n_row * n_col;
  uint8_t *d_pic;
  cudaMalloc(&d_pic, size);
  cudaMemcpy(d_pic, h_pic, size, cudaMemcpyHostToDevice);
  uint8_t *d_pic_filter;
  cudaMalloc(&d_pic_filter, size);
  cudaMemset(d_pic_filter, 0, size);


  //__apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_pic_filter, d_filter, sum_filter, n_row_filter, n_col_filter);
  __apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_pic_filter, n_row_filter, n_col_filter);

  if (n_col>1024)
	printf("Big picture. Remake separate threads. Picture not filtered");
  cudaMemcpy(h_pic_filter, d_pic_filter, size, cudaMemcpyDeviceToHost);
  cudaDeviceSynchronize();
  cudaFree(d_pic);
  cudaFree(d_pic_filter);
}