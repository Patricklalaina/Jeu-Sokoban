#include "../include/game.h"

void	exit_process(t_data *game)
{
	SDL_DestroyRenderer(game->render);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	exit (1);
}

void	init_image(t_data *game, t_img *img, char *path)
{
	img->pos.w = 25;
	img->pos.h = 25;
	img->src = IMG_Load(path);
	if (!img->src)
		exit(1);
	img->image = SDL_CreateTextureFromSurface(game->render, img->src);
	SDL_FreeSurface(img->src);
}

int	nb_collect(int map[24][28])
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (++i != 24)
	{
		j = -1;
		while (++j != 28)
		{
			if (map[i][j] == 2)
				count++;
		}
	}
	return (count);
}

void	start_game(t_data *game)
{
	int	run;
	int	i;
	int	j;
	int	mark;
/***************************INIT MAP*********************************************/
	int	map[24][28] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 3, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 4, 3, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 3, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 2, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 2, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
/************************************END************************************************/
	t_img	wall;
	t_img	collect;
	t_img	object;
	t_img	player;

	run = 1;
/*************************INIT IMAGE****************************************/
	init_image(game, &wall, "./assets/wall.png");
	init_image(game, &collect, "./assets/collect.png");
	init_image(game, &object, "./assets/caisse.png");
	init_image(game, &player, "./assets/player.png");
/****************************END********************************************/
	SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
	SDL_RenderPresent(game->render);
	mark = 0;
	while (run)
	{
		SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
		i = -1;
		while (++i != 24)
		{
			j = -1;
			while (++j != 28)
			{
				if (map[i][j] == 1)
				{
					wall.pos.x = j * 25;
					wall.pos.y = i * 25;
					SDL_RenderCopy(game->render, wall.image, NULL, &wall.pos);
				}
				else if (map[i][j] == 2)
				{
					collect.pos.x = j * 25;
					collect.pos.y = i * 25;
					SDL_RenderCopy(game->render, collect.image, NULL, &collect.pos);
				}
				else if (map[i][j] == 3)
				{
					object.pos.x = j * 25;
					object.pos.y = i * 25;
					SDL_RenderCopy(game->render, object.image, NULL, &object.pos);
				}
				else if (map[i][j] == 4)
				{
					player.pos.x = j * 25;
					player.pos.y = i * 25;
					SDL_RenderCopy(game->render, player.image, NULL, &player.pos);
				}
			}
		}
		SDL_RenderPresent(game->render);
		SDL_RenderClear(game->render);
		wait_event_game(game, &run, map, &mark);
		if (nb_collect(map) == 0 && mark == 0)
		{
			game->scene = MENU;
			run = 0;
		}
	}
	SDL_DestroyTexture(wall.image);
	SDL_DestroyTexture(collect.image);
	SDL_DestroyTexture(object.image);
	SDL_DestroyTexture(player.image);
	render(game);
}

void	show_credit(t_data *game)
{
	int		run;
	t_img	card;
	t_img	credit;
	SDL_Surface	*cardsurf[2];
	int		i;

	run = 1;
	i = 0;
/****************************init card********************************/
	cardsurf[0] = IMG_Load("./assets/card 1.png");
	cardsurf[1] = IMG_Load("./assets/card 2.png");
	card.pos.x = 0;
	card.pos.y = 0;
	card.pos.w = 700;
	card.pos.h = 600;
	init_info_credit(game, &credit, "./assets/fidrandr.png", card.pos);
/********************************************************************/
	SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
	SDL_RenderPresent(game->render);
	while (run)
	{
		card.image = SDL_CreateTextureFromSurface(game->render, cardsurf[i++]);
		SDL_RenderCopy(game->render,
				card.image,
				NULL,
				&card.pos);
		if (i == 2)
			i = 0;
		SDL_RenderCopy(game->render,
				credit.image,
				NULL,
				&card.pos);
		SDL_DestroyTexture(card.image);
		SDL_RenderPresent(game->render);
		SDL_RenderClear(game->render);
		wait_event_credit(game, &run);
		usleep(200000);
	}
	SDL_FreeSurface(cardsurf[0]);
	SDL_FreeSurface(cardsurf[1]);
	render(game);
}

void	render(t_data *game)
{
	if (game->scene == MENU)
		show_menu(game);
	else if (game->scene == GAME)
		start_game(game);
	else if (game->scene == CREDIT)
		show_credit(game);
	else if (game->scene == EXIT)
		exit_process(game);
}