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
			printf("���ݳɹ�\n");
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
		printf("û���ļ���\n");
		perror("open file for write");
		//exit(EXIT_FAILURE);
		return;
	}
	//�������
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
	//�ж��Ƿ񿪱ٳɹ�
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
	////�ж��Ƿ�����
	//if (pc->sz == MAX)
	//{
	//	printf("�ռ��������Ų�����\n");
	//	return;
	//}
	//����
	if( CheckCapacity(pc) == 0 )
	{
		return;
	}
	//������Ϣ
	printf("����������:>");
	scanf("%s", pc->data[pc->sz].name);
	printf("����������:>");
	scanf("%d", &(pc->data[pc->sz].age));
	printf("�������Ա�:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("������绰:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("�������ַ:>");
	scanf("%s", pc->data[pc->sz].addr);

	printf("\n��Ϣ��ӳɹ�!\n");
	pc->sz++;
}

void ShowContact(const pcontact pc)
{
	int i = 0;
	if (pc->sz == 0)
	{
		printf("û����Ϣ�������\n");
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
	//�ж��Ƿ�Ϊ��
	if (pc->sz == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷�ɾ��\n");
		return;
	}
	//1.�ҵ�Ŀ��
	int p = 0;
	int pos = 0;
	char name[NAME_MAX];
	printf("������Ҫɾ��������:>");
	scanf("%s",name);
	p = Find(pc,name);
	if (p == -1)
	{
		printf("���޴���\n");
		return;
	}
	//2.ɾ��
	for (pos = p; pos < pc->sz - 1; pos++)
	{
		pc->data[pos] = pc->data[pos + 1];
	}
	printf("ɾ���ɹ�!\n");

	pc->sz--;
}

void SearchContact(pcontact pc)
{
	char name[NAME_MAX];
	printf("������Ҫ���ҵ�����:>");
	scanf("%s",name);
	int pos = Find(pc, name);
	if (pos == -1)
	{
		printf("û�д�����Ϣ\n");
	}
	else
	{
		printf("%10s\t%5s\t%5s\t%15s\t%20s\n", "name", "age", "sex", "tele", "addr");
		printf("%10s\t%5d\t%5s\t%15s\t%20s\n", pc->data[pos].name, pc->data[pos].age, pc->data[pos].sex, pc->data[pos].tele, pc->data[pos].addr);
	}
}

void ModifyContact(pcontact pc)
{
	//�ж�Ϊ��
	if (pc->sz == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷��޸�\n");
		return;
	}
	//����->find->�޸�����->�޸ĳɹ�
	char name[NAME_MAX];
	printf("������Ҫ�޸���Ϣ���˵�����:>");
	scanf("%s",name);
	int p = Find(pc,name);
	if (p == -1)
	{
		printf("û�д�����Ϣ\n");
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
		printf("��ѡ���޸���Ϣ:>");
		scanf("%d",&input);
		
        printf("�������޸�����:>");
		switch (input)
		{
		case NAME:
			scanf("%s",&name);
			strcpy(pc->data[p].name, name);
			printf("�޸ĳɹ�\n");
			break;
		case AGE:
			scanf("%d",&age);
			pc->data[p].age = age;
			printf("�޸ĳɹ�\n");
			break;
		case SEX:
			scanf("%s", sex);
			strcpy(pc->data[p].sex, sex);
			printf("�޸ĳɹ�\n");
			break;
		case TELE:
			scanf("%s", tele);
			strcpy(pc->data[p].tele, tele);
			printf("�޸ĳɹ�\n");
			break;
		case ADDR:
			scanf("%s", addr);
			strcpy(pc->data[p].addr, addr);
			printf("�޸ĳɹ�\n");
			break;
		default:
			printf("�޸�ʧ��\n");
			break;
		}
	}
}

void ClearContact(pcontact pc)
{
	//pc->sz����
	pc->sz = 0;
	printf("�ɹ����\n");
}

void SortContact(pcontact pc)
{
	//Ϊ�ղ�������
	if (pc->sz == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷�����\n");
		return;
	}
	//������ð������
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
			printf("����ɹ�\n");
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