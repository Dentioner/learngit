#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

//chess_play这个函数需要重写
//因为评分函数需要调用raw和column的值
//需要将raw和column写成全局变量，然后chess_play用来作为输入变量
void chess_play(char board[][17][3], int step_count)//传递的第二个参数是下了几局了的次数
{
	char column_c;//字母形式的纵坐标
	int raw, column;
	char black[2] = "○";
	char white[2] = "●";
	int raw_input_index = 0;//接收scanf的返回值
	bool invalid_coordinate = true;//判断选择的那个坐标上面是不是已经覆盖了棋子了
	bool invalid_raw = true;//判断输入的raw是否合法

	while (invalid_coordinate)
	{
		//下面是用户输入的坐标，还需处理
		printf("请选择下一步，先输入一个行数，例如：2\n");

		while (invalid_raw)
		{
			raw_input_index = scanf("%d", &raw);
			while (getchar() != '\n')
				continue;

			if (raw_input_index != 1)
			{
				printf("无效输入，请重试\n");
				continue;
			}
			
			if (1 > raw || 15 < raw)
			{
				printf("无效输入，请重试\n");
				continue;
			}

			invalid_raw = false;
		}

		//以下区域暂时不用修改
		/*while (getchar() != '\n')
			continue;*/

		printf("再输入一个列数，例如：B\n");
		column_c = getchar();
		while (getchar() != '\n')
			continue;
		while (column_c<'A' || (column_c > 'O'&&column_c < 'a') || column_c>'o')
		{
			printf("无效输入，请重试\n");

			column_c = getchar();
			while (getchar() != '\n')
				continue;

		}

		//下面是将用户输入的坐标转换为数组能识别的坐标
		column_c = toupper(column_c);
		column = column_c - 64;
		raw = 15 - raw;
		//判断是否该坐标已经有棋子了
		if (strncmp(board[raw][column], black, 2) == 0 
			|| strncmp(board[raw][column], white, 2) == 0)
		{
			printf("该位置已经有棋子了，请重新选择一个坐标\n");
			invalid_raw = true;//这个项用于把之前raw的循环的判断值初始化，
			//否则不会走输入raw的循环
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
	char column_c;//字母形式的纵坐标
	int raw, column;
	char black[2] = "○";
	char white[2] = "●";
	int raw_input_index = 0;//接收scanf的返回值
	bool invalid_coordinate = true;//判断选择的那个坐标上面是不是已经覆盖了棋子了
	bool invalid_raw = true;//判断输入的raw是否合法

	while (invalid_coordinate)
	{
		//下面是用户输入的坐标，还需处理
		printf("请选择下一步，先输入一个行数，例如：2\n");

		while (invalid_raw)
		{
			raw_input_index = scanf("%d", &raw);
			while (getchar() != '\n')
				continue;

			if (raw_input_index != 1)
			{
				printf("无效输入，请重试\n");
				continue;
			}

			if (1 > raw || 15 < raw)
			{
				printf("无效输入，请重试\n");
				continue;
			}

			invalid_raw = false;
		}

		//以下区域暂时不用修改
		/*while (getchar() != '\n')
			continue;*/

		printf("再输入一个列数，例如：B\n");
		column_c = getchar();
		while (getchar() != '\n')
			continue;
		while (column_c<'A' || (column_c > 'O'&&column_c < 'a') || column_c>'o')
		{
			printf("无效输入，请重试\n");

			column_c = getchar();
			while (getchar() != '\n')
				continue;

		}

		//下面是将用户输入的坐标转换为数组能识别的坐标
		column_c = toupper(column_c);
		column = column_c - 64;
		raw = 15 - raw;
		//判断是否该坐标已经有棋子了
		if (strncmp(board[raw][column], black, 2) == 0
			|| strncmp(board[raw][column], white, 2) == 0)
		{
			printf("该位置已经有棋子了，请重新选择一个坐标\n");
			invalid_raw = true;//这个项用于把之前raw的循环的判断值初始化，
			//否则不会走输入raw的循环
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
	char black[2] = "△";
	char white[2] = "▲";
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
//此函数是用来将△类型的棋子恢复成○类型的棋子
{
	int raw, column;
	char black[2] = "○";
	char white[2] = "●";
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
