#define FLOOR 5
#define FLOOR_VCX 3
//ÿ�θ���FLOOR����Ҫ��board.c�е�priority, best_score_of_upper, not_in_the_same_branch����������Ĵ�С��һ��
#define Consecutive_Five 10000000//����
#define Open_Four 1000000//����
#define Open_Three 100000//����
#define Gapped_Two_Two 100050//�������ֶ��ǳ��ģ�����������2��֮��ȱ��һ����  ��񣿡��
#define Capped_Four 100050//���ֳ�����һͷ����ס�ĳ���   ������͡�����
#define Gapped_Four 100050//���ֳ�����һ��������һ����������֮�����һ��  ��?����
#define Gapped_Three 99950//���������������Ǽ����γɻ��ĵ���  �񣿡��
#define Capped_Three 10000//����, ���ֻ���γɳ���  �����
//��Ҫ�����Ĵ���� ���1000��
/*����һ�����⼸����̬��
1. �����__
2. ����_��_
3. ���_���_
4. ���__��
5. ��_��_��
6. ��_����_��
*/
#define Open_two 1000//����
#define depth_of_hashing 100000
void DrawBoard(char board[][17][3], int i, long int value, int mode_choice, int coordinate[], int step_count);
void chess_play(char **board, int step_count);
bool judgement(char board[][17][3], int step_count);
long int evaluation(char board[][17][3], int step_count, bool my_turn, int raw, int column);
void get_coordinate(int coordinate[], char board[][17][3], int step_count);
void chess_play_ver2(char board[][17][3], int step_count, int coordinate[]);
long int Minimax2(char board[][17][3], int step_count, bool my_turn, bool ai_first, int floor, int coordinate[], long int best_score_of_upper[], int priority[][26][2], bool not_in_the_same_branch[], long long int hashing_value_now, long long int key[][15][2], long long int hashing_value[][2], int fatal_priority[][32][2], long int fatal_best_score_of_upper[], bool fatal_not_in_the_same_branch[]);
void auto_play(char board[][17][3], char chess[], char opponent_chess[], int coordinate[]);
bool verify_coordinate(char board[][17][3], int raw, int column, char chess, char opponent_chess);
bool before_evaluation(char board[][17][3], int priority[][26][2], int floor, int step_count, bool my_turn);
void return_to_normal_chess(char board[][17][3], int step_count, int coordinate[]);
void initialize_hashing_sheet(long long int key[][15][2]);
long int Zobrist_hashing(long long int hashing_value[][2], long long int key[][15][2], int best_raw, int best_column, bool write_new_coordinate, int step_count, char board[][17][3], bool my_turn, long long int hashing_value_now);
bool find_fatal_point(char board[][17][3], int fatal_priority[][32][2], int floor_vcx, int step_count, bool my_turn);
long int fatal_step(char board[][17][3], int step_count, bool my_turn, bool ai_first, int floor_vcx, int coordinate[], long int fatal_best_score_of_upper[], int fatal_priority[][32][2], bool fatal_not_in_the_same_branch[]);

