/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:47:58 by kamys             #+#    #+#             */
/*   Updated: 2026/03/31 16:12:13 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"
# include "types.h"

typedef struct s_data	t_data;
typedef struct s_parser	t_parser;

void	write_erro(char *s);
int		erro_int(char *s, int exit_code);
char	**erro_matrix(char *s);

void	free_matrix(char **splits);
void	destroy_game(t_data *game, t_parser *p);

int		ft_isspace(int c);
int		is_empty_line(char *line);

t_bool	is_player(char p);
void	set_vec2(double x, double y, double *tx, double *ty);

t_bool	init_game(t_data *game);
void	closer(t_data *game);

#endif
