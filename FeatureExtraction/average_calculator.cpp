//
//  average_calculator.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include "average_calculator.hpp"

float diagonalAverage(int rowOffset, int columnOffset, int height, int width, int index, const cv::Mat& data) {
    int column = columnOffset;
    int row = rowOffset;
    
    float sum = 0.0f;
    int counter = 0;
    
    if(index < width) {
        column += index;
    } else {
        row +=  index - height + 1;
        column += width - 1;
    }
    
    while(row < rowOffset + height && column >= columnOffset) {
        sum += data.at<uchar>(row++, column--);
        counter++;
    }
    return sum / counter;
}

float segmentAverageByDiagonal(int rowOffset, int columnOffset, int height, int width, const cv::Mat& data) {
    float result = 0.0f;
    int counter = 0;
    
    for(int i=0; i<height+width-1; i++) {
        result += diagonalAverage(rowOffset, columnOffset, height, width, i, data);
        counter++;
    }
    return result/counter;
}

float rowAverage(int rowOffset, int columnOffset, int width, int index, cv::Mat& data) {
    float result = 0.0f;
    
    for(int i=0; i < width; i++) {
        result += data.at<uchar>(rowOffset+index, columnOffset+i);
    }
    
    return result/width;
}

float segmentAverageByRow(int rowOffset, int columnOffset, int height, int width, cv::Mat& data) {
    float result = 0.0f;
    
    for(int i=0; i<height; i++) {
        result += rowAverage(rowOffset, columnOffset, width, i, data);
    }
    
    return result/width;
}

float columnAverage(int rowOffset, int columnOffset, int height, int index, cv::Mat& data) {
    float result = 0.0f;
    
    for(int i=0; i < height; i++) {
        result += data.at<uchar>(rowOffset+i, columnOffset+index);
    }
    
    return result/height;
}

float segmentAverageByColumn(int rowOffset, int columnOffset, int height, int width, cv::Mat& data) {
    float result = 0.0f;
    
    for(int i=0; i<width; i++) {
        result += columnAverage(rowOffset, columnOffset, height, i, data);
    }
    
    return result/width;
}
