#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct mybook
{
	int num;     //���
	char bookname[30]; //����
	char author[20]; //����
	int price;      //��۸�
	int flag;      //�ж��Ƿ����(1:���ģ�0��û����)
}BOOK, *PBOOK;

typedef struct mystudent
{
	int carnum;//���鿨��
	char stuname[20];//����
	char stuclass[20];//���
	char lenbook[30];//���ĵ�����
	int stuflag;//����Ƿ��Ѿ����飬�ݶ�һ��ֻ�ܽ�һ��
}STUDENT, *PSTUDENT;



int main()
{
	BOOK book[1000];
	STUDENT student[1000];
	srand(time(NULL));
	FILE *fpb = fopen("book.txt", "a+");
	FILE *fps = fopen("student.txt", "a+");
	for (int i = 0; i < 10; i++)
	{
		book[i].num = i;
		book[i].price = rand() % 100;
		book[i].flag = 0;
		sprintf(book[i].bookname, "�鱾%d", i);
		sprintf(book[i].author, "����%d", i);

		student[i].carnum = i+10000;
		student[i].stuflag = 0;
		sprintf(student[i].stuname, "ѧ��%d", i);
		sprintf(student[i].stuclass, "�༶%d", i);
		sprintf(student[i].lenbook, "��");

		fwrite(&student[i], sizeof(STUDENT), 1, fps);
		fwrite(&book[i], sizeof(BOOK), 1, fpb);

	}

	fclose(fpb);
	fclose(fps);



	return 0;
}