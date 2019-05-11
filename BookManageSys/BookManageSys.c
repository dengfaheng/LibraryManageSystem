#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


typedef struct mybook
{
	int num;     //���
	char bookname[30]; //����
	char author[20]; //����
	int price;      //��۸�
	int flag;      //�ж��Ƿ����(1:���ģ�0��û����)
}BOOK,*PBOOK;

typedef struct mystudent
{
	int carnum;//���鿨��
	char stuname[20];//����
	char stuclass[20];//���
	char lenbook[30];//���ĵ�����
	int stuflag;//����Ƿ��Ѿ����飬�ݶ�һ��ֻ�ܽ�һ��
}STUDENT,*PSTUDENT;

BOOK book[1000];
STUDENT student[1000];


/*��ѯͼ����Ϣģ��*/
/*(1)����������*/
void SearchBookByName(); //��������������ѯͼ��
/*(2)�����߲���*/
void SearchBookByAuthor();//��������������ѯͼ��
void SearchBook();

/*����ϵͳģ��*/
void ManageSys();
void AddBookInfo();
void ChangeBookInfo();
void ShowLendBook();


/*����ģ��*/
void LendBook();//����

/*����ģ��*/
void ReturnBook();//����

/*����ģ��*/
void ApplyCarnum(); //���뿨��

void showinfo();


int main()
{
	
	showinfo();
	char ch;
	do
	{
		system("title ͼ�����ϵͳ-����@�˷���");
		system("cls");
		printf("\t\t\t                        �� ���                               \n");
		printf("\t\t\t         ����������..������ �� ��� ..../            �﷫�� \n");
		printf("\t\t\t      �����|�|�����|�|�����|�|�|�|�|��������                 \n");
		printf("\t\t\t        ����������������������������������                   \n");
		printf("\t\t\t       �� ��������������������������������������             \n");
		printf("\t\t\t                                                      \n");
		printf("\t\t\t|-------------------------------------------------|\n");
		printf("\t\t\t|__�x�y�z�{�|�~����ͼ�����ϵͳ�����~�}�|�{�z�y�x_|\n");//����˵�
		printf("\t\t\t|-------------------------------------------------|\n");
		printf("\t\t\t|                   ��.����ͼ��                   |\n");
		printf("\t\t\t|		    ��.����ͼ��                   |\n");
		printf("\t\t\t|                   ��.����ϵͳ                   |\n");
		printf("\t\t\t|                   ��.���뿨��                   |\n");
		printf("\t\t\t|                   ��.����                       |\n");
		printf("\t\t\t|                   ��.�˳�                       |\n");
		printf("\t\t\t---------------------------------------------------\n");
		printf("\n\n��ѡ��->");


	
	
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
			printf("������������������!\n");
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

	printf("������Ҫ���ҵ�����->");
	scanf("%s", bookname);

	printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i],sizeof(BOOK),1,fp) != 0 )
	{
		if (strcmp(bookname, book[i].bookname) == 0)
		{
			sum++;
			if (book[i].flag == 1)
			{
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
			else
			{
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
		}
	}
	printf("-------------------------------------------------------------------------\n");
	printf("######################���ҵ�%d����########################\n", sum);
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

	printf("������Ҫ�������������->");
	scanf("%s", author);

	printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i], sizeof(BOOK), 1, fp) != 0)
	{
		if (strcmp(author, book[i].author) == 0)
		{
			sum++;
			if (book[i].flag == 1)
			{
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
			else
			{
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
			}
		}
	}
	printf("----------------------------------------------------------\n");
	printf("######################���ҵ�%d����########################\n", sum);

	system("pause");
	fclose(fp);
	return;

}

void SearchBook()
{
	

	char ch;
	do
	{
		system("title ��ӭ����ͼ���ѯϵͳ");
		system("cls");
		printf("###################��ӭ����ͼ���ѯϵͳ###################\n");
		printf(" 1: ����������\n");
		printf(" 2: �����߲���\n");
		printf(" 0: ����\n");
		printf("������0-2:\n");
		ch = getch();
		switch (ch)
		{
		case '1':SearchBookByName(); break;
		case '2':SearchBookByAuthor(); break;
		case '0':break;
		default:printf("�޴˲���!\n"); break;
		}
	} while (ch != '0');
}

