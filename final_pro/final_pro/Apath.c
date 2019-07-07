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

pnode** malloc_Map(int row, int col)//����ͼ����ת��Ϊ�ṹ��ָ������ǰ��Ϊ�������ڴ�
{
	pnode** map = (pnode**)malloc(row * sizeof(pnode*));
	int i;
	for (i = 0; i < row; ++i)
	{
		map[i] = (pnode*)malloc(col * sizeof(pnode));
	}
	return map;
}


pnode** translate_Map(int Mapn[][18], int row, int col)//����ͼ��ά����ת��Ϊ�ṹ��ָ������
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


linklist ini_List()//��ʼ������
{
	linklist List = (linklist)malloc(sizeof(pnode));
	if (List == NULL)
		return NULL;
	else
		memset(List, 0, sizeof(pnode));
	return List;
}



void output(pnode** Mapp, int row, int col)  //��ά����ķ��ʱ���ָ��λ����������������ܽ���
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


pnode* find_start_pnode(pnode** Mapp, int row, int col, int Startpoint_x, int Startpoint_y)//�������飬Ѱ�����
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


pnode* find_end_pnode(pnode** Mapp, int row, int col, int Endpoint_x, int Endpoint_y)//�������飬Ѱ���յ�
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


int count_Pnode_F(pnode* Cur_pnode)                           //���㵱ǰ�ڵ�Fֵ
{
	Cur_pnode->F = Cur_pnode->G + Cur_pnode->H;
	return Cur_pnode->F;
}


int count_Pnode_G(pnode* Cur_pnode, pnode* Father_pnode)        //���㵱ǰ�ڵ��Gֵ
{
	if (Cur_pnode->x == Father_pnode->x && Cur_pnode->y == Father_pnode->y)
		return 1;//���쳣
	else
		Cur_pnode->G = Father_pnode->G + 1;
	return Cur_pnode->G;
}


int count_Pnode_H(pnode* Cur_pnode, pnode* End_pnode)			//���㵱ǰ�ڵ��Hֵ
{
	Cur_pnode->H = abs(End_pnode->x - Cur_pnode->x) + abs(End_pnode->y - Cur_pnode->y);
	return Cur_pnode->H;
}


void insert_openlist_by_asc(linklist Openlist, pnode* elem)//����Fֵ��С�������
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


pnode* return_openlist_min_pnode(pnode* Openlist) //���� openlist �е�Fֵ��С�ڵ㣨��һ���ڵ㣩
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


void insert_into_closelist(pnode* min_Open, linklist Closelist)//����OpenList��Fֵ��С�Ľڵ㵽CloseList��ȥ
{
	//����CloseList�еĽڵ㲢����Ҫ����,����ͷ�巨
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


bool isJoin(pnode* Cur)        //�ýڵ��Ƿ���Լ��뿪���б�
{
	if (!isExist_closeList(Cur) && !isObstacle(Cur))        //�Ȳ��ڹر��б��Ҳ�����ϰ���
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
