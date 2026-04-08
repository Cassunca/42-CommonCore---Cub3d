/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:34:36 by kamys             #+#    #+#             */
/*   Updated: 2026/04/09 13:17:19 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

static t_img	load_image(void *mlx, char *path)
{
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (!img.ptr)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("fail load sprites\n", 2);
		return ((t_img){0});
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.line_len, &img.endian);
	return (img);
}

void	load_array(t_data *game, char *mid_path,
	t_img *frames, int num_frames)
{
	int		i;
	char	*path;
	char	*num;
	char	*tmp;

	i = 0;
	while (i < num_frames)
	{
		num = ft_itoa(i);
		tmp = ft_strjoin(mid_path, num);
		free(num);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		frames[i] = load_image(game->mlx, path);
		free(path);
		i++;
	}
}

static t_bool	load_sprites(t_data *game)
{
	game->tex.ea = load_image(game->mlx, game->tex_path.ea);
	if (!game->tex.ea.ptr)
		return (FALSE);
	game->tex.no = load_image(game->mlx, game->tex_path.no);
	if (!game->tex.no.ptr)
		return (FALSE);
	game->tex.so = load_image(game->mlx, game->tex_path.so);
	if (!game->tex.so.ptr)
		return (FALSE);
	game->tex.we = load_image(game->mlx, game->tex_path.we);
	if (!game->tex.we.ptr)
		return (FALSE);
	game->door_tex = load_image(game->mlx, "assets/door.xpm");
	game->secret_door = load_image(game->mlx, "assets/secret_door.xpm");
	game->imagem_start = load_image(game->mlx, "assets/start.xpm");
	game->imagem_quit = load_image(game->mlx, "assets/quit.xpm");
	game->logo = load_image(game->mlx, "assets/cub3d_logo.xpm");
	game->logo_42 = load_image(game->mlx, "assets/42_logo.xpm");
	return (TRUE);
}

void	play_action(void *param)
{
	t_data *game = (t_data *)param;
	printf("play\n");
	game->screen = GAME;
}

void	quit_action(void *param)
{
	(void)param;
	close_window(param);
	exit(0);
}

t_button	create_button(int x, int y, int w, int h, char *text,
	void (*on_click)(void *))
{
	t_button	btn;

	btn.x = x;
	btn.y = y;
	btn.w = w;
	btn.h = h;

	btn.text = text;

	btn.on_click = on_click;

	btn.is_hover = FALSE;
	btn.glitching = 0;
	btn.glitch_timer = 0;

	// começa com texto normal
	ft_strlcpy(btn.render_text, text, sizeof(btn.render_text));

	return (btn);
}

void init_matrix(t_matrix *matrix)
{
	for (int i = 0; i < MAX_MATRIX; i++)
	{
		matrix[i].x = rand() % WIN_WIDTH;
		matrix[i].y = rand() % WIN_HEIGHT;
		matrix[i].speed = 50 + rand() % 100;
		matrix[i].c = rand() % 94 + 33; // ASCII visível
		matrix[i].char_delay = 0.1 + (rand() % 100) / 1000.0;
	}
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
		return (FALSE);;
	init_matrix(game->matrix);
	
	game->btn[0] = create_button(
	WIN_WIDTH / 2 - (360 / 2),
	WIN_HEIGHT / 2 + 85,
	360,
	40,
	"OPEN FILE",
	play_action);

	game->btn[1] = create_button(
	WIN_WIDTH / 2 - (360 / 2),
	WIN_HEIGHT / 2 + 140,
	360,
	40,
	"TERMINATE SESSION",
	quit_action);
	
	game->screen = TITLE;
	init_doors(game);
	return (TRUE);
}
