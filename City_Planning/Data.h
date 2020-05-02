#ifndef __Data_H__
#define __Data_H__
typedef struct _Point {
	int ROW;
	int COL;
}Point;

typedef struct _Graph {
	int OX;
	struct _Graph **link;
}Graph;

typedef struct _Stack {
	Graph* G_link;
	Point R_C;
	struct _Stack* S_link;
}Stack;

#endif
#define ACTUAL

#define _CRT_SECURE_NO_WARNINGS

#define SIZE_START 5
#define SIZE_END 10
#define NUM_OF_APT 18

#define NUM_OF_LINK 4

#define TRUE 1
#define FALSE 0
#define FAIL -1
