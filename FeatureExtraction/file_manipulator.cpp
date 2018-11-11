//
//  file_manipulator.cpp
//  FeatureExtraction
//
//  Created by Alvaro Tolosa on 11/9/18.
//  Copyright © 2018 Alvaro Tolosa. All rights reserved.
//

#include "file_manipulator.hpp"
#include <vector>

int readInt(std::ifstream& featureFile) {
    int number = 0;
    
    unsigned char byte = featureFile.get();
    number |= byte << 3*8;
    
    byte = featureFile.get();
    number |= byte << 2*8;
    
    byte = featureFile.get();
    number |= byte << 8;
    
    byte = featureFile.get();
    number = number | byte;
    
    return number;
}

void readArray(std::ifstream& featureFile, int rows, int columns, char* data) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            data[ j * columns + i ] = featureFile.get();
}

MNistFileReader::MNistFileReader(std::string imagesPath, std::string lablesPath) : imagesFile(imagesPath, std::ios_base::binary), labelsFile(lablesPath, std::ios_base::binary) {
    if(!imagesFile.good()) perror("Can't open the Image file");
    if(!labelsFile.good()) perror("Can't open the Label file");
    
    int magicNumber = readInt(imagesFile);
    int magicLabelNumber = readInt(labelsFile);
    
    if (magicNumber != 2051) perror("Incorrect Image File Format");
    if (magicLabelNumber != 2049) perror("Incorrect Label File Format");
    
    int numberOfImages = readInt(imagesFile);
    int numberOfLabels = readInt(labelsFile);
    
    if (numberOfImages != numberOfLabels) perror("Number Of Labels Don't Match Number Of Images");
    
    elements = numberOfImages;
    rows = readInt(imagesFile);
    columns = readInt(imagesFile);
}

std::pair<char, char*> MNistFileReader::read() {
    char *data = new char[rows*columns];
    
    char code = labelsFile.get();
    readArray(imagesFile, rows, columns, data);
    std::pair<char, char*> response(code, data);
    
    return response;
}

int MNistFileReader::numberOfRows() {
    return rows;
}

int MNistFileReader::numberOfColumns() {
    return columns;
}

int MNistFileReader::numberOfElements() {
    return elements;
}

MNistFileReader::~MNistFileReader() {
    imagesFile.close();
    labelsFile.close();
}
