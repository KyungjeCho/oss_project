#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#include "StockFunctions.h"
#include "Stock.h"

unsigned long Money;
int StockPrice[MAX_COMPANY], PrevStockPrice[MAX_COMPANY], Stocks, StockDeal, loanMoney, companyOrder[MAX_COMPANY];
int GraphData[MAX_COMPANY][48] = { 0 };
bool ifGood[MAX_COMPANY];

char *CompanyName[MAX_COMPANY] =
{
	"Naissoft",
	"HawTech",
	"�ϰܳ��",
	"MK Electronics",
	"���뱺��",
	"CJ ���ϼտ���",
	"KJS �ý���",
	"Fruit",
	"������ ���ͽ�",
	"�������",
};

void ChangeStockPrice()
{
	srand((int)time(NULL));

	for (int i = 0; i < MAX_COMPANY; i++)
	{
		if (ifGood[i] == true)
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 1000);
			}
			else
			{
				StockPrice[i] -= (rand() % 100);
			}
		}
		else
		{
			if ((rand() % 2) == 0)
			{
				StockPrice[i] += (rand() % 500);
			}
			else
			{
				StockPrice[i] -= (rand() % 1000);
			}
		}
		if (StockPrice[i] < 2000) StockPrice[i] = 2000;
		StockPrice[i] = StockPrice[i] / 10 * 10;
	}
}

void ShowStockPrice(int mode)
{
	if (mode == 0)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			PrintStockPrice(i);
			companyOrder[i] = i;
		}
		return;
	}

	int order[MAX_COMPANY], tmp;
	for (int i = 0; i < MAX_COMPANY; i++) order[i] = StockPrice[i];

	if (mode == 1)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] > order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
					companyOrder[i] = j;
				}
			}
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] < order[j])
				{
					tmp = order[i];
					order[i] = order[j];
					order[j] = tmp;
				}
			}
		}
		for (int i = 0; i < MAX_COMPANY; i++)
		{
			for (int j = 0; j < MAX_COMPANY; j++)
			{
				if (order[i] == StockPrice[j])
				{
					PrintStockPrice(j);
					order[i] = 0;
					companyOrder[i] = j;
				}
			}
		}
	}
}

void PrintStockPrice(int i)
{
	printf(" ȸ�� : ");
	if (ifGood[i])
	{
		textcolor(10);
		printf("%-20s", CompanyName[i]);
		textcolor(7);
	}
	else 
	{
		textcolor(12);
		printf("%-20s", CompanyName[i]);
		textcolor(7);
	}
	printf(" �� ���� : %5d��  ", StockPrice[i]);
	if (PrevStockPrice[i] < StockPrice[i])
	{
		textcolor(2);
		printf("��%4d�� ", StockPrice[i] - PrevStockPrice[i]);
		textcolor(7);
	}
	else if (PrevStockPrice[i] > StockPrice[i])
	{
		textcolor(14);
		printf("��%4d�� ", -1 * (StockPrice[i] - PrevStockPrice[i]));
		textcolor(7);
	}
	printf("\n");
}

void loan(int lmoney)
{
	loanMoney += lmoney;
	Money += lmoney;
}

void interest()
{
	loanMoney += (int)((double)loanMoney * 0.05);
}

void payback()
{
	Money -= loanMoney;
	loanMoney = 0;
}

void buyStock(int order, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		if (StockPrice[order] <= (int)Money)
		{
			system("cls");
			gNow = gHead;

			gTmp.company = order;
			gTmp.price = StockPrice[order];
			gNow = InsertStock(gNow, &gTmp);

			Stocks++;
			StockDeal++;
			printf(" %d���� �ְ� ��° �ֽ��� �����Ͽ����ϴ�. �ֽ��� %d���Դϴ�.\n", StockPrice[order], Stocks);
			Money -= StockPrice[order];
			printf(" ���� ���� %d���Դϴ�.\n", Money);
		}
		else
		{
			printf(" ���� �����մϴ�. �ֽ��� �� �� �����ϴ�.\n");
		}
	}
}

void sellStock(int i)
{
	Stock *f = FindStock(i - 1);
	if (f == NULL) return;
	
	Money += (StockPrice[f->company]);
	DeleteStock(f);
	
}

void showStockList()
{
	system("cls");
	int j, k;
	char i;
	k = 1;
	if (Stocks <= 0)
	{
		printf("\n �ֽ��� �����ϴ�.\n");
	}
	else
	{
		do
		{
			system("cls");
			titleLine("�ֽ� ��� ����");
			printf("\n [ A, D�� �� ���� �� �ֽ��ϴ�. ]\n\n");
			j = 1;
			for (gNow = gHead->next; gNow; gNow = gNow->next)
			{
				if (j >= k && j < k + 10) printf("\n %d. ȸ�� : %-20s, ���� : %d��", j, CompanyName[gNow->company], gNow->price);
				j++;
			}
			printf("\n ���ư����� Q�� ��������.\n");
			scanf(" %c", &i);
			if (i == 'D' || i == 'd') k += 10;
			else if (i == 'A' || i == 'a')
			{
				if (k > 10) k -= 10;
			}
		} while (i != 'Q');
	}
	system("cls");
}

void UpdateGraphData()
{
	for (int i = 0; i < MAX_COMPANY; i++)
	{
		for (int j = 46; j >= 0; j--)
		{
			GraphData[i][j + 1] = GraphData[i][j];
		}
		GraphData[i][0] = StockPrice[i];
	}
}
