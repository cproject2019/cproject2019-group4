/*
吉林大学唐敖庆理科试验班-C语言

		第四组
凤囚凰-ALL FOR LOVE

成员：
李成午（物理）
王鹤翔（化学）
郝新培（生物）

开发环境：Microsoft Visual Studio 2017 & 如鹏游戏引擎（www.rupeng.com）
*/

#include <stdio.h>
#include <yzkgame.h>
#include "control.h"

#pragma comment( linker, "/subsystem:\"console\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib, "YZKGame.lib")

void gameMain(void);
void game1Main(void);
void game2Main(void);

Item_t it;
enum gamecontrol control = start; //要不换一个
bool hassuccess = false;
bool hasfailed = false;

int main(void)
{
	rpInit(gameMain);
	
	return 0;
}

void gameMain(void)
{
	creatAllImages();
	setGameTitle("All for love");
	setGameSize(900, 550);

	createImage(0, "王后和国王.png");
	setImagePosition(0, 0, 0);

	createText(01, "Group members");
	setTextPosition(01, 550, 220);
	setTextColor(01, 0, 0, 0);
	setTextFontSize(01, 35);

	createText(02, "Li Chengwu");
	setTextPosition(02, 580, 175);
	setTextColor(02, 0, 0, 0.65);
	setTextFontSize(02, 30);

	createText(03, "Hao Xinpei");
	setTextPosition(03, 580, 140);
	setTextColor(03, 0, 0, 0.65);
	setTextFontSize(03, 30);

	createText(04, "Wang Hexiang");
	setTextPosition(04, 580, 105);
	setTextColor(04, 0, 0, 0.65);
	setTextFontSize(04, 30);

	createText(05, "All for love");
	setTextPosition(05, 170, 480);
	setTextColor(05, 0.2, 0, 1);
	setTextFontSize(05, 10);
	pauseGame(800);
	hideText(05);
	pauseGame(800);
	setTextFontSize(05, 20);
	setTextColor(05, 0.4, 0, 1);
	showText(05);
	pauseGame(800);
	hideText(05);
	pauseGame(800);
	setTextFontSize(05, 30);
	setTextColor(05, 0.6, 0, 1);
	showText(05);
	pauseGame(800);
	hideText(05);
	pauseGame(800);
	setTextFontSize(05, 40);
	setTextColor(05, 0.8, 0, 1);
	showText(05);
	pauseGame(800);
	hideText(05);
	pauseGame(800);
	setTextFontSize(05, 45);
	setTextColor(05, 1, 0, 1);
	showText(05);

	createText(49, "Press any key to start the game");
	setTextPosition(49, 300, 25);
	setTextColor(49, 0, 0, 0);
	setTextFontSize(49, 25);

	while (1)
	{
		if (getPressedKeyCode())
		{
			hideText(49);
			break;
		}

	}

	hideText(01);
	hideText(02);
	hideText(03);
	hideText(04);
	hideText(05);
	hideImage(0);

	createImage(01, "情景初1.png");
	setImagePosition(0, 0, 0);
	pauseGame(1000);
	////////////////////////////
	createImage(1111, "鼠标指针.png");
	setImagePosition(1111, 800, 50);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1111) && mouseX < getImageX(1111) + getImageWidth(1111) && mouseY>getImageY(1111) && mouseY < getImageY(1111) + getImageHeight(1111))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1111);
	///////////////////////////////
	hideImage(01);

	createImage(02, "情景初2.png");
	setImagePosition(0, 0, 0);
	pauseGame(1000);
	////////////////////////////
	createImage(1112, "鼠标指针.png");
	setImagePosition(1112, 800, 50);
	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1112) && mouseX < getImageX(1112) + getImageWidth(1112) && mouseY>getImageY(1112) && mouseY < getImageY(1112) + getImageHeight(1112))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1112);
	///////////////////////////////
	hideImage(02);

	createImage(03, "情景初3.png");
	setImagePosition(0, 0, 0);
	createImage(031, "对话001.png");
	setImagePosition(031, 300, 360);
	pauseGame(1000);
	////////////////////////////
	createImage(1113, "鼠标指针.png");
	setImagePosition(1113, 800, 50);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1113) && mouseX < getImageX(1113) + getImageWidth(1113) && mouseY>getImageY(1113) && mouseY < getImageY(1113) + getImageHeight(1113))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1113);
	///////////////////////////////
	hideImage(031);
	pauseGame(10);
	createImage(032, "对话002.png");
	setImagePosition(032, 240, 340);
	pauseGame(1000);
	////////////////////////////
	createImage(1114, "鼠标指针.png");
	setImagePosition(1114, 800, 50);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1114) && mouseX < getImageX(1114) + getImageWidth(1114) && mouseY>getImageY(1114) && mouseY < getImageY(1114) + getImageHeight(1114))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1114);
	///////////////////////////////
	hideImage(032);

	createImage(033, "对话003.png");
	setImagePosition(033, 310, 355);
	pauseGame(1000);
	////////////////////////////
	createImage(1115, "鼠标指针.png");
	setImagePosition(1115, 800, 50);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1115) && mouseX < getImageX(1115) + getImageWidth(1115) && mouseY>getImageY(1115) && mouseY < getImageY(1115) + getImageHeight(1115))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1115);
	///////////////////////////////
	hideImage(033);

	createImage(034, "对话004.png");
	setImagePosition(034, 240, 360);
	pauseGame(1000);
	////////////////////////////
	createImage(1116, "鼠标指针.png");
	setImagePosition(1116, 800, 50);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1116) && mouseX < getImageX(1116) + getImageWidth(1116) && mouseY>getImageY(1116) && mouseY < getImageY(1116) + getImageHeight(1116))
			{
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1116);
	///////////////////////////////
	hideImage(034);
	hideImage(03);

	pauseGame(10);

	createImage(04, "情景初4.png");
	setImagePosition(0, 0, 0);

	/*********************************************************************************************************************************************************/
		////////////////////////////
	createImage(1117, "选王后按钮.png");
	setImagePosition(1117, 248, 220);
	createImage(1118, "选将军按钮.png");
	setImagePosition(1118, 248, 50);
	////////////////////////////

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1117) && mouseX < getImageX(1117) + getImageWidth(1117) && mouseY>getImageY(1117) && mouseY < getImageY(1117) + getImageHeight(1117))
			{
				control = modeOne;
				break;
			}
			else if (mouseX > getImageX(1118) && mouseX < getImageX(1118) + getImageWidth(1118) && mouseY>getImageY(1118) && mouseY < getImageY(1118) + getImageHeight(1118))
			{
				control = modeTwo;
				break;
			}
			else {}
		}
		else {}
	}
	hideImage(1117);
	hideImage(1118);
	///////////////////////////////
	hideImage(04);

	pauseGame(10);

	createImage(05, "情景初5.png");
	setImagePosition(0, 0, 0);
	////////////////////////////
	createImage(1119, "开始游戏按钮.png");
	setImagePosition(1119, 295, 35);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1119) && mouseX < getImageX(1119) + getImageWidth(1119) && mouseY>getImageY(1119) && mouseY < getImageY(1119) + getImageHeight(1119))
			{
				hideImage(1119);
				hideImage(05);
				pauseGame(10);
				chooseGame();
				break;
			}
			else {}
		}
		else {}
	}

	pauseGame(10000);
	getchar();
}

