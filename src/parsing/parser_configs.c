/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_configs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:54:23 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 19:34:14 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_pw(t_parser *p, char *line);

static t_id	get_id(char *line)
{
	int					i;
	static t_id_config	config[] = {
	{"NO ", ID_NO},
	{"SO ", ID_SO},
	{"WE ", ID_WE},
	{"EA ", ID_EA},
	{"PW ", ID_PW},
	{"F ", ID_F},
	{"C ", ID_C},
	{NULL, ID_INVALID}
	};

	i = 0;
	while (config[i].str)
	{
		if (!ft_strncmp(line, config[i].str, ft_strlen(config[i].str)))
			return (config[i].id);
		i++;
	}
	return (ID_INVALID);
}

static t_bool	parser_identifier(t_parser *p, char *line)
{
	t_id				id;
	static t_parse_func	parse[] = {
		parse_no,
		parse_so,
		parse_we,
		parse_ea,
		parse_floor,
		parse_ceiling,
		parse_pw
	};

	id = get_id(line);
	if (id == ID_INVALID)
		return (erro_int("Invalid identifier", FALSE));
	if (!parse[id](p, line))
		return (FALSE);
	return (TRUE);
}

static t_bool	is_map(char *line)
{
	int	i;
	int	has_map_char;

	i = 0;
	has_map_char = 0;
	if (!line || line[0] == '\0')
		return (FALSE);
	while (line[i])
	{
		if (!ft_isspace(line[i])
			&& line[i] != '1'
			&& line[i] != '0'
			&& line[i] != 'N'
			&& line[i] != 'S'
			&& line[i] != 'E'
			&& line[i] != 'W')
			return (FALSE);
		if (line[i] == '1' || line[i] == '0')
			has_map_char = 1;
		i++;
	}
	return (has_map_char);
}

static void	skip_empty_lines(t_parser *p)
{
	while (p->file[p->i] && is_empty_line(p->file[p->i]))
		p->i++;
}

t_bool	parser_configs(t_parser *p)
{
	char	*line;

	if (!p->file)
		return (FALSE);
	while (p->file[p->i])
	{
		skip_empty_lines(p);
		if (!p->file[p->i])
			break ;
		line = p->file[p->i];
		if (is_map(line))
			break ;
		if (!parser_identifier(p, line))
			return (FALSE);
		p->i++;
		p->config_count++;
	}
	if (p->config_count != 7)
		return (erro_int("missing configs", FALSE));
	return (TRUE);
}
