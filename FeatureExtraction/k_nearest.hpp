//
//  k_nearest.hpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#ifndef k_nearest_hpp
#define k_nearest_hpp

#include <vector>

class KNearest {
    std::vector<std::pair<char, std::vector<float>>> patterns;
    
public:
        
    void addPattern(char label, std::vector<float> feature);
    
    char predict(std::vector<float>& newElem, int k);
};

#endif /* k_nearest_hpp */
