#include "ALL.h"

Stack* top;
int main()
{
	srand((unsigned int)time(NULL));
	int** check_list;
	Graph** city;
	int size;
	int i;
	int plane_cnt[4] = { 0 };
	top = Add_new_node();

	city = Make_City();
	size = _msize(city) / sizeof(Graph*);
	check_list = (int**)malloc(size * sizeof(int*));
	for (i = 0; i < size; i++)
		check_list[i] = (int*)calloc(size, sizeof(int));

	Input_Apt(city);
	Input_Link(city);
	City_Planning_Simulation(city, check_list, plane_cnt);
	for (i = 0; i < 4; i++)
		printf("%d", plane_cnt[i]);
	//������ ��鿡 �̾����� ����Ʈ ������ ��� ���� ����
	//��谪�� ������ �κ� ó��
	

}