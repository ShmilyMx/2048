#include "cocos2d.h"
USING_NS_CC;

class createBoxandNumber :public Layer
{
public:
	createBoxandNumber();
	~createBoxandNumber();
	bool init();
	//����һ������ָ�����
	static createBoxandNumber * createbox(int number, int wight, int height, float boxX, float boxY);
	void createNumber(int number, int wight, int height, float boxX, float boxY);
	//number��get��set����
	int getNumber();
	void setNumber(int number);
private:
	int number;
	//Ϊ�˿纯��ʹ��
	LabelTTF *labelNumber;
};