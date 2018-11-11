//
//  file_manipulator.hpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#ifndef file_manipulator_hpp
#define file_manipulator_hpp

#include <fstream>
#include <utility>

class MNistFileReader {
    std::ifstream imagesFile;
    std::ifstream labelsFile;
    int rows;
    int columns;
    
    uint elements;
    
public:
    MNistFileReader(std::string imagesPath, std::string lablesPath);
    
    std::pair<char, char*> read();
    
    int numberOfRows();
    int numberOfColumns();
    
    int numberOfElements();
    ~MNistFileReader();
};

#endif /* file_manipulator_hpp */
