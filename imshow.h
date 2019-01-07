#ifndef IMSHOW_H
#define IMSHOW_H
#include <opencv2/opencv.hpp>

using namespace cv;

void ImageShow(){

    Mat image = imread("/home/pupof/Pictures/google-earth-view-2433.jpg", IMREAD_COLOR);
    Mat out_img = imread("/home/pupof/Pictures/google-earth-view-2433.jpg", IMREAD_COLOR);
    resize(image, image, Size(image.cols*0.5, image.rows*0.5));
    resize(out_img, out_img, Size(out_img.cols*0.5, out_img.rows*0.5));
    
    for (int r = 0; r < out_img.rows; ++r) {
        for (int c = 0; c < out_img.cols; ++c) {
            out_img.at<Vec3b>(r, c)[0] *= 0.95;
            out_img.at<Vec3b>(r, c)[1] *= 0.45;
            out_img.at<Vec3b>(r, c)[2] *= 0.87;
        }
    }
    imshow("Original", image);
    imshow("Modified", out_img);
    waitKey(0);
}


#endif // IMSHOW_H
