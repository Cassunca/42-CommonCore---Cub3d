/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:33:56 by kamys             #+#    #+#             */
/*   Updated: 2026/03/23 21:29:35 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "cub3d.h"

typedef struct s_img	t_img;

typedef struct s_texpath
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texpath;

typedef struct s_tex
{
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
}	t_tex;

typedef struct s_colors
{
	int		floor;
	int		ceiling;
}	t_colors;

typedef struct s_map
{
	char	**grid;
	char	**visualizer;
	int		width;
	int		height;
}	t_map;

#endif
