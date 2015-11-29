#include "createBoxandNumber.h"

createBoxandNumber::createBoxandNumber()
{
	this->number = 0;
	this->labelNumber = nullptr;
}
createBoxandNumber::~createBoxandNumber()
{

}
bool createBoxandNumber::init()
{
	do
	{
		CC_BREAK_IF(!Layer::init());
		return true;
	} while (0);
	return false;
}

createBoxandNumber *createBoxandNumber::createbox(int number, int wight, int height, float boxX, float boxY)
{
	createBoxandNumber *BoxandNumber = new createBoxandNumber();
	if (BoxandNumber &&BoxandNumber->init())
	{
		BoxandNumber->autorelease();
		BoxandNumber->createNumber(number,wight,height,boxX,boxY);
	}
	else
	{
		CC_SAFE_DELETE(BoxandNumber);
	}
	return BoxandNumber;
}

void createBoxandNumber::createNumber(int number, int wight, int height, float boxX, float boxY)
{
	this->number = number;
    auto colorBackground = LayerColor::create(Color4B::GRAY,wight-1,height-1);
	colorBackground->setPosition(Vec2(boxX, boxY));
	if (number>0)
	{
		labelNumber = LabelTTF::create(__String::createWithFormat("%d", number)->getCString(), "Cambria", 36);
		labelNumber->setPosition(Vec2(colorBackground->getContentSize()/2));
		colorBackground->addChild(labelNumber);
	}
	else
	{
		labelNumber = LabelTTF::create("", "Cambria", 36);
		labelNumber->setPosition(Vec2(colorBackground->getContentSize() / 2));
		colorBackground->addChild(labelNumber);
	}
	this->addChild(colorBackground);
}

int createBoxandNumber::getNumber()
{
	return number;
}

void createBoxandNumber::setNumber(int number)
{
	this->number = number;
	if (number>0)
	{
		labelNumber->setString(__String::createWithFormat("%d", number)->getCString());
	}
	else
	{
		 labelNumber->setString("");
	}
	if (number == 2)
	{
		labelNumber->setColor(Color3B(128,128,64));
	}
	else if (number == 4)
	{
		labelNumber->setColor(Color3B(64,128,128));
	}
	else if (number == 8)
	{
		labelNumber->setColor(Color3B(0, 128, 0));
	}
	else if (number == 16)
	{
		labelNumber->setColor(Color3B(0,0,255));
	}
	else if (number == 32)
	{
		labelNumber->setColor(Color3B(0,0,128));
	}
	else if (number == 64)
	{
		labelNumber->setColor(Color3B(0,0,64));
	}
	else if (number == 128)
	{
		labelNumber->setColor(Color3B(128,0,128));
	}
	else if (number == 256)
	{
		labelNumber->setColor(Color3B(128,0,64));
	}
	else if (number == 512)
	{
		labelNumber->setColor(Color3B(255,0,128));
	}
	else if (number == 1024)
	{
		labelNumber->setColor(Color3B(255,128,0));
	}
	else if (number == 2048)
	{
		labelNumber->setColor(Color3B(255,0,0));
	}
}