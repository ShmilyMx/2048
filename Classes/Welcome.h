#ifndef __welcome_h_
#define __welcome_h_

#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

class Welcome :public Layer
{
public:
	static Scene *createScene();
	bool init();
	CREATE_FUNC(Welcome);
};
#endif