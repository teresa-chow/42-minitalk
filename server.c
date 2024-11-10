/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:44:05 by tchow-so          #+#    #+#             */
/*   Updated: 2024/11/10 10:47:24 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_server(int sig, siginfo_t *info, void *context);
static void	receive_len(int signal, t_msg *msg);
static void	receive_str(int signal, t_msg *msg);
static void	print_msg(t_msg *msg);

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	block_signals(&sa);
	sa.sa_sigaction = &handle_server;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	set_sigaction(&sa);
	ft_printf("Server PID: %d\nListening...\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/* Server signal handler */
static void	handle_server(int signal, siginfo_t *info, void *context)
{
	static t_msg	msg = {0};

	(void)info;
	(void)context;
	if (!msg.active && (signal == SIGUSR1 || signal == SIGUSR2))
		receive_len(signal, &msg);
	if (msg.active && !msg.str)
	{
		msg.str = ft_calloc(msg.len + 1, sizeof(char));
		if (!msg.str)
			printerr_exit("Memory allocation failed.\n");
	}
	else if (msg.active && (signal == SIGUSR1 || signal == SIGUSR2))
		receive_str(signal, &msg);
}

static void	receive_len(int signal, t_msg *msg)
{
	static int	bitshift = (sizeof(int) * 8) - 1;

	if (bitshift > -1)
	{
		if (signal == SIGUSR2)
			msg->len |= (1 << bitshift);
		if (signal == SIGUSR1)
			msg->len |= (0 << bitshift);
		bitshift--;
	}
	if (!msg->active && (bitshift == -1))
		msg->active = 1;
	if (msg->active)
		bitshift = (sizeof(int) * 8) - 1;
}

static void	receive_str(int signal, t_msg *msg)
{
	static int			bitshift = (sizeof(char) * 8) - 1;
	static unsigned int	i = 0;

	if (bitshift > -1)
	{
		if (signal == SIGUSR2)
			msg->str[i] |= (1 << bitshift);
		if (signal == SIGUSR1)
			msg->str[i] |= (0 << bitshift);
		bitshift--;
	}
	if (bitshift == -1)
	{
		bitshift = (sizeof(char) * 8) - 1;
		i++;
		if (i == (msg->len + 1))
		{
			print_msg(msg);
			i = 0;
		}
	}
}

static void	print_msg(t_msg *msg)
{
	int	i;

	i = 0;
	while (msg->str[i])
	{
		write(1, &msg->str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	free(msg->str);
	msg->str = NULL;
	msg->active = 0;
	msg->len = 0;
}
