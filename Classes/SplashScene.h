#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"
#include "Field.h"

USING_NS_CC;

class Splash : public cocos2d::Layer {
private:
    void configureField();
    Field field;

public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float delta);
    CREATE_FUNC(Splash);

};

#endif // __Splash_SCENE_H__
