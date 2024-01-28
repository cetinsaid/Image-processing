cmake_minimum_required(VERSION 3.22)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment1 main.cpp
        Convolution.cpp
        ImageMatrix.cpp
        ImageLoader.cpp
        ImageSharpening.cpp
        DecodeMessage.cpp
        EdgeDetector.cpp
        EncodeMessage.cpp
        ImageProcessor.cpp)
