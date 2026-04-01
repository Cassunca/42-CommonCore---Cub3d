/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:08 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/01 18:44:55 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(int keycode, t_data *game)
{
	if (keycode == KEY_ESC)
	{
		// print_exit();
		printf("flw fia\n");
		closer(game);
		exit(0);
	}
	if (keycode == KEY_D)
		game->player.move_r= 1;
	if (keycode == KEY_A)
		game->player.move_l = 1;
	if (keycode == KEY_W)
		game->player.move_f = 1;
	if (keycode == KEY_S)
		game->player.move_b = 1;
	if (keycode == KEY_LEFT)
		game->player.rot_l = 1;
	if (keycode == KEY_RIGHT)
		game->player.rot_r = 1;
	return (0);
}

int	handle_key_release(int keycode, t_data *game)
{
	if (keycode == KEY_D)
		game->player.move_r = 0;
	if (keycode == KEY_A)
		game->player.move_l = 0;
	if (keycode == KEY_W)
		game->player.move_f = 0;
	if (keycode == KEY_S)
		game->player.move_b = 0;
	if (keycode == KEY_LEFT)
		game->player.rot_l = 0;
	if (keycode == KEY_RIGHT)
		game->player.rot_r = 0;
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