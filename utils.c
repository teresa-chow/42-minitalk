/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:17 by tchow-so          #+#    #+#             */
/*   Updated: 2024/10/29 11:43:56 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	printerr_exit(char *str)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	exit(EXIT_FAILURE);
}

/*void	send_bit(pid_t pid, unsigned char bit, bool pause_flag)
{
	if ((bit == 0) && (kill(pid, SIGUSR1) == -1))
			printerr_exit("kill() failed to send SIGUSR1\n");
	else if ((bit == 1) && (kill(pid, SIGUSR2) == -1))
			printerr_exit("kill() failed to send SIGUSR2\n");
	if (pause_flag)
		usleep(PAUSE);
}*/
