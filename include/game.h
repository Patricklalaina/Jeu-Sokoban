#ifndef GAME_H
# define GAME_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_ttf.h>
# include <stdio.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define MENU 0
# define GAME 1
# define CREDIT 2
# define EXIT 3
# define NORMAL 0
# define SELECTED 1

enum {VIDE, WALL, COLLECT, CAISSE, PLAYER, PLAYER_CO, CAISSE_CO};
enum {UP, DOWN, RIGHT, LEFT};

typedef struct s_button
{
	SDL_Surface		*src[3];
	SDL_Texture		*image;
	SDL_Rect		pos;
}	t_button;

typedef struct s_img
{
	SDL_Surface	*src;
	SDL_Texture	*image;
	SDL_Rect	pos;
}	t_img;

typedef struct s_data
{
	SDL_Window		*window;
	SDL_Renderer	*render;
	SDL_Event		event;
	Mix_Chunk		*music;
	int				scene;
}	t_data;


/*****************
 * INIT SCREEN
 * ***************/
void	init_screen(t_data *game);
void	init_btn(t_button *new_game, t_button *credit, t_button *exitbtn);
/****************
 * RENDER
 * **************/
void	render(t_data *game);
/*****************
 * SHOW GAME
 * **************/
void	start_game(t_data *game);
/****************
 * SHOW_MENU
 * *************/
void	show_menu(t_data *game);
/*********************
 * EVENT HANDLE MENU
 * ******************/
void	wait_event_menu(t_data *game, int *run, int *actifbtn);
/********************
 * EVENT HANDLE CREDIT
 * ******************/
void	wait_event_credit(t_data *game, int *run);
/*********************
 * EVENT HANDLE GAME
 * *******************/
void	wait_event_game(t_data *game, int *run, int map[24][28]);
void	init_info_credit(t_data *game, t_img *credit, char *path, SDL_Rect pos);
void	player_move(int map[24][28], int x, int y, int direction);

#endif //GAME_H
