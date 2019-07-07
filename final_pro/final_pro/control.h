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

/*ͼƬ���ͼ����*/
#define WIDTH 18 //x����ͼƬ����
#define HIGH 11 //y����ͼƬ����
#define LENGTH 50 //������ͼƬ�ı߳�
#define COMMENT_IMAGE 12345 //����ͼƬ�ǵ�Ҫ����ͼһ����

/*��ͼ�������*/
#define WALL 5 //�߽�
#define FLOOR 9 //���µ�����
#define AIR 0  //ʲô��û�е�λ��
#define I_WALL 70000 //ͼƬ���
#define I_FLOOR 80000 //ͼƬ���
#define I_AIR 90000 //ͼƬ���

/************************������Ʊ����볣��*********************/
#define H 4 //���ĸ߶�
#define TIME 1100

/********************����ͼ�Σ�sprites������********************/

/*sprites_�ƶ���_PLAYER{0}*/
#define PLAYER 0
#define PLAYER_START_X (1 * LENGTH)
#define PLAYER_START_Y 2

/*BULLET*/
#define BULLET 123456 //SPRITE
#define BULLET_MAX_NUM 20
#define BULLET_ENEMY 2
#define BULLET_MAP 1

#define BULLETTIME 45000


/*enemy������*/
#define ENEMY_MAX 10 //warning!:���棡�������ֵ�������޸ģ���Ϊ������ʹ����10������֣������ٸ����������Ҳû��ʲô��
#define ENEMY_NUM 2 //����ĵ�������

/*sprites_�ƶ���_ENEMY{100-109}{ 0 < n < 9 }*/
#define Enemy(n) (100+(n))//����#define Enemy(n) 10 ## n

#define ENEMY_LIFE 3

/*sprites_�̶���{200+}*/
#define NUM 2
#define YELLOWKEY 200
#define BOX 201

/*�������*/
#define UP 1 //�ϣ�
#define DOWN 2 //�£�
#define LEFT 3 //��
#define RIGHT 4 //��
#define JUMP 5 //��Ծ

/****************************ȫ�ֵĽṹ��*************************/

/*���*/
typedef struct player
{
	int sprite;
	int x, y;//����
	bool yKey;//yellow key
	bool box;
}Player_t;

/*����*/
typedef struct item
{
	int sprite;
	int x;
	int y;
}Item_t;
/*���˽ṹ��������ͷ�ļ�*/

typedef struct bullet {
	int sprite;
	int x, y;
	int direction;
	bool exist;
	bool new;
}Bullet_t;

enum gamecontrol { start, modeOne, modeTwo };

/***************����ȫ�ֱ������ܹ������е��ļ�ʹ��***************/
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


/***********************��������ԭ��****************************/
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
void wantMap(void);//���ֻ���������
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

/***************ʹ��A*�㷨*****************/
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

//ʹ�÷�����playerMove(keyboard());  ���ã������ƶ�
void playerMove(int direction);
void Xmove(int direction);
void Ymove(void * p);

#endif // !CONTROL_H_