#include "../include/game.h"

void	move(int *first_case, int *second_case, int *third_case)
{
	if (*second_case == VIDE)
	{
		if (*first_case == PLAYER_CO)
			*first_case = COLLECT;
		else
			*first_case = VIDE;
		*second_case = PLAYER;
	}
	else if (*second_case == COLLECT)
	{
		if (*first_case == PLAYER_CO)
			*first_case = COLLECT;
		else
			*first_case = VIDE;
		*second_case = PLAYER_CO;
	}
	else if (*second_case == CAISSE)
	{
		if (*third_case == CAISSE || *third_case == WALL
			|| *third_case == CAISSE_CO)
			return ;
		if (*first_case == PLAYER_CO)
			*first_case = COLLECT;
		else
			*first_case = VIDE;
		*second_case = PLAYER;
		if (*third_case == COLLECT)
			*third_case = CAISSE_CO;
		else if (*third_case == VIDE)
			*third_case = CAISSE;
	}
	else if (*second_case == CAISSE_CO)
	{
		if (*third_case == CAISSE || *third_case == WALL
			|| *third_case == CAISSE_CO)
			return ;
		if (*first_case == PLAYER_CO)
			*first_case = COLLECT;
		else
			*first_case = VIDE;
		*second_case = PLAYER_CO;
		if (*third_case == COLLECT)
			*third_case = CAISSE_CO;
		else if (*third_case == VIDE)
			*third_case = CAISSE;
	}
}

void	player_move(int map[24][28], int x, int y, int direction)
{
	if (direction == UP)
		move(&map[y][x], &map[y - 1][x], &map[y - 2][x]);
	else if (direction == DOWN)
		move(&map[y][x], &map[y + 1][x], &map[y + 2][x]);
	else if (direction == RIGHT)
		move(&map[y][x], &map[y][x + 1], &map[y][x + 2]);
	else if (direction == LEFT)
		move(&map[y][x], &map[y][x - 1], &map[y][x - 2]);
}