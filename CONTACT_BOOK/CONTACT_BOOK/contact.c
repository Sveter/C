#include "contact.h"

int CheckCapacity(pcontact pc)
{
	if (pc->sz == pc->capacity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + INC_SZ) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capacity += INC_SZ;
			printf("增容成功\n");
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

void LoadContact(pcontact pc)
{
	//int i = 0;
	FILE* pf = fopen("contact.txt","rb");
	PeoInfo tmp = { 0 };
	if (pf == NULL)
	{
		printf("没有文件夹\n");
		perror("open file for write");
		//exit(EXIT_FAILURE);
		return;
	}
	//检查容量
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		CheckCapacity(pc);
		pc->data[pc->sz++] = tmp;
	}
	fclose(pf);
	pf = NULL;
}

void InitContact(pcontact pc)
{
	/*pc->sz = 0;
	memset(pc->data,0,sizeof(pc->data));*/
	pc->data = (PeoInfo *)calloc(DEFAULT_SZ, sizeof(PeoInfo));
	//判断是否开辟成功
	if (pc->data == NULL)
	{
		printf("%s\n",strerror(errno));
		return;
	}
	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;

	LoadContact(pc);
}

void DestoryContact(pcontact pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}

void AddContact(pcontact pc)
{
	////判断是否已满
	//if (pc->sz == MAX)
	//{
	//	printf("空间已满，放不下了\n");
	//	return;
	//}
	//增容
	if( CheckCapacity(pc) == 0 )
	{
		return;
	}
	//增加信息
	printf("请输入名字:>");
	scanf("%s", pc->data[pc->sz].name);
	printf("请输入年龄:>");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("请输入性别:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("请输入电话:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("请输入地址:>");
	scanf("%s", pc->data[pc->sz].addr);

	printf("\n信息添加成功!\n");
	pc->sz++;
}

void ShowContact(const pcontact pc)
{
	int i = 0;
	if (pc->sz == 0)
	{
		printf("没有信息，请添加\n");
		return;
	}
	printf("%10s\t%5s\t%5s\t%15s\t%20s\n","name","age","sex","tele","addr");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%10s\t%5d\t%5s\t%15s\t%20s\n",pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

int Find(pcontact pc, char name[])
{
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (!strcmp(pc->data[i].name, name))
		{
			return i;
		}
	}
	if (i == pc->sz)
	{
		return -1;
	}
}

void DelContact(pcontact pc)
{
	//判断是否为空
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法删除\n");
		return;
	}
	//1.找到目标
	int p = 0;
	int pos = 0;
	char name[NAME_MAX];
	printf("请输入要删除的名字:>");
	scanf("%s",name);
	p = Find(pc,name);
	if (p == -1)
	{
		printf("查无此人\n");
		return;
	}
	//2.删除
	for (pos = p; pos < pc->sz - 1; pos++)
	{
		pc->data[pos] = pc->data[pos + 1];
	}
	printf("删除成功!\n");

	pc->sz--;
}

void SearchContact(pcontact pc)
{
	char name[NAME_MAX];
	printf("请输入要查找的名字:>");
	scanf("%s",name);
	int pos = Find(pc, name);
	if (pos == -1)
	{
		printf("没有此人信息\n");
	}
	else
	{
		printf("%10s\t%5s\t%5s\t%15s\t%20s\n", "name", "age", "sex", "tele", "addr");
		printf("%10s\t%5d\t%5s\t%15s\t%20s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].addr);
	}
}

void ModifyContact(pcontact pc)
{
	//判断为空
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法修改\n");
		return;
	}
	//姓名->find->修改内容->修改成功
	char name[NAME_MAX];
	printf("请输入要修改信息的人的名字:>");
	scanf("%s",name);
	int p = Find(pc,name);
	if (p == -1)
	{
		printf("没有此人信息\n");
	}
	else
	{
		int input = 0; 
		char name[NAME_MAX];
		int age = 0;
		char sex[SEX_MAX];
		char tele[TELE_MAX];
		char addr[ADDR_MAX];
		printf("%d", NAME);
		printf("****  1.name  2.age  3.sex  4.tele  5.addr  ****\n");
		printf("请选择修改信息:>");
		scanf("%d",&input);
		
        printf("请输入修改内容:>");
		switch (input)
		{
		case NAME:
			scanf("%s",&name);
			strcpy(pc->data[p].name, name);
			printf("修改成功\n");
			break;
		case AGE:
			scanf("%d",&age);
			pc->data[p].age = age;
			printf("修改成功\n");
			break;
		case SEX:
			scanf("%s", sex);
			strcpy(pc->data[p].sex, sex);
			printf("修改成功\n");
			break;
		case TELE:
			scanf("%s", tele);
			strcpy(pc->data[p].tele, tele);
			printf("修改成功\n");
			break;
		case ADDR:
			scanf("%s", addr);
			strcpy(pc->data[p].addr, addr);
			printf("修改成功\n");
			break;
		default:
			printf("修改失败\n");
			break;
		}
	}
}

void ClearContact(pcontact pc)
{
	//pc->sz清零
	pc->sz = 0;
	printf("成功清空\n");
}

void SortContact(pcontact pc)
{
	//为空不用排序
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法排序\n");
		return;
	}
	//姓名，冒泡排序
	int flag = 0;
	for (int i = 0; i < pc->sz - 1; i++)
	{
		flag = 1;
		for (int j = 0; j < pc->sz - i - 1; j++)
		{
			if (strcmp(pc->data[j].name, pc->data[j + 1].name) > 0)
			{
				struct PeoInfo tmp = pc->data[j];
				pc->data[j] = pc->data[j + 1];
				pc->data[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			break;
		}
		else
		{
			printf("排序成功\n");
		}
	}
}

void SaveContact(pcontact pc)
{
	int i = 0;
	FILE* pf = fopen("contact.txt","wb");
	if (pf == NULL)
	{
		perror("open file for write");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data+i,sizeof(PeoInfo),1,pf);
	}
	fclose(pf);
	pf = NULL; 
}