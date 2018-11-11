//
//  label_manager.hpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#ifndef label_manager_hpp
#define label_manager_hpp

#include <unordered_map>

class LabelManager {
    std::unordered_map<char, char> labels;
public:
    LabelManager();
    
    char get(char code);
};

#endif /* label_manager_hpp */
