/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 20:45:45 by kamys             #+#    #+#             */
/*   Updated: 2026/03/15 13:17:43 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"



t_bool	parser_configs(t_parser *p)
{
	if (!p->file)
		return (FALSE);
	// while (p->file[p->i])
	// {
	// 	if (is_texture(p->file[p->i]))
	// 		parser_texture(p);
	// 	else if (is_color(p->file[p->i]))
	// 		parser_color(p);
	// 	else
	// 		break ;
	// 	p->i++;
	// }
	return (TRUE);
}

t_bool	parser(char *file, t_data *game)
{
	t_parser	p;

	p.file = read_file(file);
	p.i	= 0;
	p.game = game;
	if (!parser_configs(&p))
		return (FALSE);
	/*
	parser_config(&p);
	// parser_config_tex(&p);
	// parser_config_color(&p);
	parser_map(&p);
	*/
	return (TRUE);
}



/* 
parser = maestro do parser;
parser_config.g = 
Função: interpretar as configurações do arquivo

Ele percorre o começo do arquivo procurando:

NO
SO
WE
EA
F
C

Responsabilidades:

Detectar identificadores

Garantir que não há duplicidade

Chamar funções específicas para cada tipo

Exemplo:

NO ./north.xpm
SO ./south.xpm
F 220,100,0

Esse arquivo decide:

isso é textura → parse_texture
isso é cor → parse_color



parser_texture.c =
Função: processar texturas

Responsável por linhas como:

NO ./textures/north.xpm

Ele deve:

Extrair o path

Validar:

caminho válido

extensão .xpm

arquivo existe

Guardar no struct:

game->map->tex_path->no

Também verifica duplicidade.

parse_color.c
Função: processar cores do chão e teto

Linhas:

F 220,100,0
C 255,255,255

Responsabilidades:

Separar os 3 números

Validar:

apenas números

0–255

Converter para RGB



parser_map = validação do mapa




111111111
100000001
100111001
1001 1001
100111001
100000001
111111111
*/