void game1Main(void) //hard
{
	creatAllImages();//记得删掉

	int control_game = 0;
	int control_bullet = 0;
	setGameTitle("All for love");
	setGameSize(900, 550);
	setBgColor(0.2, 0, 1);

	wantMap();
	Initialize();
	jump_shoot();

	while (1)
	{
		
		if (hasfailed || hassuccess)
		{
			break;
		}

		if (control_game++ % SPEED ==0)
		{
			updateTime();
			if (speed++ % TIME == 0)
			{
				playerMove(keyboard());  //获取键盘输入以左右移动，暂停，退出游戏
			}
			if (control_bullet++ % BULLETTIME == 0)
			{
				moveBullet();
			}
			if (GetAsyncKeyState(0xd) & 0x8000)  //回车键暂停
				stop();
			else if (GetAsyncKeyState(80) & 0x8000)  //P 键查询当前排名
			{
				inquire();
			}
			gravity();

			updateEnemyImportantDate();

			check_intersect();
			check_win(1);
		}
	}

	if (GetAsyncKeyState(0xd) & 0x8000)  //回车键暂停
		stop();
	else if (GetAsyncKeyState(80) & 0x8000)  //P 键查询当前排名
	{
		inquire();
	}
	pauseGame(10000);
}

void game2Main(void) //easy
{
	int control_game = 0;
	int control_bullet = 0;
	setGameTitle("All for love");
	setGameSize(900, 550);
	setBgColor(0.2, 0, 1);

	wantMap();
	Initialize();
	jump_shoot();

	while (1)
	{
		updateTime();
		game2();

		if (control_game++ % 300 == 0)
		{
			if (speed++ % (TIME * 10) == 0)
			{
				playerMove(keyboard());  //获取键盘输入以左右移动，暂停，退出游戏
			}
			if (control_bullet++ % (BULLETTIME * 10) == 0)
			{
				moveBullet();
			}

			if (GetAsyncKeyState(0xd) & 0x8000)  //回车键暂停
				stop();
			else if (GetAsyncKeyState(80) & 0x8000)  //P 键查询当前排名
			{
				inquire();
			}

			gravity();

			updateEnemyImportantDate();

			check_intersect();
			check_win(2);
		}
		
		if (GetAsyncKeyState(0xd) & 0x8000)  //回车键暂停
			stop();
		else if (GetAsyncKeyState(80) & 0x8000)  //P 键查询当前排名
		{
			inquire();
		}
	}

	pauseGame(10000);
}

