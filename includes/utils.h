/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:47:58 by kamys             #+#    #+#             */
/*   Updated: 2026/03/25 18:30:32 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

void	write_erro(char *s);
int		erro_int(char *s, int exit_code);
char	**erro_matrix(char *s);

#endif
