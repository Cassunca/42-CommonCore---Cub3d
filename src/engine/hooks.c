/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:08 by cassunca          #+#    #+#             */
/*   Updated: 2026/03/31 18:03:33 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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