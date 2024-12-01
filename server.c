#include "includes/ftprintf/ft_printf.h"
#include <signal.h>

void handel_signal(int signal)
{
	static int bit;
  	static int chars;

  	if(signal == SIGUSR1)
    		chars |= (1 << bit);
  	bit++;
  	if(bit == 8)
  	{
    		ft_printf("%c",chars);
    		bit = 0;
    		chars = 0;
	}
}

int main(int argc, char *argv[])
{

	(void)argv;
	int pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	signal(SIGUSR1,handel_signal);
	signal(SIGUSR2,handel_signal);
	while(argc == 1)
	{
		pause();
	}
  
	return 0;
}
