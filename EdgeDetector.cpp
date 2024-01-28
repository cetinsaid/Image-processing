// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>

#include "EdgeDetector.h"
#include "ImageSharpening.h"
#include <cmath>
#include <iostream>

// Default constructor
EdgeDetector::EdgeDetector() {
    magnitude == nullptr;
    Gx = new double*[3];
    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
    }
    Gx[0][0] = -1.0 , Gx[0][1] = 0.0, Gx[0][2] = 1.0 ;
    Gx[1][0] = -2.0, Gx[1][1] = 0.0, Gx[1][2] = 2.0;
    Gx[2][0] = -1.0, Gx[2][1] = 0.0, Gx[2][2] = 1.0;

    Gy = new double*[3];
    for (int i = 0; i < 3; i++) {
        Gy[i] = new double[3];
    }

    Gy[0][0] = -1.0 , Gy[0][1] = -2,0 , Gy[0][2] = -1.0 ;
    Gy[1][0] = 0.0, Gy[1][1] = 0.0, Gy[1][2] = 0.0;
    Gy[2][0] = 1.0, Gy[2][1] = 2.0, Gy[2][2] = 1.0;

    customKernel = new double * [3];
    for (int i = 0; i < 3; ++i) {
        customKernel[i] = new double [3];
        for (int j = 0; j < 3; ++j) {
            customKernel[i][j] = 1;
        }
    }




}

// Destructor
EdgeDetector::~EdgeDetector() {
    for (int i = 0; i < 3; ++i) {
        delete[] Gx[i];
        delete[] Gy[i];
        delete[] customKernel[i];
    }
    delete[] customKernel;
    delete[] Gx;
    delete[] Gy;
    if(magnitude != nullptr){
        for (int i = 0; i < height; ++i) {
            delete[] magnitude[i];
        }
        delete[] magnitude;
    }

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
    std::vector<std::pair<int,int>> pairs;
    Convolution convolution;
    height = input_image.getHeight();
    int width = input_image.getWidth();
    Convolution xConvolver(Gx,3,3,1, true);
    Convolution yConvolver(Gy,3,3,1, true);
    magnitude = new double * [height];
    double** xHolder = new double * [height];
    double** yHolder = new double * [height];
    for (int i = 0; i < height; ++i) {
        magnitude[i] = new double[width];
        xHolder[i] = new double[width];
        yHolder[i] = new double [width];
    }
    const double** constXHolder = const_cast<const double**>(xHolder);
    const double** constYHolder = const_cast<const double**>(yHolder);

    ImageMatrix xImage(constXHolder, height,width);
    ImageMatrix yImage(constYHolder, height, width);

    xImage = xConvolver.convolve(input_image);
    yImage = yConvolver.convolve(input_image);

    double summ = 0;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            magnitude[i][j] = std::sqrt(std::pow(xImage.get_data(i,j) , 2.0)
                                         + std::pow(yImage.get_data(i,j) ,2.0));
            summ += magnitude[i][j];
        }
    }

    double average = summ/(height*width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(magnitude[i][j] > average){
                pairs.push_back(std::make_pair(i,j));
            }
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] xHolder[i];
        delete[] yHolder[i];
    }
    delete[] xHolder;
    delete[] yHolder;

    return pairs;
}

