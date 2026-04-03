/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:05:52 by kamys             #+#    #+#             */
/*   Updated: 2026/04/02 19:18:47 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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

typedef struct s_leaf
{
	double	x, y;
	double	prev_x, prev_y;

	double	speed_y;

	double	amplitude;
	double	frequency;
	double	time;

	double	anim_speed;
	
	int		frame;
	int		frame_dir;
	double	anim_time;
}	t_leaf;

#endif
