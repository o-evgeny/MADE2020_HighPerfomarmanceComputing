#include <opencv2/opencv.hpp>
#include <iostream>


void filter_template_grayscale(const uint8_t* h_pic, uint8_t* h_pic_filter, size_t n_row, size_t n_col);

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
  cv::imshow("original_grayscale_filter_template", picture_filter);
  cv::imwrite("../original_grayscale_filter_template.jpg", picture_filter);
  cv::waitKey();

}