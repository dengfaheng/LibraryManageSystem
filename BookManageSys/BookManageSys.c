#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


typedef struct mybook
{
	int num;     //编号
	char bookname[30]; //书名
	char author[20]; //作者
	int price;      //书价格
	int flag;      //判断是否借阅(1:借阅，0：没借阅)
}BOOK,*PBOOK;

typedef struct mystudent
{
	int carnum;//借书卡号
	char stuname[20];//姓名
	char stuclass[20];//班别
	char lenbook[30];//借阅的书名
	int stuflag;//标记是否已经借书，暂定一人只能借一本
}STUDENT,*PSTUDENT;

BOOK book[1000];
STUDENT student[1000];


/*查询图书信息模块*/
/*(1)按书名查找*/
void SearchBookByName(); //按照书名搜索查询图书
/*(2)按作者查找*/
void SearchBookByAuthor();//按照作者搜索查询图书
void SearchBook();

/*管理系统模块*/
void ManageSys();
void AddBookInfo();
void ChangeBookInfo();
void ShowLendBook();


/*借书模块*/
void LendBook();//借书

/*还书模块*/
void ReturnBook();//还书

/*还书模块*/
void ApplyCarnum(); //申请卡号

void showinfo();


int main()
{
	
	showinfo();
	char ch;
	do
	{
		system("title 图书管理系统-华科@邓发珩");
		system("cls");
		printf("\t\t\t                        ▍ ★∴                               \n");
		printf("\t\t\t         ．．▍▍．..．█▍ ☆ ★∵ ..../            扬帆起航 \n");
		printf("\t\t\t      ◥█▅▅██▅▅██▅▅▅▅▅███◤                 \n");
		printf("\t\t\t        ◥███████████████◤                   \n");
		printf("\t\t\t       ～ ◥█████████████◤～～～～             \n");
		printf("\t\t\t                                                      \n");
		printf("\t\t\t|-------------------------------------------------|\n");
		printf("\t\t\t|__▁▂▃▄▅▇█▉图书管理系统▉▉▇▆▅▄▃▂▁_|\n");//打出菜单
		printf("\t\t\t|-------------------------------------------------|\n");
		printf("\t\t\t|                   ①.查阅图书                   |\n");
		printf("\t\t\t|		    ②.借阅图书                   |\n");
		printf("\t\t\t|                   ③.管理系统                   |\n");
		printf("\t\t\t|                   ④.申请卡号                   |\n");
		printf("\t\t\t|                   ⑤.还书                       |\n");
		printf("\t\t\t|                   ⑥.退出                       |\n");
		printf("\t\t\t---------------------------------------------------\n");
		printf("\n\n请选择->");


	
	
		ch = getch();
		switch (ch)
		{
		case '1':
			SearchBook();
			break;
		case '2':
			LendBook();
			break;
		case '3':
			ManageSys();
			break;
		case '4':
			ApplyCarnum();
			break;
		case '5':
			ReturnBook();
			break;
		case '6':
			exit(0);
			break;
		default:
			printf("输入有误，请重新输入!\n");
			break;
		}
	} while (ch != '6');


	return 0;
}

