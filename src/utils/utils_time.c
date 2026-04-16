/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:06:46 by amyrodri          #+#    #+#             */
/*   Updated: 2026/04/09 00:27:34 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void	fps_limiter(double current, double fps)
{
	double	frame_end;
	double	frame_duration;
	double	target_frame_time;

	if (fps == 0.0)
		return ;
	frame_end = get_time();
	frame_duration = frame_end - current;
	target_frame_time = 1.0 / fps;
	if (frame_duration < target_frame_time)
		my_usleep(target_frame_time - frame_duration);
}

char	*get_time_str(void)
{
	static char	buffer[9];
	time_t		rawtime;
	struct tm	*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	buffer[0] = (timeinfo->tm_hour / 10) + '0';
	buffer[1] = (timeinfo->tm_hour % 10) + '0';
	buffer[2] = ':';
	buffer[3] = (timeinfo->tm_min / 10) + '0';
	buffer[4] = (timeinfo->tm_min % 10) + '0';
	buffer[5] = ':';
	buffer[6] = (timeinfo->tm_sec / 10) + '0';
	buffer[7] = (timeinfo->tm_sec % 10) + '0';
	buffer[8] = '\0';
	return (buffer);
}
