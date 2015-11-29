#include "Welcome.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene *Welcome::createScene()
{
	auto scene = Scene::create();
	auto layer = Welcome::create();
	scene->addChild(layer);
	return scene;
}

bool Welcome::init()
{
	do
	{
		//Ìí¼Ó±³¾°ÒôÀÖ
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.mp3");
		//ÉèÖÃÒôÁ¿
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
		//²¥·Å±³¾°ÒôÀÖ
		SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3", true);

		auto vSize = Director::getInstance()->getVisibleSize();
		auto logo = Sprite::create("logo.png");
		logo->setPosition(Vec2(vSize / 2));
		this->addChild(logo);
		auto scaleIn = ScaleTo::create(1.5f, 2);
		auto scaleOut = FadeOut::create(2.5f);
		auto callfun = CallFunc::create([](){
			Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
			/*auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(scene);*/
		});
		logo->runAction(Sequence::create(scaleIn, scaleOut, /*DelayTime::create(1),*/ callfun, NULL));
		return true;
	} while (0);
	return false;
}