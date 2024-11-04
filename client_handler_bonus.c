/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 09:50:07 by tchow-so          #+#    #+#             */
/*   Updated: 2024/11/03 11:37:32 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handle_client(int signal, siginfo_t *info, void *context)
{
	static t_msg	msg = {0};
	
	(void)info;
	(void)context;
	if (signal == SIGUSR2)
		write(1, "SUCCESS: Message sent\n", 22);
}