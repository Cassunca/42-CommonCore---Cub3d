/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:34:36 by kamys             #+#    #+#             */
/*   Updated: 2026/04/09 13:20:30 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	init_framebuffer(t_data *game)
{
	int	w;
	int	h;

	w = WIN_WIDTH;
	h = WIN_HEIGHT;
	game->frame.ptr = mlx_new_image(game->mlx, w, h);
	if (!game->frame.ptr)
		return (FALSE);
	game->frame.addr = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (FALSE);
	game->frame.width = w;
	game->frame.height = h;
	return (TRUE);
}

void	init_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < MAX_MATRIX)
	{
		matrix[i].x = rand() % WIN_WIDTH;
		matrix[i].y = rand() % WIN_HEIGHT;
		matrix[i].speed = 50 + rand() % 100;
		matrix[i].c = rand() % 94 + 33;
		matrix[i].char_delay = 0.1 + (rand() % 100) / 1000.0;
		i++;
	}
}

void	init_buttons(t_data *game)
{
	t_point	pos;
	t_point	size;

	size.x = 360;
	size.y = 40;
	pos.x = (WIN_WIDTH / 2) - (size.x / 2);
	pos.y = WIN_HEIGHT / 2 + 65;
	game->btn[0] = create_button(
			pos,
			size,
			"OPEN FILE", play_action);
	pos.y = WIN_HEIGHT / 2 + 120;
	game->btn[1] = create_button(
			pos,
			size,
			"TERMINATE SESSION", quit_action);
}

t_bool	init_game(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (FALSE);
	if (!load_sprites(game))
		return (FALSE);
	if (!init_framebuffer(game))
		return (FALSE);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUBO");
	if (!game->win)
		return (FALSE);
	init_matrix(game->matrix);
	init_buttons(game);
	game->screen = TITLE;
	init_doors(game);
	return (TRUE);
}
