/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_button.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 19:41:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 00:03:33 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	start_glitch(t_button *b)
{
	if (b->is_hover && !b->was_hover)
	{
		b->glitch_timer = 0.4;
		b->glitch_frame_timer = 0;
		b->glitching = 1;
		b->has_glitched = 0;
	}
	b->was_hover = b->is_hover;
}

static int	base_state(t_button *b)
{
	if (!b->is_hover)
	{
		b->glitching = 0;
		b->has_glitched = 0;
		ft_strlcpy(b->render_text, b->text, sizeof(b->render_text));
		return (1);
	}
	if (b->has_glitched)
	{
		ft_strlcpy(b->render_text, b->text, sizeof(b->render_text));
		return (1);
	}
	return (0);
}

static void	apply_glitch(t_button *b)
{
	const char	cs[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%&";
	int			i;

	ft_strlcpy(b->render_text, b->text, sizeof(b->render_text));
	i = 0;
	while (b->render_text[i])
	{
		if (rand() % 100 < 40)
			b->render_text[i] = cs[rand() % (sizeof(cs) - 1)];
		i++;
	}
}

static int	update_timers(t_button *b, double dt)
{
	b->glitch_timer -= dt;
	if (b->glitch_timer <= 0)
	{
		b->glitching = 0;
		b->has_glitched = 1;
		ft_strlcpy(b->render_text, b->text, sizeof(b->render_text));
		return (1);
	}
	b->glitch_frame_timer -= dt;
	if (b->glitch_frame_timer > 0)
		return (1);
	b->glitch_frame_timer = 0.08;
	return (0);
}

void	update_button_text(t_button *b, double dt)
{
	start_glitch(b);
	if (base_state(b))
		return ;
	if (update_timers(b, dt))
		return ;
	apply_glitch(b);
}
