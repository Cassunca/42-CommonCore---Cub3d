/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 00:47:38 by kamys             #+#    #+#             */
/*   Updated: 2026/03/15 13:10:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	write_erro(char *s)
{
	if (!s)
		s = "Unknown error";
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
}

int	erro_int(char *s, int exit_code)
{
	write_erro(s);
	return (exit_code);
}

char	**erro_matrix(char *s)
{
	write_erro(s);
	return (NULL);
}
