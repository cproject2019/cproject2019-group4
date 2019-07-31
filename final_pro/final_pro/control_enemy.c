#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void InitializeEnemy(void)
{
	int i;
	//为了简便，现在只设置2个
	enemy[0].x = (rand() % (8 - 3 + 1) + 3); enemy[0].y = 5;
	enemy[1].x = 8; enemy[1].y = 8;
	
	for (i = 0; i < enemy_num; i++)
	//for (i = 1; i < enemy_num; i++)//演示专用代码
	{
		enemy[i].sprite = Enemy(i);
		enemy[i].number = i;
		enemy[i].mode = 0;
		enemy[i].life = ( rand() % ( ENEMY_LIFE - 1 + 1) + 1 ); //
		enemy[i].exit = true;

		createSprite(enemy[i].sprite, "enemy");
		setSpritePosition(enemy[i].sprite, LENGTH * enemy[i].x, LENGTH * enemy[i].y);
		playSpriteAnimate(enemy[i].sprite, "new");
	}
	/* 展示用代码
	i = 0;
	enemy[i].sprite = Enemy(i);
	enemy[i].number = i;
	enemy[i].mode = 0;
	enemy[i].life = (rand() % (ENEMY_LIFE - 1 + 1) + 1); //
	enemy[i].exit = true;

	createSprite(enemy[i].sprite, "enemy");

	i = 1;
	enemy[i].sprite = Enemy(i);
	enemy[i].number = i;
	enemy[i].mode = 0;
	enemy[i].life = (rand() % (ENEMY_LIFE - 1 + 1) + 1); //
	enemy[i].exit = true;

	createSprite(enemy[i].sprite, "enemy");
	setSpritePosition(enemy[i].sprite, LENGTH * enemy[i].x, LENGTH * enemy[i].y);
	playSpriteAnimate(enemy[i].sprite, "new");
	*/
}

void setEnemyList(void)
{
	int i;

	for (i = 0; i < enemy_num; i++)
	{
		if (ListIsFull(&list))
		{
			fprintf(stderr, "the list is full, can't add enemy");
			exit(EXIT_FAILURE);
		}

		if (AddEnemy(enemy[i], &list) == false)
		{
			fprintf(stderr, "can't add enemy");
			exit(EXIT_FAILURE);
		}
	}
}

void seletEnemy(void) //算出来距离player最近的enemy是哪一个 0 - enemy_num
{
	int i;
	int a[ENEMY_NUM];
	int max;
	int oo;
	Node_t * pTemp;

	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.exit == false)
		{
			a[pTemp->enemy.number] = 999;
			continue;
		}
		a[pTemp->enemy.number] = (int)hypot((double)(pTemp->enemy.x - player.x), (double)(pTemp->enemy.y - player.y)); //C99 /*	a = delet x^2 + delet y^2	*/		
	}

	oo = a[0];

	for (i = 0; i < ListItemCount(&list); i++)
	{
		if (a[i] >= oo)
		{
			oo = a[i];
			max = i;
		}
	}

	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.number == max)
		{
			pTemp->enemy.mode = 1;
		}
	}

}

void moveEnemy(void) //mode = 1的链表里的项
{
	Node_t * pTemp;
	coor address = { 0, 0 };

	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.exit == false)
		{
			continue;
		}

		if (pTemp->enemy.mode == 1)
		{//player.x % 50
			A_star_algorithm(map1n, (int)(player.x / LENGTH), player.y, pTemp->enemy.x, pTemp->enemy.y, &address);
			pTemp->enemy.x = address.x;
			pTemp->enemy.y = address.y;
			setSpritePosition(pTemp->enemy.sprite, LENGTH * pTemp->enemy.x, LENGTH * pTemp->enemy.y);
			pTemp->enemy.mode = 0;
		}

		if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
			stop();
		else if (GetAsyncKeyState(80) & 0x8000)  //P 键
		{
			inquire();
		}
	}
}

