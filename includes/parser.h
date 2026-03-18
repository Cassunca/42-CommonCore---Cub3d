/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:50:08 by kamys             #+#    #+#             */
/*   Updated: 2026/03/15 19:54:56 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

# define EXTENSION ".cub"
# define USAGE "usage: ./bin/cub3d map.cub\n"

typedef struct s_data	t_data;
typedef enum e_bool	t_bool;


typedef enum e_id
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C,
	ID_INVALID
}	t_id;

typedef struct s_parser
{
	t_data	*game;
	char	**file;
	int		i;
	int		config_count;
}	t_parser;

typedef void (*t_parse_func)(t_parser *, char *);

t_bool	parser(char *file, t_data *game);
char	**read_file(char *path);

#endif