void chooseGame(void)
{
	if (control == modeOne)
	{
		game1Main();
	}
	else if (control == modeTwo)
	{
		game2Main();
	}
	else
		exit(EXIT_FAILURE);
}

void succeed(int which)
{
	hassuccess = true;
	gameEnd = clock();
	EmptyTheList(&list);
	clearAllPicture();

	if (which == 1)
	{
		record();
	}

	setImagePosition(4001, 0, 0);
	showImage(4001);
	////////////////////////////
	setImagePosition(1120, 248, 255);
	setImagePosition(1121, 248, 70);
	showImage(1120);
	showImage(1121);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1120) && mouseX < getImageX(1120) + getImageWidth(1120) && mouseY>getImageY(1120) && mouseY < getImageY(1120) + getImageHeight(1120))
			{
				hideImage(1120);
				hideImage(1121);
				hideImage(4001);
				restartGame();
				break;
			}
			else if (mouseX > getImageX(1121) && mouseX < getImageX(1121) + getImageWidth(1121) && mouseY>getImageY(1121) && mouseY < getImageY(1121) + getImageHeight(1121))
			{
				hideImage(1120);
				hideImage(1121);
				hideImage(4001);

				setImagePosition(42, 0, 0);

				pauseGame(1000);
				hideImage(42);

				showImage(431);
				showImage(432);
				showImage(433);
				setImagePosition(431, 0, 0);
				setImagePosition(432, 500, 135);
				setImagePosition(433, 200, 50);

				pauseGame(2000);
				hideImage(431);
				hideImage(432);
				hideImage(433);

				pauseGame(5000);
				exit(0);

				break;
			}
			else {}
		}
		else {}
		pauseGame(10);
	}
}


void failed(void)
{
	hasfailed = true;
	EmptyTheList(&list);
	clearAllPicture();

	setImagePosition(51, 0, 0);
	showImage(51);
	////////////////////////////
	setImagePosition(1122, 248, 205);
	showImage(1122);
	setImagePosition(1123, 248, 50); showImage(1123);

	while (1)
	{
		pauseGame(10);
		if (isMouseLeftButtonDown())
		{
			int mouseX = getMousePositionX();
			int mouseY = getMousePositionY();
			if (mouseX > getImageX(1122) && mouseX < getImageX(1122) + getImageWidth(1122) && mouseY>getImageY(1122) && mouseY < getImageY(1122) + getImageHeight(1122))
			{
				hideImage(1122);
				hideImage(1123);
				hideImage(51);
				restartGame();
				break;
			}
			else if (mouseX > getImageX(1123) && mouseX < getImageX(1123) + getImageWidth(1123) && mouseY>getImageY(1123) && mouseY < getImageY(1123) + getImageHeight(1123))
			{
				hideImage(1122);
				hideImage(1123);
				hideImage(51);

				pauseGame(10);
				showImage(52);
				setImagePosition(52, 0, 0);
				
				pauseGame(2000);
				
				hideImage(52);
				showImage(53);
				setImagePosition(53, 0, 0);

				pauseGame(5000);
				exit(0);
				break;
			}
		}
		else {}
		pauseGame(10);
	}

}

