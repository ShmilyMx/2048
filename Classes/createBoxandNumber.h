#include "cocos2d.h"
USING_NS_CC;

class createBoxandNumber :public Layer
{
public:
	createBoxandNumber();
	~createBoxandNumber();
	bool init();
	//创建一个智能指针对象
	static createBoxandNumber * createbox(int number, int wight, int height, float boxX, float boxY);
	void createNumber(int number, int wight, int height, float boxX, float boxY);
	//number的get和set方法
	int getNumber();
	void setNumber(int number);
private:
	int number;
	//为了跨函数使用
	LabelTTF *labelNumber;
};