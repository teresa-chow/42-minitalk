/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 10:39:38 by tchow-so          #+#    #+#             */
/*   Updated: 2024/11/10 10:58:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define PAUSE 100

# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft/libft.h"
# include "libft/ft_printf/ft_printf.h"

typedef struct s_msg
{
	unsigned int		len;
	bool				active;
	char				*str;
}	t_msg;

void	printerr_exit(char *str);
void	block_signals(struct sigaction *sa);
void	set_sigaction(struct sigaction *sa);
void	send_bit(pid_t pid, int bit);

#endif
