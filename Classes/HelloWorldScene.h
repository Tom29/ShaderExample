#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void callbackCTime(cocos2d::GLProgram* glProgram, cocos2d::Uniform* uniform);
    void callbackColor(cocos2d::GLProgram* glProgram, cocos2d::Uniform* uniform);
    float m_ctime;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
