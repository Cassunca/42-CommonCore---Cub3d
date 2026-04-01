/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:33:56 by kamys             #+#    #+#             */
/*   Updated: 2026/04/01 16:47:34 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "types.h"

typedef struct s_texpath
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_texpath;

typedef struct s_tex
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_tex;

typedef struct s_colors
{
	int		floor;
	int		ceiling;
	t_bool	floor_set;
	t_bool	ceiling_set;
}	t_colors;

typedef struct s_map
{
	char	**grid;
	char	**visualizer;
	int		width;
	int		height;
}	t_map;

#endif
