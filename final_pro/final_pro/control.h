#ifndef CONTROL_H_
#define CONTROL_H_

#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include "list.h"
#include "Apath.h"

#define SPEED 567

/*图片与地图参数*/
#define WIDTH 18 //x方向图片数量
#define HIGH 11 //y方向图片数量
#define LENGTH 50 //正方形图片的边长
#define COMMENT_IMAGE 12345 //这张图片记得要跟地图一样大

/*地图数组编码*/
#define WALL 5 //边界
#define FLOOR 9 //脚下的土地
#define AIR 0  //什么都没有的位置
#define I_WALL 70000 //图片编号
#define I_FLOOR 80000 //图片编号
#define I_AIR 90000 //图片编号

/************************人物控制编码与常数*********************/
#define H 4 //跳的高度
#define TIME 1100

/********************精灵图形（sprites）常数********************/

/*sprites_移动物_PLAYER{0}*/
#define PLAYER 0
#define PLAYER_START_X (1 * LENGTH)
#define PLAYER_START_Y 2

/*BULLET*/
#define BULLET 123456 //SPRITE
#define BULLET_MAX_NUM 20
#define BULLET_ENEMY 2
#define BULLET_MAP 1

#define BULLETTIME 45000


/*enemy的数量*/
#define ENEMY_MAX 10 //warning!:警告！：这个数值不能再修改，因为代码中使用了10这个数字，并且再更改这个常数也没有什么用
#define ENEMY_NUM 2 //允许的敌人数量

/*sprites_移动物_ENEMY{100-109}{ 0 < n < 9 }*/
#define Enemy(n) (100+(n))//或者#define Enemy(n) 10 ## n

#define ENEMY_LIFE 3

/*sprites_固定物{200+}*/
#define NUM 2
#define YELLOWKEY 200
#define BOX 201

/*方向编码*/
#define UP 1 //上？
#define DOWN 2 //下？
#define LEFT 3 //左
#define RIGHT 4 //右
#define JUMP 5 //跳跃

/****************************全局的结构体*************************/

/*玩家*/
typedef struct player
{
	int sprite;
	int x, y;//坐标
	bool yKey;//yellow key
	bool box;
}Player_t;

/*道具*/
typedef struct item
{
	int sprite;
	int x;
	int y;
}Item_t;
/*敌人结构体在链表头文件*/

typedef struct bullet {
	int sprite;
	int x, y;
	int direction;
	bool exist;
	bool new;
}Bullet_t;

enum gamecontrol { start, modeOne, modeTwo };

/***************声明全局变量，能够在所有的文件使用***************/
extern enum gamecontrol control;
extern bool gameover;
extern bool gamewin;
extern int enemy_num;
extern int position;
extern bool doing_jump;
extern int bul_num;
extern int speed;

extern FILE *fCanvas;
extern int canvas[HIGH][WIDTH];

extern Player_t player;
extern Item_t item[NUM];
extern Enemy_t enemy[ENEMY_MAX];
extern Bullet_t bullet[BULLET_MAX_NUM];
extern List_t list;


/***********************声明函数原型****************************/
/*MAIN.C*/
void chooseGame(void);
void succeed(void);
void failed(void);
void clearAllPicture(void);
void game2(void);
void cheat(void);
void restartGame(void);
void resetGame(void);

/*CONTROL.C*/
void Initialize(void);
bool check_intersect(void);
void gravity(void);
void check_win(void);
void update_game(void);
bool check_x_location(int direction);
bool check_y_location_up(int input);
bool check_y_location_down(int input);
bool checkLocation(void);

/*CONTROL_MAP.C*/
void wantMap(void);//最后只用这个就行
void loadCanvas(void);
void getCanvas(void);
void drawCanvas(int input, int y, int x);
void InitializeItem(void);
void createCanvasImage(void);

/*CONTROL_ENEMY.C*/
void InitializeEnemy(void);
void setEnemyList(void);
void seletEnemy(void);
void moveEnemy(void);
void updateEnemyImportantDate(void);
void restore(Enemy_t enemyList);
void copy_ToArray(Enemy_t enemyList);
void copy_ToList(Enemy_t enemyList);

/***************使用A*算法*****************/
void A_star_algorithm(int mapn[][18], int startpoint_x, int startpoint_y, int endpoint_x, int endpoint_y, coor* Coor_next_step);

/*CONTROL_BULLET.C*/
void InitializeBullet(void);
int checkBulletHit(int num);
void BulletHit(int num, int mode);
void moveBullet(void);
void drawBullet(int num);
void shoot(void * p);

/*CONTROL_PLAYER.C*/
int keyboard(void);
void jump_shoot(void);
void wantnJump_Shoot(unsigned char key);
void wantsJump(int key);
void stop(void);

//使用方法：playerMove(keyboard());  作用：左右移动
void playerMove(int direction);
void Xmove(int direction);
void Ymove(void * p);

#endif // !CONTROL_H_