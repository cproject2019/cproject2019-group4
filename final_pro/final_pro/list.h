#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

/*特定的声明*/

struct enemy
{
	int sprite;
	int number;
	int x, y;
	int mode;
	int life;
	bool exit;
};

/*一般的声明*/

typedef struct enemy Enemy_t;

typedef struct node
{
	Enemy_t enemy;
	struct node * next;
}Node_t;

typedef Node_t * List_t;

/*函数原型*/

/*操作：初始化一个链表*/ /*前提条件：plist指向一个链表*/ /*后置条件：链表初始化为空*///1
void InitializeList(List_t * plist);

/*操作：确定链表是否为空定义*/ /*前提条件：plist指向一个已初始化的链表*/ /*后置条件：如果链表为空，该函数返回true，否则返回false*///1
bool ListIsEmpty(const List_t * plist);

/*操作：确定链表是否已满*/ /*前提条件：plist指向一个已初始化的链表*/ /*后置条件：如果链表已满，该函数返回true，否则返回false*///1
bool ListIsFull(const List_t * plist);

/*操作：把函数作用于链表中的每一项*/
/*前提条件：plist指向一个已初始化的链表*/
/*			pfun指向一个函数，该函数接受一个Enemy_t类型的参数且无返回值*/
/*后置条件：pfun指向的函数作用于链表的每一项一次*/
void Traverse(const List_t * plist, void(*pfun)(Enemy_t enemy));

/*操作：释放已分配的内存*/ /*前提条件：plist指向一个已初始化的链表*/ /*后置条件：释放了为链表分配的所有内存，链表设置为空*///1
void EmptyTheList(List_t * plist);

/*操作：在链表的开头添加项*///1
/*前提条件：plist指向一个已初始化的链表*/
/*			enemy是一个待添加的项*/
/*后置条件：如果可以，在链表开头添加一个项，且返回true，反之返回false*/
bool AddEnemy(Enemy_t enemy, List_t * plist);

/*操作：在链表中找出指定的项*/ /*前提条件：plist指向一个已初始化的链表*/ /*后置条件：返回项的sprite，没有找到则返回0*/
int FindOldEnemy(List_t * plist);

/*操作：在链表中删除指定的项*/ /*前提条件：plist指向一个已初始化的链表， n为需要删除项的sprite编号*/ /*后置条件：删除项，并释放其内存，运行成功返回true*/
bool DeleteEnemy(List_t * plist, int num);

/*操作：确定链表中的项数*/ /*前提条件：plist指向一个已初始化的链表*/ /*后置条件：返回链表中的项数*/
int ListItemCount(const List_t * plist);

#endif // !LIST_H_
