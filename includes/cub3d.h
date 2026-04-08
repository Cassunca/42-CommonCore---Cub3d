/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:51:33 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/09 13:16:30 by kamys            ###   ########.fr       */
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
|               |
|               |
|♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙|
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

# define MOVE_SPEED 0.01
# define ROT_SPEED 0.007

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define MAX_BTNS 2

# include "door.h"
# include "types.h"
# include "map.h"
# include "parser.h"
# include "libft.h"
# include "minimap.h"
# include "mlx.h"
# include <sys/time.h>
# include <math.h>

typedef struct s_button
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		is_hover;
	int		was_hover;
	int		has_glitched;
	double	state_timer;
	double	glitch_frame_timer;
	int		glitching;
	char	*text;
	char	render_text[32];
	double	glitch_timer;
	void	(*on_click)(void *param);
}	t_button;

typedef enum e_screen
{
	TITLE,
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

# define MAX_MATRIX 100
# define TRAIL_SIZE 4

typedef struct s_matrix
{
	int     x;        // posição horizontal
	float   y;        // posição vertical (float pra suavizar)
	float   speed;    // velocidade da queda
	char    c;        // caractere atual
	char    trail[TRAIL_SIZE];
	float 	char_timer;
	float 	char_delay;
	float 	last_y;
} t_matrix;

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
	
	t_player	player;
	t_img		frame;
	t_ray		ray;
	void		*mlx;
	void		*win;
}	t_data;

/* ========== HOOKS ========== */

int	close_window(void *param);
int	handle_key(int keycode, t_data *game);
int	handle_key_release(int keycode, t_data *game);
int	handle_mouse(t_data *data);

/* ========== RENDER ========== */

void	render_background(t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

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

void    draw_wall_column(t_data *data, int x);
t_img	*get_wall_tex(t_data *data);
int		get_tex_pixel(t_img *tex, int x, int y);
int		get_tex_x(t_data *data, t_img *tex);

int		game_loop(t_data *game);

void	draw_sprite_to_frame(t_data *game, t_img *sprite, int x, int y, int is_hover);

#endif
