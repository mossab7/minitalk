#include "includes/ftprintf/ft_printf.h"
#include <signal.h>

size_t	len;

void ft_check(int signal)
{
        unsigned int            bar_width;
        unsigned int            pos;
        unsigned int            percentage;
        unsigned int            i;
        char                    *color;
        static unsigned int     count;
        
	if(signal == SIGUSR1)
                color = "\x1b[32m";
        else
                color = "\x1b[31m";
        bar_width = 50;
        count++;
        percentage = (count * 100) / len;
        pos = (percentage * bar_width) / 100;
        ft_printf("%s[",color);
        i = 0;
        while(i++ < pos)
                ft_printf("%s#",color);
        while(i++ < bar_width)
                ft_printf ("%s ",color);
        ft_printf("%s] %d%%\r",color,percentage);
        if(signal == SIGUSR2)
                return;
}

int    send_signal(char c, pid_t pid)
{
    int	bit;
    int	return_value;
    bit = 0;
    while (bit < 8)
    {
        if((c & (1 << bit)) != 0)
            return_value = kill(pid,SIGUSR1);
        else
            return_value = kill(pid,SIGUSR2);
	if(return_value == -1)
		break;
        usleep(100);
        bit++;
    }
    return (return_value);
}

int main(int argc, char **argv)
{
    int     	i;
    pid_t   	pid;
    int		return_value;
    
    len = strlen(argv[2]) + 1;
    if(argc != 3)
    {
        printf("\x1b[31mwrong format <./client pid message>\n");
        return (0);
    }
    i = 0;
    pid = atoi(argv[1]);
    signal(SIGUSR1,ft_check);
    signal(SIGUSR2,ft_check);
    while(argv[2][i] != '\0')
    {
        return_value = send_signal(argv[2][i],pid);
        if(return_value == -1)
	{
		ft_check(SIGUSR2);
		write(1,"\n",1);
		return (0);
	}
	i++;
    }
    send_signal('\n',pid);
    write(1,"\n",1);
    return (0);
    
}
