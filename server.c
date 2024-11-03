/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:49:57 by tchow-so          #+#    #+#             */
/*   Updated: 2024/11/03 11:34:18 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	block_signals(struct sigaction *sa);
static void	set_sigaction(struct sigaction *sa);
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

/* Blocking signals during the execution of the handler:
this set of signals will not interrupt the execution of the handler */
static void	block_signals(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGINT);
	sigaddset(&sa->sa_mask, SIGQUIT);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
}

/* sigaction examines and sets the action to be associated with a signal */
static void	set_sigaction(struct sigaction *sa)
{
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		printerr_exit("sigaction() failed to handle SIGUSR1\n");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		printerr_exit("sigaction() failed to handle SIGUSR2\n");
}

/* Server signal handler */
static void	handle_server(int signal, siginfo_t *info, void *context)
{
	static t_msg	*msg = {0};
	
	(void)info;
	(void)context;
	if (!msg)
	{
		msg = ft_calloc(1, sizeof(msg));
		ft_printf(" msg->active: %d ", msg->active);
		if (!msg)
			printerr_exit("Memory allocation failed.\n");
		msg->active = 0;
	}
	if (msg->active && (signal == SIGUSR1 || signal == SIGUSR2))
		receive_str(signal, msg);
	if (!msg->active && (signal == SIGUSR1 || signal == SIGUSR2))
		receive_len(signal, msg);
	if (msg->active && !msg->str)
	{
		msg->str = ft_calloc(msg->len + 1, sizeof(char));
		if (!msg->str)
			printerr_exit("Memory allocation failed.\n");
	}
}

static void	receive_len(int signal, t_msg *msg)
{
	static int	bitshift = (sizeof(int) * 8) - 1;
	
	if (bitshift > -1)
	{
		if (signal == SIGUSR2)
		{
			ft_printf("1");
			msg->len |= (1 << bitshift);
		}
		if (signal == SIGUSR1)
		{
			ft_printf("0");
			msg->len |= (0 << bitshift);
		}
		bitshift--;
	}
	if (!msg->active && (bitshift == -1))
	{
		msg->active = 1;
		ft_printf("msg->len: %d\n", msg->len);
	}
	if (msg->active)
		bitshift = (sizeof(int) * 8) - 1;
	return ;
}

static void	receive_str(int signal, t_msg *msg)
{
	static int	bitshift = (sizeof(char) * 8) - 1;
	static unsigned int i = 0;
	
	if (bitshift > -1)
	{
		if (signal == SIGUSR2)
		{
			ft_printf("1");
			msg->str[i] |= (1 << bitshift);
		}
		if (signal == SIGUSR1)
		{
			ft_printf("0");
			msg->str[i] |= (0 << bitshift);
		}
		bitshift--;
	}
	if (bitshift == -1)
	{
		ft_printf("\n");
		bitshift = (sizeof(char) * 8) - 1;
		i++;
		msg->str[i] = '\0';
		if (!msg->end && i == (msg->len + 1))
		{
			print_msg(msg);
			i = 0;
		}
	}
	return ;
}

static void	print_msg(t_msg *msg)
{
	/*unsigned int	i;

	i = 0;
	while (i < (msg->len + 1))
	{
		write(1, &msg->str[i], msg->len + 1);
		i++;
	}*/
	ft_printf("%s", msg->str);
	free(msg->str);
	return ;
}