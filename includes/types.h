/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:05:52 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 01:41:20 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define MAX_MATRIX 100
# define TRAIL_SIZE 4

# define MAX_BTNS 2

# define MAX_KEYPAD 12

# define PANEL_COLOR 0x121826
# define PANEL_BORDER 0x2A3142

typedef struct s_data	t_data;

typedef struct s_matrix
{
	int		x;
	float	y;
	float	speed;
	char	c;
	char	trail[TRAIL_SIZE];
	float	char_timer;
	float	char_delay;
	float	last_y;
}	t_matrix;

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

typedef struct s_click
{
	int		x;
	int		y;
	int		width;
	int		height;
	char	*url;
	int		is_text;
}	t_click;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef enum e_shape_type
{
	SHAPE_RECT,
	SHAPE_CIRCLE
}	t_shape_type;

typedef struct s_shape
{
	int				x;
	int				y;
	int				w;
	int				h;
	int				radius;
	int				fill_color;
	int				border_color;
	int				border_thickness;
	t_shape_type	type;
}	t_shape;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_rect
{
	t_vec2	center;
	t_vec2	size;
	float	radius;
}	t_rect;

typedef struct s_circle
{
	t_vec2	center;
	float	radius;
}	t_circle;

typedef struct s_key
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		value;
	int		is_hover;
	void	(*action)(t_data *game, int value);
}	t_key;

#endif
