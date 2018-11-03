#include <stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include<math.h>
#include"head.h"
#include<time.h>

//ע��д��֮��Ҫ������ʦ���Ĺ淶�����Ż���������������doc�ļ�
void main()
{
	int step_count = 0; //��Ϸ���˼����ӵļ���
	bool my_turn = true; //��ʱ�ò��ϣ����������ȷ����һ������һ��������
	bool continue_playing = true; //ȷ����Ϸ�Ƿ����
	bool ai_first = false;//Ĭ�ϵ��Ժ���
	bool invalid_mode = true;
	long int value = 0;//���ֺ����Ĵ��
	long int my_value = 0;//�ҷ��÷�
	long int opponent_value = 0;//�Է��÷�

	int mode_choice;
	int mode_choice_index;


	char board[15][17][3] =
	{
		{"15","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","15"},
		{"14","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","14"},
		{"13","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","13"},
		{"12","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","12"},
		{"11","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","11"},
		{"10","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","10"},
		{"9","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","9"},
		{"8","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","8"},
		{"7","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","7"},
		{"6","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","6"},
		{"5","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","5"},
		{"4","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","4"},
		{"3","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","3"},
		{"2","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","2"},
		{"1","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","1"}

	};

	int coordinate[2] = { 0, 0 };
	char black[3] = "��";
	char white[3] = "��";
	char roaming[3] = "��";//��㶨���һ���������������¼��һ���Ŀո����ĸ�λ�ã����ڻ���
	//����׼��дһ���ж���PVP����PVE�����
		//�����PVE��ѡ����ӻ��ǰ���
	printf("************************************************\n");
	printf("��ѡ��ģʽ\n");
	printf("1.pvp\t\t2.pve\n");
	printf("************************************************\n");
	while (invalid_mode)
	{

		mode_choice_index = scanf("%d", &mode_choice);
		while (getchar() != '\n')
			continue;
		if (mode_choice_index != 1)
		{
			printf("��Ч���룬������\n");

			continue;
		}
		if ((mode_choice != 1) && (mode_choice != 2))
		{
			printf("��Ч���룬������\n");

			continue;
		}

		invalid_mode = false;
	}

	if (mode_choice == 1)
	{
		DrawBoard(board, 15, value, mode_choice, coordinate, -1);
		while (continue_playing)
		{
			
			
			//chess_play(board, step_count);�ϵ�chessplay����
			get_coordinate(coordinate, board, step_count);
			strncpy(roaming, board[coordinate[0]][coordinate[1]], 2);//��¼��һ����״̬
			chess_play_ver2(board, step_count, coordinate);
			value = evaluation(board, step_count, my_turn, coordinate[0], coordinate[1]);
			//my_value = evaluation(board, step_count, my_turn, coordinate[0], coordinate[1]);
			//opponent_value = evaluation(board, step_count + 1, !my_turn, coordinate[0], coordinate[1]);
			//value = my_value + opponent_value;
			//��������ֿ���ֵĿ���������
			DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
			return_to_normal_chess(board, step_count, coordinate, coordinate);
			printf("�Ƿ���Ҫ���壿��y���壬��������������������Ϸ.\n");
			char c_getback = ' ';
			c_getback = getchar();
			while (getchar() != '\n')
				continue;
			int i_getback = c_getback;
			if (i_getback == 89 || i_getback == 121)
			{
				strncpy(board[coordinate[0]][coordinate[1]], roaming, 2);
				DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
				continue;
			}
			continue_playing = judgement(board, step_count);
			my_turn = !my_turn;
			step_count++;
		}
		DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
		if (step_count % 2)
		{
			printf("���ӻ�ʤ");
		}
		else
		{
			printf("���ӻ�ʤ");
		}

		return;
	}


	else
	{
		//PVE

		printf("�������ֻ��ǶԷ����֣�\n");
		printf("1.��������\t\t2.�Է�����\n");
		printf("************************************************\n");
		int ai_choice = 0;
		int ai_choice_index = 0;
		int floor = FLOOR;//��������
		char *chess;
		char *opponent_chess;
		bool invalid_ai_choice = true;
		//���漸��������zobrist��ϣ�㷨ʹ�õ�
		long long int key[15][15][2] = { 0 };//����ά�ȷֱ������ӺͰ��ӣ�0Ϊ�հ�
		long long int hashing_value[depth_of_hashing][3] = { {0,0,0} };
		//�ڶ�ά�ȵ�[0]���������̵Ĺ�ϣֵ��[1]��[2]�Ǵ˹�ϣֵ��Ӧ���������֣�Ӧ�ö����ں�������
		long long int hashing_value_now = 0;//Ŀǰ�Ĺ�ϣֵ�������Ҫ��minimax.c������������
		while (invalid_ai_choice)
		{
			ai_choice_index = scanf("%d", &ai_choice);
			while (getchar() != '\n')
				continue;
			if (ai_choice_index != 1)
			{
				printf("��Ч���룬������\n");

				continue;
			}
			if ((ai_choice != 1) && (ai_choice != 2))
			{
				printf("��Ч���룬������\n");

				continue;
			}

			invalid_ai_choice = false;
		}

		if (ai_choice == 1)
		{
			ai_first = true;
		}
		else
		{
			ai_first = false;
		}

		if (ai_first)
		{
			my_turn = true;
			chess = black;
			opponent_chess = white;
			strncpy(board[7][8], chess, 2);
			my_turn = false;
			step_count++;
		}
		else
		{
			my_turn = false;
			chess = white;
			opponent_chess = black;

		}
		DrawBoard(board, 15, value, mode_choice, coordinate, -1);
		initialize_hashing_sheet(key);
		while (continue_playing)
		{
			
			//ע���������轫my_turn���ˣ��ڦ��¼�֦�������Ѿ�����
			int priority[10][26][2] =
			{
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},

				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},

				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},

				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				},
				{
					{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
					{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},//����
				}
			};//����˫��ֻ��Ҫ1�������ġ�˫���������ġ����������������꣨�ݶ���
			//��һ�������ʾ���ǣ�minimax���������Ĳ�����ÿһ����һ����ά�ȵ�����
			//�ڶ���������������ζ�Ӧ�������ǣ�
			//�ҷ����壬�Է����壬�ҷ���˫�����ģ��Է���˫�����ģ�������������Ҫ��һ��ϸ�֣�
			//�ҷ�˫�������Է�˫�������ҷ����ģ��Է����ģ��ҷ��������Է�����
			//��������Ǻ���������
			long int best_score_of_upper[11] = { -89999900 , 89999900 , -89999900, 89999900 , -89999900, 89999900, - 89999900 , 89999900 , -89999900, 89999900, -89999900 };//��minimax����ļ�֦�õ�
			//ע����������������ı�����⡣floor�Ǵ�11��0�ݹ�ģ����Ҫ�������һ��Ԫ�ز��䡣
			bool not_in_the_same_branch[11] = { true, true, true, true, true, true, true, true, true, true, true };
			//����3����fatal_��ͷ����ɱ��ר�õ�����
			int fatal_priority[6][32][2] =
			{
				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ��Ļ���
					{0,0},{0,0},{0,0},{0,0},{0,0},//����Ļ���
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ��ĳ���
					{0,0},{0,0},{0,0},{0,0},{0,0},//����ĳ���
				},
				//��ͬ
				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
				},

				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
				},

				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
				},
				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
				},
				{
					{0,0},//�Լ�������
					{0,0},//�Է�������
					{0,0},{0,0},{0,0},{0,0},{0,0},//�Լ���˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},//�����˫����
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
					{0,0},{0,0},{0,0},{0,0},{0,0},
				}
			};
			long int fatal_best_score_of_upper[7] = { -89999900 , 89999900 , -89999900, 89999900 , -89999900, 89999900, -89999900 };
			bool fatal_not_in_the_same_branch[7] = { true, true, true, true, true, true, true };
			if (my_turn)
			{
				double start_time = clock();
				double end_time, cost_time;
				if (step_count > 2)
				{
					value = Minimax2(board, step_count, my_turn, ai_first, floor, coordinate, best_score_of_upper, priority, not_in_the_same_branch, hashing_value_now, key, hashing_value, fatal_priority, fatal_best_score_of_upper, fatal_not_in_the_same_branch);
					if ((coordinate[0] == 0) && (coordinate[1] == 1))
					{
						auto_play(board, chess, opponent_chess, coordinate);
						chess_play_ver2(board, step_count, coordinate);
						hashing_value_now = hashing_value_now ^ key[coordinate[0]][coordinate[1]][(step_count % 2)];
						DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
						return_to_normal_chess(board, step_count, coordinate, coordinate);
					}
					else
					{
						chess_play_ver2(board, step_count, coordinate);
						hashing_value_now = hashing_value_now ^ key[coordinate[0]][coordinate[1]][(step_count % 2)];
						DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
						return_to_normal_chess(board, step_count, coordinate, coordinate);
					}

				}
				else
				{
					auto_play(board, chess, opponent_chess, coordinate);
					chess_play_ver2(board, step_count, coordinate);
					hashing_value_now = hashing_value_now ^ key[coordinate[0]][coordinate[1]][(step_count % 2)];
					DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
					return_to_normal_chess(board, step_count, coordinate, coordinate);
					/*for (int p = 0; p < 15; p++)
					{
						for (int q = 0; q < 17; q++)
						{
							if ((strncmp(board[p][q], opponent_chess, 2)) == 0)
							{
								if (((strncmp(board[p + 1][q], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p + 1][q], chess, 2)) != 0))
								{
									strncpy(board[p + 1][q], chess, 2);

								}
								else if (((strncmp(board[p][q + 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p][q + 1], chess, 2)) != 0))
								{
									strncpy(board[p][q + 1], chess, 2);
								}
								else if (((strncmp(board[p - 1][q], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p - 1][q], chess, 2)) != 0))
								{
									strncpy(board[p - 1][q], chess, 2);
								}
								else if (((strncmp(board[p][q - 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p][q - 1], chess, 2)) != 0))
								{
									strncpy(board[p][q - 1], chess, 2);
								}
								else if (((strncmp(board[p - 1][q - 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p - 1][q - 1], chess, 2)) != 0))
								{
									strncpy(board[p - 1][q - 1], chess, 2);
								}
								else if (((strncmp(board[p - 1][q + 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p - 1][q + 1], chess, 2)) != 0))
								{
									strncpy(board[p - 1][q + 1], chess, 2);
								}
								else if (((strncmp(board[p + 1][q + 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p + 1][q + 1], chess, 2)) != 0))
								{
									strncpy(board[p + 1][q + 1], chess, 2);
								}
								else if (((strncmp(board[p + 1][q - 1], opponent_chess, 2)) != 0)
									&& ((strncmp(board[p + 1][q - 1], chess, 2)) != 0))
								{
									strncpy(board[p + 1][q - 1], chess, 2);
								}
							}
						}
					}*/
				}
				end_time = clock();
				cost_time = (end_time - start_time) / CLK_TCK;
				printf("time=%fs.\n", cost_time);
				//printf("��ͣ�У���enter������");
				//system("pause");
			}
			else
			{
				get_coordinate(coordinate, board, step_count);
				//��value��chessplay����λ���ˣ���֪��������
				strncpy(roaming, board[coordinate[0]][coordinate[1]], 2);//��¼��һ����״̬
				value = evaluation(board, step_count, my_turn, coordinate[0], coordinate[1]);
				chess_play_ver2(board, step_count, coordinate);
				hashing_value_now = hashing_value_now ^ key[coordinate[0]][coordinate[1]][(step_count % 2)];
				DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
				return_to_normal_chess(board, step_count, coordinate, coordinate);
				//�����ǻ�����룬���ܻ�������			
				printf("�Ƿ���Ҫ���壿��y���壬��������������������Ϸ.\n");
				char c_getback = ' ';
				c_getback = getchar();
				while (getchar() != '\n')
					continue;
				int i_getback = c_getback;
				if (i_getback == 89 || i_getback == 121)
				{
					strncpy(board[coordinate[0]][coordinate[1]], roaming, 2);
					hashing_value_now = hashing_value_now ^ key[coordinate[0]][coordinate[1]][(step_count % 2)];
					DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
					continue;
				}
			
			}

			continue_playing = judgement(board, step_count);
			my_turn = !my_turn;
			step_count++;
		}
		DrawBoard(board, 15, value, mode_choice, coordinate, step_count);
		if (step_count % 2)
		{
			printf("���ӻ�ʤ");
		}
		else
		{
			printf("���ӻ�ʤ");
		}

		return;




	}

}

void DrawBoard(char board[][17][3], int i, long int value, int mode_choice, int coordinate[], int step_count)
{
	char c_column;
	int i_raw;
	i_raw = 15 - coordinate[0];
	c_column = 64 + coordinate[1];
	char *mode;
	if (mode_choice == 1)
	{
		mode = "PVP";
	}
	else
	{
		mode = "PVE";
	}
	system("cls");   //����
	printf("  ==Welcome to FiveInRow Game==\n");
	printf("          ==%s mode==\n\n", mode);



	printf("   A B C D E F G H I J K L M N O \n");



	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			for (int k = 0; k < 2; k++)
				putchar(board[i][j][k]);
		}
		putchar('\n');
	}
	printf("   A B C D E F G H I J K L M N O \n");
	//system("pause");
	if (step_count != -1)
	{ 
		printf("�������(%d, %c), value = %ld\n", i_raw, c_column, value);
	}
	
	
}
