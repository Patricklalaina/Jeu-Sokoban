#include "../include/game.h"

void	init_btn(t_button *new_game, t_button *credit, t_button *exitbtn)
{
	new_game->src[0] = IMG_Load("./assets/button/new game 0.png");
	new_game->src[1] = IMG_Load("./assets/button/new game 1.png");
	new_game->src[2] = IMG_Load("./assets/button/new game 2.png");
	credit->src[0] = IMG_Load("./assets/button/credit 0.png");
	credit->src[1] = IMG_Load("./assets/button/credit 1.png");
	credit->src[2] = IMG_Load("./assets/button/credit 2.png");
	exitbtn->src[0] = IMG_Load("./assets/button/exit 0.png");
	exitbtn->src[1] = IMG_Load("./assets/button/exit 1.png");
	exitbtn->src[2] = IMG_Load("./assets/button/exit 2.png");
}

void	init_screen(t_data *game)
{
	game->scene = MENU;
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		printf("Init SDL fail\n");
		exit (1);
	}
	IMG_Init(IMG_INIT_PNG);
	game->window = SDL_CreateWindow("Gasikarako V0.1",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									700,
									600,
									SDL_WINDOW_BORDERLESS);
	if (!game->window)
	{
		printf("Init window fail\n");
		IMG_Quit();
		SDL_Quit();
		exit (1);
	}
	game->render = SDL_CreateRenderer(game->window, -1, 0);
	if (!game->render)
	{
		printf("Fail to create render\n");
		SDL_DestroyWindow(game->window);
		IMG_Quit();
		SDL_Quit();
		exit (1);
	}
	SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
	SDL_RenderPresent(game->render);
}

void	init_info_credit(t_data *game, t_img *credit, char *path, SDL_Rect pos)
{
	credit->src = IMG_Load(path);
	if (!credit->src)
		exit(1);
	credit->image = SDL_CreateTextureFromSurface(game->render, credit->src);
	if (!credit->image)
		exit(1);
	SDL_FreeSurface(credit->src);
	credit->pos.x = pos.x;
	credit->pos.y = pos.y;
	credit->pos.w = pos.w;
	credit->pos.h = pos.h;
}