#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct mybook
{
	int num;     //编号
	char bookname[30]; //书名
	char author[20]; //作者
	int price;      //书价格
	int flag;      //判断是否借阅(1:借阅，0：没借阅)
}BOOK, *PBOOK;

typedef struct mystudent
{
	int carnum;//借书卡号
	char stuname[20];//姓名
	char stuclass[20];//班别
	char lenbook[30];//借阅的书名
	int stuflag;//标记是否已经借书，暂定一人只能借一本
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
		sprintf(book[i].bookname, "书本%d", i);
		sprintf(book[i].author, "作者%d", i);

		student[i].carnum = i+10000;
		student[i].stuflag = 0;
		sprintf(student[i].stuname, "学生%d", i);
		sprintf(student[i].stuclass, "班级%d", i);
		sprintf(student[i].lenbook, "无");

		fwrite(&student[i], sizeof(STUDENT), 1, fps);
		fwrite(&book[i], sizeof(BOOK), 1, fpb);

	}

	fclose(fpb);
	fclose(fps);



	return 0;
}