#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(){
    data = nullptr;
    
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double * [imgHeight];
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double [imgWidth];
        for (int j = 0; j < imgWidth; ++j) {
            data[i][j] = 0;
        }
    }
}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    if(data != nullptr && data[0] != nullptr){
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth):height(imgHeight), width(imgWidth){
    data = new double *[imgHeight];
    for (int i = 0; i < imgHeight; ++i) {
        data[i] = new double[imgWidth];
        for (int j = 0; j < imgWidth; ++j) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {
    this->height = other.height;
    this->width = other.width;
    if(other.data){
        this->data = new double* [other.height];
        for (int i = 0; i < other.height; ++i) {
            this->data[i] = new double[other.width];
            for (int j = 0; j < other.width; ++j) {
                this->data[i][j] = other.get_data(i,j);
            }
        }
    }else{
        this->data = nullptr;
    }

}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if(this != &other)
    {
        for (int i = 0; i < this->height; ++i) {
            delete[] this->data[i];
        }
        delete[] this->data;
        this->height = other.height;
        this->width = other.width;
        this->data = new double *[this->height];
        for (int i = 0; i < this->height; ++i) {
            this->data[i] = new double[this->width];
            for (int j = 0; j < this->width; ++j) {
                this->data[i][j] = other.get_data(i,j);
            }
        }
    }
    return *this;
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix matrix(*this);
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            matrix.data[i][j] += other.data[i][j];
        }
    }
    return matrix;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix matrix(*this);
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            matrix.data[i][j] -= other.data[i][j];
        }
    }
    return matrix;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix matrix(*this);
    for (int i = 0; i < matrix.height; ++i) {
        for (int j = 0; j < matrix.width; ++j) {
            matrix.data[i][j] = matrix.data[i][j] * scalar;
        }
    }
    return matrix;
}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;

}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];

}

int ImageMatrix::getHeight() const {
    return height;
}

int ImageMatrix::getWidth() const {
    return width;
}

int ImageMatrix::get_width() const {
    return width;
}

int ImageMatrix::get_height() const {
    return height;
}

