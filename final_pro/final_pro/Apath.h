#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef AHEAD_H
#define AHEAD_H


#define MAP_MAX_X 18   //地图边界，二维数组大小
#define MAP_MAX_Y 11
#define MOVEABLE_AIR_SQUARE 3 //敌人可移动的方格
#define OBSTACLE 7 //障碍物与不可移动方格：边界（5）、土地（9）、非两层连接处的空气（0）
#define TRUE 1
#define FALSE 0

typedef struct PathNode
{
	int data;	//对应数组中的值
	int x;		//列坐标
	int y;		//行坐标
	int F;		//F = G + H
	int G;		//起点到该点的移动耗费	
	int H;		//此点到终点最短距离（不考虑障碍物）
	bool open_list;//是否在开放链表中，是则为1，否则为0
	bool close_list;//是否在关闭链表中，是则为1，否则为0
	bool is_Endpoint_Here; // 路径终点
	bool is_Startpoint_Here; // 路径起点
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