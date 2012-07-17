#ifndef CITY_H
#define CITY_H

#include "list.h"
#include "block.h"
#include "zone.h"
#include "element.h"

class City
{
private:

    List<Block*> *blockList;
    List<Element*> *roadList;
    int xWidth, yWidth;
    int minBlockSize, maxBlockSize;
    float minBuildingHeight, maxBuildingHeight;
    float heightMean, heightVariance;
    bool garden;

public:

    City(int xWidth, int yWidth);
    ~City();

    int getXWidth() const {return xWidth;}
    int getYWidth() const {return yWidth;}
    int getMinBlockSize() const {return minBlockSize;}
    int getMaxBlockSize() const {return maxBlockSize;}
    float getMinBuildingHeight() const {return minBuildingHeight;}
    float getMaxBuildingHeight() const {return maxBuildingHeight;}
    float getHeightMean() const {return heightMean;}
    float getHeightVariance() const {return heightVariance;}
    bool getGarden() const {return garden;}
    List<Block*>* getBlockList() {return blockList;}
    List<Element*>* getRoadList() {return roadList;}

    void setXWidth(int xWidth) {this->xWidth = xWidth;}
    void setYWidth(int yWidth) {this->yWidth = yWidth;}
    void setMinBlockSize(int minBlockSize) {this->minBlockSize = minBlockSize;}
    void setMaxBlockSize(int maxBlockSize) {this->maxBlockSize = maxBlockSize;}
    void setMinBuildingHeight(float minBuildingHeight) {this->minBuildingHeight = minBuildingHeight;}
    void setMaxBuildingHeight(float maxBuildingHeight) {this->maxBuildingHeight = maxBuildingHeight;}
    void setHeightMean(float heightMean) {this->heightMean = heightMean;}
    void setHeightVariance(float heightVariance) {this->heightVariance = heightVariance;}
    void setGarden(bool garden) {this->garden = garden;}

    void divideInBlocks(Zone zone);

};

#endif // CITY_H
