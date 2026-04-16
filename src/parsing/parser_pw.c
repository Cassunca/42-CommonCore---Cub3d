/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 16:49:54 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/13 17:49:03 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parse_pw(t_parser *p, char *line)
{
	char	*password;
	size_t	len;

	if (p->game->pw_door)
		return (write_erro("Duplicate password"), FALSE);
	password = line + 3;
	password = ft_strtrim(password, " \t\n");
	if (!password)
		return (FALSE);
	len = ft_strlen(password);
	if (len > 7 || len < 1)
		return (erro_int("invalid size password: Max 7 Min 0", FALSE));
	p->game->pw_door = password;
	return (TRUE);
}
