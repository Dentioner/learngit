#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include"head.h"
#include<time.h>


long int Minimax2(char board[][17][3], int step_count,
	bool my_turn, bool ai_first,
	int floor, int coordinate[], long int best_score_of_upper[], int priority[][26][2], bool not_in_the_same_branch[], 
	long long int hashing_value_now, long long int key[][15][2], long long int hashing_value[][2],
	int fatal_priority[][32][2], long int fatal_best_score_of_upper[], bool fatal_not_in_the_same_branch[])
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
	
	if (floor != 0)
	{
		if (my_turn)
		{
			//best_score_of_upper[floor] = 0;
			//�Ƚ����ȵ���Щ���ҵ����ݹ�
			final_hit = before_evaluation(board, priority, floor, step_count, my_turn);
			
			
			
			//�������˫���forѭ�����ڲ��Ե�ʱ������ģ���ʽʹ�õ�ʱ����Թص�
			/*
			for (int test_raw = 0; test_raw < 10; test_raw++)
			{
				for (int test_raw2 = 0; test_raw2 < 26; test_raw2++)
				{
					
					printf("%d,", priority[test_raw][test_raw2][0]);
					printf("%d", priority[test_raw][test_raw2][1]);
					printf(" ");
				}
				printf("\n");
			}
			*/
			
			if (final_hit
				&&(FLOOR == floor))
			{//������������壬ֱ������
				coordinate[0] = priority[0][0][0];
				coordinate[1] = priority[0][0][1];
				best_score = evaluation(board, step_count, my_turn, priority[0][0][0], priority[0][0][1]);
				return best_score;
			}
			//�������if������¼ӵĵ�������
			if (final_hit && (FLOOR != floor))
			{
				best_score = evaluation(board, step_count, my_turn, priority[0][0][0], priority[0][0][1]);
				return best_score;
			}
			if (!final_hit && (FLOOR == floor))
			{//������ֶԷ������γ����壬�����Լ�û�����壬�Ͻ�����ȥ
				if ((priority[0][1][0] != 0) || (priority[0][1][1]) != 0)
				{
					coordinate[0] = priority[0][1][0];
					coordinate[1] = priority[0][1][1];
					best_score = evaluation(board, step_count, my_turn, priority[0][1][0], priority[0][1][1]);
					return best_score;
				}
				
			}
			//�����ǳ��Լ�����ɱ��Ŀǰֻ�뵽������㿪�ѣ��ڱ�Ĳ���������ʱ�޷�ʵ��
/*
			if (priority[FLOOR - floor][8][0] != 0 || priority[FLOOR - floor][8][1] != 0 
				|| priority[FLOOR - floor][11][0] != 0 || priority[FLOOR - floor][11][1] != 0)//����ҵ���˫�����ĵ�Ļ����ͽ�����ɱ
			{
				if (floor == FLOOR)
				{
					int floor_vcx = FLOOR_VCX;
					int fatal_best_coordinate[2] = { 0,1 };
				
					best_score = fatal_step(board, step_count, my_turn, ai_first, floor_vcx, fatal_best_coordinate, fatal_best_score_of_upper, fatal_priority, fatal_not_in_the_same_branch);
					printf("%d,%d\n", priority[FLOOR - floor][8][0], priority[FLOOR - floor][8][1]);
					printf("%d,%d\n", priority[FLOOR - floor][11][0], priority[FLOOR - floor][11][1]);
					system("pause");
				}
				
			}
			*/

			//else
			//{

			
				for (int a = 0; a < 26; a++)
				{
					not_in_the_same_branch[floor - 1] = true;//�ж��Ƿ���ͬһ��֧�У��������֦
					int raw = priority[FLOOR - floor][a][0];
					int column = priority[FLOOR - floor][a][1];
					if ((raw != 0) || (column != 0))
					{
						if ((strncmp(board[raw][column], chess, 2) != 0)
							&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
						{
							//��ʼ����֦�Ĳ���
							if (floor - 2 >= 0)
							{
								best_score_of_upper[floor - 2] = 89999900;
								//not_in_the_same_branch[floor - 2] = true;
							}
							strncpy(temp_blank, board[raw][column], 2);
							strncpy(board[raw][column], chess, 2);
							hashing_value_now = hashing_value_now ^ key[raw][column][(step_count % 2)];
							//�����������ڲ��Ե�ʱ��ʹ�õģ���ʽʹ�õ�ʱ��ص�
							//DrawBoard(board, 15, 0, 2, coordinate, step_count);
							long int temp_score1 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count, board, my_turn, hashing_value_now);
							long int temp_score2 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count + 1, board, !my_turn, hashing_value_now);
							if (temp_score1 == 0 && temp_score2 == 0)
							{
								temp_score = Minimax2(board, step_count + 1,
									!my_turn, ai_first,
									floor - 1, coordinate, best_score_of_upper, priority, not_in_the_same_branch, hashing_value_now, key, hashing_value, fatal_priority, fatal_best_score_of_upper, fatal_not_in_the_same_branch);
							}
							else
							{
								temp_score = temp_score1 + temp_score2;
							}
							//�����������ڲ��Ե�ʱ��ʹ�õģ���ʽʹ�õ�ʱ��ص�
							//DrawBoard(board, 15, 0, 2, coordinate, step_count);
							if ((temp_score != 0) && (best_score == 0))
							{
								best_score = temp_score;

							}
							if ((temp_score != 0) && (temp_score >= best_score))
							{
								best_score = temp_score;

								//valid_coordinate = verify_coordinate(board, raw, column, chess, opponent_chess);
								//if ((floor == FLOOR)&&valid_coordinate)
								if (floor == FLOOR)
									//���������㣬��¼��ʱ����
								{
									best_coordinate[0] = raw;
									best_coordinate[1] = column;
								}
								//�����֦���޸�
								else
								{
									if ((best_score >= best_score_of_upper[floor])&&(not_in_the_same_branch[floor]))//��֦
									{
										strncpy(board[raw][column], temp_blank, 2);
										return 89999900;
									}
								
								}
							}
							//��ԭ
							strncpy(board[raw][column], temp_blank, 2);
							Zobrist_hashing(hashing_value, key, raw, column, true, step_count, board, my_turn, hashing_value_now);
							hashing_value_now = hashing_value_now ^ key[raw][column][(step_count % 2)];
							if (best_score > best_score_of_upper[floor - 1])
							{
								best_score_of_upper[floor - 1] = best_score;
								not_in_the_same_branch[floor - 1] = false;
							}
							if (best_score == 89999900)
							{
								return best_score;
							}
						
						}
					}

				


				}
		
			//}
		}
		else
		{
			//best_score_of_upper[floor] = 0;
			final_hit = before_evaluation(board, priority, floor, step_count, my_turn);
			

			
			//�������˫���forѭ�����ڲ��Ե�ʱ������ģ���ʽʹ�õ�ʱ����Թص�
			/*
			for (int test_raw = 0; test_raw < 10; test_raw++)
			{
				for (int test_raw2 = 0; test_raw2 < 26; test_raw2++)
				{
					
					printf("%d,", priority[test_raw][test_raw2][0]);
					printf("%d", priority[test_raw][test_raw2][1]);
					printf(" ");
				}
				printf("\n");
			}
			*/

			//�������if���¼ӵĵ�������
			if (!final_hit)
			{
				if ((priority[FLOOR - floor][1][0] != 0) || (priority[FLOOR- floor][1][1]) != 0)
				{
					
					best_score = evaluation(board, step_count, my_turn, priority[FLOOR - floor][1][0], priority[FLOOR - floor][1][1]);
					return best_score;
				}

			}
			//�������else if ��ʵ���Դ���֤����������һ��
			
			else if (final_hit)
			{
				if ((priority[FLOOR - floor][1][0] == 0) && ((priority[FLOOR - floor][1][1]) == 0))
				{
					best_score = evaluation(board, step_count, my_turn, priority[FLOOR - floor][0][0], priority[FLOOR - floor][0][1]);
					return best_score;
				}
			}
			
				for (int a = 0; a < 26; a++)
				{
					not_in_the_same_branch[floor - 1] = true;
					int raw = priority[FLOOR - floor][a][0];
					int column = priority[FLOOR - floor][a][1];
					if ((raw != 0) || (column != 0))
					{
						if ((strncmp(board[raw][column], chess, 2) != 0)
							&& (strncmp(board[raw][column], opponent_chess, 2) != 0))
						{
							//��ʼ����֦�Ĳ���
							if (floor - 2 >= 0)
							{
								best_score_of_upper[floor - 2] = -89999900;
								//not_in_the_same_branch[floor - 2] = true;
							}
							strncpy(temp_blank, board[raw][column], 2);
							strncpy(board[raw][column], chess, 2);
							hashing_value_now = hashing_value_now ^ key[raw][column][(step_count % 2)];
							long int temp_score1 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count, board, my_turn, hashing_value_now);
							long int temp_score2 = Zobrist_hashing(hashing_value, key, raw, column, false, step_count + 1, board, !my_turn, hashing_value_now);
						
							//����������ڲ��Ե�ʱ������ģ���ʽʹ�õ�ʱ����Թص�
							//DrawBoard(board, 15, 0, 2, coordinate, step_count);
							if (temp_score1 == 0 && temp_score2 == 0)
							{
								temp_score = Minimax2(board, step_count + 1,
									!my_turn, ai_first,
									floor - 1, coordinate, best_score_of_upper, priority, not_in_the_same_branch, hashing_value_now, key, hashing_value, fatal_priority, fatal_best_score_of_upper, fatal_not_in_the_same_branch);
							}
							else
							{
								temp_score = temp_score1 + temp_score2;
							}
							if ((temp_score != 0) && (best_score == 0))
							{
								best_score = temp_score;

							}
							if ((temp_score != 0) && (temp_score <= best_score))
							{
								best_score = temp_score;
								//����û���Ǹ�������ж�����Ķ�������Ϊ������ǲ����ܻ���ִ���min�������

								if (floor == FLOOR)
									//���������㣬��¼��ʱ����
								{
									best_coordinate[0] = raw;
									best_coordinate[1] = column;
								}
								else
								{
									if ((best_score <= best_score_of_upper[floor])&&not_in_the_same_branch[floor])//��֦
									{
										strncpy(board[raw][column], temp_blank, 2);
										return -89999900;
									}
								}
							}
							strncpy(board[raw][column], temp_blank, 2);
							Zobrist_hashing(hashing_value, key, raw, column, true, step_count, board, my_turn, hashing_value_now);
							hashing_value_now = hashing_value_now ^ key[raw][column][(step_count % 2)];
							if (best_score > best_score_of_upper[floor - 1])
							{
								best_score_of_upper[floor - 1] = best_score;
								not_in_the_same_branch[floor - 1] = false;
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
		//int floor_vcx = FLOOR_VCX;//�������ɱר��floor
		//int fatal_best_coordinate[2] = { 0,1 };
		//����ѵĵ�����ֵ
		if (my_turn)
		{
			temp_score = 0;
			//best_score_of_upper[floor] = 0;
			//��������ϣ������оͲ������
			temp_score1 = Zobrist_hashing(hashing_value, key, best_raw, best_column, false, step_count, board, my_turn, hashing_value_now);
			temp_score2 = Zobrist_hashing(hashing_value, key, best_raw, best_column, false, step_count + 1, board, !my_turn, hashing_value_now);
			if (temp_score1 == 0 && temp_score2 == 0)
			{//�����ϣ��û��ֵ
				//����������ײ������ɱ�����ð棬Ŀǰ����
				/*
				temp_score = fatal_step(board, step_count, my_turn, ai_first, floor_vcx, fatal_best_coordinate, fatal_best_score_of_upper, fatal_priority, fatal_not_in_the_same_branch);
				if (fatal_best_coordinate[0] == 0 && fatal_best_coordinate[1] == 0)
				{*/

				
				
					//���forѭ����һ��ʼ���еģ���������ɾ��
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
									if ((best_score < best_score_of_upper[floor]) && not_in_the_same_branch[floor])//��֦
									{

										return -89999900;
									}
									*/
								}
							}
						}
					}
				//��������������Ǻ�������Ǹ���ɱif���׵�
				//}
				//�������Ҳ�Ƿ�������ɱ
				/*
				else
				{
					best_score = evaluation(board, step_count, my_turn, fatal_best_coordinate[0], fatal_best_coordinate[1]);
				}*/

				//��ѭ�������󣬽���ѵ������������ϣ������
				Zobrist_hashing(hashing_value, key, best_raw, best_column, true, step_count, board, my_turn, hashing_value_now);
				
			
			
			}
			/*
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
							if ((best_score < best_score_of_upper[floor]) && not_in_the_same_branch[floor])//��֦
							{

								return -89999900;
							}
							*/
				

			else
			{
				best_score = temp_score1 + temp_score2;
			}
				
			
			
			
			
		
		}
		else
		{
			temp_score = 0;
			temp_score1 = Zobrist_hashing(hashing_value, key, best_raw, best_column, false, step_count, board, my_turn, hashing_value_now);
			temp_score2 = Zobrist_hashing(hashing_value, key, best_raw, best_column, false, step_count + 1, board, !my_turn, hashing_value_now);
			
			if (temp_score1 == 0 && temp_score2 == 0)
			{
				//����������ײ������ɱ�����ð�
				/*
				temp_score = fatal_step(board, step_count, my_turn, ai_first, floor_vcx, fatal_best_coordinate, fatal_best_score_of_upper, fatal_priority, fatal_not_in_the_same_branch);
				if (fatal_best_coordinate[0] == 0 && fatal_best_coordinate[1] == 0)
					//best_score_of_upper[floor] = 0;
				{*/

					//�������forѭ����ɾ��
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
									if ((best_score > best_score_of_upper[floor]) && not_in_the_same_branch[floor])//��֦
									{

										return 89999900;
									}
									*/
								}
							}
			
						}
					}
				//�������Ҳ����ɱ��
				/*}
				
				else
				{
					best_score = evaluation(board, step_count, my_turn, fatal_best_coordinate[0], fatal_best_coordinate[1]);
				}
				*/


				//��ѭ�������󣬽���ѵ������������ϣ������
				Zobrist_hashing(hashing_value, key, best_raw, best_column, true, step_count, board, my_turn, hashing_value_now);

			
			
			}
			else
			{
				best_score = temp_score1 + temp_score2;
			}

		}
	}

	//����㣬��Ҫ����һ�����վ�������������
	if ((FLOOR - floor) == 0)
	{
		*coordinate = *best_coordinate;
		*(coordinate + 1) = *(best_coordinate + 1);
		best_score = evaluation(board, step_count, my_turn, coordinate[0], coordinate[1]);
	}



//strncpy(board[best_coordinate[0]][best_coordinate[1]], temp_blank, 2);
	
	
	return best_score;
}