void SearchBookByName()
{
	char bookname[30];
	int i = 0;
	int sum = 0;
	FILE *fp = fopen("book.txt", "r");

	printf("请输入要查找的书名->");
	scanf("%s", bookname);

	printf("编号		书名		作者		价格		是否已借阅\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i],sizeof(BOOK),1,fp) != 0 )
	{
		if (strcmp(bookname, book[i].bookname) == 0)
		{
			sum++;
			if (book[i].flag == 1)
			{
				printf("%d		%s		%s		%d		是\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
			else
			{
				printf("%d		%s		%s		%d		否\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
		}
	}
	printf("-------------------------------------------------------------------------\n");
	printf("######################共找到%d本书########################\n", sum);
	system("pause");
	fclose(fp);
	return;

}

void SearchBookByAuthor()
{
	char author[20];
	int i = 0;
	int sum = 0;
	FILE *fp = fopen("book.txt", "r");

	printf("请输入要查找书的作者名->");
	scanf("%s", author);

	printf("编号		书名		作者		价格		是否已借阅\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i], sizeof(BOOK), 1, fp) != 0)
	{
		if (strcmp(author, book[i].author) == 0)
		{
			sum++;
			if (book[i].flag == 1)
			{
				printf("%d		%s		%s		%d		是\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
			else
			{
				printf("%d		%s		%s		%d		否\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
		}
	}
	printf("----------------------------------------------------------\n");
	printf("######################共找到%d本书########################\n", sum);

	system("pause");
	fclose(fp);
	return;

}

void SearchBook()
{
	

	char ch;
	do
	{
		system("title 欢迎进入图书查询系统");
		system("cls");
		printf("###################欢迎进入图书查询系统###################\n");
		printf(" 1: 按书名查找\n");
		printf(" 2: 按作者查找\n");
		printf(" 0: 返回\n");
		printf("请输入0-2:\n");
		ch = getch();
		switch (ch)
		{
		case '1':SearchBookByName(); break;
		case '2':SearchBookByAuthor(); break;
		case '0':break;
		default:printf("无此操作!\n"); break;
		}
	} while (ch != '0');
}

void LendBook()
{
	system("title 欢迎进入图书借阅系统");
	char ch;
	system("cls");
	FILE *fpbook = fopen("book.txt", "rt+");
	FILE *fpstudent = fopen("student.txt", "rt+");
	int carnum, booknum;//学生编号和书本编号
	int i,j;
	printf("###################欢迎进入图书借阅系统###################\n");
	printf("请输入你的借书卡号->");
	scanf("%d", &carnum);
	i = 0;
	j = 0;
	
	while (fread(&student[i], sizeof(STUDENT), 1, fpstudent) != 0)
	{
		if (student[i].carnum == carnum)
		{
			if (student[i].stuflag == 1)
			{
				printf("你已经借过图书:%s，一人只限一本书，请还书后再借。谢谢！\n", student[i].lenbook);
				system("pause");
				return;
			}
			printf("该借书卡号信息如下，请确认:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("姓名:%s    班别:%s	  卡号:%d\n", student[i].stuname, student[i].stuclass, student[i].carnum);
			printf("-------------------------------------------------------------------------\n");
			goto Lend;
		}
		i++;
	}
	printf("卡号无效，请确认你是否已经申请借书卡号！\n\n");
	system("pause");
	return;
Lend:
	printf("请输入你要借的图书编号->");
	scanf("%d", &booknum);

	while (fread(&book[j], sizeof(BOOK), 1, fpbook) != 0)
	{
		if (book[j].num == booknum)
		{
			if (book[j].flag == 1)
			{
				printf("此书:%s已经被人借走。请换一本书！\n\n", book[j].bookname);
				system("pause");
				return;
			}
			printf("该借书信息如下，请确认:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("编号		书名		作者		价格		是否已借阅\n");
			printf("%d		%s		%s		%d		否\n", book[j].num, book[j].bookname, book[j].author, book[j].price);
			printf("-------------------------------------------------------------------------\n");
			printf("请确认是否借书？(Y/N)->");
			ch = getch();
			if (ch == 'y' || ch == 'Y')
			{
				memset(student[i].lenbook, 0, 30);
				strcpy(student[i].lenbook, book[j].bookname);
				student[i].stuflag = 1;
				book[j].flag = 1;
				fseek(fpbook, sizeof(BOOK)*(j), SEEK_SET);
				fseek(fpstudent, sizeof(STUDENT)*(i), SEEK_SET);
				fwrite(&student[i], sizeof(STUDENT), 1, fpstudent);
				fwrite(&book[j], sizeof(BOOK), 1, fpbook);
				printf("\n\n借书成功！！！");
				system("pause");
				fclose(fpbook);
				fclose(fpstudent);
				return;
			}
			else
			{
				fclose(fpbook);
				fclose(fpstudent);
				return;
			}
		}
		j++;
	}
	fclose(fpbook);
	fclose(fpstudent);
}

void ManageSys()
{
	
	char ch;
	
	do
	{
		system("cls");
		system("title 欢迎进入图书管理系统");
		printf("################欢迎进入图书管理系统################\n");
		printf(" 1: 添加图书信息\n");
		printf(" 2: 修改图书信息\n");
		printf(" 3: 借书情况统计\n");
		printf(" 0: 返回\n");
		printf("请输入0-3:\n");
		ch = getch();
		switch (ch)
		{
		case '1':AddBookInfo(); break;
		case '2':ChangeBookInfo(); break;
		case '3':ShowLendBook();
		case '0': break;
		default:printf("无此操作!\n"); break;
		}
	} while (ch != '0');
}

void AddBookInfo()
{
	system("title 添加图书");
	system("cls");
	BOOK tbook;
	char ch;
Start:
	printf("\n\n###################添加图书信息###################\n");
	printf("请输入图书编号->");
	scanf("%d", &tbook.num);
	printf("请输入书名->");
	scanf("%s", tbook.bookname);
	printf("请输入作者名->");
	scanf("%s", tbook.author);
	printf("请输入价格->");
	scanf("%d", &tbook.price);

	tbook.flag = 0; //设置未借阅
	FILE *fp = fopen("book.txt", "a+");
	if (fwrite(&tbook, sizeof(BOOK), 1, fp) != 0)
	{
		printf("更新图书信息成功！是否继续添加图书？(Y/N):\n");
		ch = getch();
		if (ch == 'y' || ch == 'Y')
		{
			goto Start;
		}
		else
		{
			fclose(fp);
			system("pause");
			return;
		}
	}

}

void ChangeBookInfo()
{
	int num;
	char ch;
	system("cls");
	system("title 修改图书");
	printf("\n\n###################修改图书信息###################\n");
	printf("请输入图书编号->");
	scanf("%d", &num);
	int i = 0;
	FILE *fpbook = fopen("book.txt", "rt+");
	while (fread(&book[i], sizeof(BOOK), 1, fpbook) != 0)
	{
		if (book[i].num == num)
		{
			if (book[i].flag == 1)
			{
				printf("该借书信息如下，请确认:\n");
				printf("-------------------------------------------------------------------------\n");
				printf("编号		书名		作者		价格		是否已借阅\n");
				printf("%d		%s		%s		%d		是\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
				printf("-------------------------------------------------------------------------\n");
			}
			else
			{
				printf("该借书信息如下，请确认:\n");
				printf("-------------------------------------------------------------------------\n");
				printf("编号		书名		作者		价格		是否已借阅\n");
				printf("%d		%s		%s		%d		否\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
				printf("-------------------------------------------------------------------------\n");
			}
			printf("请确认是否修改此书？(Y/N)->\n");
			ch = getch();
			if (ch == 'y' || ch == 'Y')
			{
				printf("请输入图书编号->");
				scanf("%d", &book[i].num);
				printf("请输入书名->");
				scanf("%s", book[i].bookname);
				printf("请输入作者名->");
				scanf("%s", book[i].author);
				printf("请输入价格->");
				scanf("%d", &book[i].price);

				fseek(fpbook, sizeof(BOOK)*(i), SEEK_SET);
				fwrite(&book[i], sizeof(BOOK), 1, fpbook);
				fclose(fpbook);
				printf("添加图书成功！！！\n");
				system("pause");
				return;
			}
			else
			{
				fclose(fpbook);
				return;
			}
		}
		i++;
	}
}

void ShowLendBook()
{
	int i = 0;
	int sum = 0;
	FILE *fp = fopen("book.txt", "r");
	system("cls");

	printf("\n\n######################查询已借图书#####################\n");
	printf("编号		书名		作者		价格		是否已借阅\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i], sizeof(BOOK), 1, fp) != 0)
	{
		
		i++;
		if (book[i].flag == 1)
		{
			sum++;
			printf("%d		%s		%s		%d		是\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
		}

	}
	printf("-------------------------------------------------------------------------\n");
	printf("######################共找到%d本书########################\n", sum);
	system("pause");
	fclose(fp);
}

void ReturnBook()
{
	system("title 欢迎进入图书还书系统");
	system("cls");
	FILE *fpb= fopen("book.txt", "rt+");
	FILE *fps = fopen("student.txt", "rt+");
	int i, j,booknum,carnum;
	char ch;

	printf("################欢迎进入图书还书系统################\n");
	printf("请输入你的借书卡号->\n");
	scanf("%d", &carnum);
	i = 0;
	j = 0;

	while (fread(&student[i], sizeof(STUDENT), 1, fps) != 0)
	{
		if (student[i].carnum == carnum)
		{
			printf("该借书卡号信息如下，请确认:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("姓名:%s    班别:%s	  卡号:%d\n", student[i].stuname, student[i].stuclass, student[i].carnum);
			printf("-------------------------------------------------------------------------\n");
			if (student[i].stuflag == 1)
			{
				printf("你已经借过图书:%s，请确认是否还书？(Y/N)\n", student[i].lenbook);
				ch = getch();
				if (ch == 'Y' || ch == 'y')
				{
					printf("请输入图书编号->");
					scanf("%d", &booknum);

					student[i].stuflag = 0;
					memset(student[i].lenbook, 0, 30);

					fseek(fps, sizeof(STUDENT)*(i), SEEK_SET);
					fwrite(&student[i], sizeof(STUDENT), 1, fps);

					while (fread(&book[j], sizeof(BOOK), 1, fpb) != 0)
					{
						if (book[j].num == booknum)
						{
							book[j].flag = 0;
							fseek(fpb, sizeof(BOOK)*(j), SEEK_SET);
							fwrite(&book[j], sizeof(BOOK), 1, fpb);
							printf("还书成功！！！\n\n\n");
							system("pause");
							fclose(fpb);
							fclose(fps);
							return;
						}
						j++;
					}
				}
				else
				{
					fclose(fpb);
					fclose(fps);
					return;
				}
			}

		}
		i++;
	}
	fclose(fpb);
	fclose(fps);
	return;

}

void ApplyCarnum()
{
	system("title 申请借书卡号");
	STUDENT tstu;
	char ch;
Start:
	system("cls");
	printf("\n\n###################申请借书卡号###################\n");
	printf("请输入你的姓名->");
	scanf("%s", tstu.stuname);
	printf("请输入你的班别->");
	scanf("%s", tstu.stuclass);
	tstu.stuflag = 0;//设置未借阅
	memset(tstu.lenbook, 0, 30);

	srand(time(NULL));
	tstu.carnum = 10000 + rand() % 100; //随机卡号


	FILE *fp = fopen("student.txt", "a+");
	if (fwrite(&tstu, sizeof(STUDENT), 1, fp) != 0)
	{
		printf("申请卡号成功！你申请的卡号为：%d   是否继续申请卡号？(Y/N):", tstu.carnum);
		ch = getch();
		if (ch == 'y' || ch == 'Y')
		{
			goto Start;
		}
		else
		{
			fclose(fp);
			system("pause");
			return;
		}
	}


}

void showinfo()
{
	system("cls");
	system("color 3E");
	system("color 3F");
	system("color 3A");
	system("color 3B");
	system("color 3C");
	system("color 3A");
	system("color 3C");
	system("color 3A");
	system("color 3F");
	system("color 3E");
	system("color 3F");
	system("color 3A");
	system("color 3B");
	system("color 3F");
	system("color 3D");
	system("color 3C");
	system("color 3A");
	system("color 3E");
	system("color 3A");
	system("color 3F");
	system("color 3D");
	system("color 3B");
	system("color 3C");
	system("color 3A");
	system("color 3C");
	system("color 3A");
	system("color 3F");
	printf(" \t\t                                                      \n");
	system("cls");
	printf("\t\t\t                        ▍ ★∴                               \n");
	printf("\t\t\t         ．．▍▍．..．█▍ ☆ ★∵ ..../            扬帆起航 \n");
	printf("\t\t\t      ◥█▅▅██▅▅██▅▅▅▅▅███◤                 \n");
	printf("\t\t\t        ◥███████████████◤                   \n");
	printf("\t\t\t       ～ ◥█████████████◤～～～～             \n");
	printf("\t\t\t                                                      \n");


	system("color 3b");
	Sleep(100);
	printf("\t\t\t|-------------------------------------------------|\n");
	system("color 3c");
	Sleep(100);
	printf("\t\t\t|__▁▂▃▄▅▇█▉图书管理系统▉▉▇▆▅▄▃▂▁_|\n");//打出菜单
	system("color 3d");
	Sleep(100);
	printf("\t\t\t|-------------------------------------------------|\n");
	system("color 3e");
	Sleep(100);
	printf("\t\t\t|                   ①.查阅图书                   |\n");
	system("color 3f");
	Sleep(100);
	printf("\t\t\t|		    ②.借阅图书                   |\n");
	system("color 3a");
	Sleep(100);
	printf("\t\t\t|                   ③.管理系统                   |\n");
	system("color 3c");
	Sleep(100);
	printf("\t\t\t|                   ④.申请卡号                   |\n");
	system("color 3f");
	Sleep(100);
	printf("\t\t\t|                   ⑤.还书                       |\n");
	system("color 3d");
	Sleep(100);
	printf("\t\t\t|                   ⑥.退出                       |\n");
	system("color 3e");
	Sleep(100);
	printf("\t\t\t---------------------------------------------------\n");
	system("color 3b");
	Sleep(100);
	printf("\n\n请选择->");
}