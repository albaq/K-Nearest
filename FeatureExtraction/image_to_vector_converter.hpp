//
//  image_to_vector_converter.hpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#ifndef image_to_vector_converter_hpp
#define image_to_vector_converter_hpp

#include <opencv2/opencv.hpp>

std::vector<float> convertImage(const cv::Mat* element, const CvSize subArea);
//std::pair<char, std::vector<float>> convertImage(const std::pair<char, cv::Mat*> element, const CvSize subArea);

#endif /* image_to_vector_converter_hpp */
