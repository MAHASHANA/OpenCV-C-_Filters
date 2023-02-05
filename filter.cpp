
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <random>


using namespace std;
using namespace cv;

int greyscale(cv::Mat& src, cv::Mat& dst) {
    dst = cv::Mat(src.size(), CV_8UC1);// creats a all zero matrix of uchara 8 with 1 channel
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            Vec3b intensity = src.at<Vec3b>(i, j);
            int blue = intensity.val[0];
            int green = intensity.val[1];
            int red = intensity.val[2];
            dst.at<uchar>(i, j) = blue * 0.0722 + green * 255 + red * 0.0722;
        }
    }
    return 1;
}

int blur5x5(cv::Mat& src, cv::Mat& dst) {
    // Create kernels for horizontal and vertical blurring
    float horizontalKernel[5] = { 1, 2, 4, 2, 1 };
    float verticalKernel[5] = { 1, 2, 4, 2, 1 };

    // Create temporary matrices for storing intermediate results
    cv::Mat temp1(src.rows, src.cols, CV_32FC3);
    cv::Mat temp2(src.rows, src.cols, CV_32FC3);

    // Perform horizontal blurring
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            for (int k = 0; k < 3; k++) {
                float sum = 0;
                for (int m = -2; m <= 2; m++) {
                    if (j + m < 0 || j + m >= src.cols) {
                        sum += src.at<cv::Vec3b>(i, j)[k] * horizontalKernel[m + 2];
                    }
                    else {
                        sum += src.at<cv::Vec3b>(i, j + m)[k] * horizontalKernel[m + 2];
                    }
                }
                temp1.at<cv::Vec3f>(i, j)[k] = sum / 8;
            }
        }
    }

    // Perform vertical blurring
    for (int i = 0; i < temp1.rows; i++) {
        for (int j = 0; j < temp1.cols; j++) {
            for (int k = 0; k < 3; k++) {
                float sum = 0;
                for (int m = -2; m <= 2; m++) {
                    if (i + m < 0 || i + m >= temp1.rows) {
                        sum += temp1.at<cv::Vec3f>(i, j)[k] * verticalKernel[m + 2];
                    }
                    else {
                        sum += temp1.at<cv::Vec3f>(i + m, j)[k] * verticalKernel[m + 2];
                    }
                }
                temp2.at<cv::Vec3f>(i, j)[k] = sum / 12;
            }
        }
    }

    // Convert the final result to 8-bit unsigned char format
    temp2.convertTo(dst, CV_8UC3);

    return 0;
}


// Sobel Filter


