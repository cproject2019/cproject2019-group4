#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void InitializeBullet(void)
{
	int i;

	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		bullet[i].exist = false;
		bullet[i].sprite = BULLET + 26 * i + 1;
		createSprite(bullet[i].sprite, "bullet");
	}
}

void shoot(void * p)
{
	switch (position)
	{
	case LEFT:
		bullet[bul_num].direction = LEFT;
		bullet[bul_num].x = (int)(player.x / LENGTH) - 1;
		bullet[bul_num].y = player.y;
		break;
	case DOWN:
	case RIGHT:
	default:
		bullet[bul_num].direction = RIGHT;
		bullet[bul_num].x = (int)(player.x / LENGTH) + 1;
		bullet[bul_num].y = player.y;
		break;
	}

	bullet[bul_num].new = true;
	bullet[bul_num].exist = true;
	
	bul_num++;
	if (bul_num == BULLET_MAX_NUM)
	{
		bul_num = 0;
	}
}

void drawBullet(int num)
{
	showSprite(bullet[num].sprite);
	setSpritePosition(bullet[num].sprite, LENGTH * bullet[num].x, LENGTH * bullet[num].y);
	playSpriteAnimate(bullet[num].sprite, "NEW");
}

void moveBullet(void)
{
	int i;
	int mode;

	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullet[i].exist == true)
		{
			if (bullet[i].new == false)
			{
				if ((bullet[i].direction == LEFT && bullet[i].x > 0) || (bullet[i].direction == RIGHT && bullet[i].x < WIDTH))
				{
					switch (bullet[i].direction)
					{
					case LEFT:
						bullet[i].x--;
						break;
					case RIGHT:
						bullet[i].x++;
						break;
					}
				}
			}
			else
			{
				bullet[i].new = false;
			}

			if (!(mode = checkBulletHit(i)))
			{
				drawBullet(i);
			}
			else
			{
				bullet[i].exist = false;
				hideSprite(bullet[i].sprite);
				BulletHit(i, mode);
			}
		}
	}
}

void BulletHit(int num, int mode)
{

	if (mode != 0 && mode != BULLET_MAP)
	{
		Node_t * pTemp;

		num = mode - 20 * BULLET_ENEMY;

		for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)/*enemy[num].life--;*/
		{
			if (pTemp->enemy.number == num)
			{
				pTemp->enemy.life--;
			}
		}
	}
}

int checkBulletHit(int num) //¼ì²é×Óµ¯Åö×²,ÅöÉÏtrue
{
	Node_t * pTemp;

	if (canvas[bullet[num].y][bullet[num].x] == WALL || canvas[bullet[num].y][bullet[num].x] == FLOOR)
	{
		return BULLET_MAP;
	}

	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.exit == false)
		{
			continue;
		}

		if (bullet[num].x == pTemp->enemy.x && bullet[num].y == pTemp->enemy.y)
		{
			return (20 * BULLET_ENEMY + (pTemp->enemy.number));
		}
	}
	return 0;
}