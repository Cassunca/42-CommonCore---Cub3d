/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/07 14:38:04 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include "cub3d.h"

int	get_pixel(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	handle_button_click(t_data *game, t_button *btn, int mouse_x, int mouse_y)
{
	int	px;
	int	py;
	int	color;

	if (mouse_x >= btn->x && mouse_x < btn->x + btn->img->width
	 && mouse_y >= btn->y && mouse_y < btn->y + btn->img->height)
	{
		px = mouse_x - btn->x;
		py = mouse_y - btn->y;
		color = get_pixel(btn->img, px, py);

		if ((color & 0x00FFFFFF) != 0xFF00FF)
			btn->on_click(game);
	}
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data	*game;
	int		i;

	game = (t_data *)param;

	if (game->screen != TITLE || button != 1)
		return (0);

	i = 0;
	while (i < MAX_BTNS)
	{
		handle_button_click(game, &game->btn[i], x, y);
		i++;
	}
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_data		*game;
	t_button	*btn;
	int			i;
	int			px;
	int			py;
	int			color;

	game = (t_data *)param;

	if (game->screen == GAME)
	{
		
	}
	
	i = 0;
	while (i < MAX_BTNS)
	{
		btn = &game->btn[i];
		btn->is_hover = FALSE;

		if (x >= btn->x && x < btn->x + btn->img->width
		 && y >= btn->y && y < btn->y + btn->img->height)
		{
			px = x - btn->x;
			py = y - btn->y;
			color = get_pixel(btn->img, px, py);
			if ((color & 0x00FFFFFF) != 0xFF00FF)
				btn->is_hover = TRUE;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	game;

	if (ac != 2)
		return (ft_putstr_fd(USAGE, STDERR_FILENO), EXIT_FAILURE);
	ft_bzero(&game, sizeof(game));
	if (!parser(av[1], &game))
		return (EXIT_FAILURE);
	if (!init_game(&game))
		return (EXIT_FAILURE);
	mlx_hook(game.win, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.win, 3, 1L << 1, handle_key_release, &game);
	mlx_hook(game.win, 17, 0l, close_window, &game);
	mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);
	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
