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
    for(int i = 0; i < _totalTiles; i++)
    {
        CC_SAFE_RELEASE(_tiles[i]);
    }
    
    delete _tiles;
}

Map *Map::create()
{
    Map *map = new Map();
    if(map && map->init())
    {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

GameTile *Map::getTile(int column, int row)
{
    int rowIndex = row * TILE_COLUMNS;
    int index = column + rowIndex;
    CCAssert((index >= 0 && index < _totalTiles), "Map::getTile() Invalid Tile Index Requested");
    
    return _tiles[index];
}

bool Map::init()
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
        GameTile *tile = GameTile::createWithPosition(ccp(currentX, currentY));
        CC_SAFE_RETAIN(tile);
        
        _tiles[i] = tile;
        
        tile->left = lastTile;
        if(lastTile != NULL)
        {
            lastTile->right = tile;
            if(lastTile->down)
            {
                lastTile->down->upRight = tile;
            }
        }
        
        int row = i / TILE_COLUMNS;
        tile->setZIndex(-1 * row);
        
        if(row > 0)
        {
            GameTile *downTile = _tiles[i - TILE_COLUMNS];
            tile->down = downTile;
            tile->downRight = downTile->right;
            tile->downLeft = downTile->left;
            downTile->up = tile;
            //downTile->upRight = tile->right;
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
    
    return true;
}


GameTile *Map::getTileForTouch(CCTouch *touch)
{
    return getTileForLocation(touch->getLocation());
}


GameTile *Map::getTileForLocation(const CCPoint &location)
{
    for(int i = 0; i < _totalTiles; i++)
    {
        GameTile *tile = _tiles[i];
        if(tile->getFrame().containsPoint(location))
        {
            return tile;
        }
    }
    return NULL;
}