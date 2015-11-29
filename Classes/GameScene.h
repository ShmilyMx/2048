#ifndef __GameScene_h_
#define __GameScene_h_

#include "cocos2d.h"
#include "createBoxandNumber.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene *createScene();
	bool init();
	CREATE_FUNC(GameScene);
	//创建四种滑动的方向
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	//记录起始位置和结束位置的变量
	int beginX;
	int beginY;
	int endX;
	int endY;
	//记录分值
	int m_score;
	int m_highScore;
	LabelTTF *labelScore;
	Label * labelHighScore;
	//存放最高分
	int number;
private:
	//定义一个指针数组存放产生的box
	createBoxandNumber *arr[4][4];
	//创建方块
	void createBox(Size size);
	//创建数字
	void createNumber();
	//判断数字是否加满
	void JudgeNumber();
	void setScore();
	void setHighScore(int score);
};
#endif