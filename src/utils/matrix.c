/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:04:07 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 00:11:51 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color_matrix(int j)
{
	int	color;

	if (j == 0)
		color = 0x8899AA;
	else if (j < 3)
		color = 0x445566;
	else
		color = 0x223344;
	return (color);
}

void	draw_trail(t_matrix *m, void *mlx, void *win)
{
	int		j;
	int		y;
	char	str[2];

	j = 0;
	while (j < TRAIL_SIZE)
	{
		y = (int)m->y - (j * 12);
		if (y < 0)
		{
			j++;
			continue ;
		}
		str[0] = m->trail[j];
		str[1] = '\0';
		mlx_string_put(mlx, win, m->x, y, get_color_matrix(j), str);
		j++;
	}
}

void	draw_matrix(t_matrix *matrix, void *mlx, void *win)
{
	int		i;

	i = 0;
	while (i < MAX_MATRIX)
	{
		if (!(matrix[i].x > 200 && matrix[i].x < WIN_WIDTH - 200))
			draw_trail(&matrix[i], mlx, win);
		i++;
	}
}

void	update_matrix(t_matrix *matrix, float dt)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAX_MATRIX)
	{
		matrix[i].y += matrix[i].speed * dt;
		if ((int)(matrix[i].y / 12) != (int)(matrix[i].last_y / 12))
		{
			j = TRAIL_SIZE - 1;
			while (j > 0)
			{
				matrix[i].trail[j] = matrix[i].trail[j - 1];
				j--;
			}
			matrix[i].trail[0] = rand() % 94 + 33;
		}
		matrix[i].last_y = matrix[i].y;
		if (matrix[i].y > WIN_HEIGHT)
		{
			matrix[i].y = 0;
			matrix[i].x = rand() % WIN_WIDTH;
		}
		i++;
	}
}
