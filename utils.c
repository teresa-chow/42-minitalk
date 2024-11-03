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

/* Blocking signals during the execution of the handler:
this set of signals will not interrupt the execution of the handler */
void	block_signals(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
}

/* sigaction examines and sets the action to be associated with a signal */
void	set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		printerr_exit("sigaction() failed to handle SIGUSR1\n");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		printerr_exit("sigaction() failed to handle SIGUSR2\n");
}

void	send_bit(pid_t pid, int bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			printerr_exit("kill() failed to send SIGUSR1\n");
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			printerr_exit("kill() failed to send SIGUSR2\n");
	}
	usleep(PAUSE);
}