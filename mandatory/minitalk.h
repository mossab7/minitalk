/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:51:50 by mbouhia           #+#    #+#             */
/*   Updated: 2024/12/03 16:06:04 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct bar_s
{
	unsigned int	bar_width;
	unsigned int	pos;
	unsigned int	percentage;
}					t_bar;

typedef struct s_message
{
	char			byte;
	int				state_flag;
	int				bits_count;
	pid_t			last_sender;
}					t_message;

void				ft_check(int signal, size_t len);
#endif
