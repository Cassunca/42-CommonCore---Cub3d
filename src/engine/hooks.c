/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:02:08 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/15 12:27:37 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <string.h>

void	open_secret_door(t_data *game);

int	handle_mouse(t_data *data)
{
	int		x;
	int		y;
	double	delta_x;
	double	sensitivity;

	sensitivity = 0.002;
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	delta_x = x - (WIN_WIDTH / 2);
	if (delta_x != 0)
	{
		apply_rotation(&data->player, delta_x * sensitivity);
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	return (0);
}

int	handle_password_input(int key, t_data *data)
{
	if (key == KEY_ENTER)
	{
		data->password_input[data->password_len] = '\0';
		if (strcmp(data->password_input, data->pw_door) == 0)
			open_secret_door(data);
		data->screen = GAME;
	}
	else if (key == KEY_BACKSPACE)
	{
		data->password_len = 0;
		data->password_input[0] = '\0';
	}
	else if (key == KEY_ESC)
	{
		data->screen = GAME;
		return (0);
	}
	else if (data->password_len < (int)ft_strlen(data->pw_door)
		&& ft_isdigit(key))
	{
		data->password_input[data->password_len++] = key;
		data->password_input[data->password_len] = '\0';
	}
	return (0);
}

int	handle_key(int keycode, t_data *game)
{
	if (game->screen == PASSWORD_INPUT)
		return (handle_password_input(keycode, game));
	if (keycode == KEY_ESC)
	{
		closer(game);
		exit(0);
	}
	if (keycode == KEY_D)
		game->player.move_r = 1;
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
	if (keycode == KEY_SPACE)
		open_door(game);
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
	closer((t_data *)param);
	exit(0);
	return (0);
}
