#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

FILE *fCanvas;
int canvas[HIGH][WIDTH];
int createCanvasImageOnce = false;

void loadCanvas(void)
{
	char ch[2] = { '\0','\0' };//为了获取一个0-9的数字的一个方法
	int y = 0, x = 0;

	if ((fCanvas = fopen("map.txt", "r+")) == NULL)
	{
		fprintf(stderr, "reverse can't open map");
		exit(EXIT_FAILURE);
	}

	for ( ; ; )
	{

		ch[0] = getc(fCanvas);
		if (ch[0] == '\n')
		{
			y++;
			x = 0;
			continue;
		}

		if (ch[0] != EOF && ch[0] != '\r')
		{
			canvas[y][x] = atoi(ch);
			x++;
		}

		if (ch[0] == EOF)
			break;
		/*if (y = 10 && x = 18) break;*/
	}
	fclose(fCanvas);
}

void getCanvas(void)
{
	int x, y;
	for (y = 0; y < HIGH; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			switch (canvas[y][x])
			{
			case AIR:
				drawCanvas(AIR, y, x);
				break;
			case WALL:
				drawCanvas(WALL, y, x);
				break;
			case FLOOR:
				drawCanvas(FLOOR, y, x);
				break;
			default:
				exit(EXIT_FAILURE);
				break;
			}
		}
	}
}

void drawCanvas(int input, int y, int x)
{
	switch (input)
	{
	case WALL:
		showImage((I_WALL + x + y * 50));
		setImagePosition((I_WALL + x + y * 50), LENGTH * x, LENGTH * y);//所有的HIGH - y均有问题
		break;
	case AIR:
		break;
	case FLOOR:
		showImage((I_FLOOR + x + y * 50));
		setImagePosition((I_FLOOR + x + y * 50), LENGTH * x, LENGTH * y);
		break;
	default:
		break;
	}
}

void wantMap(void)
{
	loadCanvas();
	createCanvasImage();
	getCanvas();

	InitializeItem();
}

void InitializeItem(void)
{
	item[0].sprite = YELLOWKEY;
	item[0].x = 16;
	item[0].y = 5;

	createSprite(item[0].sprite, "yellowkey");
	setSpritePosition(item[0].sprite, LENGTH * item[0].x, LENGTH * item[0].y);
	playSpriteAnimate(item[0].sprite, "new");

	item[1].sprite = BOX;
	item[1].x = 15;
	item[1].y = 8;

	createSprite(item[1].sprite, "box");
	setSpritePosition(item[1].sprite, LENGTH * item[1].x, LENGTH * item[1].y);
	playSpriteAnimate(item[1].sprite, "new");
}

void createCanvasImage(void)
{
	if (!createCanvasImageOnce)
	{
		createCanvasImageOnce = true;

		int i, j;

		for (j = 0; j < HIGH; j++)
		{
			for (i = 0; i < WIDTH; i++)
			{
				if (canvas[j][i] == WALL)
					createImage((I_WALL + i + j * 50), "wall.png");
				else if (canvas[j][i] == FLOOR)
					createImage((I_FLOOR + i + j * 50), "floor.png");
				else if (canvas[j][i] == AIR) {}
				else {}
			}
		}
	}
}
