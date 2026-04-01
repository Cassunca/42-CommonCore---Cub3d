/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:34:36 by kamys             #+#    #+#             */
/*   Updated: 2026/04/01 18:01:53 by amyrodri         ###   ########.fr       */
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

static t_img	load_image(void *mlx, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.ptr)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("fail load sprites\n", 2);
		return ((t_img){0});
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

static t_bool	load_sprites(t_data *game)
{
	game->tex.ea = load_image(game->mlx, game->tex_path.ea);
	if (!game->tex.ea.ptr)
		return (FALSE);
	game->tex.no = load_image(game->mlx, game->tex_path.no);
	if (!game->tex.no.ptr)
		return (FALSE);
	game->tex.so = load_image(game->mlx, game->tex_path.so);
	if (!game->tex.so.ptr)
		return (FALSE);
	game->tex.we = load_image(game->mlx, game->tex_path.we);
	if (!game->tex.we.ptr)
		return (FALSE);
	return (TRUE);
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
	game->screen = TITLE;
	return (TRUE);
}
