#include"ALL.h"

#ifdef ACTUAL
extern Stack* top;

Stack* Add_new_node()
{
	Stack* temp = (Stack*)malloc(sizeof(Stack));
	temp->G_link = NULL;
	temp->S_link = NULL;

	return temp;
}

void Push_Link(Graph* node)
{
	Stack* temp = Add_new_node();
	temp->G_link = node;

	temp->S_link = top->S_link;
	top->S_link = temp;
}

Graph* Pop_Link()
{
	Stack* S_temp = top->S_link;
	Graph* G_temp = top->S_link->G_link;

	top->S_link = S_temp->S_link;
	free(S_temp);

	return  G_temp;
}

void Push_ROWCOL(Point P_temp)
{
	Stack* temp = Add_new_node();
	temp->R_C = P_temp;

	temp->S_link = top->S_link;
	top->S_link = temp;
}

Point Pop_ROWCOL()
{
	Stack* S_temp = top->S_link;
	Point P_temp = top->S_link->R_C;

	top->S_link = S_temp->S_link;
	
	return  P_temp;
}

int IS_Empty()
{
	return top->S_link == NULL;
}

Graph** Make_City()
{
	int i, j;
	Graph** node;
	//int size = rand() % (SIZE_END - SIZE_START + 1) + SIZE_START;
	int size = 6;
	node = (Graph**)malloc(size * sizeof(Graph*));
	for (i = 0; i < size; i++)
	{
		node[i] = (Graph*)malloc(size * sizeof(Graph));
		for (j = 0; j < size; j++)
		{
			node[i][j].link = (Graph**)malloc(NUM_OF_LINK * sizeof(Graph*));
			node[i][j].OX = 0;
		}
	}

	return node;
}

void Input_Apt(Graph** city)
{
	int i, j;
	int cnt = 0;
	int size = _msize(city) / sizeof(Graph*);
	//int ary[6][6] = { {1,1,0,0,0,1},{1,0,1,0,0,1},{0,1,1,0,1,1},{1,0,0,0,0,1},{1,1,0,1,0,1},{0,1,0,1,0,0} };
	
	/*
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			//city[i][j].OX = rand() % 2;
			city[i][j].OX = ary[i][j];
		}
	}
	*/
	///*
	while (1)
	{
		city[rand() % size][rand() % size].OX = 1;
		cnt++;

		if (cnt == NUM_OF_APT)
			break;
	}
	//*/
}

void Input_Link(Graph** city)
{
	int i, j, idx;
	int link_i, link_j;
	int i_flag = 0, j_flag = 0;
	int size = _msize(city) / sizeof(Graph*);

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			for (idx = 0; idx < NUM_OF_LINK; idx++)
			{
				switch (idx)
				{
				case 0:
					link_i = i;
					link_j = j + 1;

					if (link_i >= 0 && link_i < size)
						i_flag = TRUE;
					else
						i_flag = FALSE;
					if (link_j >= 0 && link_j < size)
						j_flag = TRUE;
					else
						j_flag = FALSE;
					break;
				case 1:
					link_i = i + 1;
					link_j = j;
					
					if (link_i >= 0 && link_i < size)
						i_flag = TRUE;
					else
						i_flag = FALSE;
					if (link_j >= 0 && link_j < size)
						j_flag = TRUE;
					else
						j_flag = FALSE;
					break;
				case 2:
					link_i = i;
					link_j = j - 1;
					
					if (link_i >= 0 && link_i < size)
						i_flag = TRUE;
					else
						i_flag = FALSE;
					if (link_j >= 0 && link_j < size)
						j_flag = TRUE;
					else
						j_flag = FALSE;
					break;
				case 3:
					
					link_i = i - 1;
					link_j = j;
					if (link_i >= 0 && link_i < size)
						i_flag = TRUE;
					else
						i_flag = FALSE;
					if (link_j >= 0 && link_j < size)
						j_flag = TRUE;
					else
						j_flag = FALSE;
					break;
				}

				if (i_flag == TRUE && j_flag == TRUE)
					city[i][j].link[idx] = &city[link_i][link_j];
				else
					city[i][j].link[idx] = NULL;

				i_flag = 0;
				j_flag = 0;
				link_i = 0;
				link_j = 0;
			}
		}
	}

}

