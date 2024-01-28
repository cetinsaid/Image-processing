#include "EncodeMessage.h"
#include <cmath>
#include <iostream>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions) {
    std::vector<int> decimalChar;

    for (int i = 0; i < message.size(); ++i) {
        decimalChar.push_back(static_cast<int>(message[i]));
    }

    if(message.size() >= 2){
        for (int i = 2 ; i < message.size(); ++i) {
            bool isPrimeIndex = true;
            for (int j =2 ; j < (i/2) +2 ; ++j) {
                if( i != j && i%j == 0 && isPrimeIndex){
                    isPrimeIndex = false;
                }
            }
            if(isPrimeIndex){
                int count = 0;
                int first = 0;
                int second = 1;
                int result =0;
                while(count < i-1 ){
                    result = first + second;
                    first = second;
                    second =result;
                    count++;
                }
                decimalChar[i] += result;
                if(decimalChar[i] <= 32){
                    decimalChar[i] += 33;
                }else if(decimalChar[i] >= 127){
                    decimalChar[i] = 126;
                }
            }
        }
    }

    std::vector<char> manipulatedChars;
    for (int a : decimalChar) {
        manipulatedChars.push_back(static_cast<char>(a));
    }
    std::string manipulatedString(manipulatedChars.begin(),manipulatedChars.end());

    int shiftAmount = manipulatedString.length() / 2;

    std::string shiftedMessage = manipulatedString.substr(manipulatedString.length() - shiftAmount) + manipulatedString.substr(0, manipulatedString.length() - shiftAmount);

    std::vector<int> shiftedDecimal;

    for (int i = 0; i < shiftedMessage.length(); ++i) {
        shiftedDecimal.push_back(static_cast<int>(shiftedMessage[i]));
    }

    std::vector<int> binaryHolder;

    std::vector<std::string> stringHolder;


    for (int i = 0; i < shiftedDecimal.size(); ++i) {
        std::string reversedString = "";
        std::string binaryString = "";
        while (shiftedDecimal[i] > 1){
            binaryString += std::to_string(shiftedDecimal[i] %2);
            shiftedDecimal[i] /= 2;
            if(shiftedDecimal[i] == 1){
                binaryString += "1";
            }
        }
        for (int j = binaryString.size()-1; j >= 0; --j) {
            reversedString += binaryString[j];
        }
        while(binaryString.size()<7){
            binaryString.push_back('0');
        }
        stringHolder.push_back(binaryString);
    }
    
    std::string completeString;

    for (int i = 0; i < stringHolder.size(); ++i) {
        completeString += stringHolder[i];
    }

    ImageMatrix returnableImage(img);

    if(completeString.size() > positions.size()){
        for (int i = 0; i < positions.size(); ++i) {
            if((int)std::round(img.get_data(positions[i].first,positions[i].second)) % 2 ==0 && completeString[i] == '0'){
                continue;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==1 && completeString[i] == '1'){
                continue;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==0 && completeString[i] == '1'){
                returnableImage.get_data()[positions[i].first][positions[i].second] += 1;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==1 && completeString[i] == '0'){
                returnableImage.get_data()[positions[i].first][positions[i].second] -= 1;
            }
        }
    }else{
        for (int i = 0; i < completeString.size(); ++i) {
            if((int)std::round(img.get_data(positions[i].first,positions[i].second)) % 2 ==0 && completeString[i] == '0'){
                continue;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==1 && completeString[i] == '1'){
                continue;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==0 && completeString[i] == '1'){
                returnableImage.get_data()[positions[i].first][positions[i].second] += 1;
            }else if((int)std::round(img.get_data(positions[i].first,positions[i].second)) %2 ==1 && completeString[i] == '0'){
                returnableImage.get_data()[positions[i].first][positions[i].second] -= 1;
            }
        }
    }

   return returnableImage;
}
