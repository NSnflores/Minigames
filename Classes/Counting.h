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
    
    Sprite* plus;
    Sprite* minus;
    
    Vector<Sprite*> array;
    
    int circles;
    int squares;
    int triangles;
    int spawned;
    int answer;
    int counter;
    Label* label;
    
    void initVariables();
    void initListeners();
    void display();
    void displayCounter();
    void displayUp();
    void displayDown();
    void endGame();
    
    CREATE_FUNC(Counting);
};


#endif // Counting
