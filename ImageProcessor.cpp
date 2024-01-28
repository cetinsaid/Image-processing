#include <iostream>
#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    ImageSharpening sharpening;
    EdgeDetector detector;
    DecodeMessage decoder;
    ImageMatrix sharpenedImage(sharpening.sharpen(img,2));

    std::cout << decoder.decodeFromImage(sharpenedImage,detector.detectEdges(sharpenedImage))<< std::endl;
    
    return decoder.decodeFromImage(sharpenedImage,detector.detectEdges(sharpenedImage));
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageSharpening sharpening;
    EdgeDetector detector;
    ImageMatrix sharpenedImage(sharpening.sharpen(img,2));
    EncodeMessage encodeMessage;

    return encodeMessage.encodeMessageToImage(img , message , detector.detectEdges(sharpenedImage));





}
