/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:50:08 by kamys             #+#    #+#             */
/*   Updated: 2026/03/15 00:57:36 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

# define EXTENSION ".cub"
# define USAGE "usage: ./bin/cub3d map.cub\n"

typedef struct s_data	t_data;
typedef enum e_bool	t_bool;

typedef struct s_parser
{
	t_data	*game;
	char	**file;
	int		i;
}	t_parser;

t_bool	parser(char *file, t_data *game);
char	**read_file(char *path);

#endif
