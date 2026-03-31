/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:34:36 by kamys             #+#    #+#             */
/*   Updated: 2026/03/30 21:40:11 by kamys            ###   ########.fr       */
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

t_bool	init_game(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (FALSE);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUBO");
	if (!game->win)
		return (FALSE);
	if (!init_framebuffer(game))
		return (FALSE);
	// if (!load_sprites(game))
	// 	return (FALSE);
	return (TRUE);
}
