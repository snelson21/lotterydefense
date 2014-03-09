//
//  GameScene.cpp
//  LotteryDefense
//
//  Created by Steele Nelson on 2/20/14.
//
//

#include "GameScene.h"
#include "cocos2d.h"
#include "AppMacros.h"
#include "UnitFactory.h"
#include "Unit.h"
#include "Map.h"
#include "GameTile.h"

USING_NS_CC;
using namespace std;

GameScene::GameScene()
: _map(NULL)
{
}

GameScene::~GameScene()
{
    CC_SAFE_RELEASE(_map);
}

bool GameScene::init()
{
    //super (CCLayerColor) init
    if( ! CCLayerColor::initWithColor(BACKGROUND_COLOR))
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    
    setMap(Map::create());
    
    //drawMap(_map);

    addChild(UnitFactory::sharedInstance().getSpriteBatchNode());
    
    Unit *pirate = UnitFactory::sharedInstance().createUnit("Pirate");
    pirate->setAlliance(Neutral);
    pirate->warpToTile(_map->getTile(10,3));
    //drawBoundingBox(pirate);
    
    Unit *soldierAttack = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierAttack->setAlliance(Friendly);
    soldierAttack->warpToTile(_map->getTile(5,3));
    //drawBoundingBox(soldierAttack);
    
    Unit *soldierWalk = UnitFactory::sharedInstance().createUnit("USSoldier");
    soldierWalk->setAlliance(Enemy);
    soldierWalk->warpToTile(_map->getTile(6,7));
    //drawBoundingBox(soldierWalk);
    
    //schedule the update
    this->schedule(schedule_selector(GameScene::update), FIXED_TIMESTEP);
    
    
    return true;
}

void GameScene::setMap(Map *map)
{
    CC_SAFE_RELEASE(_map);
    _map = map;
    CC_SAFE_RETAIN(_map);
}

void GameScene::drawMap(Map *map)
{
    CCDrawNode *drawNode = CCDrawNode::create();
    
    for( int i = 0; i < map->getTotalTiles(); i++ )
    {
        GameTile *tile = map->getTiles()[i];
        drawNode->drawDot(tile->getPosition(), 10.0f, ccc4f(1.0f, 0.0f, 0.0f, 1.0f));
        
        if(tile->up)
        {
            drawNode->drawSegment(tile->getPosition(), tile->up->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->down)
        {
            drawNode->drawSegment(tile->getPosition(), tile->down->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->left)
        {
            drawNode->drawSegment(tile->getPosition(), tile->left->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->right)
        {
            drawNode->drawSegment(tile->getPosition(), tile->right->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->upLeft)
        {
            drawNode->drawSegment(tile->getPosition(), tile->upLeft->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        if(tile->downLeft)
        {
            drawNode->drawSegment(tile->getPosition(), tile->downLeft->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
         
        if(tile->upRight)
        {
            drawNode->drawSegment(tile->getPosition(), tile->upRight->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        
        if(tile->downRight)
        {
            drawNode->drawSegment(tile->getPosition(), tile->downRight->getPosition(), 1.0f, ccc4f(0.0f,1.0f,0.0f,1.0f));
        }
        
    }
    
    addChild(drawNode);
}

void GameScene::drawBoundingBox(Unit *unit)
{
    CCRect bb = unit->boundingBox();
    CCDrawNode *drawNode = CCDrawNode::create();
    ccColor4F fillColor = ccc4f(0.0f, 0.0f, 0.0f, 0.0f);
    ccColor4F borderColor = ccc4f(1.0f, 1.0f, 0.0f, 1.0f);
    CCPoint verts[4];
    verts[0] = bb.origin;
    verts[1] = ccp(bb.origin.x + bb.size.width, bb.origin.y);
    verts[2] = ccp(bb.origin.x + bb.size.width, bb.origin.y + bb.size.height);
    verts[3] = ccp(bb.origin.x, bb.origin.y + bb.size.height);
    
    drawNode->drawPolygon(verts, 4, fillColor, 2.0f, borderColor);
    drawNode->drawDot(unit->getPosition(), 5.0f, borderColor);
    addChild(drawNode);
}

CCScene *GameScene::scene()
{
    CCScene *scene = CCScene::create();
    
    GameScene *layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}


void GameScene::update(float timeElapsed)
{
    float timeToRun = timeElapsed + _timeAccumulator;
    while(timeToRun >= FIXED_TIMESTEP)
    {
        timeToRun = timeToRun - FIXED_TIMESTEP;
        doWork();
    }
    _timeAccumulator = timeToRun;
}

void GameScene::doWork()
{
    
    
}


