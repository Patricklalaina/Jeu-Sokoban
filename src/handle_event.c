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
				if ((*actifbtn) == 0)
					(*actifbtn) = 3;
				(*actifbtn)--;
				break ;
			}
			else if (game->event.key.keysym.sym == SDLK_DOWN && *actifbtn <= 3)
			{
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
			if (map[i][j] == PLAYER || map[i][j] == PLAYER_CO)
			{
				*x = j;
				*y = i;
				return ;
			}
		}
	}
}


void	wait_event_game(t_data *game, int *run, int map[24][28])
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
			}
			else if (game->event.key.keysym.sym == SDLK_UP)
			{
				Mix_PlayChannel(0, game->music, 0);
				player_move(map, x, y, UP);
			}
			else if (game->event.key.keysym.sym == SDLK_DOWN)
			{
				Mix_PlayChannel(0, game->music, 0);
				player_move(map, x, y, DOWN);
			}
			else if (game->event.key.keysym.sym == SDLK_RIGHT)
			{
				Mix_PlayChannel(0, game->music, 0);
				player_move(map, x, y, RIGHT);
			}
			else if (game->event.key.keysym.sym == SDLK_LEFT)
			{
				Mix_PlayChannel(0, game->music, 0);
				player_move(map, x, y, LEFT);
			}
			break ;
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