#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 100
#define TURE 1
#define FALSE 0

typedef struct customer {
	int cus_num;
	int serv_time;
	int waited_time;
	int arrival_time;
} CUS;

int is_customer_arrived();
void insert_customer(int arrival_time, CUS cus[]);
void remove_customer(CUS cus[]);
void print_stat(int customers, int served_customers, int waited_time);

int duration = 10;
double arrival_prob = 0.7;
int max_serv_time = 5;

int rear;

int main()
{
	srand((unsigned)time(NULL));

	CUS cus[100] = { 0 };
	int clock = 0;

	int customers = 0;			// 전체 고객의 수
	int served_customers = 0;	// 서비스 받은 고객의 수
	int waited_time = 0;		// 고객이 기다린 시간

	int tmp_serv_time = 0;

	for (int i = 1; i <= duration; i++)
	{
		printf("현재시각 = %d\n", i);

		if (is_customer_arrived())
		{
			insert_customer(i, cus);
			printf("고객 %d이 %d분에 들어옵니다. 서비스 시간은 %d분입니다.\n", cus[rear].cus_num, cus[rear].arrival_time, cus[rear].serv_time);
			rear++;
			customers++;
		}
		
		if (tmp_serv_time == 0 && rear > 0)
		{
			printf("고객 %d이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n", cus[0].cus_num, i, cus[0].waited_time);
			tmp_serv_time = cus[0].serv_time;
			waited_time += cus[0].waited_time;
			served_customers++;

			remove_customer(cus);
			rear--;
		}

		if (tmp_serv_time > 0 )tmp_serv_time--;

		for (int j = 0; j <= rear; j++)
		{
			cus[j].waited_time++;
		}
	}

	print_stat(customers, served_customers, waited_time);

	return 0;
}

int is_customer_arrived()
{
	double tmp;
	tmp = rand() % 101 / 100.0;

	if (tmp <= arrival_prob)
		return TURE;
	else
		return FALSE;
}

void insert_customer(int arrival_time, CUS cus[])
{
	static int count = 0;

	cus[rear].cus_num = count;
	cus[rear].serv_time = rand() % max_serv_time + 1;
	cus[rear].waited_time = 0;
	cus[rear].arrival_time = arrival_time;
	count++;
}

void remove_customer(CUS cus[])
{
	for (int i = 1; i <= rear; i++)
	{
		cus[i - 1].cus_num = cus[i].cus_num;
		cus[i - 1].serv_time = cus[i].serv_time;
		cus[i - 1].waited_time = cus[i].waited_time;
		cus[i - 1].arrival_time = cus[i].arrival_time;
	}
}

void print_stat(int customers, int served_customers, int waited_time)
{
	printf("\n서비스 받은 고객의 수 = %d명\n", served_customers);
	printf("1인당 평균 대기 시간 = %lf분\n", (double)waited_time / served_customers);
	printf("아직 대기중인 고객의 수 = %d명\n", customers - served_customers);
}