#include <signal.h>
#include "includes/ftprintf/ft_printf.h"

void    handle_signal(int signal, siginfo_t *info, void *context)
{
    static int bit;
    static int chars;

    (void)context;
    if(signal == SIGUSR1)
        chars |= (1 << bit);
    bit++;
    if(bit == 8)
    {
        printf("%c",chars);
        kill(info->si_pid,SIGUSR1);
        chars = 0;
        bit = 0;
    }
}

int main()
{
    struct sigaction set;
    pid_t  pid;

    pid = getpid();
    ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
    sigemptyset(&set.sa_mask);
    set.sa_flags = SA_SIGINFO;
    set.sa_sigaction = handle_signal;
    sigaction(SIGUSR1,&set,NULL);
    sigaction(SIGUSR2,&set,NULL);
    while(1)
    {
        pause();
    }
    return (0);
}