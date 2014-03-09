//
//  PathFindTileMinHeap.h
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#ifndef __LotteryDefense__PathFindTileMinHeap__
#define __LotteryDefense__PathFindTileMinHeap__


#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class PathFindTile;
class GameTile;

class PathFindTileMinHeap : public CCObject
{
public:
    PathFindTileMinHeap();
    ~PathFindTileMinHeap();
    static PathFindTileMinHeap *create();
    bool init();
    void insert(PathFindTile *pathFindTile);
    PathFindTile *top();
    PathFindTile *pop();
    int size();
    int indexOfGameTile(GameTile *gameTile);
    PathFindTile *pathFindTileForIndex(int index);
    
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    
protected:
    vector<PathFindTile *> _heap;
    
    int left(int parent);
    int right(int parent);
    int parent(int child);
    bool comparePathSegments(PathFindTile *left, PathFindTile *right);
    void swap(int a, int b);
};

#endif /* defined(__LotteryDefense__PathFindTileMinHeap__) */
