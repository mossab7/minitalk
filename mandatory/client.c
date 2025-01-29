/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:39:59 by mbouhia           #+#    #+#             */
/*   Updated: 2024/12/06 09:51:04 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"
#include "minitalk.h"
#include <signal.h>

int		g_state_flag;

void	set_state_flag(int signal)
{
	(void)signal;
	g_state_flag = 1;
}

int	send_bits(char c, pid_t pid)
{
	int	bit_pos;
	int	return_value;

	bit_pos = 8;
	while (--bit_pos >= 0)
	{
		if ((c >> bit_pos) & 1)
			return_value = kill(pid, SIGUSR1);
		else
			return_value = kill(pid, SIGUSR2);
		usleep(250);
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

int	check_input(int argc, char **argv)
{
	size_t	i;

	if (argc != 3)
	{
		ft_printf("\x1b[31mwrong format <./client pid message>\n\x1b");
		return (-1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			ft_printf("\x1b[31minvalid PID\n\x1b");
			return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	set;
	size_t				len;

	if (check_input(argc, argv) == -1)
		return (0);
	len = ft_strlen(argv[2]);
	sigemptyset(&set.sa_mask);
	set.sa_flags = 0;
	set.sa_handler = set_state_flag;
	pid = ft_atoi(argv[1]);
	if (sigaction(SIGUSR1, &set, NULL) == -1 || sigaction(SIGUSR2, &set,
			NULL) == -1)
		return (0);
	send_to_server(pid, argv[2], len);
	return (0);
}
