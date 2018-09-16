#ifndef __CONTACT_H__
#define __CONTACT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#pragma warning(disable:4996)

//#define MAX 1000
#define DEFAULT_SZ 3
#define INC_SZ 2

#define NAME_MAX 20
#define SEX_MAX 10
#define TELE_MAX 12
#define ADDR_MAX 20

typedef struct PeoInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
}PeoInfo;

typedef struct Contact
{
	//struct PeoInfo data[MAX];
	PeoInfo * data;
	int sz;     //有效个数
	int capacity;//容量
}*pcontact;

enum Option 
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	CLEAR,
	SORT,
	SAVE
};

enum Info
{
	NAME = 1,
	AGE,
	SEX,
	TELE,
	ADDR
};

void InitContact(pcontact pc);
void DestoryContact(pcontact pc);
void AddContact(pcontact pc);
void ShowContact(const pcontact pc);
void DelContact(pcontact pc);
int Find(pcontact pc, char name[]);
void SearchContact(pcontact pc);
void ModifyContact(pcontact pc);
void ClearContact(pcontact pc);
void SortContact(pcontact pc);
void SaveContact(pcontact pc);

#endif //!__CONTACT_H__
