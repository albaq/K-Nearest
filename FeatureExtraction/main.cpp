//
//  main.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include <iostream>
#include "label_manager.hpp"
#include "file_manipulator.hpp"
#include "k_nearest.hpp"
#include "image_to_vector_converter.hpp"

#include <unistd.h>

void printCurrentdirectory() {
    char the_path[256];
    
    getcwd(the_path, 255);
    std::cout<<the_path<<std::endl;
}

std::vector<float> preparedRawData(char* data, int numOfRows, int numOfColumns, CvSize subArea) {
    cv::Mat *image = new cv::Mat(numOfRows, numOfColumns, CV_8UC1, data);
    
    cv::resize(*image, *image, cv::Size(90, 60), cv::INTER_CUBIC);
    std::vector<float> response =  convertImage(image, subArea);
    
    delete image;
    return response;
}

int main(int argc, const char * argv[]) {
    MNistFileReader mNistTrainingReader("../../Data/emnist-byclass-train-images-idx3-ubyte", "../../Data/emnist-byclass-train-labels-idx1-ubyte");
    std::cout<<mNistTrainingReader.numberOfElements()<<std::endl;
    LabelManager labelManager;
    
    KNearest kNearest;
    
    CvSize subArea(10, 10);
    
    int totalNumOfElements = mNistTrainingReader.numberOfElements() ;
    
    for (int i=0; i<totalNumOfElements; i++ ) {
        std::pair<char, char*> read = mNistTrainingReader.read();
        
        std::vector<float> treatedData = preparedRawData(read.second, mNistTrainingReader.numberOfRows(), mNistTrainingReader.numberOfColumns(),subArea);

        kNearest.addPattern(read.first, treatedData);

        delete [] read.second;
    }
    
    //test set
    MNistFileReader mNistTestReader("../../Data/emnist-byclass-test-images-idx3-ubyte", "../../Data/emnist-byclass-test-labels-idx1-ubyte");
    
    std::cout<<"Number of Tests: "<<mNistTestReader.numberOfElements()<<std::endl;
    int numberOfCorrectPredictions = 0;
    int numberOfBadPredictions = 0;
    totalNumOfElements = 50;//mNistTestReader.numberOfElements() ;
    for(int i=0; i< totalNumOfElements; i++) {
        std::pair<char, char*> testCharacter = mNistTestReader.read();

        std::vector<float> treatedData = preparedRawData(testCharacter.second, mNistTestReader.numberOfRows(), mNistTestReader.numberOfColumns(),subArea);
        
        char predictedLabel = labelManager.get(kNearest.predict(treatedData, 3));
        char trueLabel = labelManager.get(testCharacter.first);
        
        if (predictedLabel != trueLabel) {
            numberOfBadPredictions++;
            std::cout<<"(Prediction, True) = ("<<predictedLabel<<", "<<trueLabel<<")"<<std::endl;
        } else {
            numberOfCorrectPredictions++;
        }
        
        //std::cout<<"Prediction: "<<labelManager.get(kNearest.predict(treatedData, 3))<<std::endl;
        //std::cout<<"Label: "<<labelManager.get(testCharacter.first)<<std::endl;
        
        delete [] testCharacter.second;
    }
    
    std::cout<<"(correct, incorrect) = ("<<numberOfCorrectPredictions<<", "<<numberOfBadPredictions<<")"<<std::endl;
    std::cout<<"(% correct, % incorrect) = ("<<(numberOfCorrectPredictions/(float)totalNumOfElements)<<", "<<(numberOfBadPredictions/(float)totalNumOfElements)<<")"<<std::endl;
}