void updateEnemyImportantDate(void)
{
	int sprite_num;
	int countTime = 0;
	Node_t * pTemp;

	Traverse(&list, copy_ToList);

	if ((rand() % (500 - 3 + 1) + 3) == 100) //随机3-500之间的数字，是100的概率
	{
		Traverse(&list, restore);
	}

	if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
		stop();
	else if (GetAsyncKeyState(0xd) & 0x8000)  //P 键
	{
		//inquire();
	}

	while ((sprite_num = FindOldEnemy(&list)))
	{
		hideSprite(sprite_num);

		for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
		{
			if (pTemp->enemy.sprite == sprite_num)
			{
				pTemp->enemy.exit = false;
			}
		}

		if (!(DeleteEnemy(&list, sprite_num)))
		{
			fprintf(stderr, "can't delet enemy");
			exit(EXIT_FAILURE);
		}

		if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
			stop();
		else if (GetAsyncKeyState(80) & 0x8000)  //P 键
		{
			inquire();
		}
	}
	if (countTime++ % TIME * TIME == 0)
	{
		if ((rand() % (55555555 - 3 + 1) + 3) == 100)
		{
			seletEnemy();
			if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
				stop();
			else if (GetAsyncKeyState(80) & 0x8000)  //P 键
			{
				inquire();
			}
		}
		if ((rand() % (999999 - 3 + 1) + 3) == 443)
		{
			moveEnemy();
			if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
				stop();
			else if (GetAsyncKeyState(80) & 0x8000)  //P 键
			{
				inquire();
			}
		}

		if (GetAsyncKeyState(0xd) & 0x8000)  //回车键
			stop();
		else if (GetAsyncKeyState(80) & 0x8000)  //P 键
		{
			inquire();
		}
	}

	Traverse(&list, copy_ToArray);
}

void restore(Enemy_t enemyList)
{
	enemyList.life = enemy[enemyList.number].life + (rand() % (2 - 0 + 1));
}

void copy_ToList(Enemy_t enemyList)
{
	int i;
	for (i = 0; i < enemy_num; i++)
	{
		if (i == enemyList.number)
		{
			enemyList.exit = enemy[enemyList.number].exit;
			enemyList.x = enemy[enemyList.number].x;
			enemyList.y = enemy[enemyList.number].y;
			enemyList.life = enemy[enemyList.number].life;
			enemyList.mode = enemy[enemyList.number].mode;
			enemyList.sprite = enemy[enemyList.number].sprite;
		}
	}
}

void copy_ToArray(Enemy_t enemyList)
{
	enemy[enemyList.number].exit = enemyList.exit;
	enemy[enemyList.number].x = enemyList.x;
	enemy[enemyList.number].y = enemyList.y;
	enemy[enemyList.number].life = enemyList.life;
	enemy[enemyList.number].mode = enemyList.mode;
	enemy[enemyList.number].sprite = enemyList.sprite;
}

/***************使用A*算法*****************/
void A_star_algorithm(int mapn[][18], int startpoint_x, int startpoint_y, int endpoint_x, int endpoint_y, coor* Coor_next_step)
{

	if (startpoint_y < 5)
	{
		startpoint_y = 2;
	}
	else if (startpoint_y >= 5 && startpoint_y < 8)
	{
		startpoint_y = 5;
	}
	else
	{
		startpoint_y = 8;
	}

	if (!(startpoint_x + 266 * startpoint_y - endpoint_x - 266 * endpoint_y)) // startPoint = endPoint
	{
		failed();
	}

	Coor_next_step->x = Coor_next_step->y = 0;
	pnode** mapp = translate_Map(mapn, row, col);//将地图转换为二维数组
	//output(mapp, 11, 18);

	pnode* startpnode = find_start_pnode(mapp, row, col, startpoint_x, startpoint_y);
	pnode* endpnode = find_end_pnode(mapp, row, col, endpoint_x, endpoint_y);
	pnode* curpnode = startpnode;
	curpnode->G = 0;
	count_Pnode_H(curpnode, endpnode);
	count_Pnode_F(curpnode);
	linklist openlist = (linklist)malloc(sizeof(pnode));
	memset(openlist, 0, sizeof(pnode));
	linklist closelist = (linklist)malloc(sizeof(pnode));
	memset(closelist, 0, sizeof(pnode));
	insert_openlist_by_asc(openlist, curpnode);

	while (curpnode->is_Endpoint_Here == FALSE)
	{
		curpnode = return_openlist_min_pnode(openlist);
		insert_into_closelist(curpnode, closelist);
		check_around_curpnode(curpnode, endpnode, openlist, mapp);

	}
/*	if (endpnode->path_next != NULL) 
	{
		Coor_next_step->x = (*(endpnode->path_next)).x;

		Coor_next_step->y = (*(endpnode->path_next)).y;
	}*/
	Coor_next_step->x = (*(endpnode->path_next)).x;
	Coor_next_step->y = (*(endpnode->path_next)).y;

	for (int l = 0; l < row; ++l)
	{
		free(mapp[l]);
	}

	free(mapp);

	/*while (endpnode->path_next != NULL)
	{
		printf("x:%d---y:%d\n", endpnode->path_next->x, endpnode->path_next->y);
		endpnode->path_next = endpnode->path_next->path_next;
	}*/
}