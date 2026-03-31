/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:51:33 by cassunca          #+#    #+#             */
/*   Updated: 2026/03/31 17:51:54 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* THE CHESS 🨀
_________________
|♜ ♞ ♝ ♚ ♛ ♝ ♞ ♜|
|♟ ♟ ♟ ♟ ♟ ♟ ♟ ♟|
|               |
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
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_ESC 65307

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# include "map.h"
# include "parser.h"
# include "libft.h"
# include "mlx.h"
# include <sys/time.h>

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	fov;
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

	t_player	player;
	t_img		frame;
	t_ray		ray;
	void		*mlx;
	void		*win;
}	t_data;

int	close_window(void *param);
int	handle_key(int keycode, t_data *game);
int	handle_key_release(int keycode, t_data *game);
int	game_loop(t_data *game);

#endif
