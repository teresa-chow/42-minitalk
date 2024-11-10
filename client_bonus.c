/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:36:19 by tchow-so          #+#    #+#             */
/*   Updated: 2024/11/10 11:24:21 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	check_error(int argc, char **argv);
static void	send_msg(pid_t pid, const char *msg);
static void	send_len(pid_t pid, unsigned int len);
static void	send_char(pid_t pid, unsigned char c);

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;

	ft_bzero(&sa, sizeof(sa));
	block_signals(&sa);
	sa.sa_sigaction = &handle_client;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	set_sigaction(&sa);
	check_error(argc, argv);
	server_pid = ft_atoi(argv[1]);
	send_msg(server_pid, argv[2]);
	pause();
	return (EXIT_SUCCESS);
}

static void	check_error(int argc, char **argv)
{
	pid_t	server_pid;
	int		i;

	if (argc != 3)
		printerr_exit("Usage: ./client <server_PID> <message>\n");
	i = 0;
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i]))
			printerr_exit("Invalid PID\n");
		i++;
	}
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1)
		printerr_exit("Process does not exist\n");
}

static void	send_msg(pid_t pid, const char *msg)
{
	unsigned int	msg_len;

	msg_len = ft_strlen(msg);
	send_len(pid, msg_len);
	while (*msg)
		send_char(pid, *msg++);
	send_char(pid, '\0');
}

static void	send_len(pid_t pid, unsigned int len)
{
	int	bit;
	int	bitshift;

	bit = 0;
	bitshift = (sizeof(int) * 8) - 1;
	while (bitshift >= 0)
	{
		bit = (len >> bitshift) & 1;
		send_bit(pid, bit);
		bitshift--;
	}
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	bit;
	int	bitshift;

	bit = 0;
	bitshift = (sizeof(char) * 8) - 1;
	while (bitshift >= 0)
	{
		bit = (c >> bitshift) & 1;
		send_bit(pid, bit);
		bitshift--;
	}
}
