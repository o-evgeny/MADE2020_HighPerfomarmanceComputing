#include <opencv2/opencv.hpp>
#include <iostream>


void filter_template_grayscale(const uint8_t* h_pic, uint8_t* h_pic_filter, size_t n_row, size_t n_col);
void filter_median_grayscale(const uint8_t *h_pic, uint8_t *h_pic_filter, size_t n_row, size_t n_col);
void histogram_grayscale(const uint8_t *h_pic, uint32_t *h_histogram, size_t n_row, size_t n_col);

// работа с чернобелыми изображениями (1 пиксель = 1 канал)
int main() {
  cv::Mat picture = cv::imread("../picture.jpg",cv::IMREAD_GRAYSCALE);
  cv::imshow("original_grayscale", picture);
  cv::imwrite("../original_grayscale.jpg", picture);
  cv::Mat picture_filter;

  // filter template (task1)
  // 8-битное одноканальное
  picture_filter = cv::Mat::zeros(cv::Size(picture.cols, picture.rows), CV_8UC1);
  filter_template_grayscale(picture.data, picture_filter.data, picture.rows, picture.cols);
  cv::imshow("filter_template", picture_filter);
  cv::imwrite("../filter_template.jpg", picture_filter);

  // median template (task2)
  picture_filter = cv::Mat::zeros(cv::Size(picture.cols, picture.rows), CV_8UC1);
  filter_median_grayscale(picture.data, picture_filter.data, picture.rows, picture.cols);
  cv::imshow("filter_median", picture_filter);
  cv::imwrite("../filter_median.jpg", picture_filter);

  //histogram (task3)
  uint32_t* histogram = (uint32_t*)malloc(sizeof(uint32_t)*256);
  memset(histogram,0 ,sizeof(uint32_t)*256);
  histogram_grayscale(picture.data, histogram, picture.rows, picture.cols);
  int32_t sum_pixels=0;
  for(int i=0;i<256;++i) {
	std::cout << i << "=" << histogram[i] << std::endl;
	sum_pixels += histogram[i];
  }
  std::cout<<sum_pixels;
  free(histogram);
  cv::waitKey();

}