/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:51:33 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/12 22:29:04 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* THE CHESS 🨀
_________________
|♜ ♞ ♝ ♚ ♛ ♝ ♞ ♜|
|♟ ♟ ♟   ♟ ♟ ♟ ♟|
|      ♟        |
|               |
|      ♙        |
|               |
|♙ ♙ ♙   ♙ ♙ ♙ ♙|
|♖ ♘ ♗ ♔ ♕ ♗ ♘ ♖|
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
*/

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_SPACE 32
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_ESC 65307
# define KEY_ENTER 65293
# define KEY_BACKSPACE 65288

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.007

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define PANEL_COLOR 0x121826
# define PANEL_BORDER 0x2A3142

# include "door.h"
# include "types.h"
# include "map.h"
# include "parser.h"
# include "libft.h"
# include "minimap.h"
# include "mlx.h"
# include <sys/time.h>
# include <math.h>

typedef enum e_screen
{
	TITLE,
	PASSWORD_INPUT,
	GAME
}	t_screen;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	fov;
	int		move_f;
	int		move_b;
	int		move_l;
	int		move_r;
	int		rot_l;
	int		rot_r;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_data
{
	t_map		map;
	t_texpath	tex_path;
	t_colors	colors;
	t_tex		tex;

	t_matrix	matrix[MAX_MATRIX];

	t_button	btn[MAX_BTNS];
	t_img		logo_42;
	t_img		logo;
	t_screen	screen;

	t_door		doors[100];
	int			door_count;
	t_img		door_tex;
	t_img		secret_door;

	t_key		keys[MAX_KEYPAD];
	char		password_input[5];
	int			password_len;

	t_player	player;
	t_img		frame;
	t_ray		ray;
	void		*mlx;
	void		*win;
}	t_data;

t_door	*get_door_in_sight(t_data *game);
void	render_door_keypad(t_data *game);

/* ========== HOOKS ========== */

int		close_window(void *param);
int		handle_key(int keycode, t_data *game);
int		handle_key_release(int keycode, t_data *game);
int		handle_mouse(t_data *data);

/* ========== RENDER ========== */

void	render_background(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_crosshair(t_data *data);

/* ========== RAYCAST ========== */

void	draw_minimap(t_data *data);
void	execute_raycast(t_data *data);
int		handle_door_hit(t_data *data);
double	fps(void);
void	str_num(t_data *game, int num, char *str, int x);

/* ========== MOVEMENT ========== */

void	apply_rotation(t_player *p, double speed);
void	move_player(t_data *data);

/* ========== TEXTURES ========== */

void	draw_wall_column(t_data *data, int x);
t_img	*get_wall_tex(t_data *data);
int		get_tex_pixel(t_img *tex, int x, int y);
int		get_tex_x(t_data *data, t_img *tex);

int		game_loop(t_data *game);

void	update_button_text(t_button *b, double dt);
void	handle_secret_door(t_data *game, t_door *door);

// core
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_sprite_to_frame(t_data *game, t_img *sprite, int x, int y);
int		brighten(int color, float factor);

// background
void	draw_sky(t_data *game, int top_color, int bottom_color);

// ui
void	draw_button(t_data *g, t_button *btn);
void	draw_text_button(t_data *g, t_button *btn);
void	draw_panel(t_img *img, int w, int h);
void	draw_header(t_data *game, int panel_x, int panel_y);
void	draw_content(t_data *game, int panel_x, int panel_w, int panel_y);

// matrix
void	draw_matrix(t_matrix *matrix, void *mlx, void *win);
void	update_matrix(t_matrix *matrix, float dt);

// loop
int		game_loop(t_data *game);

#endif
