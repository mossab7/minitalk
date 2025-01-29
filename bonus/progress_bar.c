/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:42:55 by mbouhia           #+#    #+#             */
/*   Updated: 2024/12/05 23:42:57 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"
#include "minitalk_bonus.h"
#include <signal.h>

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