int sobelX3x3(cv::Mat &src, cv::Mat3s &dst) {

   

    //convolution with {-1, 0, 1} . 
    

    cv::Mat3s middleimg;
    src.copyTo(middleimg);
    for (int r = 0; r < src.rows; r++)
    {
        cv::Vec3b* psrc = src.ptr<cv::Vec3b>(r);
        cv::Vec3s* pinter = middleimg.ptr<cv::Vec3s>(r);
        for (int c = 0; c < src.cols; c++)
        {
            if (c == 0 or c == src.cols - 1)
            {
                pinter[c][0] = psrc[c][0];
                pinter[c][1] = psrc[c][1];
                pinter[c][2] = psrc[c][2];
            }
            else {
                pinter[c][0] = (psrc[c + 1][0] - psrc[c - 1][0]);
                pinter[c][1] = (psrc[c + 1][1] - psrc[c - 1][1]);
                pinter[c][2] = (psrc[c + 1][2] - psrc[c - 1][2]);
            }
        }
    }

        
                                     
        //convolution with {1,2,1}  filter.
                                   
        for (int r = 1; r < src.rows - 1; r++)
        {
            cv::Vec3s* rx1 = middleimg.ptr<cv::Vec3s>(r - 1);
            cv::Vec3s* rx2 = middleimg.ptr<cv::Vec3s>(r);
            cv::Vec3s* rx2P1 = middleimg.ptr<cv::Vec3s>(r + 1);
            cv::Vec3s* Pxdst = dst.ptr<cv::Vec3s>(r);
            for (int c = 0; c < src.cols; c++)
            {
                Pxdst[c][0] = (rx1[c][0] + (2 * rx2[c][0]) + rx2P1[c][0]) / 4;
                Pxdst[c][1] = (rx1[c][1] + (2 * rx2[c][1]) + rx2P1[c][1]) / 4;
                Pxdst[c][2] = (rx1[c][2] + (2 * rx2[c][2]) + rx2P1[c][2]) / 4;
            }
        }
        return 0;
}
int sobelY3x3(cv::Mat& src, cv::Mat3s& dst) {
    //convolution with {1, 2, 1}. 
    
    cv::Mat3s intermediate;
    src.copyTo(intermediate);
    for (int r = 0; r < src.rows; r++)
    {
        cv::Vec3b* Pysrc = src.ptr<cv::Vec3b>(r);
        cv::Vec3s* Pydst = intermediate.ptr<cv::Vec3s>(r);
        for (int c = 0; c < src.cols; c++)
        {
            if (c == 0 or c == src.cols - 1)
            {
                Pydst[c][0] = Pysrc[c][0];
                Pydst[c][1] = Pysrc[c][1];
                Pydst[c][2] = Pysrc[c][2];
            }
            else {
                Pydst[c][0] = (Pysrc[c - 1][0] + (2 * Pysrc[c][0]) + Pysrc[c + 1][0]) / 4;
                Pydst[c][1] = (Pysrc[c - 1][1] + (2 * Pysrc[c][1]) + Pysrc[c + 1][1]) / 4;
                Pydst[c][2] = (Pysrc[c - 1][2] + (2 * Pysrc[c][2]) + Pysrc[c + 1][2]) / 4;
            }
        }
    }

    
                                 
    //convolution with {-1,0,-1} filter.
                              
   
    for (int r = 1; r < src.rows - 1; r++)
    {
        cv::Vec3s* r1 = intermediate.ptr<cv::Vec3s>(r - 1);
        cv::Vec3s* r2 = intermediate.ptr<cv::Vec3s>(r + 1);
        cv::Vec3s* Pydst = dst.ptr<cv::Vec3s>(r);
        for (int c = 0; c < src.cols; c++)
        {
            Pydst[c][0] = (r2[c][0] - r1[c][0]);
            Pydst[c][1] = (r2[c][1] - r1[c][1]);
            Pydst[c][2] = (r2[c][2] - r1[c][2]);
        }
    }

    return 0;
}


int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst) {
    /* calculates the gradient magnitude based on sobelX and sobelY filter  outputs.
    */
    cv::Mat magx;
    cv::convertScaleAbs(sx, magx);

    cv::Mat magy;
    cv::convertScaleAbs(sy, magy);

    cv::Mat intermeimg = cv::Mat(sx.size(), CV_8UC3);

    for (int row = 0; row < sx.rows; row++)
    {
        cv::Vec3b* sxRowPtr = magx.ptr<cv::Vec3b>(row);
        cv::Vec3b* syRowPtr = magy.ptr<cv::Vec3b>(row);
        cv::Vec3b* dstPtr = intermeimg.ptr<cv::Vec3b>(row);
        for (int col = 0; col < sx.cols; col++) {
            for (int color = 0; color < 3; color++) {
                dstPtr[col][color] = sqrt((sxRowPtr[col][color] * sxRowPtr[col][color]) + (syRowPtr[col][color] * syRowPtr[col][color]));
            }
        }
    }

    cv::convertScaleAbs(intermeimg, dst);

    return 0;
}

//BlurQuantize

