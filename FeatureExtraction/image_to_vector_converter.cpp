//
//  image_to_vector_converter.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include "image_to_vector_converter.hpp"
#include "average_calculator.hpp"

std::vector<float> convertImage(const cv::Mat* element, const CvSize subArea) {
    const cv::Mat* image = element;
    std::vector<float> averages;
    
    int finalRows = image->rows / subArea.height;
    int finalColumns = image->cols / subArea.width;
    
    for(int i=0; i< finalRows; i++)
        for(int j=0; j< finalColumns; j++)
            averages.push_back(segmentAverageByDiagonal(i*subArea.height, j*subArea.width, subArea.height, subArea.width, *image));
    
    
    return averages;
}

/*
std::pair<char, std::vector<float>> convertImage(const std::pair<char, cv::Mat*> element, const CvSize subArea) {
    std::pair<char, std::vector<float>> response;
    cv::Mat* image = element.second;
    std::vector<float> averages;
    
    int finalRows = image->rows / subArea.height;
    int finalColumns = image->cols / subArea.width;
    
    for(int i=0; i< finalRows; i++)
        for(int j=0; j< finalColumns; j++)
            averages.push_back(segmentAverageByDiagonal(i*subArea.height, j*subArea.width, subArea.height, subArea.width, *image));
    
    response.first = element.first;
    response.second = averages;
    
    return response;
}
*/
