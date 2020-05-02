#pragma once

#ifndef __FUNC_H__
#define __FUNC_H__

/*CITY_PLANNING*/
void Input_Apt(Graph** city);
void Input_Link(Graph** city);
Graph** Make_City(); 
int Plane_Detector(int size, int i, int j);
void City_Planning_Simulation(Graph** city, int** check_list, int* plane_cnt);
int Count_and_Check_Link(Graph** city, int i, int j, int** check_list);
int Count_Link(Graph* apt);

/*STACK*/
Stack* Add_new_node();
void Push_Link(Graph* node);
Graph* Pop_Link();
void Push_ROWCOL(Point P_temp);
Point Pop_ROWCOL();
int IS_Empty();

#endif
