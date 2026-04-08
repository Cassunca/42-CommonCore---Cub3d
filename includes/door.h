/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:03:44 by cassunca          #+#    #+#             */
/*   Updated: 2026/04/08 16:29:25 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include <stddef.h>

typedef struct s_data	t_data;

typedef struct s_door
{
	int		x;
	int		y;
	double	open;
	int		opening;
}	t_door;

void	update_doors(t_data	*game);
t_door	*find_door(t_data *game, int x, int y);
void	open_door(t_data *game);
void	init_doors(t_data *game);

#endif