void LendBook()
{
	system("title ��ӭ����ͼ�����ϵͳ");
	char ch;
	system("cls");
	FILE *fpbook = fopen("book.txt", "rt+");
	FILE *fpstudent = fopen("student.txt", "rt+");
	int carnum, booknum;//ѧ����ź��鱾���
	int i,j;
	printf("###################��ӭ����ͼ�����ϵͳ###################\n");
	printf("��������Ľ��鿨��->");
	scanf("%d", &carnum);
	i = 0;
	j = 0;
	
	while (fread(&student[i], sizeof(STUDENT), 1, fpstudent) != 0)
	{
		if (student[i].carnum == carnum)
		{
			if (student[i].stuflag == 1)
			{
				printf("���Ѿ����ͼ��:%s��һ��ֻ��һ���飬�뻹����ٽ衣лл��\n", student[i].lenbook);
				system("pause");
				return;
			}
			printf("�ý��鿨����Ϣ���£���ȷ��:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("����:%s    ���:%s	  ����:%d\n", student[i].stuname, student[i].stuclass, student[i].carnum);
			printf("-------------------------------------------------------------------------\n");
			goto Lend;
		}
		i++;
	}
	printf("������Ч����ȷ�����Ƿ��Ѿ�������鿨�ţ�\n\n");
	system("pause");
	return;
Lend:
	printf("��������Ҫ���ͼ����->");
	scanf("%d", &booknum);

	while (fread(&book[j], sizeof(BOOK), 1, fpbook) != 0)
	{
		if (book[j].num == booknum)
		{
			if (book[j].flag == 1)
			{
				printf("����:%s�Ѿ����˽��ߡ��뻻һ���飡\n\n", book[j].bookname);
				system("pause");
				return;
			}
			printf("�ý�����Ϣ���£���ȷ��:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
			printf("%d		%s		%s		%d		��\n", book[j].num, book[j].bookname, book[j].author, book[j].price);
			printf("-------------------------------------------------------------------------\n");
			printf("��ȷ���Ƿ���飿(Y/N)->");
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
				printf("\n\n����ɹ�������");
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
		system("title ��ӭ����ͼ�����ϵͳ");
		printf("################��ӭ����ͼ�����ϵͳ################\n");
		printf(" 1: ���ͼ����Ϣ\n");
		printf(" 2: �޸�ͼ����Ϣ\n");
		printf(" 3: �������ͳ��\n");
		printf(" 0: ����\n");
		printf("������0-3:\n");
		ch = getch();
		switch (ch)
		{
		case '1':AddBookInfo(); break;
		case '2':ChangeBookInfo(); break;
		case '3':ShowLendBook();
		case '0': break;
		default:printf("�޴˲���!\n"); break;
		}
	} while (ch != '0');
}

void AddBookInfo()
{
	system("title ���ͼ��");
	system("cls");
	BOOK tbook;
	char ch;
Start:
	printf("\n\n###################���ͼ����Ϣ###################\n");
	printf("������ͼ����->");
	scanf("%d", &tbook.num);
	printf("����������->");
	scanf("%s", tbook.bookname);
	printf("������������->");
	scanf("%s", tbook.author);
	printf("������۸�->");
	scanf("%d", &tbook.price);

	tbook.flag = 0; //����δ����
	FILE *fp = fopen("book.txt", "a+");
	if (fwrite(&tbook, sizeof(BOOK), 1, fp) != 0)
	{
		printf("����ͼ����Ϣ�ɹ����Ƿ�������ͼ�飿(Y/N):\n");
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
	system("title �޸�ͼ��");
	printf("\n\n###################�޸�ͼ����Ϣ###################\n");
	printf("������ͼ����->");
	scanf("%d", &num);
	int i = 0;
	FILE *fpbook = fopen("book.txt", "rt+");
	while (fread(&book[i], sizeof(BOOK), 1, fpbook) != 0)
	{
		if (book[i].num == num)
		{
			if (book[i].flag == 1)
			{
				printf("�ý�����Ϣ���£���ȷ��:\n");
				printf("-------------------------------------------------------------------------\n");
				printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
				printf("-------------------------------------------------------------------------\n");
			}
			else
			{
				printf("�ý�����Ϣ���£���ȷ��:\n");
				printf("-------------------------------------------------------------------------\n");
				printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
				printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
				printf("-------------------------------------------------------------------------\n");
			}
			printf("��ȷ���Ƿ��޸Ĵ��飿(Y/N)->\n");
			ch = getch();
			if (ch == 'y' || ch == 'Y')
			{
				printf("������ͼ����->");
				scanf("%d", &book[i].num);
				printf("����������->");
				scanf("%s", book[i].bookname);
				printf("������������->");
				scanf("%s", book[i].author);
				printf("������۸�->");
				scanf("%d", &book[i].price);

				fseek(fpbook, sizeof(BOOK)*(i), SEEK_SET);
				fwrite(&book[i], sizeof(BOOK), 1, fpbook);
				fclose(fpbook);
				printf("���ͼ��ɹ�������\n");
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

	printf("\n\n######################��ѯ�ѽ�ͼ��#####################\n");
	printf("���		����		����		�۸�		�Ƿ��ѽ���\n");
	printf("-------------------------------------------------------------------------\n");
	while (fread(&book[i], sizeof(BOOK), 1, fp) != 0)
	{
		
		i++;
		if (book[i].flag == 1)
		{
			sum++;
			printf("%d		%s		%s		%d		��\n", book[i].num, book[i].bookname, book[i].author, book[i].price);
		}

	}
	printf("-------------------------------------------------------------------------\n");
	printf("######################���ҵ�%d����########################\n", sum);
	system("pause");
	fclose(fp);
}

void ReturnBook()
{
	system("title ��ӭ����ͼ�黹��ϵͳ");
	system("cls");
	FILE *fpb= fopen("book.txt", "rt+");
	FILE *fps = fopen("student.txt", "rt+");
	int i, j,booknum,carnum;
	char ch;

	printf("################��ӭ����ͼ�黹��ϵͳ################\n");
	printf("��������Ľ��鿨��->\n");
	scanf("%d", &carnum);
	i = 0;
	j = 0;

	while (fread(&student[i], sizeof(STUDENT), 1, fps) != 0)
	{
		if (student[i].carnum == carnum)
		{
			printf("�ý��鿨����Ϣ���£���ȷ��:\n");
			printf("-------------------------------------------------------------------------\n");
			printf("����:%s    ���:%s	  ����:%d\n", student[i].stuname, student[i].stuclass, student[i].carnum);
			printf("-------------------------------------------------------------------------\n");
			if (student[i].stuflag == 1)
			{
				printf("���Ѿ����ͼ��:%s����ȷ���Ƿ��飿(Y/N)\n", student[i].lenbook);
				ch = getch();
				if (ch == 'Y' || ch == 'y')
				{
					printf("������ͼ����->");
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
							printf("����ɹ�������\n\n\n");
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
	system("title ������鿨��");
	STUDENT tstu;
	char ch;
Start:
	system("cls");
	printf("\n\n###################������鿨��###################\n");
	printf("�������������->");
	scanf("%s", tstu.stuname);
	printf("��������İ��->");
	scanf("%s", tstu.stuclass);
	tstu.stuflag = 0;//����δ����
	memset(tstu.lenbook, 0, 30);

	srand(time(NULL));
	tstu.carnum = 10000 + rand() % 100; //�������


	FILE *fp = fopen("student.txt", "a+");
	if (fwrite(&tstu, sizeof(STUDENT), 1, fp) != 0)
	{
		printf("���뿨�ųɹ���������Ŀ���Ϊ��%d   �Ƿ�������뿨�ţ�(Y/N):", tstu.carnum);
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
	printf("\t\t\t                        �� ���                               \n");
	printf("\t\t\t         ����������..������ �� ��� ..../            �﷫�� \n");
	printf("\t\t\t      �����|�|�����|�|�����|�|�|�|�|��������                 \n");
	printf("\t\t\t        ����������������������������������                   \n");
	printf("\t\t\t       �� ��������������������������������������             \n");
	printf("\t\t\t                                                      \n");


	system("color 3b");
	Sleep(100);
	printf("\t\t\t|-------------------------------------------------|\n");
	system("color 3c");
	Sleep(100);
	printf("\t\t\t|__�x�y�z�{�|�~����ͼ�����ϵͳ�����~�}�|�{�z�y�x_|\n");//����˵�
	system("color 3d");
	Sleep(100);
	printf("\t\t\t|-------------------------------------------------|\n");
	system("color 3e");
	Sleep(100);
	printf("\t\t\t|                   ��.����ͼ��                   |\n");
	system("color 3f");
	Sleep(100);
	printf("\t\t\t|		    ��.����ͼ��                   |\n");
	system("color 3a");
	Sleep(100);
	printf("\t\t\t|                   ��.����ϵͳ                   |\n");
	system("color 3c");
	Sleep(100);
	printf("\t\t\t|                   ��.���뿨��                   |\n");
	system("color 3f");
	Sleep(100);
	printf("\t\t\t|                   ��.����                       |\n");
	system("color 3d");
	Sleep(100);
	printf("\t\t\t|                   ��.�˳�                       |\n");
	system("color 3e");
	Sleep(100);
	printf("\t\t\t---------------------------------------------------\n");
	system("color 3b");
	Sleep(100);
	printf("\n\n��ѡ��->");
}