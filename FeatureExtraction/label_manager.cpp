//
//  label_manager.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include "label_manager.hpp"

LabelManager::LabelManager() {
    int counter =0;
    
    for(char index='0'; index <= '9'; index++) {
        labels[counter] = index;
        counter++;
    }
    
    for(char index='A'; index <= 'Z'; index++) {
        labels[counter] = index;
        counter++;
    }
    
    for(char index='a'; index <= 'z'; index++) {
        labels[counter] = index;
        counter++;
    }
}

char LabelManager::get(char code) {
    return labels[code];
}
