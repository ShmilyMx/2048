#include "GameScene.h"
#include "Welcome.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

GameScene::GameScene()
{
	this->arr[4][4] = nullptr;
	this->beginX = 0;
	this->beginY = 0;
	this->endX = 0;
	this->endY = 0;
	this->m_score=0;
	this->number = 0;
	this->m_highScore = 0;
	this->labelScore = nullptr;
	this->labelHighScore = nullptr;
}
GameScene::~GameScene()
{
}
Scene *GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	do
	{
		//获得时间随机种子
		srand((unsigned int)time(0));
		CC_BREAK_IF(!Layer::init());
		//取屏幕大小
		auto vSize = Director::getInstance()->getVisibleSize();
		auto vOrigin = Director::getInstance()->getVisibleOrigin();
		//至背景色为灰色
		auto backColor = LayerColor::create(Color4B::YELLOW);
		this->addChild(backColor);
		//添加lable（重新开始）
		auto label = Label::createWithSystemFont("ShmilyMx", "Consolas", 36);
		label->setColor(Color3B::MAGENTA);
		auto menuitem = MenuItemLabel::create(label, [](Ref *){
			Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene()));
		});
		auto menu = Menu::create(menuitem, NULL);
		menu->setPosition(vOrigin.x + vSize.width / 2, vOrigin.y + vSize.height - 60);
		this->addChild(menu);

		//创建显示label
		auto labelscore = Label::createWithSystemFont("Score:","Consolas", 30);
		labelscore->setPosition(vOrigin.x + 80, vOrigin.y + vSize.height - 130);
		labelscore->setColor(Color3B::MAGENTA);
		this->addChild(labelscore,10);

		//创建最高显示label
		auto labelhighscore = LabelTTF::create("HighScore:", "Consolas", 30);
		labelhighscore->setPosition(vOrigin.x + vSize.width - 100, vOrigin.y + vSize.height - 130);
		labelhighscore->setColor(Color3B::MAGENTA);
		this->addChild(labelhighscore);

		//创建分值label
		labelScore = LabelTTF::create("0", "Consolas", 30);
		labelScore->setPosition(vOrigin.x + 80, vOrigin.y + vSize.height - 180);
		labelScore->setColor(Color3B::MAGENTA);
		this->addChild(labelScore,10,11);


		//创建最高分值label
		auto highScore = UserDefault::getInstance()->getIntegerForKey("HighScore", m_highScore);
		number = highScore;
		labelHighScore = Label::createWithSystemFont(StringUtils::format("%d",number), "Consolas",30);
		labelHighScore->setPosition(vOrigin.x + vSize.width-100, vOrigin.y + vSize.height - 180);
		labelHighScore->setColor(Color3B::MAGENTA);
		this->addChild(labelHighScore, 10, 12);

		//创建4*4的格子
		createBox(vSize);
		//初始化时需要创建两个数字
		createNumber();
		createNumber();


		//添加监听事件
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch * touch, Event *)
		{
			log("=====begin");
			Vec2 onBegin = touch->getLocation();
			beginX = onBegin.x;
			beginY = onBegin.y;
			return  true;
		};
		listener->onTouchEnded = [=](Touch *touch, Event *)
		{
			log("=====end");
			Vec2 onEnd = touch->getLocation();
			endX = onEnd.x - beginX;
			endY = onEnd.y - beginY;


			if (abs(endX) > abs(endY))
			{
				if (endX < -30)
				{
					log("==left");
					bool ismoveleft = false;
					for (int y = 0; y < 4; y++)
					{
						for (int x = 0; x < 4; x++)
						{
							if (arr[x][y]->getNumber() != 0)
							{
								for (int x1 = 0; x1 <= x; x1++)
								{
									if (arr[x1][y]->getNumber() == 0)
									{
										ismoveleft = true;
										goto left;
									}
								}
								if (x < 3 && arr[x][y]->getNumber() == arr[x + 1][y]->getNumber())
								{
									ismoveleft = true;
									goto left;
								}
							}
							else
							{
								if (x < 3 && arr[x + 1][y]->getNumber() != 0)
								{
									ismoveleft = true;
									goto left;
								}
							}
						}
					}
				left:
					//JudgeNumber();
					moveLeft();
					if (ismoveleft == true)
					{
						createNumber();
					}
					JudgeNumber();
				}
				else if (endX > 30)
				{
					log("==right");
					bool ismoveright = false;
					for (int y = 0; y < 4; y++)
					{
						for (int x = 3; x >= 0; x--)
						{
							if (arr[x][y]->getNumber() != 0)
							{
								for (int x1 = x; x1 < 4; x1++)
								{
									if (arr[x1][y]->getNumber() == 0)
									{
										ismoveright = true;
										goto right;
									}
								}
								if (x > 0 && arr[x][y]->getNumber() == arr[x - 1][y]->getNumber())
								{
									ismoveright = true;
									goto right;
								}
							}
							else
							{
								if (x > 0 && arr[x - 1][y]->getNumber() != 0)
								{
									ismoveright = true;
									goto right;
								}
							}
						}
					}
				right:
					moveRight();
					if (ismoveright == true)
					{
						createNumber();
					}
					JudgeNumber();
				}
				/*else
				{
				log("==the diatance is not long");
				}*/
			}
			else if (abs(endX) < abs(endY))
			{
				if (endY < -30)
				{
					log("==down");
					bool ismovedown = false;
					for (int x = 0; x < 4; x++)
					{
						for (int y = 0; y < 4; y++)
						{
							if (arr[x][y]->getNumber() != 0)
							{
								for (int y1 = 0; y1 <= y; y1++)
								{
									if (arr[x][y1]->getNumber() == 0)
									{
										ismovedown = true;
										goto down;
									}
								}
								if (y < 3 && arr[x][y]->getNumber() == arr[x][y + 1]->getNumber())
								{
									ismovedown = true;
									goto down;
								}
							}
							else
							{
								if (y < 3 && arr[x][y + 1]->getNumber() != 0)
								{
									ismovedown = true;
									goto down;
								}
							}
						}
					}
				down:
					moveDown();
					if (ismovedown == true)
					{
						createNumber();
					}
					JudgeNumber();
				}
				else if (endY > 30)
				{
					log("==up");

					bool ismoveup = false;
					for (int x = 0; x < 4; x++)
					{
						for (int y = 3; y >= 0; y--)
						{
							if (arr[x][y]->getNumber() != 0)
							{
								for (int y1 = y; y1 < 4; y1++)
								{
									if (arr[x][y1]->getNumber() == 0)
									{
										ismoveup = true;
										goto up;
									}
								}
								if (y > 0 && arr[x][y]->getNumber() == arr[x][y - 1]->getNumber())
								{
									ismoveup = true;
									goto up;
								}
							}
							else
							{
								if (y > 0 && arr[x][y - 1]->getNumber() != 0)
								{
									ismoveup = true;
									goto up;
								}
							}
						}
					}
				up:
					moveUp();
					if (ismoveup == true)
					{
						createNumber();
					}
					JudgeNumber();
				}
				/*else
				{
				log("==the diatance is not long");
				}*/
			}
			/*else
			{
			log("===nomove");
			}*/
		};
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	} while (0);
	return false;
}
//创建格子
void GameScene::createBox(Size size)
{
	auto oneSize = size / 4;
	//log("%f %f", oneSize.width,oneSize.height);
	int x = oneSize.width - 5;
	//log("%d", x);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			auto box = createBoxandNumber::createbox(0, x, x, x*i + 10, x*j + 20);
			this->addChild(box);
			arr[i][j] = box;
		}
	}
}
//创建数字
void GameScene::createNumber()
{
	int x = rand() % 4;
	int y = rand() % 4;
	if (arr[x][y]->getNumber() > 0)
	{
		createNumber();
	}
	else
	{
		arr[x][y]->setNumber(rand() % 10 > 8 ? 4 : 2);
	}

}
//上移
bool GameScene::moveUp()
{
	//不能全局 否则会出现指针删除错误
	bool isMoveUp = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (arr[x][y1]->getNumber() != 0)
				{
					if (arr[x][y]->getNumber() == 0)
					{
						arr[x][y]->setNumber(arr[x][y1]->getNumber());
						arr[x][y1]->setNumber(0);
						y++;
						isMoveUp = true;
					}
					else if (arr[x][y]->getNumber() == arr[x][y1]->getNumber())
					{
						arr[x][y]->setNumber(arr[x][y1]->getNumber() * 2);						
						arr[x][y1]->setNumber(0);	
						this->m_score += arr[x][y]->getNumber();
						setScore();
						if (this->m_score>number)
						{
							setHighScore(this->m_score);
						}
						isMoveUp = true;
					}
					break;
				}
			}
		}
	}
	return isMoveUp;
}
//下移
bool GameScene::moveDown()
{
	bool isMoveDown = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (arr[x][y1]->getNumber() != 0)
				{
					//移动
					if (arr[x][y]->getNumber() == 0)
					{
						arr[x][y]->setNumber(arr[x][y1]->getNumber());
						arr[x][y1]->setNumber(0);
						y--;
						isMoveDown = true;
					}
					//叠加
					else if (arr[x][y]->getNumber() == arr[x][y1]->getNumber())
					{
						arr[x][y]->setNumber(arr[x][y1]->getNumber() * 2);
						arr[x][y1]->setNumber(0);
						this->m_score += arr[x][y]->getNumber();
						setScore();
						if (this->m_score>number)
						{
							setHighScore(this->m_score);
						}
						isMoveDown = true;
					}
					break;
				}
			}
		}
	}
	return isMoveDown;
}
//左移
bool GameScene::moveLeft()
{
	bool isMoveLeft = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (arr[x1][y]->getNumber() != 0)
				{
					if (arr[x][y]->getNumber() == 0)
					{
						arr[x][y]->setNumber(arr[x1][y]->getNumber());
						arr[x1][y]->setNumber(0);
						x--;
						isMoveLeft = true;
					}
					else if (arr[x][y]->getNumber() == arr[x1][y]->getNumber())
					{
						arr[x][y]->setNumber(arr[x1][y]->getNumber() * 2);						
						arr[x1][y]->setNumber(0);
						this->m_score += arr[x][y]->getNumber();
						setScore();
						if (this->m_score>number)
						{
							setHighScore(this->m_score);
						}
						isMoveLeft = true;
					}
					break;
				}
			}
		}
	}
	return isMoveLeft;
}
//右移
bool GameScene::moveRight()
{
	bool isMoveRight = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >= 0; x1--)
			{
				if (arr[x1][y]->getNumber() != 0)
				{
					if (arr[x][y]->getNumber() == 0)
					{
						arr[x][y]->setNumber(arr[x1][y]->getNumber());
						arr[x1][y]->setNumber(0);
						x++;
						isMoveRight = true;
					}
					else if (arr[x][y]->getNumber() == arr[x1][y]->getNumber())
					{
						arr[x][y]->setNumber(arr[x1][y]->getNumber() * 2);						
						arr[x1][y]->setNumber(0);
						this->m_score += arr[x][y]->getNumber();
						setScore();
						if (this->m_score>number)
						{
							setHighScore(this->m_score);
						}
						
						isMoveRight = true;
					}
					break;
				}
			}
		}
	}
	return isMoveRight;
}
//判断
void GameScene::JudgeNumber()
{
	int isx = 0;
	int isy = 0;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (arr[x][y]->getNumber() == 2048)
			{
				Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene()));
			}
		}
	}
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{			
			if (arr[x][y]->getNumber()==0)
			{
				isy = 0;
				return;
			}
			 if (y<3 && arr[x][y]->getNumber()!=arr[x][y+1]->getNumber())
			{		
				isy ++;
			}
		}
	}
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (arr[x][y]->getNumber() == 0)
			{
				isx = 0;
				return;
			}
		   if (x<3 && arr[x][y]->getNumber() != arr[x+ 1][y]->getNumber())
			{
				isx ++;
			}
		}
	}
	if (isx==12&&isy==12)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(2, GameScene::createScene()));
	}
}

//更新分数
void GameScene::setScore()
{
	labelScore->setString(__String::createWithFormat("%i", this->m_score)->getCString());
}

void GameScene::setHighScore(int score)
{
	log("%d", score);
	if (m_highScore<score)
	{
		m_highScore = score;
		UserDefault::getInstance()->setIntegerForKey("HighScore", m_highScore);
		labelHighScore->setString(StringUtils::format("%d", m_highScore));
	}
}