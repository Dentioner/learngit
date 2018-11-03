#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#include"head.h"
#include<time.h>
#include<stdlib.h>

/*
long long int key[15][15][2] = { 0 };//����ά�ȷֱ������ӺͰ��ӣ�0Ϊ�հ�
long long int hashing_value[depth_of_hashing][3] = { {0,0,0} };
//�ڶ�ά�ȵ�[0]���������̵Ĺ�ϣֵ��[1][2]�Ǵ˹�ϣֵ��Ӧ���������֣�Ӧ�ö����ں�������
long long int hashing_value_now = 0;//Ŀǰ�Ĺ�ϣֵ�������Ҫ��minimax.c������������
*/

void initialize_hashing_sheet(long long int key[][15][2])
{//������ÿ������ֻҪ���ʼִ��һ�ξ��У����ܶ��ִ��
	int zob_raw, zob_column, zob_status;
	long long int a, b, c;
	srand(time(NULL));
	
	for (zob_raw = 0; zob_raw < 15; zob_raw++)
	{
		for (zob_column = 0; zob_column < 15; zob_column++)
		{
			for (zob_status = 0; zob_status < 2; zob_status++)
			{
				a = rand();
				b = rand();
				c = rand();
				key[zob_raw][zob_column][zob_status] = a * 10000 + b * 1000 + c;
				//printf("%lld ", key[zob_raw][zob_column][zob_status]);
			}
			//printf("\n");
		}
		//printf("\n\n");
	}
}

long int Zobrist_hashing(long long int hashing_value[][2], long long int key[][15][2], 
	int best_raw, int best_column,
	//��ʵ�����õ�ʱ��ע��raw��column������������Ϊ���������Ҫ��¼�������̵���ѵ÷֣������ǵ�����ĵ÷�
	//ȡ����֮������ʹ�ñ�ĺ���������minimax�������������Ϊ���룬��˻�����2��value����
	//raw��column��������һ��Ҫ����ѵ�raw��column��������ѭ��������raw��column
	//long int my_value, long int opponent_value,
	bool write_new_coordinate,
	//�������ֵ�ǿ��ƴ˺����Ĺ��ܣ������true�Ļ����˺����Ż��¼�µĹ�ϣֵ�������֣����������Ϊһ����ѯ��ϣֵ�ĺ���
	int step_count, char board[][17][3], 
	bool my_turn, long long int hashing_value_now)
{
	int black = 0;
	int white = 1;
	int chess;
	int index = 0;
	if ((step_count % 2) == 0)
	{
		chess = black;
	}
	else
	{
		chess = white;
	}
	
	for (index = 0; index < depth_of_hashing; index++)
	{
	//�������߼��ǣ�������û�з�0�Ĺ�ϣֵ��
	//����У��ٿ����Ƿ���������ڵĹ�ϣֵ��ȣ������ڵ�һ��Ϊ0��λ�ü�¼�������ֵ
		if (hashing_value[index][0] != 0)//��������ϣֵ��Ϊ0
		{
			if (hashing_value[index][0] == hashing_value_now)//��������ϣֵ������Ĺ�ϣֵ���
			{
				//�������������������ű��Ƿ����ã���������ʱҪ������
				exit(0);
				//�ڱ��о��ҵ��˶�Ӧ�Ĺ�ϣֵ���Ǿͷ��ض�Ӧ������
				if (my_turn)
				{//Ŀǰ[1]��¼�����ҷ��ĵ÷�
					return hashing_value[index][1];
				}
				else//[2]��¼���ǶԷ��ĵ÷�
				{
					return hashing_value[index][2];
				}
				
			}
			
		}
		else//��������ϣֵΪ0����¼�������εĹ�ϣֵ������
		{
			if (write_new_coordinate)
			{
				hashing_value[index][0] = hashing_value[index][0] ^ key[best_raw][best_column][chess];
				hashing_value[index][1] = evaluation(board, step_count, my_turn, best_raw, best_column);
				hashing_value[index][2] = evaluation(board, step_count + 1, !my_turn, best_raw, best_column);
				return 0; //�������Ҳֻ��ִ��һ�Σ����ִ���ˣ��ͱ�������ѭ��
			}
			
		}
		
		
		
	}
	
	//ѭ�����꣬ʣ�µ�����ǣ���ϣ�����ˣ����ǻ���û��Ӧ��ֵ
		
	return 0;
}

