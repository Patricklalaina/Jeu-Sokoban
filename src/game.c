#include "../include/game.h"

void	charge_assets_to_render(t_data *game, int actifbtn, t_button *new_game, t_button *credit, t_button *exitbtn)
{
	static int	i_ng = 1;
	static int	i_cdt = 1;
	static int	i_ext = 1;

	new_game->pos.x = 100;
	new_game->pos.y = 200;
	new_game->pos.w = 500;
	new_game->pos.h = 100;
	credit->pos.x = 100;
	credit->pos.y = 280;
	credit->pos.w = 500;
	credit->pos.h = 100;
	exitbtn->pos.x = 100;
	exitbtn->pos.y = 360;
	exitbtn->pos.w = 500;
	exitbtn->pos.h = 100;
	if (actifbtn == 0)
	{
		new_game->image = SDL_CreateTextureFromSurface(game->render, new_game->src[i_ng++]);
		if (!new_game->image)
			exit(1);
		if (i_ng == 3)
			i_ng = 1;
	}
	else
	{
		new_game->image = SDL_CreateTextureFromSurface(game->render, new_game->src[0]);
		if (!new_game->image)
			exit(1);
	}
	SDL_RenderCopy(game->render,
				new_game->image,
				NULL,
				&new_game->pos);
	if (actifbtn == 1)
	{
		credit->image = SDL_CreateTextureFromSurface(game->render, credit->src[i_cdt++]);
		if (!credit->image)
			exit(1);
		if (i_cdt == 3)
			i_cdt = 1;
	}
	else
	{
		credit->image = SDL_CreateTextureFromSurface(game->render, credit->src[0]);
		if (!credit->image)
			exit(1);
	}
	SDL_RenderCopy(game->render,
				credit->image,
				NULL,
				&credit->pos);
	if (actifbtn == 2)
	{
		exitbtn->image = SDL_CreateTextureFromSurface(game->render, exitbtn->src[i_ext++]);
		if (!exitbtn->image)
			exit(1);
		if (i_ext == 3)
			i_ext = 1;
	}
	else
	{
		exitbtn->image = SDL_CreateTextureFromSurface(game->render, exitbtn->src[0]);
		if (!exitbtn->image)
			exit(1);
	}
	SDL_RenderCopy(game->render,
				exitbtn->image,
				NULL,
				&exitbtn->pos);
	SDL_DestroyTexture(new_game->image);
	SDL_DestroyTexture(credit->image);
	SDL_DestroyTexture(exitbtn->image);

}

void	show_menu(t_data *game)
{
	int	run;
	int	actifbtn;
	SDL_Surface	*src;
	SDL_Texture	*title;
	SDL_Rect	pos;
	t_button	new_game;
	t_button	credit;
	t_button	exitbtn;
	Mix_Chunk /**chunk	Mix_Music		*/*music_menu;
	int			i;

	run = 1;
	actifbtn = 0;
	pos.x = 100;
	pos.y = 50;
	pos.w = 500;
	pos.h = 100;
	src = IMG_Load("./assets/button/title.png");
	title = SDL_CreateTextureFromSurface(game->render, src);
	SDL_FreeSurface(src);
	init_btn(&new_game, &credit, &exitbtn);
	Mix_AllocateChannels(2);
	music_menu = Mix_LoadWAV("./assets/sound/sound.mp3");
	Mix_PlayChannel(1, music_menu, 0);
	while (run)
	{
		game->music = Mix_LoadWAV("./assets/sound/bouton1.mp3");
		SDL_SetRenderDrawColor(game->render, 0, 0, 0, 255);
		SDL_RenderCopy(game->render,
				title,
				NULL,
				&pos);
		charge_assets_to_render(game, actifbtn, &new_game, &credit, &exitbtn);
		wait_event_menu(game, &run, &actifbtn);
		SDL_RenderPresent(game->render);
		SDL_RenderClear(game->render);
		usleep(150000);
		if (game->music)
			Mix_FreeChunk(game->music);
		usleep(200);
	}
	i = -1;
	while (++i != 3)
	{
		SDL_FreeSurface(new_game.src[i]);
		SDL_FreeSurface(credit.src[i]);
		SDL_FreeSurface(exitbtn.src[i]);
	}
	Mix_FreeChunk(music_menu);
	SDL_DestroyTexture(title);
	render(game);
}

int main(int argc, char **argv)
{
	t_data	game;

	init_screen(&game);
	Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	(void)argv;
	if (argc != 1)
	{
		printf("Usage :: ./prog");
		exit (1);
	}
	game.scene = MENU;
	render(&game);
	return 0;
}
