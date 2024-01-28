

#include "Convolution.h"

// Default constructor 
Convolution::Convolution() {
    customKernel1 = new double* [3];
    stride = 1;
    padding = true;
    kHeight = 3;
    kWidth = 3;
    for (int i = 0; i < 3; ++i) {
        customKernel1[i] = new double [3];
        for (int j = 0; j < 3; ++j) {
            customKernel1[i][j] = 1;
        }
    }
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad):
kHeight(kh), kWidth(kw), stride(stride_val), padding(pad){
    customKernel1 = new double *[kh];
    for (int i = 0; i < kh; ++i) {
        customKernel1[i] = new double [kw];
        for (int j = 0; j < kw; ++j) {
            customKernel1[i][j] = customKernel[i][j];
        }

    }

}

// Destructor
Convolution::~Convolution() {
    for (int i = 0; i < kHeight; ++i) {
        delete[] customKernel1[i];
    }
    delete[] customKernel1;
}

// Copy constructor
Convolution::Convolution(const Convolution &other){
    customKernel1 = new double * [other.kHeight];
    kHeight = other.kHeight;
    kWidth = other.kWidth;
    padding = other.padding;
    stride = other.stride;
    for (int i = 0; i < other.kHeight; ++i) {
        customKernel1[i] = new double[other.kHeight];
        for (int j = 0; j < other.kHeight; ++j) {
            customKernel1[i][j] = other.customKernel1[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    this->customKernel1 = other.customKernel1;
    this->kWidth = other.kWidth;
    this->kHeight = other.kHeight;
    this->stride = other.stride;
    this->padding = other.padding;
    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {

    if(padding){
        int oHeight = ((input_image.getHeight() - kHeight + 2) / (stride))+1;
        int oWidth = ((input_image.getWidth() - kWidth + 2) / (stride))+1;
        int height = input_image.getHeight()+2;
        int width = input_image.getWidth()+2;
        double** convolvedHolder = new double *[height];
        double** output = new double * [oHeight];
        for (int i = 0; i < height; ++i) {
            convolvedHolder[i] = new double[width];
            convolvedHolder[i][0] = 0;
            convolvedHolder[i][width-1] = 0;
        }
        for (int j = 0; j < width; ++j) {
            convolvedHolder[0][j] = 0;
            convolvedHolder[height-1][j] = 0;
        }
        for (int i = 1; i < height-1 ; ++i) {
            for (int j = 1; j < width-1; ++j) {
                convolvedHolder[i][j] = input_image.get_data(i-1,j-1);
            }
        }
        for (int i = 0; i < oHeight; ++i) {
            output[i] = new double[oWidth];
            for (int j = 0; j < oWidth; ++j) {
                output[i][j] = 0;
                for (int k = 0; k < kHeight; ++k) {
                    for (int l = 0; l < kWidth; ++l) {
                        output[i][j] += convolvedHolder[i*stride +k][j*stride +l] * customKernel1[k][l];

                    }
                }
            }
        }
        for (int i = 0; i < height; ++i) {
            delete[] convolvedHolder[i];
        }
        delete[] convolvedHolder;

        const double** constOutput = const_cast<const double**>(output);
        ImageMatrix imageMatrix(constOutput, oHeight, oWidth);
        for (int i = 0; i < oHeight; ++i) {
            delete[] output[i];
        }
        delete[] output;
        return imageMatrix;
    }else{
        int oHeight = ((input_image.getHeight() - kHeight) / (stride))+1;
        int oWidth = ((input_image.getWidth() - kWidth) / (stride))+1;
        double** output = new double * [oHeight];
        for (int i = 0; i < oHeight; ++i) {
            output[i] = new double[oWidth];
            for (int j = 0; j < oWidth; ++j) {
                output[i][j] = 0;
                for (int k = 0; k < kHeight; ++k) {
                    for (int l = 0; l < kWidth; ++l) {
                        output[i][j] += input_image.get_data(i*stride +k , j*stride +l)* customKernel1[k][l];

                    }

                }
            }
        }
        const double** constOutput = const_cast<const double**>(output);
        ImageMatrix imageMatrix(constOutput, oHeight, oWidth);
        for (int i = 0; i < oHeight; ++i) {
            delete[] output[i];
        }
        delete[] output;
        return imageMatrix;
    }


}