int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels) {
    
    // bucket size
    int b = 255 / levels;
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            // loop through each color channel of the pixel
            for (int c = 0; c < src.channels(); c++) {
                // get the color value of the pixel
                int colorValue = src.at<cv::Vec3b>(y, x)[c];
                // calculate the quantized color value
                int quantvalue = colorValue / b * b;
                // set the pixel color to the quantized color value
                src.at<cv::Vec3b>(y, x)[c] = quantvalue;
            }
        }
    }
    dst = src;
    return 0;
}


// cartoonization


int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold) {

    cv::Mat3s Xtemp, Ytemp;
    cv::Mat edges, sx, sy;

    src.copyTo(edges);
    Xtemp = src.clone();// temporary variable to store src
    Ytemp = src.clone();// temporary variable to store src

    sobelX3x3(src, Xtemp);
    convertScaleAbs(Xtemp, sx);// sx will habe the same rows and cols as Xtemp 

    sobelY3x3(src, Ytemp);
    convertScaleAbs(Ytemp, sy);

    magnitude(sx, sy, edges);
    blurQuantize(src, dst, levels);
    //loops through rows
    for (int y = 0; y < src.rows; y++) {
        cv::Vec3b* carsrcptr = edges.ptr<cv::Vec3b>(y);
        cv::Vec3b* CartdstPtr = dst.ptr<cv::Vec3b>(y);
        //loops through colmuns
        for (int x = 0; x < src.cols; x++) {
            if (carsrcptr[x][0] > magThreshold or carsrcptr[x][1] > magThreshold or carsrcptr[x][2] > magThreshold) {
                CartdstPtr[x][0] = 0;
                CartdstPtr[x][1] = 0;
                CartdstPtr[x][2] = 0;
            }
        }
    }
    return 0;

}


// sparkels adder


void add_sparkles(cv::Mat& image, int sparkle_count)
{
    // Detect edges in the image using Canny edge detection
    cv::Mat edges;
    cv::Canny(image, edges, 50, 200);

    // Create a random number generator
    std::mt19937 gen(cv::getTickCount());
    std::uniform_int_distribution<int> x_dist(0, image.cols - 1);
    std::uniform_int_distribution<int> y_dist(0, image.rows - 1);

    // Draw sparkles along the edges
    for (int i = 0; i < sparkle_count; i++)
    {
        int x = x_dist(gen);
        int y = y_dist(gen);
        if (edges.at<uchar>(y, x) != 0)
        {
            cv::circle(image, cv::Point(x, y), 3, cv::Scalar(255, 255, 255), -1);
        }
    }
}

// Adding rainbow to the image
int addRainbowEffect(cv::Mat& src, cv::Mat& dst)
{
    cv::Mat result;
    src.copyTo(result);

    cv::Mat rainbow(src.rows, src.cols, CV_8UC3);
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            float f = static_cast<float>(x) / src.cols;
            cv::Vec3b color;
            if (f >= 0.0f && f < 0.2f) {
                color = cv::Vec3b(255, static_cast<uchar>(f * 5.0f * 255.0f), 0);
            }
            else if (f >= 0.2f && f < 0.4f) {
                color = cv::Vec3b(static_cast<uchar>((0.4f - f) * 5.0f * 255.0f), 255, 0);
            }
            else if (f >= 0.4f && f < 0.6f) {
                color = cv::Vec3b(0, 255, static_cast<uchar>((f - 0.4f) * 5.0f * 255.0f));
            }
            else if (f >= 0.6f && f < 0.8f) {
                color = cv::Vec3b(0, static_cast<uchar>((0.8f - f) * 5.0f * 255.0f), 255);
            }
            else {
                color = cv::Vec3b(static_cast<uchar>((f - 0.8f) * 5.0f * 255.0f), 0, 255);
            }
            rainbow.at<cv::Vec3b>(y, x) = color;
        }
    }

    double alpha = 0.5;
    cv::addWeighted(rainbow, alpha, result, 1 - alpha, 0, result);
    result.copyTo(dst);

    return 0;
}