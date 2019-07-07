#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

/*�ض�������*/

struct enemy
{
	int sprite;
	int number;
	int x, y;
	int mode;
	int life;
	bool exit;
};

/*һ�������*/

typedef struct enemy Enemy_t;

typedef struct node
{
	Enemy_t enemy;
	struct node * next;
}Node_t;

typedef Node_t * List_t;

/*����ԭ��*/

/*��������ʼ��һ������*/ /*ǰ��������plistָ��һ������*/ /*���������������ʼ��Ϊ��*///1
void InitializeList(List_t * plist);

/*������ȷ�������Ƿ�Ϊ�ն���*/ /*ǰ��������plistָ��һ���ѳ�ʼ��������*/ /*�����������������Ϊ�գ��ú�������true�����򷵻�false*///1
bool ListIsEmpty(const List_t * plist);

/*������ȷ�������Ƿ�����*/ /*ǰ��������plistָ��һ���ѳ�ʼ��������*/ /*������������������������ú�������true�����򷵻�false*///1
bool ListIsFull(const List_t * plist);

/*�������Ѻ��������������е�ÿһ��*/
/*ǰ��������plistָ��һ���ѳ�ʼ��������*/
/*			pfunָ��һ���������ú�������һ��Enemy_t���͵Ĳ������޷���ֵ*/
/*����������pfunָ��ĺ��������������ÿһ��һ��*/
void Traverse(const List_t * plist, void(*pfun)(Enemy_t enemy));

/*�������ͷ��ѷ�����ڴ�*/ /*ǰ��������plistָ��һ���ѳ�ʼ��������*/ /*�����������ͷ���Ϊ�������������ڴ棬��������Ϊ��*///1
void EmptyTheList(List_t * plist);

/*������������Ŀ�ͷ�����*///1
/*ǰ��������plistָ��һ���ѳ�ʼ��������*/
/*			enemy��һ������ӵ���*/
/*����������������ԣ�������ͷ���һ����ҷ���true����֮����false*/
bool AddEnemy(Enemy_t enemy, List_t * plist);

/*���������������ҳ�ָ������*/ /*ǰ��������plistָ��һ���ѳ�ʼ��������*/ /*�����������������sprite��û���ҵ��򷵻�0*/
int FindOldEnemy(List_t * plist);

/*��������������ɾ��ָ������*/ /*ǰ��������plistָ��һ���ѳ�ʼ�������� nΪ��Ҫɾ�����sprite���*/ /*����������ɾ������ͷ����ڴ棬���гɹ�����true*/
bool DeleteEnemy(List_t * plist, int num);

/*������ȷ�������е�����*/ /*ǰ��������plistָ��һ���ѳ�ʼ��������*/ /*�������������������е�����*/
int ListItemCount(const List_t * plist);

#endif // !LIST_H_
