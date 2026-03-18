/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 08:51:33 by cassunca          #+#    #+#             */
/*   Updated: 2026/03/15 18:52:39 by kamys            ###   ########.fr       */
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


# include "map.h"
# include "parser.h"
# include "utils.h"
# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray // creio que pode ter um header proprio
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

	// t_player	player;
	// t_img		img;
	// t_ray		ray;
	void		*mlx;
	void		*win;
}	t_data;

#endif
