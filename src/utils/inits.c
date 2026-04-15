/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:34:36 by kamys             #+#    #+#             */
/*   Updated: 2026/04/15 17:55:03 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_keypad(t_data *game, t_point pos, t_point size, t_point spacing);
void	init_sprites(t_data *g);

static t_bool	init_framebuffer(t_data *game)
{
	int	w;
	int	h;

	w = WIN_WIDTH;
	h = WIN_HEIGHT;
	game->frame.ptr = mlx_new_image(game->mlx, w, h);
	if (!game->frame.ptr)
		return (FALSE);
	game->frame.addr = mlx_get_data_addr(game->frame.ptr, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (FALSE);
	game->frame.width = w;
	game->frame.height = h;
	return (TRUE);
}

void	init_matrix(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < MAX_MATRIX)
	{
		matrix[i].x = rand() % WIN_WIDTH;
		matrix[i].y = rand() % WIN_HEIGHT;
		matrix[i].speed = 50 + rand() % 100;
		matrix[i].c = rand() % 94 + 33;
		matrix[i].char_delay = 0.1 + (rand() % 100) / 1000.0;
		i++;
	}
}

void	init_buttons(t_data *game)
{
	t_point	pos;
	t_point	size;

	size.x = 360;
	size.y = 40;
	pos.x = (WIN_WIDTH / 2) - (size.x / 2);
	pos.y = WIN_HEIGHT / 2 + 65;
	game->btn[0] = create_button(
			pos,
			size,
			"OPEN FILE", play_action);
	pos.y = WIN_HEIGHT / 2 + 120;
	game->btn[1] = create_button(
			pos,
			size,
			"TERMINATE SESSION", quit_action);
}

static void	setup_keypad(t_data *game)
{
	t_point	size;
	t_point	pos;
	t_point	start;
	t_point	btn_size;
	t_point	spacing;

	size = (t_point){400, 500};
	pos = (t_point){
		.x = (game->frame.width - size.x) / 2,
		.y = (game->frame.height - size.y) / 2
	};
	btn_size = (t_point){84, 50};
	spacing = (t_point){14, 15};
	start = (t_point){
		.x = pos.x + (size.x - ((3 * btn_size.x) + (2 * spacing.x))) / 2,
		.y = pos.y + 220
	};
	init_keypad(game, start, btn_size, spacing);
}

t_bool	init_game(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (FALSE);
	if (!load_sprites(game))
		return (FALSE);
	if (!init_framebuffer(game))
		return (FALSE);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "CUBO");
	if (!game->win)
		return (FALSE);
	init_matrix(game->matrix);
	init_buttons(game);
	init_doors(game);
	setup_keypad(game);
	init_sprites(game);
	game->screen = TITLE;
	game->password_len = 0;
	game->password_input[0] = '\0';
	return (TRUE);
}
