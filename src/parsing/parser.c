/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:45:45 by kamys             #+#    #+#             */
/*   Updated: 2026/03/16 21:45:51 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

void	parse_no(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.no)
		return (write_erro("duplicate NO"));
	path = line + 3;
	p->game->tex_path.no = ft_strdup(path);
}

void	parse_so(t_parser *p, char *line)
{
	char *path;
	
	if (p->game->tex_path.so)
		return (write_erro("duplicate SO"));
	path = line + 3;
	p->game->tex_path.so = ft_strdup(path);
}

void	parse_we(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.we)
		return (write_erro("duplicate we"));
	path = line + 3;
	p->game->tex_path.we = ft_strdup(path);
}

void	parse_ea(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.ea)
		return (write_erro("duplicate EA"));
	path = line + 3;
	p->game->tex_path.ea = ft_strdup(path);
}

void	free_split(char **splits)
{
	int	k;

	k = -1;
	while (splits[++k])
		free(splits[k]);
	free(splits);
}

void	parse_floor(t_parser *p, char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (p->game->colors.floor)
		return (write_erro("duplicate FLOOR (F)"));
	rgb = ft_split(line + 2, ',');

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		perror("invalid floor color");

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	p->game->colors.floor = (r << 16) | (g << 8) | b;

	free_split(rgb);
}

void	parse_ceiling(t_parser *p, char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (p->game->colors.ceiling)
		return (write_erro("duplicate CEILING (C)"));
	rgb = ft_split(line + 2, ',');

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		perror("invalid floor color");

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);

	p->game->colors.ceiling = (r << 16) | (g << 8) | b;

	free_split(rgb);
}

t_id	get_id(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (ID_NO);
	if (!ft_strncmp(line, "SO ", 3))
		return (ID_SO);
	if (!ft_strncmp(line, "WE ", 3))
		return (ID_WE);
	if (!ft_strncmp(line, "EA ", 3))
		return (ID_EA);
	if (!ft_strncmp(line, "F ", 2))
		return (ID_F);
	if (!ft_strncmp(line, "C ", 2))
		return (ID_C);
	return (ID_INVALID);
}

t_bool	parser_identifier(t_parser *p, char *line)
{
	t_id	id;
	t_parse_func parse[] = {
		parse_no,
		parse_so,
		parse_we,
		parse_ea,
		parse_floor,
		parse_ceiling
	};

	id = get_id(line);
	if (id == ID_INVALID)
		return (FALSE);
	parse[id](p, line);
	return (TRUE);
}

t_bool	is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	skip_empty_lines(t_parser *p)
{
	while (p->file[p->i] && is_empty_line(p->file[p->i]))
		p->i++;
}

t_bool	parser_configs(t_parser *p)
{
	if (!p->file)
		return (FALSE);
	char	*line;
	while (p->file[p->i])
	{
		skip_empty_lines(p);
		line = p->file[p->i];
		if (is_map(line))
			break ;
		if (!parser_identifier(p, line))
			return (FALSE);
		p->i++;
		p->config_count++;
	}
	return (p->config_count == 6);
	return (TRUE);
}

t_bool	parser(char *file, t_data *game)
{
	t_parser	p;

	p.file = read_file(file);
	p.i	= 0;
	p.game = game;
	if (!p.file)
		return (FALSE);
	printf("inicio parser\n");
	if (parser_configs(&p))
		return (FALSE);
	/*
	if (!parser_map(&p))
		return (FALSE);
	if (!validate_map(&p))
		return (FALSE);
	*/
	printf("%s\n", p.game->tex_path.no);
	printf("%s\n", p.game->tex_path.so);
	printf("%s\n", p.game->tex_path.we);
	printf("%s\n", p.game->tex_path.ea);
	printf("%d\n", p.game->colors.ceiling);
	printf("%d\n", p.game->colors.floor);
	for (; p.file[p.i]; p.i++)
		printf("%s\n", p.file[p.i]);
	return (TRUE);
}
