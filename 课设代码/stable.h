#ifndef STABLE_H_INCLUDED
#define STABLE_H_INCLUDED
#include <iostream>
#include <string>
using namespace std;

typedef struct snode snode;
typedef struct tnode tnode;
typedef struct arrnode arrnode;
typedef struct strunode strunode;
typedef struct fnode fnode;
typedef struct cnode cnode;
typedef struct lnode lnode;

void addnode(string name, string cat, char tval);

//�����ܱ�SYNBL���
struct snode
{
	string name;  //����
	tnode* typel; //���� ָ�����ͱ�
	string cat;  //����
	int addr;//��ַ(���Ͳ�ȷ����ָ�룬��Ϊint,���õ�ʱ��ǿ��ת��Ϊ��Ҫ������)
	snode* next = NULL;  //ָ����һ���ڵ�
};

//���ͱ�TAPEL���
struct tnode
{
	char tval;//����
	//i������)��r(ʵ��)��c(�ַ���)��b(������)��
	//a(������)��d(�ṹ��)

	int* tpoint;//(���Ͳ�ȷ����ָ�룬��Ϊint,���õ�ʱ��ǿ��ת��Ϊ��Ҫ������)
	// ������������(i,r,c,b)�C nul(��ָ��)��
	// ��������(a) �C ָ�������;
	// �ṹ����(d) �C ָ��ṹ��;
	tnode* next;
};


//��Ϣ��ڵ㣨����ͽṹ�壩
struct arrnode
{
	int low;//�����½�
	int up;//�����Ͻ�
	tnode* ctp;//ָ�������ɷ����ͣ����ͱ�����Ϣ��
	int clen;//�ɷ����͵�������ռֵ��Ԫ����

	arrnode* next = NULL;
};

struct strunode
{
	string id;//�ṹ������
	int off;//����
	tnode* tp;//ָ�룬ָ����ɷ�����(�����ͱ��е���Ϣ);

	strunode* next = NULL;
};

//������
struct fnode
{
	int level;//��κ�
	int off;//����
	int fn;//��������
	string entry;//��ڵ�ַ
	fnode* next = NULL;
};

//������
struct cnode
{
	int consl;//�����ĳ�ֵ
	cnode* next = NULL;
};

//���ȱ�
struct lnode
{
	int lenl;//����������ռֵ��Ԫ����
	lnode* next = NULL;
};


//�����ͷ��β
snode* shead = new snode;
tnode* thead = new tnode;

arrnode* arrhead = new arrnode;
strunode* struhead = new strunode;
fnode* fhead = new fnode;
cnode* chead = new cnode;
lnode* lhead = new lnode;

snode* stail = shead;
tnode* ttail = thead;
arrnode* arrtail = arrhead;
strunode* strutail = struhead;
fnode* ftail = fhead;
cnode* ctail = chead;
lnode* ltail = lhead;


#endif // STABLE_H_INCLUDED#pragma once
