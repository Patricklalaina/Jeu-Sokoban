#include "../include/game.h"

void	wait_event_menu(t_data *game, int *run, int *actifbtn)
{
	while (SDL_PollEvent(&game->event))
	{
		if (game->event.type == SDL_QUIT)
		{
			*run = 0;
			break ;
		}
		else if (game->event.type == SDL_KEYDOWN)
		{
			if (game->event.key.keysym.sym == SDLK_ESCAPE)
			{
				*run = 0;
				game->scene = EXIT;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_UP && *actifbtn >= 0)
			{
				Mix_PlayChannel(0, game->music, 0);
				//Mix_PlayMusic(game->music, 0);
				if ((*actifbtn) == 0)
					(*actifbtn) = 3;
				(*actifbtn)--;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_DOWN && *actifbtn <= 3)
			{
				// Mix_PlayMusic(game->music, 0);
				Mix_PlayChannel(0, game->music, 0);
				if ((*actifbtn) == 2)
					(*actifbtn) = -1;
				(*actifbtn)++;
				break ;
			}
			else if (game->event.key.keysym.sym == 13 || game->event.key.keysym.sym == SDLK_KP_ENTER)
			{
				if (*actifbtn == 0)
				{
					game->scene = GAME;
					*run = 0;
					break ;
				}
				else if (*actifbtn == 1)
				{
					game->scene = CREDIT;
					*run = 0;
					break ;
				}
				else if (*actifbtn == 2)
				{
					game->scene = EXIT;
					*run = 0;
					break ;
				}
			}
		}
	}
}

void	get_coord_of_player(int map[24][28], int *x, int *y)
{
	int	i;
	int	j;

	i = -1;
	while (++i != 24)
	{
		j = -1;
		while (++j != 28)
		{
			if (map[i][j] == 4)
			{
				*x = j;
				*y = i;
				return ;
			}
		}
	}
}


void	wait_event_game(t_data *game, int *run, int map[24][28], int *mark)
{
	int			x;
	int			y;


	x = 0;
	y = 0;
	get_coord_of_player(map, &x, &y);
	while (SDL_PollEvent(&game->event))
	{
		if (game->event.type == SDL_QUIT)
		{
			*run = 0;
			break ;
		}
		else if (game->event.type == SDL_KEYDOWN)
		{
			if (game->event.key.keysym.sym == SDLK_ESCAPE)
			{
				*run = 0;
				game->scene = MENU;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_UP && map[y - 1][x] != 1)
			{
				if (*mark == 1)
				{
					map[y][x] = 2;
					*mark = 0;
				}
				else if (*mark == 2)
				{
					*mark = 1;
				}
				else
					map[y][x] = 0;
				if (map[y - 1][x] == 2)
				{
					*mark = 1;
					map[y - 1][x] = 4;
				}
				else if (map[y - 1][x] == 3)
				{
					if (map[y - 2][x] != 1 && map[y - 2][x] != 3)
					{
						if (map[y - 2][x] == 2)
							*mark = 2;
						map[y - 2][x] = 3;
						map[y - 1][x] = 4;
					}
					else
					{
						map[y - 1][x] = 3;
						map[y][x] = 4;
					}
				}
				else if (map[y - 1][x] == 0)
					map[y - 1][x] = 4;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_DOWN && map[y + 1][x] != 1)
			{
				if (*mark == 1)
				{
					map[y][x] = 2;
					*mark = 0;
				}
				else if (*mark == 2)
				{
					*mark = 1;
				}
				else
					map[y][x] = 0;
				if (map[y + 1][x] == 2)
				{
					*mark = 1;
					map[y + 1][x] = 4;
				}
				else if (map[y + 1][x] == 3)
				{
					if (map[y + 2][x] != 1 && map[y + 2][x] != 3)
					{
						if (map[y + 2][x] == 2)
							*mark = 2;
						map[y + 2][x] = 3;
						map[y + 1][x] = 4;
					}
					else
					{
						map[y + 1][x] = 3;
						map[y][x] = 4;
					}
				}
				else if (map[y + 1][x] == 0)
					map[y + 1][x] = 4;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_RIGHT && map[y][x + 1] != 1)
			{
				if (*mark == 1)
				{
					map[y][x] = 2;
					*mark = 0;
				}
				else if (*mark == 2)
				{
					*mark = 1;
				}
				else
					map[y][x]= 0;
				if (map[y][x + 1] == 2)
				{
					*mark = 1;
					map[y][x + 1] = 4;
				}
				else if (map[y][x + 1] == 3)
				{
					if (map[y][x + 2] != 1 && map[y][x + 2] != 3)
					{
						if (map[y][x + 2] == 2)
							*mark = 2;
						map[y][x + 2] = 3;
						map[y][x + 1] = 4;
					}
					else
					{
						map[y][x + 1] = 3;
						map[y][x] = 4;
					}
				}
				else if (map[y][x + 1] == 0)
					map[y][x + 1] = 4;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_LEFT && map[y][x - 1] != 1)
			{
				if (*mark == 1)
				{
					map[y][x] = 2;
					*mark = 0;
				}
				else if (*mark == 2)
				{
					*mark = 1;
				}
				else
					map[y][x] = 0;
				if (map[y][x - 1] == 2)
				{
					*mark = 1;
					map[y][x - 1] = 4;
				}
				else if (map[y][x - 1] == 3)
				{
					if (map[y][x - 2] != 1 && map[y][x - 2] != 3)
					{
						if (map[y][x - 2] == 2)
							*mark = 2;
						map[y][x - 2] = 3;
						map[y][x - 1] = 4;
					}
					else
					{
						map[y][x - 1] = 3;
						map[y][x] = 4;
					}
				}
				else if (map[y][x - 1] == 0)
					map[y][x - 1] = 4;
				break ;
			}
		}
	}
}

void	wait_event_credit(t_data *game, int *run)
{
	while (SDL_PollEvent(&game->event))
	{
		if (game->event.type == SDL_QUIT)
		{
			*run = 0;
			break ;
		}
		else if (game->event.type == SDL_KEYDOWN)
		{
			if (game->event.key.keysym.sym == SDLK_ESCAPE)
			{
				*run = 0;
				game->scene = MENU;
				break ;
			}
		}
	}
}