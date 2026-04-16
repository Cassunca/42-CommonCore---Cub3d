/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_title.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:03:22 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 12:59:00 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "types.h"

void	draw_header(t_data *game, int panel_x, int panel_y)
{
	mlx_set_font(game->mlx, game->win, "9x15");
	mlx_string_put(game->mlx, game->win,
		panel_x + 25, panel_y + 40, 0xFF5555,
		"[ CONFIDENTIAL FILE ]");
	mlx_string_put(game->mlx, game->win,
		panel_x + 20, panel_y + 80, 0xAAAAAA,
		"Project: #######");
	mlx_string_put(game->mlx, game->win,
		panel_x + 20, panel_y + 100, 0xAAAAAA,
		"Status:");
	mlx_string_put(game->mlx, game->win,
		panel_x + 90, panel_y + 100, 0x00FF88,
		"ACTIVE");
	mlx_string_put(game->mlx, game->win,
		panel_x + 20, panel_y + 120, 0xAAAAAA,
		"Clearance:");
	mlx_string_put(game->mlx, game->win,
		panel_x + 120, panel_y + 120, 0xFF4444,
		"DENIED");
	mlx_set_font(game->mlx, game->win, "fixed");
}

void	draw_sub_title(t_data *game, int panel_x, int panel_w, int panel_y)
{
	static char	*str = "V.0 | ENCRYPTED BUILD | [####]";
	int			char_width;
	int			text_width;

	char_width = 6;
	text_width = ft_strlen(str) * char_width;
	mlx_string_put(game->mlx, game->win,
		panel_x + (panel_w / 2) - (text_width / 2), panel_y + 265,
		0x445566, str);
}

void	draw_content(t_data *game, int panel_x, int panel_w, int panel_y)
{
	draw_sub_title(game, panel_x, panel_w, panel_y);
	mlx_set_font(game->mlx, game->win, "9x15");
	draw_text_button(game, &game->btn[0]);
	draw_text_button(game, &game->btn[1]);
	mlx_set_font(game->mlx, game->win, "fixed");
	mlx_string_put(game->mlx, game->win,
		panel_x + 330, panel_y + 435, 0x445566, get_time_str());
	mlx_string_put(game->mlx, game->win,
		panel_x + 20, panel_y + 435, 0x445566, "FILE #0047");
	mlx_string_put(game->mlx, game->win,
		10, 590, 0xffffff, "By: Amyrodri and Cassunca");
}

void	render_title(t_data *game)
{
	int		panel_w;
	int		panel_h;
	int		panel_x;
	int		panel_y;

	panel_w = 400;
	panel_h = 450;
	panel_x = (game->frame.width - panel_w) / 2;
	panel_y = (game->frame.height - panel_h) / 2;
	draw_sky(game, 0x0A0A12, 0x0A0A1A);
	draw_panel(&game->frame, panel_w, panel_h);
	draw_lines(game, panel_w, panel_y);
	draw_sprite_to_frame(game, &game->logo,
		(game->frame.width / 2) - (game->logo.width / 2),
		(game->frame.height / 2) - (game->logo.height / 2) - 30);
	draw_button(game, &game->btn[0]);
	draw_button(game, &game->btn[1]);
	draw_sprite_to_frame(game, &game->logo_42, 770, 570);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.ptr, 0, 0);
	draw_matrix(game->matrix, game->mlx, game->win);
	draw_header(game, panel_x, panel_y);
	draw_content(game, panel_x, panel_w, panel_y);
}
