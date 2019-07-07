#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void jump_shoot(void)
{
	onNormalKeyUp(wantnJump_Shoot);
	onSpecialKeyUp(wantsJump);
}

void wantnJump_Shoot(unsigned char key)//n means normal
{

	if (key == 119 || key == 106)//跳跃的函数，如果按下 w 或 j ，就执行一次跳跃。 
	{
		asyncRun(Ymove, (void *)0);
	}
	else if (key == 107)//k 射击
	{
		asyncRun(shoot, (void*)0);
	}
}

void wantsJump(int key) //跳跃的函数， 如果按下小键盘↑键，就执行一次跳跃。 s means special
{
	if (key == RP_KEY_UP)
	{
		asyncRun(Ymove, (void*)0);
	}
}

void stop(void)
{
	showImage(COMMENT_IMAGE);
	setImagePosition(COMMENT_IMAGE, 0, 0);

	while (1)      //回车键
	{
		if (GetAsyncKeyState(0xD) & 0x8000)
		{
			hideImage(COMMENT_IMAGE);
			break;
		}
		else if (GetAsyncKeyState(0x1B) & 0x8000) //Esc键退出
		{
			EmptyTheList(&list);
			exit(0);
		}
	}
}

int keyboard(void)
{
	int re = 0; //为了return re;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState(0x41) & 0x8000)) //左
	{
		position = LEFT;
		re = LEFT;
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState(0x44) & 0x8000)) //右
	{
		position = RIGHT;
		re = RIGHT;
	}
	else if (GetAsyncKeyState(0x1B) & 0x8000)  // Esc键退出程序函数
	{
		EmptyTheList(&list);
		exit(0);
	}
	else if (GetAsyncKeyState(0xd) & 0x8000)  //回车键暂停
		stop();

	return re;
}

void playerMove(int direction)
{
	switch (direction)
	{
	case LEFT:
	case RIGHT:
		Xmove(direction);
		break;

	case JUMP:
	case DOWN:
	case 0:
		break;
	default:
		exit(EXIT_FAILURE);
		break;
	}
}

void Xmove(int direction) //direction为LEFT或RIGHT
{
	if (check_x_location(direction)) //检查是否可以移动
	{
		if (direction == LEFT)
		{
			player.x--;
			playSpriteAnimate(player.sprite, "LEFT");
			setSpritePosition(player.sprite, player.x, LENGTH * player.y); //这个不乘50也没关系
			playSpriteAnimate(player.sprite, "LEFT");
		}
		else
		{
			player.x++;
			playSpriteAnimate(player.sprite, "RIGHT");
			setSpritePosition(player.sprite, player.x, LENGTH * player.y);
			playSpriteAnimate(player.sprite, "RIGHT");
		}
	}
}

void Ymove(void * p)
{
	int i;

	doing_jump = true;

	switch (position)
	{
	case LEFT:
		playSpriteAnimate(player.sprite, "JUMP_L_START");
		break;
	case DOWN:
	case RIGHT:
	default:
		playSpriteAnimate(player.sprite, "JUMP_R_START");
		break;
	}

	for (i = 0; i < H; i++)
	{
		if (check_y_location_up(JUMP))
		{
			player.y++;
			playSpriteAnimate(player.sprite, "JUMP");
			pauseGame(100);
			setSpritePosition(player.sprite, player.x, LENGTH * player.y);
			playSpriteAnimate(player.sprite, "JUMP");
			pauseGame(100);
		}
		else
			break;
	}

	pauseGame(100);

	for (i = 0; i < H; i++)
	{
		if (check_y_location_down(JUMP))
		{
			player.y--;
			playSpriteAnimate(player.sprite, "JUMP");
			pauseGame(100);
			setSpritePosition(player.sprite, player.x, LENGTH * player.y);
			playSpriteAnimate(player.sprite, "JUMP");
			pauseGame(100);
		}
		else
			break;
	}

	pauseGame(10);
	playSpriteAnimate(player.sprite, "NEW");
	doing_jump = false;

}