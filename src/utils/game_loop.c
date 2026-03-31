/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/03/31 17:42:48 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

static void	my_usleep(double seconds)
{
	double	start;
	double	end;

	start = get_time();
	end = get_time();
	while (end - start < seconds)
		end = get_time();
}

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

// alpha para interpolação, salvar onde estava e onde esta agora
// , e quanto já andamos
void	render(t_data *game, double alpha)
{
	(void)alpha;
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
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
	render(game, (accumulator / tick_rate));
	fps_limiter(current, 244.0);
	return (0);
}
