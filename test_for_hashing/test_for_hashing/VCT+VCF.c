#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#include"head.h"
#include<time.h>

//��ɱ����
//����ĵ�һά�����������
/*
int fatal_priority[6][32][2] =
{
	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ��Ļ���
		{0,0},{0,0},{0,0},{0,0},{0,0},//����Ļ���
		{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ��ĳ���
		{0,0},{0,0},{0,0},{0,0},{0,0},//����ĳ���
	},
	//��ͬ
	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
	},

	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
	},

	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
	},
	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
	},
	{
		{0,0},//�Լ�������
		{0,0},//�Է�������
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
		{0,0},{0,0},{0,0},{0,0},{0,0},
	}
};
long int fatal_best_score_of_upper[7] = { -89999900 , 89999900 , -89999900, 89999900 , -89999900, 89999900, -89999900 };//��minimax����ļ�֦�õ�
bool fatal_not_in_the_same_branch[7] = { true, true, true, true, true, true, true };
*/
bool find_fatal_point(char board[][17][3], int fatal_priority[][32][2], int floor_vcx,
	int step_count, bool my_turn)
{
	int my_raw = 0;
	int my_column = 0;
	char black[2] = "��";
	char white[2] = "��";
	long int my_value = 0;
	long int opponent_value = 0;
	bool final_hit = false;
	bool find_five = false;
	bool find_opponent_five = false;
	bool find_double_three1 = false;
	bool find_double_three2 = false;
	bool find_double_three3 = false;
	bool find_double_three4 = false;
	bool find_double_three5 = false;
	bool find_opponent_double_three1 = false;
	bool find_opponent_double_three2 = false;
	bool find_opponent_double_three3 = false;
	bool find_opponent_double_three4 = false;
	bool find_opponent_double_three5 = false;
	bool find_CapFour1 = false;
	bool find_CapFour2 = false;
	bool find_CapFour3 = false;
	bool find_CapFour4 = false;
	bool find_CapFour5 = false;
	bool find_opponent_CapFour1 = false;
	bool find_opponent_CapFour2 = false;
	bool find_opponent_CapFour3 = false;
	bool find_opponent_CapFour4 = false;
	bool find_opponent_CapFour5 = false;
	bool find_three1 = false;
	bool find_three2 = false;
	bool find_three3 = false;
	bool find_three4 = false;
	bool find_three5 = false;
	bool find_opponent_three1 = false;
	bool find_opponent_three2 = false;
	bool find_opponent_three3 = false;
	bool find_opponent_three4 = false;
	bool find_opponent_three5 = false;

	//�ȳ�ʼ������֮ǰ��ķ�֧�ù��ļ�¼��Ϊ0

	for (int ele = 0; ele < 32; ele++)
	{
		fatal_priority[FLOOR_VCX - floor_vcx][ele][0] = 0;
		fatal_priority[FLOOR_VCX - floor_vcx][ele][1] = 0;
	}

	//���濪ʼ��ʽ��¼
	for (my_raw = 0; my_raw < 15; my_raw++)
	{
		for (my_column = 1; my_column < 16; my_column++)
		{
			if ((strncmp(board[my_raw][my_column], black, 2) != 0)
				&& (strncmp(board[my_raw][my_column], white, 2) != 0))
			{
				my_value = evaluation(board, step_count, my_turn, my_raw, my_column);
				my_value = labs(my_value);
				opponent_value = evaluation(board, step_count + 1, !my_turn, my_raw, my_column);
				opponent_value = labs(opponent_value);

				if (my_value >= Consecutive_Five)
				{
					if (!find_five)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][0][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][0][1] = my_column;
						find_five = true;
						final_hit = true;
						return final_hit;
					}
				}
				
				else if (my_value >= 2 * Gapped_Three)
				{
					if (!find_double_three1)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][2][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][2][1] = my_column;
						find_double_three1 = true;
					}
					else if (!find_double_three2)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][3][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][3][1] = my_column;
						find_double_three2 = true;
					}
					else if (!find_double_three3)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][4][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][4][1] = my_column;
						find_double_three3 = true;
					}
					else if (!find_double_three4)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][5][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][5][1] = my_column;
						find_double_three4 = true;
					}
					else if (!find_double_three5)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][6][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][6][1] = my_column;
						find_double_three5 = true;
					}


				}
				else if (my_value >= Capped_Four)
				{
					if (!find_CapFour1)//�����һ�����ĵ�λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][22][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][22][1] = my_column;
						find_CapFour1 = true;
					}
					else if (!find_CapFour2)//�����2����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][23][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][23][1] = my_column;
						find_CapFour2 = true;
					}
					else if (!find_CapFour3)//�����3����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][24][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][24][1] = my_column;
						find_CapFour3 = true;
					}
					else if (!find_CapFour4)//�����4����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][25][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][25][1] = my_column;
						find_CapFour4 = true;
					}
					else if (!find_CapFour5)//�����5����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][26][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][26][1] = my_column;
						find_CapFour5 = true;
					}
				}
				else if (my_value >= Open_Three)
				{
					if (!find_three1)//�����һ��������λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][12][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][12][1] = my_column;
						find_three1 = true;
					}
					else if (!find_three2)//�����2����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][13][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][13][1] = my_column;
						find_three2 = true;
					}
					else if (!find_three3)//�����3����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][14][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][14][1] = my_column;
						find_three3 = true;
					}
					else if (!find_three4)//�����4����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][15][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][15][1] = my_column;
						find_three4 = true;
					}
					else if (!find_three5)//�����5����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][16][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][16][1] = my_column;
						find_three5 = true;
					}
				}


				if (opponent_value >= Consecutive_Five)
				{
					if (!find_opponent_five)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][1][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][1][1] = my_column;
						find_opponent_five = true;
						final_hit = true;
						return final_hit;
					}
				}
				else if (opponent_value >= 2 * Gapped_Three)
				{
					if (!find_opponent_double_three1)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][7][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][7][1] = my_column;
						find_opponent_double_three1 = true;
					}
					else if (!find_opponent_double_three2)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][8][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][8][1] = my_column;
						find_opponent_double_three2 = true;
					}
					else if (!find_opponent_double_three3)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][9][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][9][1] = my_column;
						find_opponent_double_three3 = true;
					}
					else if (!find_opponent_double_three4)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][10][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][10][1] = my_column;
						find_opponent_double_three4 = true;
					}
					else if (!find_opponent_double_three5)
					{
						fatal_priority[FLOOR_VCX - floor_vcx][11][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][11][1] = my_column;
						find_opponent_double_three5 = true;
					}
				}
				else if (opponent_value >= Capped_Four)
				{
					if (!find_opponent_CapFour1)//�����һ�����ĵ�λ���ǿյ�
					{//��18��19��20�����������ĵ����꣬Ҳ����17,18,19��λ
						fatal_priority[FLOOR_VCX - floor_vcx][27][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][27][1] = my_column;
						find_opponent_CapFour1 = true;
					}
					else if (!find_opponent_CapFour2)//�����2����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][28][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][28][1] = my_column;
						find_opponent_CapFour2 = true;
					}
					else if (!find_opponent_CapFour3)//�����3����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][29][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][29][1] = my_column;
						find_opponent_CapFour3 = true;
					}
					else if (!find_opponent_CapFour4)//�����4����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][30][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][30][1] = my_column;
						find_opponent_CapFour4 = true;
					}
					else if (!find_opponent_CapFour5)//�����5����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][31][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][31][1] = my_column;
						find_opponent_CapFour5 = true;
					}
				}
				
				else if (opponent_value >= Open_Three)
				{
					if (!find_opponent_three1)//�����һ��������λ���ǿյ�
					{//��24��25��26�����������������꣬Ҳ����23,24,25��λ
						fatal_priority[FLOOR_VCX - floor_vcx][17][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][17][1] = my_column;
						find_opponent_three1 = true;
					}
					else if (!find_opponent_three2)//�����2����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][18][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][18][1] = my_column;
						find_opponent_three2 = true;
					}
					else if (!find_opponent_three3)//�����3����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][19][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][19][1] = my_column;
						find_opponent_three3 = true;
					}
					else if (!find_opponent_three4)//�����4����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][20][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][20][1] = my_column;
						find_opponent_three4 = true;
					}
					else if (!find_opponent_three5)//�����5����λ���ǿյ�
					{
						fatal_priority[FLOOR_VCX - floor_vcx][21][0] = my_raw;
						fatal_priority[FLOOR_VCX - floor_vcx][21][1] = my_column;
						find_opponent_three5 = true;
					}





				}


			}

			if (find_CapFour1
				&& find_CapFour2
				&& find_CapFour3
				&& find_CapFour4
				&& find_CapFour5
				&& find_double_three1
				&& find_double_three2
				&& find_double_three3
				&& find_double_three4
				&& find_double_three5
				&& find_opponent_double_three1
				&& find_opponent_double_three2
				&& find_opponent_double_three3
				&& find_opponent_double_three4
				&& find_opponent_double_three5
				&& find_opponent_CapFour1
				&& find_opponent_CapFour2
				&& find_opponent_CapFour3
				&& find_opponent_CapFour4
				&& find_opponent_CapFour5
				&& find_opponent_three1
				&& find_opponent_three2
				&& find_opponent_three3
				&& find_opponent_three4
				&& find_opponent_three5
				&& find_three1
				&& find_three2
				&& find_three3
				&& find_three4
				&& find_three5)
			{
				return final_hit;
			}

		}




	}

	return final_hit;
}



