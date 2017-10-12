//
//  Counting.cpp
//  Sofe-4th-mobile
//
//  Created by Alejos on 10/11/17.
//

#include "Counting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Counting::createScene()
{
    return Counting::create();
}

bool Counting::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    initComponents();
    initListeners();
    displaySprites();
    return true;
}

void Counting::initComponents()
{
    spriteArray = Vector<Sprite*>();
    
    circleAmount = 0;
    circleSprite = Sprite::create("circle.png");
    
    squareAmount = 0;
    squareSprite = Sprite::create("square.png");
    
    
    triangleAmount = 0;
    triangleSprite = Sprite::create("triforce.png");
    
    despawnedSprites = 0;
    populateArray();
}

void Counting::populateArray()
{
    int objectAmount = RandomHelper::random_int(2,10);
    for(int i = 0; i < objectAmount; i++)
    {
        int objectPicker = RandomHelper::random_int(1,3);
        switch(objectPicker)
        {
            case 1 :
                spriteArray.pushBack(circleSprite);
                circleAmount++;
                break;
            case 2 :
                spriteArray.pushBack(squareSprite);
                circleAmount++;
                break;
            case 3 :
                spriteArray.pushBack(triangleSprite);
                circleAmount++;
                break;
        }
    }
}

void Counting::initListeners()
{
    auto despawnListener = EventListenerCustom::create("custom_event_sprite_disappear", [=](EventCustom* event)
    {
        despawnedSprites++;
        if (despawnedSprites == spriteArray.size())
        {
            displayCounter();
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(despawnListener, 1);
    
    auto tapListener = EventListenerTouchOneByOne::create();
    tapListener->onTouchBegan = [ this ](Touch* touch, Event* event)
    {
        if (plusButton->getBoundingBox().containsPoint(touch->getLocation()))
        {
            counterUp();
        }
        else if (minusButton->getBoundingBox().containsPoint(touch->getLocation()))
        {
            counterDown();
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(tapListener, this);
    
    auto endListener = EventListenerCustom::create("custom_event_end", [=](EventCustom* event)
    {
       endGame();
    });
    _eventDispatcher->addEventListenerWithSceneGraphPriority(endListener, this);
}

void Counting::displaySprites()
{
    auto size = Director::getInstance()->getVisibleSize();
    float delaySeconds = 0.8;
    for( int i = 0; i < spriteArray.size(); i++ )
    {
        auto delay = DelayTime::create(delaySeconds * i);
        auto spriteSpawn = CallFunc::create([ this, i, size ]()
         {
             Sprite* originalSprite = this->spriteArray.at(i);
             Sprite* clonedSprite = Sprite::createWithTexture(originalSprite->getTexture());
             clonedSprite->setScale(originalSprite->getScaleX(), originalSprite->getScaleY());
             
             clonedSprite->setPosition(Vec2(size.width, size.height/2));
             
             auto moveToLeft = MoveTo::create(1.5f, Vec2(0, size.height/2));
             auto removeSprite = RemoveSelf::create();
             auto callListener = CallFunc::create([this]()
              {
                  EventCustom event("custom_event_sprite_disappear");
                  _eventDispatcher->dispatchEvent(&event);
              });
             
             auto sequence = Sequence::create(moveToLeft, removeSprite, callListener, NULL);
             clonedSprite->runAction(sequence);
             
             addChild(clonedSprite);
         });
        
        auto seq = Sequence::create(delay, spriteSpawn, NULL);
        this->runAction(seq);
    }
}

void Counting::displayCounter()
{
    auto size = Director::getInstance()->getVisibleSize();
    
    auto myLabel = Label::create();
    myLabel->setString("How many did you find?");
    myLabel->setTextColor(Color4B::WHITE);
    myLabel->setPosition(Vec2(size.width/2, size.height/3));
    addChild(myLabel);
    
    counter = 0;
    counterLabel = Label::create();
    counterLabel->setString("0");
    counterLabel->setTextColor(Color4B::WHITE);
    counterLabel->setPosition(Vec2(size.width/2, size.height/4));
    addChild(counterLabel);
    
    minusButton = Sprite::create("minus.png");
    minusButton->setPosition(Vec2(size.width/2.5, size.height/4));
    minusButton->setScale(.5);
    addChild(minusButton);
    
    plusButton = Sprite::create("plus.png");
    plusButton->setScale(.5);
    plusButton->setPosition(Vec2(size.width/1.5 - minusButton->getBoundingBox().size.width, size.height/4));
    addChild(plusButton);
    
    int objectPicker = RandomHelper::random_int(1,3);
    Sprite* questionSprite;
    switch(objectPicker)
    {
        case 1 :
            questionSprite = Sprite::create("circle.png");
            answer = circleAmount;
            break;
        case 2 :
            questionSprite = Sprite::create("square.png");
            answer = squareAmount;
            break;
        case 3 :
            questionSprite = Sprite::create("triforce.png");
            answer = triangleAmount;
            break;
    }
    
    questionSprite->setScale(1.0f);
    questionSprite->setPosition(Vec2(size.width/2, size.height/2));
    
    addChild(questionSprite);
    
    int timeLimit = 5;
    auto delay = DelayTime::create(timeLimit);
    auto end = CallFunc::create([ this ]()
    {
        EventCustom event("custom_event_end");
        _eventDispatcher->dispatchEvent(&event);
    });
    
    auto sequence = Sequence::create(delay, end, NULL);
    this->runAction(sequence);
}

void Counting::counterUp()
{
    counter++;
    counterLabel->setString(std::to_string(counter));
}

void Counting::counterDown()
{
    counter--;
    counterLabel->setString(std::to_string(counter));
}

void Counting::endGame()
{
    int difference = abs(answer - counter);
    counterLabel->setString("ended");
    removeChild(plusButton);
    removeChild(minusButton);
}
