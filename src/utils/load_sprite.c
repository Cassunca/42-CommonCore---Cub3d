/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:16:26 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/15 13:02:00 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

t_bool	load_sprites(t_data *game)
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
	game->logo = load_image(game->mlx, "assets/cub3d_logo.xpm");
	game->logo_42 = load_image(game->mlx, "assets/42_logo.xpm");
	load_array(game, "assets/thawan/xpm/thawan_",
		game->sign_frames, MAX_THAWAN);
	return (TRUE);
}
