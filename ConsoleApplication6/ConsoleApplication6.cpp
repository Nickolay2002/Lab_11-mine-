#include <iostream>
#define N 9
using namespace std;

//int method;
//int load_capacity = 25;//(R)
//int sizes[] = { 7, 100, 2, 15, 2, 600, 4, 10, 11 };//a[i]
//int prices[] = { 30, 4, 30, 120, 6, 30, 8, 60, 11 };//b[i]
//const int N = sizeof(sizes) / sizeof(int);
//int V[N] = { 0 };
//int Kbest = 0, record = 0, value = 0;
//int best[100][N];
//int sum = 0, index = 0, p = 0;


int method;
const int load_capacity = 25;
int sizes[N], prices[N];
int V[N] = { 0 };
int Kbest = 0, record = 0, value = 0;
int best[50][N];
int sum = 0, index = 0, p = 0;

void check()
{
	if (p < value)
		return;
	if (p > value)
	{
		Kbest = 0;
		value = p;
	}
	if (Kbest < 50)
	{
		for (int i = 0; i < N; i++)
		{
			best[Kbest][i] = V[i];
		}
		Kbest++;
	}
}

void forward(int varf)
{
	switch (varf)
	{
	case 2:
		for (int i = index; i < N; i++)
		{
			if (sizes[i] + sum <= load_capacity)
			{
				V[i] = 1;
				sum += sizes[i];
				//p += prices[i];
			}
			else V[i] = 0;
		}
		return;
	case 4:
		for (int i = index; i < N; i++)
		{
			if (sizes[i] + sum <= load_capacity)
			{
				V[i] = 1;
				sum += sizes[i];
				p += prices[i];
			}
			else V[i] = 0;
		}
		return;
	}
}

int back(int varb)
{
	switch (varb)
	{
	case 2:
		if (V[N - 1])
		{
			V[N - 1] = 0;
			sum -= sizes[N - 1];
		}
		for (int i = N - 2; i >= 0; i--)
		{
			if (V[i])
			{
				V[i] = 0;
				sum -= sizes[i];
				index = i + 1;
				return 1;
			}
		}
	case 4:
		if (V[N - 1])
		{
			V[N - 1] = 0;
			sum -= sizes[N - 1];
			p -= prices[N - 1];
		}
		for (int i = N - 2; i >= 0; i--)
		{

			if (V[i])
			{
				V[i] = 0;
				sum -= sizes[i];
				p -= prices[i];
				index = i + 1;
				return 1;
			}
		}
	}
}

void show(int vars)
{
	switch (vars)
	{
	case 12:
		printf("Size of bag = %d\nSizes = ", load_capacity);
		//print_array(sizes);
		//print_array(prices);
		for (int i = 0; i < N; i++)
		{
			printf("%d\t", sizes[i]);
		}
		printf("\nThe best selections:");
		for (int i = 0; i < Kbest; i++)
		{
			printf("\n");
			for (int j = 0; j < N; j++)
				if (best[i][j])
					printf("%d ", sizes[j]);
		}
		printf("\n");
		printf("value = %d\n", value);
		printf("Kbest = %d\n", Kbest);
		return;
	case 34:
		printf("Size of bag = %d\nSizes = ", load_capacity);
		//print_array(sizes);
		for (int i = 0; i < N; i++)
		{
			printf("%d\t", sizes[i]);
		}
		printf("\nPrices = ");
		//print_array(prices);
		for (int i = 0; i < N; i++)
		{
			printf("%d\t", prices[i]);
		}
		printf("\nThe best selections based on price:");
		for (int i = 0; i < Kbest; i++)
		{
			printf("\n");
			for (int j = 0; j < N; j++)
			{
				if (best[i][j])
				{
					printf("%d ", sizes[j]);
				}
			}
		}
		printf("\n");
		printf("value = %d\n", value);
		printf("Kbest = %d\n", Kbest);
		return;
	}
}

int main()
{
	for (int i = 0; i < N; i++)
	{
		printf_s("Size of the [%d] item=", i);
		scanf_s("%d", &sizes[i]);
	}
	printf_s("Choose the method: \n 1.Exhaustive search. \n 2.Exhaustive search with clipping. \n 3.Exhaustive search with price. \n 4.Exhaustive search with price and cliping. \n");
	scanf_s("%d", &method);
	switch (method)
	{
	case 1:
		V[N - 1] = 1;
		for (size_t i = 0; i < N; i++)
		{
			check();
		}
		show(12);
		break;
	case 2:
		V[N - 1] = 1;
		do
		{
			forward(2);
			check();
		} while (back(2));
		show(12);
		break;
	case 3:
		for (int i = 0; i < N; i++)
		{
			printf_s("Price of the [%d] item=", i);
			scanf_s("%d", &prices[i]);
		}
		V[N - 1] = 1;
		for (size_t i = 0; i < N; i++)
		{
			check();
		}
		show(34);
		break;
	case 4:
		for (int i = 0; i < N; i++)
		{
			printf_s("Price of the [%d] item=", i);
			scanf_s("%d", &prices[i]);
		}
		V[N - 1] = 1;
		do {
			forward(4);
			check();
		} while (back(4));
		show(34);
		break;
	}
}