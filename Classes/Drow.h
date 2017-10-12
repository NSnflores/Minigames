#ifndef __Drow_SCENE_H__
#define __Drow_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Drow : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    Sprite* barSprite;
    Sprite* circleSprite;
    
    void initComponents();
    void initAnimation();
    void initClickListener();
    bool isTouchingTheCircle();
    void addPunctuation();

    CREATE_FUNC(Drow);
};

#endif // Drow
