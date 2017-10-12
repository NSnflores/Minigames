#ifndef __Stacking_SCENE_H__
#define __Stacking_SCENE_H__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class Stacking : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    vector<Sprite*> layers;
    
    void initElement();
    
    void initClickListener();
    
    void runInitialAnimation();
    
    void stopAndFall();
    
    Stacking* context = this;

    CREATE_FUNC(Stacking);
};

#endif // Drow
