#include "Apath.h"

int col = MAP_MAX_X;
int row = MAP_MAX_Y;

int map1n[11][18] = {
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,3,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,3,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,3,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,3,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }
};
/*
int map1n[11][18] = {
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,3,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,3,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,3,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,3,7,7,7,7,7 },
	{ 7,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }
};*/

pnode** malloc_Map(int row, int col)//将地图数组转化为结构体指针数组前，为其申请内存
{
	pnode** map = (pnode**)malloc(row * sizeof(pnode*));
	int i;
	for (i = 0; i < row; ++i)
	{
		map[i] = (pnode*)malloc(col * sizeof(pnode));
	}
	return map;
}


pnode** translate_Map(int Mapn[][18], int row, int col)//将地图二维数组转化为结构体指针数组
{
	pnode** Mapp = malloc_Map(row, col);
	int i, j;
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
		{
			(Mapp[i] + j)->data = Mapn[i][j];
			(Mapp[i] + j)->x = j;
			(Mapp[i] + j)->y = i;
			(Mapp[i] + j)->F = 0;
			(Mapp[i] + j)->G = 0;
			(Mapp[i] + j)->H = 0;
			(Mapp[i] + j)->open_list = FALSE;
			(Mapp[i] + j)->close_list = FALSE;
			(Mapp[i] + j)->is_Startpoint_Here = FALSE;
			(Mapp[i] + j)->is_Endpoint_Here = FALSE;
			(Mapp[i] + j)->next = NULL;
			(Mapp[i] + j)->path_next = NULL;
		}

	return Mapp;

}


linklist ini_List()//初始化链表
{
	linklist List = (linklist)malloc(sizeof(pnode));
	if (List == NULL)
		return NULL;
	else
		memset(List, 0, sizeof(pnode));
	return List;
}



void output(pnode** Mapp, int row, int col)  //二维数组的访问必须指明位数，否则编译器不能解析
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%d\t", (Mapp[i] + j)->data);
		}
		printf("\n");
	}
}


pnode* find_start_pnode(pnode** Mapp, int row, int col, int Startpoint_x, int Startpoint_y)//遍历数组，寻找起点
{
	pnode* Start_pnode = NULL;
	int i, j;
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
		{
			if ((Mapp[i] + j)->x == Startpoint_x && (Mapp[i] + j)->y == Startpoint_y)
			{
				Start_pnode = (Mapp[i] + j);
				Start_pnode->is_Startpoint_Here = TRUE;
				return Start_pnode;
			}
		}
	return NULL;
}


pnode* find_end_pnode(pnode** Mapp, int row, int col, int Endpoint_x, int Endpoint_y)//遍历数组，寻找终点
{
	pnode* End_pnode = NULL;
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			if ((Mapp[i] + j)->x == Endpoint_x && (Mapp[i] + j)->y == Endpoint_y)
			{
				End_pnode = (Mapp[i] + j);
				End_pnode->is_Endpoint_Here = TRUE;
				return End_pnode;
			}
		}
	return NULL;
}


int count_Pnode_F(pnode* Cur_pnode)                           //计算当前节点F值
{
	Cur_pnode->F = Cur_pnode->G + Cur_pnode->H;
	return Cur_pnode->F;
}


int count_Pnode_G(pnode* Cur_pnode, pnode* Father_pnode)        //计算当前节点的G值
{
	if (Cur_pnode->x == Father_pnode->x && Cur_pnode->y == Father_pnode->y)
		return 1;//有异常
	else
		Cur_pnode->G = Father_pnode->G + 1;
	return Cur_pnode->G;
}


int count_Pnode_H(pnode* Cur_pnode, pnode* End_pnode)			//计算当前节点的H值
{
	Cur_pnode->H = abs(End_pnode->x - Cur_pnode->x) + abs(End_pnode->y - Cur_pnode->y);
	return Cur_pnode->H;
}


void insert_openlist_by_asc(linklist Openlist, pnode* elem)//按照F值从小到大插入
{
	pnode *p, *q;
	p = q = Openlist;
	while (p->next != NULL && p->F < elem->F)
	{
		q = p;
		p = p->next;
	}
	if (p->F < elem->F) q = p;
	elem->next = q->next;
	q->next = elem;
	elem->open_list = 1;
}


pnode* return_openlist_min_pnode(pnode* Openlist) //返回 openlist 中的F值最小节点（第一个节点）
{
	pnode *elem = NULL;
	if (Openlist->next != NULL)
	{
		Openlist->next->open_list = 0;
		elem = Openlist->next;
		Openlist->next = Openlist->next->next;
		elem->next = NULL;
	}
	else
		printf("empty openlist!");
	return elem;
}


void insert_into_closelist(pnode* min_Open, linklist Closelist)//插入OpenList中F值最小的节点到CloseList中去
{
	//对于CloseList中的节点并不需要排序,采用头插法
	min_Open->next = Closelist->next;
	Closelist->next = min_Open;
	min_Open->close_list = 1;
}


bool isExist_openList(pnode* Cur_pnode)
{
	return Cur_pnode->open_list;
}


bool isExist_closeList(pnode* Cur_pnode)
{
	return Cur_pnode->close_list;
}


bool isObstacle(pnode* Cur_pnode)
{
	if (Cur_pnode->data == 7)
		return TRUE;
	else
		return FALSE;
}


bool isJoin(pnode* Cur)        //该节点是否可以加入开放列表
{
	if (!isExist_closeList(Cur) && !isObstacle(Cur))        //既不在关闭列表里，也不是障碍物
	{
		return TRUE;
	}
	else
		return FALSE;
}


void insert_open(pnode *Node, pnode* ahead, pnode* End_pnode, linklist Openlist, pnode** Mapp)
{
	if (isJoin(Node))
	{
		if (isExist_openList(Node))
		{
			if (Node->G > (ahead->G + 1))
			{
				count_Pnode_G(Node, ahead);
				count_Pnode_F(Node);
				Node->path_next = ahead;
			}

		}
		else
		{
			count_Pnode_G(Node, ahead);
			count_Pnode_H(Node, End_pnode);
			count_Pnode_F(Node);
			Node->path_next = ahead;
			insert_openlist_by_asc(Openlist, Node);
		}
	}
}



void check_around_curpnode(pnode* cur, pnode* End_pnode, linklist Openlist, pnode** Mapp)
{
	int x = cur->x;
	int y = cur->y;
	if (y > 0 && y < 11)
	{
		if (x > 0 && x < 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
		if (x == 0)
		{
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
		if (x == 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
	}

	if (y == 0)
	{
		if (x == 0)
		{
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
		}

		if (x == 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
		}
		if (x > 0 && x < 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y + 1] + x, cur, End_pnode, Openlist, Mapp);
		}
	}

	if (y == 11)
	{
		if (x == 0)
		{
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
		if (x == 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
		if (x > 0 && x < 18)
		{
			insert_open(Mapp[y] + x - 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y] + x + 1, cur, End_pnode, Openlist, Mapp);
			insert_open(Mapp[y - 1] + x, cur, End_pnode, Openlist, Mapp);
		}
	}
}
