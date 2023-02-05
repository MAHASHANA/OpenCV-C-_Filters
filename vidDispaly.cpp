//Srinivs Peri
#include <opencv2\opencv.hpp>
#include <opencv2\imgcodecs.hpp>
#include <iostream>
#include "filter.h"
using namespace cv;
using namespace std;



VideoCapture cap(0);
cv::Mat frame;
Mat gray;
Mat cart;
char key = ' ';


int main() {
   while (true) {
        cap >> frame;
        cv::imshow("Color", frame);
        char key = cv::waitKey(1);
        if (key == 'g') {
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::imshow("Grayscale", gray);
            
        }
        else if (key == 's') {
            cap >> frame;
            cv::imwrite("Capturedimage.jpg", frame);// save's image
            printf("captured image");
        }
        else if (key == 'h') {
            Mat altergrey;
            greyscale(frame, altergrey);
            imshow("AlternativeGreyScale", altergrey); // Alter ative gray scale image
        }
        else if (key == 'b') {

            Mat blurred;
            blur5x5(frame, blurred);
            imshow("Gaussina filtered", blurred); //Gaussian filter output
            
        }
        // If the key is 'y', use the custom Sobel filter in the X direction to find the edges in the X direction and display the result
        else if (key == 'x') {
            Mat3s sobx;
            Mat sx;
            sx=frame.clone();
            sobx= frame.clone();
            sobelX3x3(frame, sobx);
            convertScaleAbs(sobx, sx);
            imshow("sobeloutput_X", sx);  //SobelX filter output     
        }
        // If the key is 'y', use the custom Sobel filter in the Y direction to find the edges in the Y direction and display the result
        else if (key == 'y') {
            Mat3s soby;
            Mat sy;
            sy = frame.clone();
            soby = frame.clone();
            sobelX3x3(frame, soby);
            convertScaleAbs(soby, sy);
            imshow("sobeloutput_Y", sy);//SobelY filter output 
         
        }

        else if (key == 'm') {
            Mat3s xsob;
            Mat3s ysob;
            Mat3s magimg;
            //creates a zero-initialized Mat object with the same number of rows and columns as the input frame,
            //with 3 channels and each channel being of 8-bit unsigned char data type (CV_8UC3)
            xsob = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
            ysob = Mat::zeros(frame.rows, frame.cols, CV_8UC3);
            sobelY3x3(frame, ysob);
            sobelX3x3(frame, xsob);
            magnitude(xsob, ysob, magimg);
            imshow("magnitudefilter", magimg); //Magnitude filter output 
        }
        else if (key == 'l') {
            Mat GausImg;
            blur5x5(frame, GausImg);
            Mat blur;
            blurQuantize(GausImg, blur, 15);
            imshow("blurQuantize", blur); //BlurQuantized filter output 
        }

        else if (key == 'c') {
            for (;;) {
                cap >> frame;
                cartoon(frame, cart, 15, 20);
                imshow("cartoonization", cart);
                waitKey(1);
                //Press p key to exit from the cartoon loop.
                if (waitKey(10) == 'p')
                    break;
                
            }
        }
        //Adds sparkels to the image.To rus the code press w key
        else if (key == 'w') {
            Mat estra = frame;
            add_sparkles(estra, 10000);
            imshow("sparkels", estra); //Extar filter
        }
        //Adds rainbow filter to the image
        else if (key == 'a') {
            Mat rbow ;
            addRainbowEffect(frame, rbow);
            imshow("rbow", rbow);
        }
        
        // keep the curser on the main video and hold it of 2 seconds to quit from the window.
        else if (waitKey(1) == 'q')
            break;
   }
   
   return 0;
}


