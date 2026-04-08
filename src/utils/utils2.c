/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:59:30 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/08 18:11:22 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

void	my_usleep(double seconds)
{
	double	start;
	double	end;

	start = get_time();
	end = get_time();
	while (end - start < seconds)
		end = get_time();
}