void City_Planning_Simulation(Graph **city, int **check_list, int *plane_cnt)
{
	int size = _msize(city) / sizeof(Graph*);
	int idx;
	int break_flag = 0;
	int local_break = 0;
	int print_i, print_j;
	Graph* temp;
	Point P_temp;

	int i = 0, j = 0;
	while (1)
	{
		for (print_i = 0; print_i < size; print_i++)
		{
			for (print_j = 0; print_j < size; print_j++)
			{
				if (check_list[print_i][print_j])
					printf("■");
				else
					printf("□");
			}
			puts("");
		}
		puts("");

		while (1)
		{
			if ((city[i][j].OX == 0) || (city[i][j].OX == 1 && check_list[i][j] == 1))//1이 아닌 곳
			{
				if (j < size - 1)
					j++;
				else
				{
					j = 0;
					if (i < size - 1)
						i++;
					else
					{
						j = 5;
						break;
					}
						
				}
			}
			else//1인 곳중에서 방문하지 않은 곳일떄만 break
			{
				if (check_list[i][j] == 0)
					break;
			}
		}
		if (i == size - 1 && j == size - 1)
			break;
		//1인곳 중에서 방문한 적이 없는 노드인 경우
		check_list[i][j] = 1;
		//temp = &city[i][j];
		P_temp.ROW = i;
		P_temp.COL = j;
		
		while (1)
		{
			switch (Count_and_Check_Link(city, P_temp.ROW, P_temp.COL, check_list))//방문한적이 없고, 숫자가 1인 노드 갯수를 리턴하는 함수
			{
			case 0:
				if (IS_Empty() == FALSE)
					//temp = Pop_Link();//i,j 값이 그대로 나오는 것이 아님! 이부분 해결해야함
					P_temp = Pop_ROWCOL();
				else
					break_flag = TRUE;
				break;
			case 1://남은 하나가 다른 사분면인지 아닌지
				for (idx = 0; idx < NUM_OF_LINK; idx++)
				{
					if (local_break == TRUE)
					{
						local_break = 0;
						break;
					}
					
					if (city[P_temp.ROW][P_temp.COL].link[idx])
					{
						if (city[P_temp.ROW][P_temp.COL].link[idx]->OX == 1)
						{
							switch (idx)
							{
							case 0:
								if (check_list[P_temp.ROW][P_temp.COL + 1] != 1 && city[P_temp.ROW][P_temp.COL + 1].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) != Plane_Detector(size, P_temp.ROW, P_temp.COL + 1))
									{
										local_break = TRUE;
										break_flag = TRUE;
									}

								}
								break;
							case 1:
								if (check_list[P_temp.ROW + 1][P_temp.COL] != 1 && city[P_temp.ROW + 1][P_temp.COL].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) != Plane_Detector(size, P_temp.ROW + 1, P_temp.COL))
									{
										local_break = TRUE;
										break_flag = TRUE;
									}

								}
								break;
							case 2:
								if (check_list[P_temp.ROW][P_temp.COL - 1] != 1 && city[P_temp.ROW][P_temp.COL - 1].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) != Plane_Detector(size, P_temp.ROW, P_temp.COL - 1))
									{
										local_break = TRUE;
										break_flag = TRUE;
									}

								}
								break;
							case 3:
								if (check_list[P_temp.ROW - 1][P_temp.COL] != 1 && city[P_temp.ROW - 1][P_temp.COL].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) != Plane_Detector(size, P_temp.ROW - 1, P_temp.COL))
									{
										local_break = TRUE;
										break_flag = TRUE;
									}
								}
								break;
							}
						}
					}
				}
				break;
			default:
				//Push_Link(temp);
				Push_ROWCOL(P_temp);
				break;
			}

			if (break_flag == TRUE)
			{
				break_flag = 0;
				plane_cnt[Plane_Detector(size, i, j)]++;
				break;
			}
			else
			{
				for (idx = 0; idx < NUM_OF_LINK; idx++)
				{
					if (local_break == TRUE)
					{
						local_break = 0;
						break;
					}

					if (city[P_temp.ROW][P_temp.COL].link[idx])
					{
						if (city[P_temp.ROW][P_temp.COL].link[idx]->OX == 1)
						{
							switch (idx)
							{
							case 0:
								if (check_list[P_temp.ROW][P_temp.COL + 1] != 1 && city[P_temp.ROW][P_temp.COL + 1].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) == Plane_Detector(size, P_temp.ROW, P_temp.COL + 1))
									{
										check_list[P_temp.ROW][P_temp.COL + 1] = 1;
										P_temp.COL = P_temp.COL + 1;
										local_break = TRUE;
									}
									
								}
								break;
							case 1:
								if (check_list[P_temp.ROW + 1][P_temp.COL] != 1 && city[P_temp.ROW + 1][P_temp.COL].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) == Plane_Detector(size, P_temp.ROW + 1, P_temp.COL))
									{
										check_list[P_temp.ROW + 1][P_temp.COL] = 1;
										P_temp.ROW = P_temp.ROW + 1;
										local_break = TRUE;
									}
									
								}
								break;
							case 2:
								if (check_list[P_temp.ROW][P_temp.COL - 1] != 1 && city[P_temp.ROW][P_temp.COL - 1].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) == Plane_Detector(size, P_temp.ROW, P_temp.COL - 1))
									{
										check_list[P_temp.ROW][P_temp.COL - 1] = 1;
										P_temp.COL = P_temp.COL - 1;
										local_break = TRUE;
									}
									
								}
								break;
							case 3:
								if (check_list[P_temp.ROW - 1][P_temp.COL] != 1 && city[P_temp.ROW - 1][P_temp.COL].OX == 1)
								{
									if (Plane_Detector(size, P_temp.ROW, P_temp.COL) == Plane_Detector(size, P_temp.ROW - 1, P_temp.COL))
									{
										check_list[P_temp.ROW - 1][P_temp.COL] = 1;
										P_temp.ROW = P_temp.ROW - 1;
										local_break = TRUE;
									}
									
								}
								break;
							}
						}
					}
				}
			}

		}
		
		
	
	}
	
	
	
}
int Count_Link(Graph* apt)
{
	int idx;
	int cnt = 0;
	for (idx = 0; idx < NUM_OF_LINK; idx++)
	{
		if (apt->link[idx]->OX == 1)
			cnt++;
	}
			
	return cnt;
}

