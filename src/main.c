/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/03/12 19:13:47 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	// t_game	game;

	(void)av;
	if (ac != 2)
		return (ft_putstr_fd("usage: ./bin/cub3d map.cub", STDERR_FILENO), 1);
	/*	
	if (init_game(&game))
		return (1);
	
	if (parse_map(av[1], &game))
		return (free_game(&game), 1);
		
	init_player(&game);
	init_mlx(&game);
	
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->win, 17, 0l, close_window, game);
	
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	*/
	return (0);
}
