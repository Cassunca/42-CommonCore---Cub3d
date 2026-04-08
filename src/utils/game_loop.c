/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 13:19:46 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *game, double alpha)
{
	(void)alpha;
	draw_sky(game, game->colors.ceiling, game->colors.floor);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
}

static void	update(t_data *game, double frame_time,
					double *acc, double tick)
{
	while (*acc >= tick)
	{
		update_matrix(game->matrix, tick);
		*acc -= tick;
	}
	update_button_text(&game->btn[0], frame_time);
	update_button_text(&game->btn[1], frame_time);
}

static void	render_frame(t_data *game, double interp)
{
	mlx_clear_window(game->mlx, game->win);
	if (game->screen == TITLE)
		render_title(game);
	else if (game->screen == GAME)
		render(game, interp);
}

int	game_loop(t_data *game)
{
	static double	acc = 0.0;
	static double	prev = 0.0;
	double			cur;
	double			frame;
	const double	tick = 1.0 / 240.0;

	if (prev == 0)
		prev = get_time();
	cur = get_time();
	frame = cur - prev;
	prev = cur;
	if (frame > 0.25)
		frame = 0.25;
	acc += frame;
	update(game, frame, &acc, tick);
	render_frame(game, acc / tick);
	fps_limiter(cur, 244.0);
	return (0);
}