void clearAllPicture(void)
{
	int i, j;

	for (i = 0; i < enemy_num; i++)
	{
		hideSprite(enemy[i].sprite);
	}

	for (i = 0; i < NUM; i++)
	{
		hideSprite(item[i].sprite);
	}

	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		hideSprite(bullet[i].sprite);
	}

	for (j = 0; j < HIGH; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (canvas[j][i] == WALL)
				hideImage((I_WALL + i + j * 50));
			else if (canvas[j][i] == FLOOR)
				hideImage((I_FLOOR + i + j * 50));
			else if (canvas[j][i] == AIR) {}
			else {}
		}
	}

	hideSprite(player.sprite);
	hideText(TIME_TXT_NUM);
	hideText(TIME_TXT_NUM + 1);
}

void game2(void)
{
	setImagePosition(6666,400,0);
	showImage(6666);

	if (isMouseLeftButtonDown())
	{
		int mouseX = getMousePositionX();
		int mouseY = getMousePositionY();
		if (mouseX > getImageX(6666) && mouseX < getImageX(6666) + getImageWidth(6666) && mouseY>getImageY(6666) && mouseY < getImageY(6666) + getImageHeight(6666))
		{
			hideImage(6666);
			cheat();
		}

	}
}

void cheat(void)
{
	coor address = { 0, 0 };
	Node_t * pTemp;
	int control_speed = 0;

	for (pTemp = list; pTemp != NULL; pTemp = pTemp->next)
	{
		pTemp->enemy.exit = false;
		hideSprite(pTemp->enemy.sprite);
	}
	
	playSpriteAnimate(player.sprite, "RIGHT");
	hideSprite(item[0].sprite);
	while (!((int)(player.x / LENGTH) == item[1].x && player.y == item[1].y))
	{
		if (control_speed++ % (BULLETTIME * 500) == 0)
		{
			A_star_algorithm(map1n, item[1].x, item[1].y, (int)(player.x / LENGTH), player.y, &address);
			player.x = address.x * LENGTH;
			player.y = address.y;
			setSpritePosition(player.sprite, player.x, player.y * LENGTH);
		}
	}

	succeed(0);
}

/*以下为新完善的功能*/

void restartGame(void)// NEED 
{
	int control_game = 0;
	int control_bullet = 0;

	resetGame();
	

	while (1)
	{
		if (control_game++ % SPEED == 0)
		{
			if (speed++ % TIME == 0)
			{
				playerMove(keyboard());  //获取键盘输入以左右移动，暂停，退出游戏
			}
			gravity();

			if (((int)(player.x / LENGTH) == it.x && player.y == it.y))
			{
				break;
			}
		}
	}
	pauseGame(200);
	hideSprite(player.sprite);
	hideSprite(it.sprite);

	createImage(46662, "情景末happy ending.png");
	setImagePosition(46662, 0, 0);

	pauseGame(10000);
}

void resetGame(void)
{
	getCanvas();

	player.x = PLAYER_START_X;
	player.y = PLAYER_START_Y;

	setSpritePosition(player.sprite, player.x, player.y);
	showSprite(player.sprite);
	playSpriteAnimate(player.sprite, "new");

	it.sprite = BOX * 3 + 1;
	it.x = 15;
	it.y = 8;

	createSprite(it.sprite, "box");
	setSpritePosition(it.sprite, LENGTH * it.x, LENGTH * it.y);
	playSpriteAnimate(it.sprite, "new");
}