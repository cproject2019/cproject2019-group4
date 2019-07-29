#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

/***定义变量***/

/*指向一个链表*/
List_t list;

//结构体变量
Player_t player = {
	.x = PLAYER_START_X,
	.y = PLAYER_START_Y,
	.sprite = PLAYER,
	.yKey = false,
	.box = false
};

Item_t item[NUM];
Enemy_t enemy[ENEMY_MAX];
Bullet_t bullet[BULLET_MAX_NUM];

//全局变量

bool gameover = false;
bool gamewin = false;
int position = DOWN;
int enemy_num = ENEMY_NUM; //暂时这样初始化，可以在之后的程序中更改
bool doing_jump = false;
int speed = 10;
int bul_num = 0;

bool initializeOnce = false;
bool creatAllImagesOnce = false;

void Initialize(void)// after wantMap()
{
	if (!initializeOnce) //确保只执行一次
	{
		initializeOnce = true;

		srand((unsigned int)time(NULL)); //为了引用随机数

		InitializeBullet();
		InitializeEnemy();

		/*enemy链表的一系列初始化，最终得到一个装好数据的enemy链表*/
		InitializeList(&list);
		if (ListIsFull(&list))
		{
			fprintf(stderr, "No memory!!!!");
			exit(EXIT_FAILURE);
		}

		setEnemyList();

		createSprite(player.sprite, "player");
		setSpritePosition(player.sprite, player.x, LENGTH * player.y);
		playSpriteAnimate(player.sprite, "NEW");
		/*以下不能实现*/
		hideImage(COMMENT_IMAGE);
	}
}

void gravity(void)
{
	if (!checkLocation() && doing_jump == false)
	{
		for (player.y; player.y >= 0; player.y--)
		{
			playSpriteAnimate(player.sprite, "DROP");
			setSpritePosition(player.sprite, player.x, LENGTH * player.y);
			playSpriteAnimate(player.sprite, "DROP");
			if (checkLocation())
			{
				playSpriteAnimate(player.sprite, "NEW");
				break;
			}
		}
	}
}

bool check_intersect(void) //与什么东西碰上之后就retuen true
{
	if (((int)(player.x / LENGTH)) == item[0].x && player.y == item[0].y)
	{
		player.yKey = true;
		hideSprite(item[0].sprite);
		return true;
	}
	else if ((int)(player.x / LENGTH) == item[1].x && player.y == item[1].y && player.yKey == true)
	{
		player.box = true;
		hideSprite(item[1].sprite);
		return true;
	}
	else
		return false;
}

void check_win(void)
{
	update_game();

	if (gameover == true && gamewin == false)
	{
		failed();
	}
	else if (gamewin == true)
	{
		succeed();
	}
	else {}
}

void update_game(void) //update gamewin & gameover
{
	Node_t * pTemp;

	if (player.box == true)
	{
		gamewin = true;
	}
	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.exit == false)
		{
			continue;
		}
		
		if (((int)(player.x / LENGTH)) == pTemp->enemy.x && player.y == pTemp->enemy.y)
		{
			gameover = false;
			break;
		}
	}
}

bool check_x_location(int direction)//检查朝向的方向上是否有障碍，没有则返回true。direction为LEFT或RIGHT
{
	if (direction == LEFT)
	{
		if (canvas[player.y][((int)((player.x - 50) / LENGTH))] == AIR || (player.x > 65 && player.x < 110) ) //如果想要起始的出生地不可进入的话就去掉||后面的内容
			return true;
		else
			return false;
	}
	else if (direction == RIGHT)
	{
		if (canvas[player.y][((int)((player.x + 50)/ LENGTH))] == AIR )
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}

bool check_y_location_up(int input)
{
	if (canvas[(player.y + 1)][((int)(player.x / LENGTH))] == AIR) //我不知道？？？？
		return true;
	else
		return false;
}

bool check_y_location_down(int input)
{
	if (canvas[(player.y - 1)][((int)(player.x / LENGTH))] == AIR)
		return true;
	else
		return false;
}

bool checkLocation(void)//脚下有东西，return true;
{
	if (canvas[(player.y - 1)][(int)(player.x / LENGTH)] == FLOOR)
		return true;
	else
		return false;
}

void creatAllImages(void)
{
	if (!creatAllImagesOnce)
	{
		creatAllImagesOnce = true;

		/*main.c 中的所有图片*/
		createImage(6666, "一个按钮.png");//game2
		
		createImage(4001, "情景末成功.png");//??
		createImage(1120, "再救一次按钮.png");
		createImage(1121, "成功结束按钮.png");

		createImage(42, "情景末happy ending.png");
		createImage(431, "宫殿.png");
		createImage(432, "勇士勋章.png");
		createImage(433, "女将军.png");

		createImage(51, "情景末失败.png");
		createImage(1122, "再救一次按钮.png");
		createImage(1123, "放弃营救.png");

		createImage(52, "情景末tragic ending.png");
		createImage(53, "国王死掉.png");

		/*control.c 中的图片*/
		createImage(COMMENT_IMAGE, "暂停.png");

	}
	hideImage(6666);
	hideImage(4001);
	hideImage(1120);
	hideImage(1121);
	hideImage(42);
	hideImage(431);
	hideImage(432);
	hideImage(433);
	hideImage(51);
	hideImage(1122);
	hideImage(1123);
	hideImage(52);
	hideImage(53);
	hideImage(COMMENT_IMAGE);
}