long int fatal_step(char board[][17][3], int step_count,
	bool my_turn, bool ai_first,
	int floor_vcx, int coordinate[], long int fatal_best_score_of_upper[], int fatal_priority[][32][2], bool fatal_not_in_the_same_branch[])
{
	char black[2] = "��";
	char white[2] = "��";
	char temp_blank[2];//���������ԭ���̣��൱�ڻ���һ����
	char *chess;
	char *opponent_chess;
	bool final_hit = false;
	//bool valid_coordinate = false;
	//�������ڽ���ai���֡��غ����롰�Ƿ����ҷ��غϡ��Ĺ�ϵ

	if ((step_count % 2) == 0)
	{
		chess = black;
		opponent_chess = white;
		if (ai_first)
		{
			my_turn = true;
		}
		else
		{
			my_turn = false;
		}
	}
	else
	{
		chess = white;
		opponent_chess = black;
		if (ai_first)
		{
			my_turn = false;
		}
		else
		{
			my_turn = true;
		}

	}
	long int best_score = 0;
	int best_coordinate[2] = { 0,1 };
	long int temp_score = 0;
	


	if (floor_vcx != 0)
	{
		if (my_turn)
		{

			final_hit = find_fatal_point(board, fatal_priority, floor_vcx, step_count, my_turn);
			//�������˫���forѭ�����ڲ��Ե�ʱ������ģ���ʽʹ�õ�ʱ����Թص�
			
			for (int test_raw = 0; test_raw < 6; test_raw++)
			{
				for (int test_raw2 = 0; test_raw2 < 32; test_raw2++)
				{

					printf("%d,", fatal_priority[test_raw][test_raw2][0]);
					printf("%d", fatal_priority[test_raw][test_raw2][1]);
					printf(" ");
				}
				printf("\n");
			}
			
			
			if (final_hit)
			{
				if (fatal_priority[FLOOR_VCX - floor_vcx][0][0] != 0 || fatal_priority[FLOOR_VCX - floor_vcx][0][1] != 0)
				{
					if (FLOOR_VCX == floor_vcx)
					{
						coordinate[0] = fatal_priority[0][0][0];
						coordinate[1] = fatal_priority[0][0][1];
						best_score = evaluation(board, step_count, my_turn, fatal_priority[0][0][0], fatal_priority[0][0][1]);
						return best_score;
					}
					else
					{
						best_score = evaluation(board, step_count, my_turn, fatal_priority[0][0][0], fatal_priority[0][0][1]);
						return best_score;
					}
				}
				else if (fatal_priority[FLOOR_VCX - floor_vcx][1][0] != 0 || fatal_priority[FLOOR_VCX - floor_vcx][1][1] != 0)
				{
					if (fatal_priority[FLOOR_VCX - floor_vcx][0][0] == 0 && fatal_priority[FLOOR_VCX - floor_vcx][0][1] == 0)
					{
						best_score = evaluation(board, step_count, my_turn, fatal_priority[0][1][0], fatal_priority[0][1][1]);
						return best_score;
					}
				}
			}
			for (int a = 0; a < 32; a++)
			{
				fatal_not_in_the_same_branch[floor_vcx - 1] = true;//�ж��Ƿ���ͬһ��֧�У��������֦
				int raw = fatal_priority[FLOOR_VCX - floor_vcx][a][0];
				int column = fatal_priority[FLOOR_VCX - floor_vcx][a][1];
				if ((raw != 0) || (column != 0))
				{
					if ((strncmp(board[raw][column], chess, 2) != 0)
						&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
					{
						//��ʼ����֦�Ĳ���
						if (floor_vcx - 2 >= 0)
						{
							fatal_best_score_of_upper[floor_vcx - 2] = 89999900;
							//not_in_the_same_branch[floor - 2] = true;
						}
						strncpy(temp_blank, board[raw][column], 2);
						strncpy(board[raw][column], chess, 2);
						//�����⼸�й�ϣ���ȵ�minimax����Ĺ�ϣ�������ٷų���
						//hashing_value_now = hashing_value_now ^ key[raw][column][(step_count % 2)];
						//long int temp_score1 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count, board, my_turn, hashing_value_now);
						//long int temp_score2 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count + 1, board, !my_turn, hashing_value_now);
						//if (temp_score1 == 0 && temp_score2 == 0)

						//�����������ڲ��Ե�ʱ��ʹ�õģ���ʽʹ�õ�ʱ��ص�
						DrawBoard(board, 15, 0, 2, coordinate, step_count);
						
						temp_score = fatal_step(board, step_count + 1,
							!my_turn, ai_first,
							floor_vcx - 1, coordinate, fatal_best_score_of_upper, fatal_priority, fatal_not_in_the_same_branch);

						
						if ((temp_score != 0) && (best_score == 0))
						{
							best_score = temp_score;

						}
						if ((temp_score != 0) && (temp_score >= best_score))
						{
							best_score = temp_score;

							//valid_coordinate = verify_coordinate(board, raw, column, chess, opponent_chess);
							//if ((floor_vcx == FLOOR_VCX)&&valid_coordinate)
							if (floor_vcx == FLOOR_VCX)
								//���������㣬��¼��ʱ����
							{
								best_coordinate[0] = raw;
								best_coordinate[1] = column;
							}
							//�����֦���޸�
							else
							{
								if ((best_score >= fatal_best_score_of_upper[floor_vcx]) && (fatal_not_in_the_same_branch[floor_vcx]))//��֦
								{
									strncpy(board[raw][column], temp_blank, 2);
									return 89999900;
								}

							}
						}
						//��ԭ
						strncpy(board[raw][column], temp_blank, 2);
						if (best_score > fatal_best_score_of_upper[floor_vcx - 1])
						{
							fatal_best_score_of_upper[floor_vcx - 1] = best_score;
							fatal_not_in_the_same_branch[floor_vcx - 1] = false;
						}
						if (best_score == 89999900)
						{
							return best_score;
						}

					}
				}




			}
			
		}
		else
		{
			//best_score_of_upper[floor_vcx] = 0;
			final_hit = find_fatal_point(board, fatal_priority, floor_vcx, step_count, my_turn);
			//�������˫���forѭ�����ڲ��Ե�ʱ������ģ���ʽʹ�õ�ʱ����Թص�

			for (int test_raw = 0; test_raw < 6; test_raw++)
			{
				for (int test_raw2 = 0; test_raw2 < 32; test_raw2++)
				{

					printf("%d,", fatal_priority[test_raw][test_raw2][0]);
					printf("%d", fatal_priority[test_raw][test_raw2][1]);
					printf(" ");
				}
				printf("\n");
			}

			if (final_hit)
			{
				if (fatal_priority[FLOOR_VCX - floor_vcx][1][0] != 0 || fatal_priority[FLOOR_VCX - floor_vcx][1][1] != 0)
				{
					
						best_score = evaluation(board, step_count, my_turn, fatal_priority[0][0][0], fatal_priority[0][0][1]);
						return best_score;
					
				}
				else if (fatal_priority[FLOOR_VCX - floor_vcx][0][0] != 0 || fatal_priority[FLOOR_VCX - floor_vcx][0][1] != 0)
				{
					if (fatal_priority[FLOOR_VCX - floor_vcx][1][0] == 0 && fatal_priority[FLOOR_VCX - floor_vcx][1][1] == 0)
					{
						best_score = evaluation(board, step_count, my_turn, fatal_priority[0][1][0], fatal_priority[0][1][1]);
						return best_score;
					}
				}
			}

			for (int a = 0; a < 32; a++)
			{
				fatal_not_in_the_same_branch[floor_vcx - 1] = true;
				int raw = fatal_priority[FLOOR_VCX - floor_vcx][a][0];
				int column = fatal_priority[FLOOR_VCX - floor_vcx][a][1];
				if ((raw != 0) || (column != 0))
				{
					if ((strncmp(board[raw][column], chess, 2) != 0)
						&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
					{
						//��ʼ����֦�Ĳ���
						if (floor_vcx - 2 >= 0)
						{
							fatal_best_score_of_upper[floor_vcx - 2] = -89999900;
							//not_in_the_same_branch[floor - 2] = true;
						}

						strncpy(temp_blank, board[raw][column], 2);
						strncpy(board[raw][column], chess, 2);
						//�����������ڲ��Ե�ʱ��ʹ�õģ���ʽʹ�õ�ʱ��ص�
						DrawBoard(board, 15, 0, 2, coordinate, step_count);
						temp_score = fatal_step(board, step_count + 1,
							!my_turn, ai_first,
							floor_vcx - 1, coordinate, fatal_best_score_of_upper, fatal_priority, fatal_not_in_the_same_branch);
						if ((temp_score != 0) && (best_score == 0))
						{
							best_score = temp_score;

						}
						if ((temp_score != 0) && (temp_score <= best_score))
						{
							best_score = temp_score;
							//����û���Ǹ�������ж�����Ķ�������Ϊ������ǲ����ܻ���ִ���min�������

							if (floor_vcx == FLOOR_VCX)
								//���������㣬��¼��ʱ����
							{
								best_coordinate[0] = raw;
								best_coordinate[1] = column;
							}
							else
							{
								if ((best_score <= fatal_best_score_of_upper[floor_vcx]) && fatal_not_in_the_same_branch[floor_vcx])//��֦
								{
									strncpy(board[raw][column], temp_blank, 2);
									return -89999900;
								}
							}
						}
						strncpy(board[raw][column], temp_blank, 2);
						if (best_score < fatal_best_score_of_upper[floor_vcx - 1])
						{
							fatal_best_score_of_upper[floor_vcx - 1] = best_score;
							fatal_not_in_the_same_branch[floor_vcx - 1] = false;
						}
						if (best_score == -89999900)
						{
							return best_score;
						}

					}
				}

			}

			
		}

	}
	//��ײ��
	else
	{
		long int temp_score1 = 0;
		long int temp_score2 = 0;
		int best_raw = 0;
		int best_column = 1;
		//����ѵĵ�����ֵ
		if (my_turn)
		{
			temp_score = 0;
			//best_score_of_upper[floor_vcx] = 0;
			for (int raw = 0; raw < 15; raw++)
			{
				for (int column = 1; column < 16; column++)
				{
					if ((strncmp(board[raw][column], chess, 2) != 0)
						&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
					{
						//temp_score = evaluation(board, step_count, my_turn, raw, column);
						temp_score1 = evaluation(board, step_count, my_turn, raw, column);
						temp_score2 = evaluation(board, step_count + 1, !my_turn, raw, column);
						temp_score = temp_score1 + temp_score2;
						if (temp_score != 0)
						{


							if (best_score == 0)
							{
								best_score = temp_score;
								best_raw = raw;
								best_column = column;
							}
							if (temp_score > best_score)
							{
								best_score = temp_score;
								best_raw = raw;
								best_column = column;
								//best_coordinate[0] = raw;
									//best_coordinate[1] = column;
							}
							/*
							if ((best_score < best_score_of_upper[floor_vcx]) && not_in_the_same_branch[floor_vcx])//��֦
							{

								return -89999900;
							}
							*/
						}
					}
				}
			}
		}
		else
		{
			temp_score = 0;
			//best_score_of_upper[floor_vcx] = 0;
			for (int raw = 0; raw < 15; raw++)
			{
				for (int column = 1; column < 16; column++)
				{
					if ((strncmp(board[raw][column], chess, 2) != 0)
						&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
					{
						//temp_score = evaluation(board, step_count, my_turn, raw, column);
						temp_score1 = evaluation(board, step_count, my_turn, raw, column);
						temp_score2 = evaluation(board, step_count + 1, !my_turn, raw, column);
						temp_score = temp_score1 + temp_score2;
						if (temp_score != 0)
						{


							if (best_score == 0)
							{
								best_score = temp_score;
								best_raw = raw;
								best_column = column;

							}

							if (temp_score < best_score)
							{
								best_score = temp_score;
								best_raw = raw;
								best_column = column;
								//best_coordinate[0] = raw;
									//best_coordinate[1] = column;
							}
							/*
							if ((best_score > best_score_of_upper[floor_vcx]) && not_in_the_same_branch[floor_vcx])//��֦
							{

								return 89999900;
							}
							*/
						}
					}

				}
			}
		}
	}

	//����㣬��Ҫ����һ�����վ�������������
	if ((FLOOR_VCX - floor_vcx) == 0)
	{
		*coordinate = *best_coordinate;
		*(coordinate + 1) = *(best_coordinate + 1);
		best_score = evaluation(board, step_count, my_turn, coordinate[0], coordinate[1]);
	}



	//strncpy(board[best_coordinate[0]][best_coordinate[1]], temp_blank, 2);


	return best_score;
}

