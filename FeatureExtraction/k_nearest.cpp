//
//  k_nearest.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include "k_nearest.hpp"
#include <queue>
#include <cmath>
#include <map>

char findMostCommonLabel(std::map<char, int>& bagOfResponses);

float minSquareError(std::vector<float> one, std::vector<float> other);

void KNearest::addPattern(char label, std::vector<float> feature) {
    std::pair<char, std::vector<float>> stored(label, feature);
    patterns.push_back(stored);
}

char KNearest::predict(std::vector<float>& newElem, int k) {
    auto comparator = [](std::pair<char, float> left, std::pair<char, float> right) { return left.second < right.second;};
    std::priority_queue<std::pair<char, float>, std::vector<std::pair<char, float>>, decltype(comparator)> queue(comparator);
    
    for(auto index = patterns.begin(); index != patterns.end(); index++) {
        float mse = minSquareError(index->second, newElem);
        std::pair<char, float> p(index->first, mse);
        queue.push(p);
        if(queue.size() > k) {
            queue.pop();
        }
    }
    
    std::map<char, int> bagOfResponses;
    while(!queue.empty()) {
        
        char label = queue.top().first;
        if(bagOfResponses.find(label) == bagOfResponses.end()) {
            bagOfResponses[label] = 0;
        }
        bagOfResponses[label]++;
        
        queue.pop();
    }
    
    return findMostCommonLabel(bagOfResponses);
}

char findMostCommonLabel(std::map<char, int>& bagOfResponses) {
    char label = 0;
    int max = -1;
    for(auto index = bagOfResponses.begin(); index != bagOfResponses.end(); index++) {
        if (index->second > max) {
            max = index->second;
            label = index->first;
        }
    }
    
    return label;
}

float minSquareError(std::vector<float> one, std::vector<float> other) {
    float error = 0.0f;
    
    for(int i=0; i< one.size(); i++) {
        error += pow(one[i] - other[i], 2);
    }
    
    return error / one.size();
}
