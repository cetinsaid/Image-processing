// DecodeMessage.cpp

#include "DecodeMessage.h"
#include <iostream>
#include <cmath>
#include <bitset>

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    std::vector<int> lsbHolder;
    std::vector<int> decimalHolder;
    std::vector<char> chars;
    std::string lsbValues;

    for(std::pair<int,int> pair:edgePixels){
        lsbHolder.push_back(static_cast<int>(image.get_data(pair.first,pair.second)) % 2);
    }
    for(std::pair<int,int> pair:edgePixels){
        if(static_cast<int>(image.get_data(pair.first,pair.second)) % 2 == 1){
            lsbValues.push_back('1');
        }else{
            lsbValues.push_back('0');}
    }


    int remainder = lsbValues.size() %7;
    if(remainder !=0){
        for (int i = 0; i < 7-remainder; ++i) {
            lsbValues.insert(lsbValues.begin(),'0');
        }
    }

    for (int i = 0; i < lsbValues.size(); i+=7) {
        std::string binarySet = "";
        for (int j = 0; j < 7; ++j) {
            binarySet.push_back(lsbValues[i+j]);
        }
        std::bitset<32> bitset(binarySet);
        unsigned int decimal = bitset.to_ulong();
        decimalHolder.push_back(static_cast<int>(decimal));
    }


    for(int a:decimalHolder){
        if(a <= 32){
            a +=33;
        }else if(a == 127){
            a = 126;}
        chars.push_back(static_cast<char>(a));
    }

    std::string decodedMessage(chars.begin(),chars.end());

    return decodedMessage;
}

