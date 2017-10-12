//
//  Counting.h
//  Sofe-4th
//
//  Created by Alejos on 10/11/17.
//

#ifndef __Counting_SCENE_H__
#define __Counting_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class Counting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    Sprite* circleSprite;
    Sprite* squareSprite;
    Sprite* triangleSprite;
    Sprite* plusButton;
    Sprite* minusButton;
    
    Vector<Sprite*> spriteArray;
    
    int circleAmount;
    int squareAmount;
    int triangleAmount;
    int despawnedSprites;
    int answer;
    int counter;
    Label* counterLabel;
    
    void initComponents();
    void populateArray();
    void initListeners();
    void displaySprites();
    void displayCounter();
    void counterUp();
    void counterDown();
    void endGame();
    
    CREATE_FUNC(Counting);
};


#endif // Counting
