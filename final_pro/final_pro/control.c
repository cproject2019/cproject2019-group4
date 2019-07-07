#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

/***�������***/

/*ָ��һ������*/
List_t list;

//�ṹ�����
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

//ȫ�ֱ���

bool gameover = false;
bool gamewin = false;
int position = DOWN;
int enemy_num = ENEMY_NUM; //��ʱ������ʼ����������֮��ĳ����и���
bool doing_jump = false;
int speed = 10;
int bul_num = 0;

void Initialize(void)// after wantMap()
{
	srand((unsigned int)time(NULL)); //Ϊ�����������

	InitializeBullet();
	InitializeEnemy();

	/*enemy�����һϵ�г�ʼ�������յõ�һ��װ�����ݵ�enemy����*/
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
	/*���²���ʵ��*/
	createImage(COMMENT_IMAGE, "��ͣ.png");
	hideImage(COMMENT_IMAGE);
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

bool check_intersect(void) //��ʲô��������֮���retuen true
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

bool check_x_location(int direction)//��鳯��ķ������Ƿ����ϰ���û���򷵻�true��directionΪLEFT��RIGHT
{
	if (direction == LEFT)
	{
		if (canvas[player.y][((int)((player.x - 50) / LENGTH))] == AIR || (player.x > 65 && player.x < 110) ) //�����Ҫ��ʼ�ĳ����ز��ɽ���Ļ���ȥ��||���������
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
	if (canvas[(player.y + 1)][((int)(player.x / LENGTH))] == AIR) //�Ҳ�֪����������
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

bool checkLocation(void)//�����ж�����return true;
{
	if (canvas[(player.y - 1)][(int)(player.x / LENGTH)] == FLOOR)
		return true;
	else
		return false;
}
