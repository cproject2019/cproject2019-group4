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
Info_t thisGrade = { .game_time = 0,"" };
Info_t bestGrade = { .game_time = 0,"" };

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

clock_t gameStart, gameEnd, Ntime;
clock_t stopTime = (clock_t)0;
clock_t stopStart, stopEnd;

FILE * fGrade;

void Initialize(void)// after wantMap()
{
	char timeAddress[2] = {0, '\0'};

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
		/*以下之前不能实现*/
		hideImage(COMMENT_IMAGE);
		hideImage(INQUIRE_IMAGE);

		createText(TIME_TXT_NUM, timeAddress);
		setTextPosition(TIME_TXT_NUM, 300, 450);
		createText(TIME_TXT_NUM + 1, "时间：");
		setTextPosition(TIME_TXT_NUM + 1, 250, 450);
	}

	gameStart = clock();
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

void check_win(int which)
{
	update_game();

	if (gameover == true && gamewin == false)
	{
		failed();
	}
	else if (gamewin == true)
	{
		succeed(which);
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
		
		/*inquire*/
		createImage(INQUIRE_IMAGE, "查询.png");
		createText(INQ + 1, "");
		createText(INQ + 2, "");
		createText(INQ + 3, "");
		createText(INQ + 4, "");
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
	hideImage(INQUIRE_IMAGE);
	//inquire
	hideText(INQ + 1);
	hideText(INQ + 2);
	hideText(INQ + 3);
	hideText(INQ + 4);
}

/*新增的计时系统*/
void updateTime(void)
{
	char str_double[30];
	double runningTime;

	Ntime = clock();
	runningTime = (double)(Ntime - gameStart - stopTime) / CLK_TCK;

	gcvt(runningTime, 8, str_double);
	setText(TIME_TXT_NUM, str_double);
}

void record(void)
{
	clock_t totalGameTime;
	time_t curtime;
	char str_double[30];
	double grade;

	totalGameTime = gameEnd - gameStart - stopTime;
	grade = (double)totalGameTime / CLK_TCK;
	gcvt(grade, 8, str_double);
	time(&curtime);

	thisGrade.game_time = grade;
	strcpy(thisGrade.date, ctime(&curtime));
	updateBestGrade();

	createText(233, "您当前的成绩是：");
	setTextPosition(233, 245, 300);
	setTextColor(233, 255, 255, 255);
	setTextFontSize(233, 25);

	createText(888, str_double);
	setTextPosition(888, 450, 300);
	setTextColor(888, 255, 255, 255);
	setTextFontSize(888, 25);

	createText(666, ctime(&curtime));
	setTextPosition(666, 450, 250);
	setTextColor(666, 255, 255, 255);
	setTextFontSize(666, 25);

	gcvt(bestGrade.game_time, 8, str_double);

	showText(INQ + 1);
	setText(INQ + 1, "您的最好成绩是：");
	setTextPosition(INQ + 1, 245, 200);
	setTextColor(INQ + 1, 255, 255, 255);
	setTextFontSize(INQ + 1, 25);

	showText(INQ + 2);
	setText(INQ + 2, str_double);
	setTextPosition(INQ + 2, 450, 200);
	setTextColor(INQ + 2, 255, 255, 255);
	setTextFontSize(INQ + 2, 25);

	pauseGame(10000);

	hideText(233);
	hideText(888);
	hideText(666);
	hideText(INQ + 1);
	hideText(INQ + 2);
}

void updateBestGrade(void)
{
	if ((fGrade = fopen("grade.txt", "r")) == NULL)
	{
		fprintf(stderr, "reverse can't open grade file");
		exit(EXIT_FAILURE);
	}

	if (fscanf(fGrade, "%lf", &bestGrade.game_time) ){}
	else 
	{
		bestGrade.game_time = -1;
	}
	fclose(fGrade);

	if (bestGrade.game_time > thisGrade.game_time)
	{
		if ((fGrade = fopen("grade.txt", "w")) == NULL)
		{
			fprintf(stderr, "reverse can't open grade file");
			exit(EXIT_FAILURE);
		}

		fprintf(fGrade, "%f %s", thisGrade.game_time, thisGrade.date);
		fclose(fGrade);
	}
}

/*以下是未完成部分*/
/*
void readGradeDate(void)
{
	char chd, string[30];
	int i = 0;
	if ((fGrade = fopen("grade.txt", "r")) == NULL)
	{
		fprintf(stderr, "reverse can't open grade file");
		exit(EXIT_FAILURE);
	}
	while ((chd = getc(fGrade)) != " ") {}

	while ((chd = getc(fGrade)) != EOF) 
	{
		string[i] = chd;
		i++;
	}
	string[i] = '\0';

	strcpy(bestGrade.date, string);
}*/
/*void inquire(void)
{
	char str_double[30];

	stopStart = clock();
	hideText(TIME_TXT_NUM);
	hideText(TIME_TXT_NUM + 1);

	showImage(INQUIRE_IMAGE);
	setImagePosition(INQUIRE_IMAGE, 0, 0);

	if ((fGrade = fopen("grade.txt", "r")) == NULL)
	{
		fprintf(stderr, "reverse can't open grade file");
		exit(EXIT_FAILURE);
	}

	readGradeDate();
	if (fscanf(fGrade, "%lf", &bestGrade.game_time))
	{
		gcvt(bestGrade.game_time, 8, str_double);

		showText(INQ + 1);
		setText(INQ + 1, "您的最好成绩是：");
		setTextPosition(INQ + 1, 245, 300);
		setTextColor(INQ + 1, 255, 255, 255);
		setTextFontSize(INQ + 1, 25);

		showText(INQ + 2);
		setText(INQ + 2, str_double);
		setTextPosition(INQ + 2, 450, 300);
		setTextColor(INQ + 2, 255, 255, 255);
		setTextFontSize(INQ + 2, 25);

		showText(INQ + 3);
		setText(INQ + 3, bestGrade.date);
		setTextPosition(INQ + 3, 450, 250);
		setTextColor(INQ + 3, 255, 255, 255);
		setTextFontSize(INQ + 3, 25);
	}
	else
	{
		showText(INQ + 4);
		setText(INQ + 4, "您还没有成绩");
		setTextPosition(INQ + 4, 245, 300);
		setTextColor(INQ + 4, 255, 255, 255);
		setTextFontSize(INQ + 4, 25);
	}

	fclose(fGrade);

	while (true)
	{
		if (GetAsyncKeyState(80) & 0x8000)
		{
			hideText(INQ + 1);
			hideText(INQ + 2);
			hideText(INQ + 3);
			hideText(INQ + 4);
			hideImage(INQUIRE_IMAGE);
			break;
		}
		else if (GetAsyncKeyState(0xd) & 0x8000)
		{
			stop();
		}
		else if (GetAsyncKeyState(0x1B) & 0x8000) //Esc键退出
		{
			EmptyTheList(&list);
			exit(0);
		}
	}

	showText(TIME_TXT_NUM);
	showText(TIME_TXT_NUM + 1);

	stopEnd = clock();
	stopTime = stopTime + stopEnd - stopStart;
}*/
void inquire(void)
{

}