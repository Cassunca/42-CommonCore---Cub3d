/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/01 18:59:54 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps_limiter(double current, double fps)
{
	double	frame_end;
	double	frame_duration;
	double	target_frame_time;

	if (fps == 0.0)
		return ;
	frame_end = get_time();
	frame_duration = frame_end - current;
	target_frame_time = 1.0 / fps;
	if (frame_duration < target_frame_time)
		my_usleep(target_frame_time - frame_duration);
}

void	render(t_data *game, double alpha)
{
	(void)alpha;
	// render_background(game, game->colors.ceiling, game->colors.floor);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

void	render_title(t_data *game)
{
	// render_background(game, 0x87CEEB, 0x8B4513);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	game->btn.x = 400;
	game->btn.y = 300;
	game->btn.width = 200;
	game->btn.height = 80;
	mlx_string_put(game->mlx, game->win, 450, 340, 0xFFFFFF, "PLAY");
}

int	game_loop(t_data *game)
{
	static double	accumulator = 0.0;
	static double	previos = 0.0;
	double			current;
	double			frame_time;
	const double	tick_rate = 1.0 / 240.0;

	if (previos == 0)
		previos = get_time();
	current = get_time();
	frame_time = current - previos;
	previos = current;
	if (frame_time > 0.25)
		frame_time = 0.25;
	accumulator += frame_time;
	while (accumulator >= tick_rate)
	{
		accumulator -= tick_rate;
	}
	mlx_clear_window(game->mlx, game->win);
	if (game->screen == TITLE)
		render_title(game);
	else if (game->screen == GAME)
		render(game, (accumulator / tick_rate));
	fps_limiter(current, 244.0);
	return (0);
}
