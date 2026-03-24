/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:45:45 by kamys             #+#    #+#             */
/*   Updated: 2026/03/24 19:39:08 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

t_bool	test_tex(char *path)
{
	int	fd;
	
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (erro_int("dont open texture", FALSE));
	close(fd);
	return (TRUE);
}

t_bool	parse_no(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.no)
		return (write_erro("duplicate NO"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.no = path;
	return (TRUE);
}

t_bool	parse_so(t_parser *p, char *line)
{
	char *path;
	
	if (p->game->tex_path.so)
		return (write_erro("duplicate SO"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.so = path;
	return (TRUE);
}

t_bool	parse_we(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.we)
		return (write_erro("duplicate we"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.we = path;
	return (TRUE);
}

t_bool	parse_ea(t_parser *p, char *line)
{
	char *path;

	if (p->game->tex_path.ea)
		return (write_erro("duplicate EA"), FALSE);
	path = line + 3;
	path = ft_strtrim(path, " \t\n");
	if (!path)
		return (FALSE);
	if (!test_tex(path))
		return (FALSE);
	p->game->tex_path.ea = path;
	return (TRUE);
}

void	free_matrix(char **splits)
{
	int	k;

	k = -1;
	while (splits[++k])
		free(splits[k]);
	free(splits);
}

t_bool	parse_rgb(char *color, int *r, int *g, int *b)
{
	char	**rgb;
	int i;
	
	rgb = ft_split(color, ',');
	if (!rgb)
		return (FALSE);
	i = -1;
	while (rgb[++i]);
	if (i != 3)
		return (free_matrix(rgb), FALSE);
	rgb[0] = ft_strtrim(rgb[0], " ");
	rgb[1] = ft_strtrim(rgb[1], " ");
	rgb[2] = ft_strtrim(rgb[2], " ");
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (free_matrix(rgb), FALSE);
	free_matrix(rgb);
	return (TRUE);
}

t_bool	parse_floor(t_parser *p, char *line)
{
	int		r;
	int		g;
	int		b;

	if (p->game->colors.floor)
		return (write_erro("duplicate FLOOR (F)"), FALSE);
	if (!parse_rgb(line + 2, &r, &g, &b))
		return (write_erro("invalid floor color"), FALSE);
	p->game->colors.floor = (r << 16) | (g << 8) | b;
	return (TRUE);
}

t_bool	parse_ceiling(t_parser *p, char *line)
{
	int		r;
	int		g;
	int		b;

	if (p->game->colors.ceiling)
		return (write_erro("duplicate CEILING (C)"), FALSE);
	if (!parse_rgb(line + 2, &r, &g, &b))
		return (write_erro("invalid floor color"), FALSE);
	p->game->colors.ceiling = (r << 16) | (g << 8) | b;
	return (TRUE);
}

t_id	get_id(char *line)
{
	int			i;
	t_id_config	config[] = {
		{"NO ", ID_NO},
		{"SO ", ID_SO},
		{"WE ", ID_WE},
		{"EA ", ID_EA},
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
	if (!parse[id](p, line))
		return (FALSE);
	return (TRUE);
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

t_bool	is_map(char *line)
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
	return (p->config_count == 6);
}

static t_bool	copy_grid(t_map *map, t_parser *p)
{
	int		i;
	int		file_i;

	map->height = 0;
	file_i = p->i;
	while (p->file[file_i++])
		map->height++;
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (erro_int("malloc\n", 0));
	i = 0;
	file_i = p->i;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(p->file[file_i++]);
		if (!map->grid[i])
		{
			free_matrix(map->grid);
			return (erro_int("strdup\n", FALSE));
		}
		i++;
	}
	map->grid[map->height] = NULL;
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
	if (!parser_configs(&p))
		return (FALSE);
	if (!copy_grid(&p.game->map, &p))
		return (FALSE);
	
	// printf("%s\n", p.game->tex_path.no);	
	// printf("%s\n", p.game->tex_path.so);
	// printf("%s\n", p.game->tex_path.we);
	// printf("%s\n", p.game->tex_path.ea);
	printf("%d\n", p.game->colors.ceiling);
	printf("%d\n", p.game->colors.floor);
	// for (int j = 0; p.game->map.grid[j]; j++)
	// 	printf("%s\n", p.game->map.grid[j]);
	return (TRUE);
}
