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
	//�������ֻ����ķ���
	bool moveUp();
	bool moveDown();
	bool moveLeft();
	bool moveRight();
	//��¼��ʼλ�úͽ���λ�õı���
	int beginX;
	int beginY;
	int endX;
	int endY;
	//��¼��ֵ
	int m_score;
	int m_highScore;
	LabelTTF *labelScore;
	Label * labelHighScore;
	//�����߷�
	int number;
private:
	//����һ��ָ�������Ų�����box
	createBoxandNumber *arr[4][4];
	//��������
	void createBox(Size size);
	//��������
	void createNumber();
	//�ж������Ƿ����
	void JudgeNumber();
	void setScore();
	void setHighScore(int score);
};
#endif