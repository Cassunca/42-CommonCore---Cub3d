/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 23:59:29 by kamys             #+#    #+#             */
/*   Updated: 2026/04/15 23:21:53 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	destroy_game(t_data *game, t_parser *p)
{
	if (p && p->file)
		free_matrix(p->file);
	free(game->password_input);
	free(game->pw_door);
	free(game->tex_path.no);
	free(game->tex_path.so);
	free(game->tex_path.we);
	free(game->tex_path.ea);
	if (game->map.grid)
		free_matrix(game->map.grid);
	if (game->map.visualizer)
		free_matrix(game->map.visualizer);
}

void	free_matrix(char **splits)
{
	int	k;

	k = -1;
	while (splits[++k])
		free(splits[k]);
	free(splits);
}

static void	free_sprite_array(void *mlx, t_img *sprite, int num_frame)
{
	int	i;

	i = 0;
	while (i < num_frame)
	{
		if (sprite[i].ptr)
			mlx_destroy_image(mlx, sprite[i].ptr);
		i++;
	}
}

void	closer(t_data *game)
{
	mlx_destroy_image(game->mlx, game->logo.ptr);
	mlx_destroy_image(game->mlx, game->logo_42.ptr);
	mlx_destroy_image(game->mlx, game->secret_door.ptr);
	mlx_destroy_image(game->mlx, game->door_tex.ptr);
	mlx_destroy_image(game->mlx, game->tex.ea.ptr);
	mlx_destroy_image(game->mlx, game->tex.no.ptr);
	mlx_destroy_image(game->mlx, game->tex.we.ptr);
	mlx_destroy_image(game->mlx, game->tex.so.ptr);
	mlx_destroy_image(game->mlx, game->frame.ptr);
	free_sprite_array(game->mlx, game->sign_frames, MAX_THAWAN);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game->tex_path.no);
	free(game->tex_path.so);
	free(game->tex_path.we);
	free(game->tex_path.ea);
	free(game->password_input);
	free(game->pw_door);
	if (game->map.grid)
		free_matrix(game->map.grid);
}
