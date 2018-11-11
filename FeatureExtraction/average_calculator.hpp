//
//  average_calculator.hpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#ifndef average_calculator_hpp
#define average_calculator_hpp

#include <opencv2/opencv.hpp>

float segmentAverageByDiagonal(int rowOffset, int columnOffset, int height, int width, const cv::Mat& data);

#endif /* average_calculator_hpp */
