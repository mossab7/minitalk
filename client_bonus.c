/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:40:14 by mbouhia           #+#    #+#             */
/*   Updated: 2024/12/03 20:49:33 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ftprintf/ft_printf.h"
#include "minitalk_bonus.h"
#include <signal.h>

int		g_state_flag;

void	set_state_flag(int signal)
{
	(void)signal;
	g_state_flag = 1;
}

void	ft_check(int signal, size_t len)
{
	t_bar				bar;
	unsigned int		i;
	char				*color;
	static unsigned int	count;

	if (signal == SIGUSR1)
		color = "\x1b[32m";
	else
		color = "\x1b[31m";
	bar.bar_width = 50;
	count++;
	bar.percentage = (count * 100) / len;
	bar.pos = (bar.percentage * bar.bar_width) / 100;
	ft_printf("%s[", color);
	i = 0;
	while (i++ < bar.pos)
		ft_printf("%s#", color);
	while (i++ < bar.bar_width)
		ft_printf("%s ", color);
	ft_printf("%s] %d%%\r", color, bar.percentage);
	if (signal == SIGUSR2)
		return ;
}

int	send_bits(char c, pid_t pid)
{
	int	j;
	int	return_value;

	j = 8;
	while (--j >= 0)
	{
		if ((c >> j) & 1)
			return_value = kill(pid, SIGUSR1);
		else
			return_value = kill(pid, SIGUSR2);
		usleep(270);
		if (!g_state_flag)
			return (-1);
		g_state_flag = 0;
	}
	return (return_value);
}

void	send_to_server(pid_t pid, char *str, size_t len)
{
	int	i;
	int	return_value;

	i = 0;
	while (1)
	{
		return_value = send_bits(str[i], pid);
		if (!str[i] || return_value == -1)
		{
			send_bits('\n', pid);
			if (return_value == -1)
				ft_check(SIGUSR2, len);
			write(1, "\n", 1);
			break ;
		}
		ft_check(SIGUSR1, len);
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	set;
	size_t				len;

	len = strlen(argv[2]);
	if (argc != 3)
	{
		printf("\x1b[31mwrong format <./client pid message>\n");
		return (0);
	}
	sigemptyset(&set.sa_mask);
	set.sa_flags = 0;
	set.sa_handler = set_state_flag;
	pid = atoi(argv[1]);
	sigaction(SIGUSR1, &set, NULL);
	sigaction(SIGUSR2, &set, NULL);
	send_to_server(pid, argv[2], len);
	return (0);
}
