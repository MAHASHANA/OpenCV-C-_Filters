#pragma once
#include <opencv2\opencv.hpp>
#include <opencv2\imgcodecs.hpp>
#include <iostream>
#include <random>
int greyscale(cv::Mat& src, cv::Mat& dst);
int blur5x5(cv::Mat& src, cv::Mat& dst);
int sobelX3x3(cv::Mat &src, cv::Mat3s &dst);
int sobelY3x3(cv::Mat& src, cv::Mat3s& dst);
int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst);
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);
int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold);
void add_sparkles(cv::Mat& image, int sparkle_count);
int addRainbowEffect(cv::Mat& src, cv::Mat& dst);