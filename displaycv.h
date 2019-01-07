#ifndef DISPLAYCV_H
#define DISPLAYCV_H
#include <opencv2/opencv.hpp>

using namespace cv;

void Display(Qlabel lbl){
    Mat img = imread("/home/pupof/Pictures/google-earth-view-2433.jpg");
    cvtColor(img, img, COLOR_BGR2RGB);
    
}

#endif // DISPLAYCV_H
