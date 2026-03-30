/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:50:08 by kamys             #+#    #+#             */
/*   Updated: 2026/03/30 12:09:10 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include "utils.h"

# define EXTENSION ".cub"
# define USAGE "usage: ./bin/cub3d map.cub\n"

typedef struct s_data	t_data;

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

typedef struct s_id_config
{
	char	*str;
	t_id	id;
}	t_id_config;

typedef t_bool			(*t_parse_func)(t_parser *, char *);

t_bool	parser(char *file, t_data *game);
char	**read_file(char *path);

t_bool	parser_configs(t_parser *p);

t_bool	parse_floor(t_parser *p, char *line);
t_bool	parse_ceiling(t_parser *p, char *line);

t_bool	parse_no(t_parser *p, char *line);
t_bool	parse_so(t_parser *p, char *line);
t_bool	parse_we(t_parser *p, char *line);
t_bool	parse_ea(t_parser *p, char *line);

t_bool	parser_map(t_data *game);

#endif
