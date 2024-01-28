#include "ImageSharpening.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    sharpenedMatrix = nullptr;
    Gx = new double*[3];
    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
        for (int j = 0; j < 3 ; ++j) {
            Gx[i][j] = 1;
        }
    }

}

ImageSharpening::~ImageSharpening(){
    for (int i = 0; i < 3; ++i) {
        delete[] Gx[i];
    }
    delete[] Gx;
    if(sharpenedMatrix != nullptr){
        for (int i = 0; i < height; ++i) {
            delete[] sharpenedMatrix[i];
        }
        delete[] sharpenedMatrix;
    }

}
ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    Convolution convelver(Gx, 3, 3 ,1 , true);
    ImageMatrix test = convelver.convolve(input_image);
    height = test.getHeight();
    width = test.getWidth();

    double ** blurredMatrix = new double * [height];
    sharpenedMatrix = new double * [height];

    for (int i = 0; i < height; ++i) {
        sharpenedMatrix[i] = new double [width];
        blurredMatrix[i] = new double [width];
        for (int j = 0; j < width; ++j) {
            blurredMatrix[i][j] = test.get_data(i,j)/9;
            sharpenedMatrix[i][j] = input_image.get_data(i,j) + k*(input_image.get_data(i,j) - blurredMatrix[i][j]);
            if(sharpenedMatrix[i][j] > 255.0){
                sharpenedMatrix[i][j] = 255.0;
            }else if(sharpenedMatrix[i][j] < 0.2){
                sharpenedMatrix[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < height; ++i) {
        delete[] blurredMatrix[i];
    }
    delete[] blurredMatrix;

    const double** constSharpenedMatrix = const_cast<const double**>(sharpenedMatrix);
    return ImageMatrix(constSharpenedMatrix, height, width);

}
