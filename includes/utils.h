/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:47:58 by kamys             #+#    #+#             */
/*   Updated: 2026/04/13 01:07:39 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"
# include "types.h"

# define PANEL_W 400
# define PANEL_H 500

# define INPUT_W 280
# define INPUT_H 90

# define DOT_SIZE 12
# define DOT_SPACING 30
# define DOT_COUNT 4

# define STATUS_H 35

typedef struct s_data	t_data;
typedef struct s_parser	t_parser;
typedef struct s_button	t_button;

void		write_erro(char *s);
int			erro_int(char *s, int exit_code);
char		**erro_matrix(char *s);

void		free_matrix(char **splits);
void		destroy_game(t_data *game, t_parser *p);

int			ft_isspace(int c);
int			is_empty_line(char *line);

t_bool		is_player(char p);
void		set_vec2(double x, double y, double *tx, double *ty);

t_bool		init_game(t_data *game);
void		closer(t_data *game);

double		lerp(double prev, double x, double alpha);

double		get_time(void);
void		my_usleep(double seconds);

t_bool		load_sprites(t_data *game);
t_button	create_button(t_point pos, t_point size, char *text,
				void (*on_click)(void *));
// t_button	create_button(int x, int y, int w, int h, char *text,
// 				void (*on_click)(void *));
void		quit_action(void *param);
void		play_action(void *param);

int			mouse_hook(int button, int x, int y, void *param);
int			mouse_move(int x, int y, void *param);

void		update_button_text(t_button *b, double dt);

// core
void		put_pixel(t_img *img, int x, int y, int color);
void		draw_sprite_to_frame(t_data *game, t_img *sprite, int x, int y);
int			brighten(int color, float factor);

// shapes
void		draw_rect(t_img *img, t_point pos, t_point size, int color);
void		draw_border(t_img *img, t_point pos, t_point size, int color);
void		draw_triangle(t_img *img, t_point pos, int size, int color);
void		draw_line(t_img *img, t_line *l, int color);

// background
void		draw_sky(t_data *game, int top_color, int bottom_color);

// ui
void		draw_button(t_data *g, t_button *btn);
void		draw_text_button(t_data *g, t_button *btn);;
void		draw_panel(t_img *img, int w, int h);
void		draw_header(t_data *game, int panel_x, int panel_y);
void		draw_content(t_data *game, int panel_x, int panel_w, int panel_y);

// matrix
void		draw_matrix(t_matrix *matrix, void *mlx, void *win);
void		update_matrix(t_matrix *matrix, float dt);

// loop
int			game_loop(t_data *game);

// utils
char		*get_time_str(void);
void		fps_limiter(double current, double fps);

void		render_title(t_data *game);
void		draw_lines(t_data *game, int panel_w, int panel_y);
void		draw_shape(t_img *img, t_shape s);

#endif
