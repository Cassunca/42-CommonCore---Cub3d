/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 13:35:24 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_sprites(t_data *g)
{
	t_sprite	*s;
	int			i;
	double		now;

	now = get_time();
	i = 0;
	while (i < g->sprite_count)
	{
		s = &g->sprites[i];
		if (now - s->last_update >= s->delay)
		{
			s->current_frame = (s->current_frame + 1)
				% s->frame_count;
			s->last_update = now;
		}
		i++;
	}
}

static void	update(t_data *game, double frame_time,
					double *acc, double tick)
{
	while (*acc >= tick)
	{
		if (game->screen == TITLE)
			update_matrix(game->matrix, tick);
		if (game->screen == GAME)
		{
			update_doors(game);
			handle_mouse(game);
			move_player(game);
		}
		*acc -= tick;
	}
	if (game->screen == GAME)
		update_sprites(game);
	update_button_text(&game->btn[0], frame_time);
	update_button_text(&game->btn[1], frame_time);
}

static void	render_frame(t_data *game)
{
	static int		mouse_hidden = FALSE;

	if (game->screen == TITLE)
	{
		mlx_clear_window(game->mlx, game->win);
		render_title(game);
	}
	else if (game->screen == GAME)
	{
		if (!mouse_hidden)
		{
			mlx_mouse_hide(game->mlx, game->win);
			mouse_hidden = FALSE;
		}
		execute_raycast(game);
	}
	else if (game->screen == PASSWORD_INPUT)
	{
		render_door_keypad(game);
		mouse_hidden = FALSE;
	}
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
	render_frame(game);
	fps_limiter(cur, 244.0);
	return (0);
}
