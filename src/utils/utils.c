/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 16:56:02 by kamys             #+#    #+#             */
/*   Updated: 2026/03/28 17:49:34 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_player(char p)
{
	return (p == 'N' || p == 'S' || p == 'E' || p == 'W');
}

void	set_vec2(double x, double y, double *tx, double *ty)
{
	*tx = x;
	*ty = y;
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}
