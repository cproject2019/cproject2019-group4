#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef AHEAD_H
#define AHEAD_H


#define MAP_MAX_X 18   //��ͼ�߽磬��ά�����С
#define MAP_MAX_Y 11
#define MOVEABLE_AIR_SQUARE 3 //���˿��ƶ��ķ���
#define OBSTACLE 7 //�ϰ����벻���ƶ����񣺱߽磨5�������أ�9�������������Ӵ��Ŀ�����0��
#define TRUE 1
#define FALSE 0

typedef struct PathNode
{
	int data;	//��Ӧ�����е�ֵ
	int x;		//������
	int y;		//������
	int F;		//F = G + H
	int G;		//��㵽�õ���ƶ��ķ�	
	int H;		//�˵㵽�յ���̾��루�������ϰ��
	bool open_list;//�Ƿ��ڿ��������У�����Ϊ1������Ϊ0
	bool close_list;//�Ƿ��ڹر������У�����Ϊ1������Ϊ0
	bool is_Endpoint_Here; // ·���յ�
	bool is_Startpoint_Here; // ·�����
	struct PathNode* next;
	struct PathNode* path_next;
} pnode, *linklist;

typedef struct Coordinate
{
	int x;
	int y;
}coor;



extern int col;
extern int row;

extern int map1n[][18];

void A_star_algorithm(int mapn[][18], int startpoint_x, int startpoint_y, int endpoint_x, int endpoint_y, coor* Coor_next_step);
pnode** malloc_Map(int row, int col);
pnode** translate_Map(int Mapn[][18], int row, int col);
linklist ini_List();
void output(pnode** Mapp, int row, int col);
pnode* find_start_pnode(pnode** Mapp, int row, int col, int Startpoint_x, int Startpoint_y);
pnode* find_end_pnode(pnode** Mapp, int row, int col, int Endpoint_x, int Endpoint_y);
int count_Pnode_F(pnode* Cur_pnode);
int count_Pnode_G(pnode* Cur_pnode, pnode* Father_pnode);
int count_Pnode_H(pnode* Cur_pnode, pnode* End_pnode);
void insert_openlist_by_asc(linklist Openlist, pnode* elem);
pnode* return_openlist_min_pnode(pnode* Openlist);
void insert_into_closelist(pnode* min_Open, linklist Closelist);
bool isExist_openList(pnode* Cur_pnode);
bool isExist_closeList(pnode* Cur_pnode);
bool isObstacle(pnode* Cur_pnode);
bool isJoin(pnode* Cur);
void insert_open(pnode *Node, pnode* ahead, pnode* End_pnode, linklist Openlist, pnode** Mapp);
void check_around_curpnode(pnode* cur, pnode* End_pnode, linklist Openlist, pnode** Mapp);

#endif //!AHEAD_H