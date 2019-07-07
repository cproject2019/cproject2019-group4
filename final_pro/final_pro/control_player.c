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

	if (key == 119 || key == 106)//��Ծ�ĺ������������ w �� j ����ִ��һ����Ծ�� 
	{
		asyncRun(Ymove, (void *)0);
	}
	else if (key == 107)//k ���
	{
		asyncRun(shoot, (void*)0);
	}
}

void wantsJump(int key) //��Ծ�ĺ����� �������С���̡�������ִ��һ����Ծ�� s means special
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

	while (1)      //�س���
	{
		if (GetAsyncKeyState(0xD) & 0x8000)
		{
			hideImage(COMMENT_IMAGE);
			break;
		}
		else if (GetAsyncKeyState(0x1B) & 0x8000) //Esc���˳�
		{
			EmptyTheList(&list);
			exit(0);
		}
	}
}

int keyboard(void)
{
	int re = 0; //Ϊ��return re;

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState(0x41) & 0x8000)) //��
	{
		position = LEFT;
		re = LEFT;
	}
	else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) || (GetAsyncKeyState(0x44) & 0x8000)) //��
	{
		position = RIGHT;
		re = RIGHT;
	}
	else if (GetAsyncKeyState(0x1B) & 0x8000)  // Esc���˳�������
	{
		EmptyTheList(&list);
		exit(0);
	}
	else if (GetAsyncKeyState(0xd) & 0x8000)  //�س�����ͣ
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

void Xmove(int direction) //directionΪLEFT��RIGHT
{
	if (check_x_location(direction)) //����Ƿ�����ƶ�
	{
		if (direction == LEFT)
		{
			player.x--;
			playSpriteAnimate(player.sprite, "LEFT");
			setSpritePosition(player.sprite, player.x, LENGTH * player.y); //�������50Ҳû��ϵ
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