int Count_and_Check_Link(Graph** city,int i, int j, int** check_list)
{
	int idx;
	int cnt = 0;
	
	for (idx = 0; idx < NUM_OF_LINK; idx++)
	{
		if (city[i][j].link[idx])
		{
			if (city[i][j].link[idx]->OX == 1)
			{
				switch (idx)
				{
				case 0:
					if (check_list[i][j + 1] != 1)
						cnt++;
					break;
				case 1:
					if (check_list[i + 1][j] != 1)
						cnt++;
					break;
				case 2:
					if (check_list[i][j - 1] != 1)
						cnt++;
					break;
				case 3:
					if (check_list[i - 1][j] != 1)
						cnt++;
					break;
				}
			}
		}
	}
	
	return cnt;
}

int Plane_Detector(int size, int i, int j)
{
	int i_flag = 0, j_flag = 0;

	if (i >= 0 && i < size / 2)
		i_flag = TRUE;
	else// 범위 문제 생기면 확인할 부분
		i_flag = FALSE;

	if (j >= 0 && j < size / 2)
		j_flag = TRUE;
	else
		j_flag = FALSE;

	if (i_flag == TRUE && j_flag == TRUE)
		return 0;
	else if (i_flag == TRUE && j_flag == FALSE)
		return 1;
	else if (i_flag == FALSE && j_flag == TRUE)
		return 2;
	else
		return 3;

}
#endif
/*
/////////////////////////////


else
			{
				for (idx = 0; idx < NUM_OF_LINK; idx++)
				{
					if (local_break == TRUE)
					{
						local_break = 0;
						break;
					}

					if (city[P_temp.ROW][P_temp.COL].link[idx])
					{
						if (city[P_temp.ROW][P_temp.COL].link[idx]->OX == 1)
						{
							switch (idx)
							{
							case 0:
								if (check_list[P_temp.ROW][P_temp.COL + 1] != 1 && city[P_temp.ROW][P_temp.COL + 1].OX == 1)
								{
									check_list[P_temp.ROW][P_temp.COL + 1] = 1;
									P_temp.COL = P_temp.COL + 1;
									local_break = TRUE;
								}
								break;
							case 1:
								if (check_list[P_temp.ROW + 1][P_temp.COL] != 1 && city[P_temp.ROW + 1][P_temp.COL].OX == 1)
								{
									check_list[P_temp.ROW + 1][P_temp.COL] = 1;
									P_temp.ROW = P_temp.ROW + 1;
									local_break = TRUE;
								}
								break;
							case 2:
								if (check_list[P_temp.ROW][P_temp.COL - 1] != 1 && city[P_temp.ROW][P_temp.COL - 1].OX == 1)
								{
									check_list[P_temp.ROW][P_temp.COL - 1] = 1;
									P_temp.COL = P_temp.COL - 1;
									local_break = TRUE;
								}
								break;
							case 3:
								if (check_list[P_temp.ROW - 1][P_temp.COL] != 1 && city[P_temp.ROW - 1][P_temp.COL].OX == 1)
								{
									check_list[P_temp.ROW - 1][P_temp.COL] = 1;
									P_temp.ROW = P_temp.ROW - 1;
									local_break = TRUE;
								}
								break;
							}
						}
					}
				}
			}


/////////////////////////////

else
			{
				for (idx = 0; idx < NUM_OF_LINK; idx++)
				{
					if (local_break == TRUE)
					{
						local_break = 0;
						break;
					}

					if (temp->link[idx])
					{
						if (temp->link[idx]->OX == 1)
						{
							switch(idx)
							{
							case 0:
								if (check_list[i][j + 1] != 1 && city[i][j + 1].OX == 1)
								{
									check_list[i][j + 1] = 1;
									j = j + 1;
									local_break = TRUE;
								}
								break;
							case 1:
								if (check_list[i + 1][j] != 1 && city[i + 1][j].OX == 1)
								{
									check_list[i + 1][j] = 1;
									i = i + 1;
									local_break = TRUE;
								}
								break;
							case 2:
								if (check_list[i][j - 1] != 1 && city[i][j - 1].OX == 1)
								{
									check_list[i][j - 1] = 1;
									j = j - 1;
									local_break = TRUE;
								}
								break;
							case 3:
								if (check_list[i - 1][j] != 1&& city[i - 1][j].OX == 1)
								{
									check_list[i - 1][j] = 1;
									i = i - 1;
									local_break = TRUE;
								}
								break;
							}
						}
					}
				}
			}

////////////////////////////



while (1)
		{

			if (IS_Empty() == TRUE)
				break;
			else



			for (idx = 0; idx < NUM_OF_LINK; idx++)
			{ }



		}
	for (idx = 0; idx < NUM_OF_LINK; idx++)
			{

				carton[i][j].link[idx];
			}
			
			
			for (idx = 0; idx < NUM_OF_LINK; idx++)
	{
		carton[0][size - 1];
		carton[size - 1][0];
		carton[size - 1][size - 1];
	}
	
	if((i>=0&&i<size)&&(j>=0&&j<size))
	for (i = 1; i < size - 1; i++)
	{
	}
	for (j = 1; j < size - 1; j++)
	{
	}

	for (i = 1; i < size-1; i++)
	{
		for (j = 1; j < size-1; j++)
		{
			//Link[0]: (i-1, j), Link[1]: (i, j+1), Link[2]: (i+1, j), Link[3]: (i, j-1)
			if()
		
		}
	}
		
			*/