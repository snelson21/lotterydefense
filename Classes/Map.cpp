//
//  Map.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/24/14.
//
//

#include "Map.h"
#include "AppMacros.h"
#include "GameTile.h"

Map::Map()
{
    
}

Map::~Map()
{
    
}

void Map::init()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _totalTiles = TILE_ROWS * TILE_COLUMNS;
    _tiles = new GameTile*[_totalTiles];
    
    float firstX = HORIZONTAL_MARGINS + (TILE_HEIGHT / 2.0f);
    float firstY = VERTICAL_MARGINS + (TILE_HEIGHT / 2.0f);
    
    float lastX = winSize.width - HORIZONTAL_MARGINS - (TILE_HEIGHT / 2.0f);
    
    float currentX = firstX;
    float currentY = firstY;
    
    GameTile *lastTile = NULL;
    
    for(int i = 0; i < _totalTiles; i++)
    {
        GameTile *tile = new GameTile();
        tile->setPosition(ccp(currentX, currentY));
        
        _tiles[i] = tile;
        
        tile->left = lastTile;
        if(lastTile != NULL)
        {
            lastTile->right = tile;
        }
        
        int row = i / TILE_COLUMNS;
        if(row > 0)
        {
            GameTile *downTile = _tiles[i - TILE_COLUMNS];
            tile->down = downTile;
            tile->downRight = downTile->right;
            tile->downLeft = downTile->left;
            downTile->up = tile;
            downTile->upRight = tile->right;
            downTile->upLeft = tile->left;
        }
        
        lastTile = tile;
        currentX += TILE_HEIGHT;
        if(currentX > lastX)
        {
            lastTile = NULL;
            currentX = firstX;
            currentY += TILE_HEIGHT;
        }
    }
}