#ifndef CITY_H
#define CITY_H

#include "chain.h"
#include "block.h"

class City
{
private:

    Chain<Block> *blockChain;
    int xWidth, yWidth;
    int minBlockSize, maxBlockSize;
    float minBuildingHeight, maxBuildingHeight;
    float heightMean, heightSigma;
    bool garden;

public:

    City(int xWidth, int yWidth);

    int getXWidth() const {return xWidth;}
    int getYWidth() const {return yWidth;}
    int getMinBlockSize() const {return minBlockSize;}
    int getMaxBlockSize() const {return maxBlockSize;}
    float getMinBuildingHeight() const {return minBuildingHeight;}
    float getMaxBuildingHeight() const {return maxBuildingHeight;}
    float getHeightMean() const {return heightMean;}
    float getHeightSigma() const {return heightSigma;}
    bool getGarden() const {return garden;}
    Chain<Block>* getBlockChain() {return blockChain;}

    void setXWidth(int xWidth) {this->xWidth = xWidth;}
    void setYWidth(int yWidth) {this->yWidth = yWidth;}
    void setMinBlockSize(int minBlockSize) {this->minBlockSize = minBlockSize;}
    void setMaxBlockSize(int maxBlockSize) {this->maxBlockSize = maxBlockSize;}
    void setMinBuildingHeight(float minBuildingHeight) {this->minBuildingHeight = minBuildingHeight;}
    void setMaxBuildingHeight(float maxBuildingHeight) {this->maxBuildingHeight = maxBuildingHeight;}
    void setHeightMean(float heightMean) {this->heightMean = heightMean;}
    void setHeightSigma(float heightSigma) {this->heightSigma = heightSigma;}
    void setGarden(bool garden) {this->garden = garden;}

    void divideInBlocks();

};

#endif // CITY_H
