/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:40:42 by mbouhia           #+#    #+#             */
/*   Updated: 2024/12/03 16:33:08 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ftprintf/ft_printf.h"
#include "minitalk_bonus.h"
#include <signal.h>

t_message	g_message;

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (g_message.bits_count != 0 && g_message.last_sender != info->si_pid)
		g_message.bits_count = 0;
	if (signum == SIGUSR1)
		g_message.byte = (g_message.byte << 1) | 1;
	else
		g_message.byte <<= 1;
	g_message.bits_count++;
	if (g_message.bits_count < 8)
		g_message.state_flag = 1;
	g_message.last_sender = info->si_pid;
}

void	check_signal(void)
{
	while (1)
	{
		if (g_message.state_flag)
		{
			g_message.state_flag = 0;
			kill(g_message.last_sender, SIGUSR1);
		}
		else if (g_message.bits_count == 8)
		{
			write(1, &g_message.byte, 1);
			g_message.bits_count = 0;
			kill(g_message.last_sender, SIGUSR1);
		}
	}
}

int	main(void)
{
	struct sigaction	set;
	pid_t				pid;

	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	sigemptyset(&set.sa_mask);
	set.sa_flags = SA_SIGINFO;
	set.sa_sigaction = handle_signal;
	sigaction(SIGUSR1, &set, NULL);
	sigaction(SIGUSR2, &set, NULL);
	check_signal();
	return (0);
}
