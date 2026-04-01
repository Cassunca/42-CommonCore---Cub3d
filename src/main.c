/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/01 18:34:45 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_data *game = (t_data *)param;

	if (game->screen == TITLE && button == 1)
	{
		if (x >= game->btn.x && x <= game->btn.x + game->btn.width
		 && y >= game->btn.y && y <= game->btn.y + game->btn.height)
		{
			printf("PLAY!\n");
			game->screen = GAME;
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	game;

	(void)av;
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
	mlx_mouse_hook(game.win, mouse_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
