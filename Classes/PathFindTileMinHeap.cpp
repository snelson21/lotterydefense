//
//  PathFindTileMinHeap.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 3/1/14.
//
//

#include "PathFindTileMinHeap.h"
#include "PathFindTile.h"
#include "GameTile.h"

PathFindTileMinHeap::PathFindTileMinHeap(){}

PathFindTileMinHeap::~PathFindTileMinHeap()
{
    for(int i = 0; i < _heap.size(); i++)
    {
        CC_SAFE_RELEASE(_heap[i]);
    }
}

PathFindTileMinHeap *PathFindTileMinHeap::create()
{
    PathFindTileMinHeap *pathFindTileMinHeap = new PathFindTileMinHeap();
    if(pathFindTileMinHeap && pathFindTileMinHeap->init())
    {
        pathFindTileMinHeap->autorelease();
        return pathFindTileMinHeap;
    }
    CC_SAFE_DELETE(pathFindTileMinHeap);
    return NULL;
}
bool PathFindTileMinHeap::init()
{
    return true;
}

int PathFindTileMinHeap::indexOfGameTile(GameTile *gameTile)
{
    for(int i = 0; i < _heap.size(); i++)
    {
        
        if((gameTile->getPosition().x == _heap[i]->getGameTile()->getPosition().x) &&
            gameTile->getPosition().y == _heap[i]->getGameTile()->getPosition().y)
        {
            return i;
        }
    }
    return -1;
}

bool PathFindTileMinHeap::containsGameTile(GameTile *gameTile)
{
    return (indexOfGameTile(gameTile) >= 0);
}

PathFindTile *PathFindTileMinHeap::pathFindTileForIndex(int index)
{
    return _heap[index];
}

void PathFindTileMinHeap::insert(PathFindTile *pathFindTile)
{
    CC_SAFE_RETAIN(pathFindTile);
    _heap.push_back(pathFindTile);
    heapifyUp(_heap.size() - 1);
}

PathFindTile *PathFindTileMinHeap::top()
{
    CCAssert(_heap.size() > 0, "Tried to get the top element of an empty heap");
    return _heap.front();
}

PathFindTile *PathFindTileMinHeap::pop()
{
    CCAssert(_heap.size() > 0, "Tried to pop an empty heap");
    PathFindTile *topSegment = top();
    _heap[0] = _heap.at(_heap.size() - 1); //move last element to the root
    _heap.pop_back();                      //remove last element
    heapifyDown(0);
    
    CC_SAFE_RELEASE(topSegment);
    return topSegment;
}

int PathFindTileMinHeap::size()
{
    return _heap.size();
}

int PathFindTileMinHeap::left(int parent)
{
    int left = 2 * parent + 1;
    return (left < _heap.size()) ? left : -1;
}
int PathFindTileMinHeap::right(int parent)
{
    int right = 2 * parent + 2;
    return (right < _heap.size()) ? right : -1;
}
int PathFindTileMinHeap::parent(int child)
{
    int parent = (child - 1) / 2;
    return (child == 0) ? -1 : parent;
}
void PathFindTileMinHeap::heapifyUp(int index)
{
    if(index == 0)
    {
        return;
    }
    
    PathFindTile *parentSegment = _heap[parent(index)];
    PathFindTile *currentSegment = _heap[index];
    
    if(comparePathSegments(currentSegment, parentSegment))
    {
        return;
    }
    
    swap(parent(index), index);
    heapifyUp(parent(index));
}
void PathFindTileMinHeap::heapifyDown(int index)
{
    int childIndex = left(index); //default to left child
    int tmpChildIndex = right(index);
    if(childIndex >= 0 && tmpChildIndex >= 0 && comparePathSegments(_heap[childIndex], _heap[tmpChildIndex]))
    {
        childIndex = tmpChildIndex; //use the right child
    }
    if(childIndex > 0 && comparePathSegments(_heap[index], _heap[childIndex]))
    {
        swap(childIndex, index);
        heapifyDown(childIndex);
    }
}

bool PathFindTileMinHeap::comparePathSegments(PathFindTile *left, PathFindTile *right)
{
    return left->getFinalScore() > right->getFinalScore();
}

void PathFindTileMinHeap::swap(int a, int b)
{
    PathFindTile *temp = _heap[a];
    _heap[a] = _heap[b];
    _heap[b] = temp;
}