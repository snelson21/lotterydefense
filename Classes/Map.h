//
//  Map.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/24/14.
//
//

#ifndef __LotteryDefense__Map__
#define __LotteryDefense__Map__

#include "cocos2d.h"

USING_NS_CC;

class GameTile;

class Map 
{
public:
    Map();
    ~Map();
    
    void init();
    
    inline GameTile **getTiles() { return _tiles; }
    inline int getTotalTiles() { return _totalTiles; }
    
    GameTile *getTile(int column, int row);
    
    GameTile *getTileForTouch(CCTouch *touch);
    
protected:
    
    GameTile **_tiles;
    float _width;
    float _height;
    int _totalTiles;
};

#endif /* defined(__LotteryDefense__Map__) */


