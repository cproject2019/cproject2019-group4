#include <stdio.h>
#include "control.h"

static void CopyToNode(Enemy_t enemy, Node_t * pnode);

/**/
/*��ʼ������*/
void InitializeList(List_t * plist)
{
	*plist = NULL;
}

/*����Ϊ�գ�����true*/
bool ListIsEmpty(const List_t * plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

/*��������������true*/
bool ListIsFull(const List_t * plist)
{
	Node_t * pt;
	bool full;

	pt = (Node_t *)malloc(sizeof(Node_t));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);

	return full;
}

/*����ÿ���ڵ㣬����pfunָ��ĺ���*/
void Traverse(const List_t * plist, void(*pfun)(Enemy_t enemy))
{
	Node_t * pnode = *plist;
	while (pnode != NULL)
	{
		(*pfun)(pnode->enemy);
		pnode = pnode->next;
	}
}

/*�ͷ��ڴ�*/
void EmptyTheList(List_t * plist)
{
	Node_t * pnode;

	while (*plist != NULL)
	{
		pnode = (*plist)->next;
		free(*plist);
		*plist = pnode;
	}
}

/*�ҳ��ض���enemy*/
int FindOldEnemy(List_t * plist)
{
	Node_t * pTemp;

	for (pTemp = *plist; pTemp != NULL; pTemp = pTemp->next)
	{
		if (pTemp->enemy.life == 0)
		{
			return pTemp->enemy.sprite;
		}
	}
	return 0;
}

/*ɾ��enemy.spriteΪ�����ҵ���ֵ�������е���*/
bool DeleteEnemy(List_t * plist, int num)
{
	Node_t * pTemp = *plist;
	Node_t * pNodeDelete = NULL;
	Node_t * pPreNode = NULL;

	while (pTemp && pNodeDelete == NULL)
	{
		if (pTemp->enemy.sprite == num)
			pNodeDelete = pTemp;
		else
			pPreNode = pTemp;
		pTemp = pTemp->next;
	}

	if (pNodeDelete == NULL)//none
		return false;
	else if (pPreNode == NULL)//first
	{
		*plist = (*plist)->next; //???????????
		free(pNodeDelete);
	}
	else if (pNodeDelete->next == NULL)//last
	{
		pPreNode->next = NULL;
		free(pNodeDelete);
	}
	else//middle
	{
		pPreNode->next = pNodeDelete->next;
		free(pNodeDelete);
	}

	return true;
}

/*�����������*/
bool AddEnemy(Enemy_t enemy, List_t * plist)
{
	Node_t * pnew;

	pnew = (Node_t *)malloc(sizeof(Node_t));
	if (pnew == NULL)
	{
		return false;
	}

	CopyToNode(enemy, pnew);
	pnew->next = NULL;

	if (!(*plist))
		*plist = pnew;
	else
	{
		pnew->next = *plist;
		*plist = pnew;
	}
	return true;
}

void CopyToNode(Enemy_t enemy, Node_t * pnode)
{
	pnode->enemy = enemy;
}

/*���ؽڵ������*/
int ListItemCount(const List_t * plist)
{
	int count = 0;
	Node_t * pnode = *plist;

	while (pnode != NULL)
	{
		count++;
		pnode = pnode->next;
	}

	return count;
}