/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:57:44 by kamys             #+#    #+#             */
/*   Updated: 2026/03/30 11:57:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_bool	parse_component(char **str, int *value)
{
	char	*tmp;
	long	num;
	int		i;

	tmp = ft_strtrim(*str, " ");
	if (!tmp || tmp[0] == '\0')
		return (free(tmp), FALSE);
	i = 0;
	num = 0;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
			return (free(tmp), FALSE);
		num = num * 10 + (tmp[i] - '0');
		if (num > 255)
			return (free(tmp), FALSE);
		i++;
	}
	free(*str);
	*str = tmp;
	*value = (int)num;
	return (TRUE);
}

static int	count_strs(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_bool	parse_rgb(char *color, int *r, int *g, int *b)
{
	char	**rgb;

	rgb = ft_split(color, ',');
	if (!rgb)
		return (FALSE);
	if (count_strs(rgb) != 3)
		return (free_matrix(rgb),
			erro_int("Invalid RGB format: expected 3 values (R,G,B)", FALSE));
	if (!parse_component(&rgb[0], r)
		|| !parse_component(&rgb[1], g)
		|| !parse_component(&rgb[2], b))
		return (free_matrix(rgb),
			erro_int("Invalid RGB: must be numbers between 0 and 255", FALSE));
	free_matrix(rgb);
	return (TRUE);
}

t_bool	parse_floor(t_parser *p, char *line)
{
	int		r;
	int		g;
	int		b;

	if (p->game->colors.floor_set)
		return (write_erro("Duplicate floor color definition (F)"), FALSE);
	if (!parse_rgb(line + 2, &r, &g, &b))
		return (write_erro("Invalid floor color"), FALSE);
	p->game->colors.floor = (r << 16) | (g << 8) | b;
	p->game->colors.floor_set = TRUE;
	return (TRUE);
}

t_bool	parse_ceiling(t_parser *p, char *line)
{
	int		r;
	int		g;
	int		b;

	if (p->game->colors.ceiling_set)
		return (write_erro("Duplicate ceiling color definition (C)"), FALSE);
	if (!parse_rgb(line + 2, &r, &g, &b))
		return (write_erro("Invalid ceiling color"), FALSE);
	p->game->colors.ceiling = (r << 16) | (g << 8) | b;
	p->game->colors.ceiling_set = TRUE;
	return (TRUE);
}
