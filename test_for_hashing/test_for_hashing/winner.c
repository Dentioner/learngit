#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool judgement(char board[][17][3], int step_count)
//����������һ�������̣���һ���ǲ����������ж�����һ��Ӯ
//����ֵ����ɲ�����
{
	int i, j, k;
	bool continue_playing = true;
	bool not_full = false;//�������ֵ�����жϣ������Ƿ�������
	char black[2] = "��";
	char white[2] = "��";
	char *chess;
	if (step_count % 2)//���step����������2�Ļ������ǰ���
	{
		chess = white;
	}
	else
	{
		chess = black;
	}
	
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 17; j++)
	//������ˮƽ����������ӵ��ж�
		{
			if ((strncmp(board[i][j], chess, 2) == 0)
				&& (strncmp(board[i][j + 1], chess, 2) == 0)
				&& (strncmp(board[i][j + 2], chess, 2) == 0)
				&& (strncmp(board[i][j + 3], chess, 2) == 0)
				&& (strncmp(board[i][j + 4], chess, 2) == 0))
			{
				continue_playing = false;
			}
	//��������ֱ����������ӵ��ж�
			if ((strncmp(board[i][j], chess, 2) == 0)
				&& (strncmp(board[i + 1][j], chess, 2) == 0)
				&& (strncmp(board[i + 2][j], chess, 2) == 0)
				&& (strncmp(board[i + 3][j], chess, 2) == 0)
				&& (strncmp(board[i + 4][j], chess, 2) == 0))
			{
				continue_playing = false;
			}
	//��������������б�ߵ������ж�
			if ((strncmp(board[i][j], chess, 2) == 0)
				&& (strncmp(board[i+1][j + 1], chess, 2) == 0)
				&& (strncmp(board[i+2][j + 2], chess, 2) == 0)
				&& (strncmp(board[i+3][j + 3], chess, 2) == 0)
				&& (strncmp(board[i+4][j + 4], chess, 2) == 0))
			{
				continue_playing = false;
			}

	//��������������б�ߵ������ж�
			if ((strncmp(board[i][j], chess, 2) == 0)
				&& (strncmp(board[i+1][j -1], chess, 2) == 0)
				&& (strncmp(board[i+2][j -2], chess, 2) == 0)
				&& (strncmp(board[i+3][j - 3], chess, 2) == 0)
				&& (strncmp(board[i+4][j - 4], chess, 2) == 0))
			{
				continue_playing = false;
			}
		}
	}

	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 17; j++)
		{
			if ((strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0)
				|| (strncmp(board[i][j], "��", 2) == 0))
			{
				not_full = true;
			}
		}
	}

	if (not_full == false)
		continue_playing = false;

	return continue_playing;

}