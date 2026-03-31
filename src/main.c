/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:52 by cassunca          #+#    #+#             */
/*   Updated: 2026/03/30 21:45:14 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_data *game)
{
	if (!game)
		return ;
	// destroy_game(game, NULL);
	free(game);
}

void	closer(t_data *game)
{
	mlx_destroy_image(game->mlx, game->frame.ptr);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->tex_path.no);
	free(game->tex_path.so);
	free(game->tex_path.we);
	free(game->tex_path.ea);
	if (game->map.grid)
		free_matrix(game->map.grid);
}

int	handle_key(int keycode, t_data *game)
{
	(void)game;
	if (keycode == KEY_ESC)
	{
		// print_exit();
		printf("flw fia\n");
		closer(game);
		exit(0);
	}
	// if (keycode == KEY_D || keycode == KEY_RIGHT)
	// 	game->player.right_pressed = 1;
	// if (keycode == KEY_A || keycode == KEY_LEFT)
	// 	game->player.left_pressed = 1;
	// if (keycode == KEY_W || keycode == KEY_UP)
	// 	game->player.jump_pressed = 1;
	return (0);
}

int	handle_key_release(int keycode, t_data *game)
{
	(void)keycode;
	(void)game;
	// if (keycode == KEY_D || keycode == KEY_RIGHT)
	// 	game->player.right_pressed = 0;
	// if (keycode == KEY_A || keycode == KEY_LEFT)
	// 	game->player.left_pressed = 0;
	// if (keycode == KEY_W || keycode == KEY_UP)
	// 	game->player.jump_pressed = 0;
	return (0);
}

int	close_window(void *param)
{
	// print_exit();
	printf("flw fia\n");
	closer((t_data *)param);
	exit(0);
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
	// mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
