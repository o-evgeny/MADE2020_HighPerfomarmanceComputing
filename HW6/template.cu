#include <iostream>
#include <opencv2/opencv.hpp>

// kernel
__global__ void __apply(const uint8_t *pic, uint8_t *pic_filter,
						double *filter, double sum_filter, int32_t n_row_filter, int32_t n_col_filter) {
  int32_t i = blockIdx.x;
  int32_t j = threadIdx.x;
  int32_t n_col = blockDim.x;
  int32_t n_row = gridDim.x;
  uint32_t pixel_current = i * n_col + j;
  // края не размываю
  if (((i - n_row_filter) < 0) |
	  ((i + n_row_filter+2) > n_row) |
	  ((j - n_col_filter) < 0) |
	  ((j + n_col_filter+2) > n_col)) {
	pic_filter[pixel_current] = pic[pixel_current];
	return;
  }
  pic_filter[pixel_current]=0;
  double filt;
  uint8_t pic_part;

  for (int k = 0; k < n_row_filter; ++k) {
	for (int l = 0; l < n_col_filter; ++l) {
	  filt = filter[k*5 + l];
	  pic_part = pic[(i+k-n_row_filter/2)*n_col + (j+l-n_col_filter/2)];
	  //pic_part = pic[i * n_col + j];
	  //printf("%f %f %i k=%i l=%i n_row_filter=%i n_col=%i\n",sum_filter, filt, pic_part, k, l, n_row_filter, n_col);
	  pic_filter[pixel_current] += 1.0/sum_filter*filt*pic_part;
	}
	}
  __syncthreads();
  }

  __host__ void filter_template_grayscale(const uint8_t *h_pic, uint8_t *h_pic_filter, size_t n_row, size_t n_col) {

	// задание шаблона
	  int32_t n_row_filter = 3;
	  int32_t n_col_filter = 3;
	  double sum_filter = 0.0;
	  double h_filter[9];
	  for (auto &f : h_filter) {
		f = 0.9;
		sum_filter += f;
	  }
	double *d_filter;
	cudaMalloc(&d_filter, sizeof(double) * n_row_filter * n_col_filter);
	cudaMemcpy(d_filter, h_filter, sizeof(double) * n_row_filter * n_col_filter, cudaMemcpyHostToDevice);


	// перенос картинки и вывода
	size_t size = sizeof(uint8_t) * n_row * n_col;
	uint8_t *d_pic;
	cudaMalloc(&d_pic, size);
	cudaMemcpy(d_pic, h_pic, size, cudaMemcpyHostToDevice);
	uint8_t *d_pic_filter;
	cudaMalloc(&d_pic_filter, size);
	cudaMemset(d_pic_filter, 0, size);


	//__apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_pic_filter, d_filter, sum_filter, n_row_filter, n_col_filter);
	__apply<<<dim3(n_row, 1, 1), dim3(n_col, 1, 1)>>>(d_pic, d_pic_filter, d_filter, sum_filter, n_row_filter, n_col_filter);

	if (n_col>1024)
	  printf("Big picture. Remake separate threads. Picture not filtered");
	cudaMemcpy(h_pic_filter, d_pic_filter, size, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	cudaFree(d_pic);
	cudaFree(d_pic_filter);
  }