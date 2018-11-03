#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

//chess_play���������Ҫ��д
//��Ϊ���ֺ�����Ҫ����raw��column��ֵ
//��Ҫ��raw��columnд��ȫ�ֱ�����Ȼ��chess_play������Ϊ�������
void chess_play(char board[][17][3], int step_count)//���ݵĵڶ������������˼����˵Ĵ���
{
	char column_c;//��ĸ��ʽ��������
	int raw, column;
	char black[2] = "��";
	char white[2] = "��";
	int raw_input_index = 0;//����scanf�ķ���ֵ
	bool invalid_coordinate = true;//�ж�ѡ����Ǹ����������ǲ����Ѿ�������������
	bool invalid_raw = true;//�ж������raw�Ƿ�Ϸ�

	while (invalid_coordinate)
	{
		//�������û���������꣬���账��
		printf("��ѡ����һ����������һ�����������磺2\n");

		while (invalid_raw)
		{
			raw_input_index = scanf("%d", &raw);
			while (getchar() != '\n')
				continue;

			if (raw_input_index != 1)
			{
				printf("��Ч���룬������\n");
				continue;
			}
			
			if (1 > raw || 15 < raw)
			{
				printf("��Ч���룬������\n");
				continue;
			}

			invalid_raw = false;
		}

		//����������ʱ�����޸�
		/*while (getchar() != '\n')
			continue;*/

		printf("������һ�����������磺B\n");
		column_c = getchar();
		while (getchar() != '\n')
			continue;
		while (column_c<'A' || (column_c > 'O'&&column_c < 'a') || column_c>'o')
		{
			printf("��Ч���룬������\n");

			column_c = getchar();
			while (getchar() != '\n')
				continue;

		}

		//�����ǽ��û����������ת��Ϊ������ʶ�������
		column_c = toupper(column_c);
		column = column_c - 64;
		raw = 15 - raw;
		//�ж��Ƿ�������Ѿ���������
		if (strncmp(board[raw][column], black, 2) == 0 
			|| strncmp(board[raw][column], white, 2) == 0)
		{
			printf("��λ���Ѿ��������ˣ�������ѡ��һ������\n");
			invalid_raw = true;//��������ڰ�֮ǰraw��ѭ�����ж�ֵ��ʼ����
			//���򲻻�������raw��ѭ��
			continue;
		}
		else
		{
			invalid_coordinate = false;
		}
	
	}

	if (step_count % 2 == 0)
	{
		strncpy(board[raw][column], black, 2);
	}
	else
	{
		strncpy(board[raw][column], white, 2);
	}
}

void get_coordinate(int coordinate[], char board[][17][3], int step_count)
{
	char column_c;//��ĸ��ʽ��������
	int raw, column;
	char black[2] = "��";
	char white[2] = "��";
	int raw_input_index = 0;//����scanf�ķ���ֵ
	bool invalid_coordinate = true;//�ж�ѡ����Ǹ����������ǲ����Ѿ�������������
	bool invalid_raw = true;//�ж������raw�Ƿ�Ϸ�

	while (invalid_coordinate)
	{
		//�������û���������꣬���账��
		printf("��ѡ����һ����������һ�����������磺2\n");

		while (invalid_raw)
		{
			raw_input_index = scanf("%d", &raw);
			while (getchar() != '\n')
				continue;

			if (raw_input_index != 1)
			{
				printf("��Ч���룬������\n");
				continue;
			}

			if (1 > raw || 15 < raw)
			{
				printf("��Ч���룬������\n");
				continue;
			}

			invalid_raw = false;
		}

		//����������ʱ�����޸�
		/*while (getchar() != '\n')
			continue;*/

		printf("������һ�����������磺B\n");
		column_c = getchar();
		while (getchar() != '\n')
			continue;
		while (column_c<'A' || (column_c > 'O'&&column_c < 'a') || column_c>'o')
		{
			printf("��Ч���룬������\n");

			column_c = getchar();
			while (getchar() != '\n')
				continue;

		}

		//�����ǽ��û����������ת��Ϊ������ʶ�������
		column_c = toupper(column_c);
		column = column_c - 64;
		raw = 15 - raw;
		//�ж��Ƿ�������Ѿ���������
		if (strncmp(board[raw][column], black, 2) == 0
			|| strncmp(board[raw][column], white, 2) == 0)
		{
			printf("��λ���Ѿ��������ˣ�������ѡ��һ������\n");
			invalid_raw = true;//��������ڰ�֮ǰraw��ѭ�����ж�ֵ��ʼ����
			//���򲻻�������raw��ѭ��
			continue;
		}
		else
		{
			invalid_coordinate = false;
		}

	}
	
	coordinate[0] = raw;
	coordinate[1] = column;
	
}

void chess_play_ver2(char board[][17][3], int step_count, 
	int coordinate[])
{
	int raw, column;
	char black[2] = "��";
	char white[2] = "��";
	raw = coordinate[0];
	column = coordinate[1];
	if (step_count % 2 == 0)
	{
		strncpy(board[raw][column], black, 2);
	}
	else
	{
		strncpy(board[raw][column], white, 2);
	}

}

void return_to_normal_chess(char board[][17][3], int step_count,
	int coordinate[])
//�˺����������������͵����ӻָ��ɡ����͵�����
{
	int raw, column;
	char black[2] = "��";
	char white[2] = "��";
	raw = coordinate[0];
	column = coordinate[1];
	if (step_count % 2 == 0)
	{
		strncpy(board[raw][column], black, 2);
	}
	else
	{
		strncpy(board[raw][column], white, 2);
	}
}
