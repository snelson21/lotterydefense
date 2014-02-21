//
//  UnitFactory.h
//  LotteryDefense
//
//  Created by Steele Nelson on 2/21/14.
//
//

#ifndef __LotteryDefense__UnitFactory__
#define __LotteryDefense__UnitFactory__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Unit;

class UnitFactory : public CCNode
{
public:
    
    /**
     @brief returns the singleton UnitFactory
     */
    static UnitFactory &sharedInstance();
    
    bool init();
    
    void loadSpriteCache();
    
    void loadAnimations();
    
    CCArray *getUnitTypes();
    
    CCSpriteBatchNode *getSpriteBatchNode();
    
    void setSpriteBatchNode(CCSpriteBatchNode *spriteBatchNode);
    
    Unit *createUnit(const char *name);
    
    
private:
    
    UnitFactory();
    
    CCDictionary *_units;
    
    CCArray *unitTypes;
    
    CCSpriteBatchNode *_spriteBatchNode;
    
    //DO NOT IMPLEMENT
    UnitFactory(UnitFactory const&);
    //DO NOT IMPLEMENT
    void operator=(UnitFactory const&);
};

#endif /* defined(__LotteryDefense__UnitFactory__) */
