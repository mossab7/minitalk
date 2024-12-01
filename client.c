#include "includes/ftprintf/ft_printf.h"
#include <signal.h>
void send_bit(char c,pid_t pid)
{
	int bit = 0;
  	while(bit < 8)
  	{
    		if((c & (1 << bit)) != 0)
      			kill(pid,SIGUSR1);
    		else 
      			kill(pid,SIGUSR2);
    		usleep(100);
    		bit++;
  	}
}

int main(int argc, char *argv[])
{
	if(argc == 3)
  	{
    		pid_t pid = atoi(argv[1]);
    		int i = 0;
    		while(argv[2][i] != '\0')
    		{
      			send_bit(argv[2][i],pid);
      			i++;
    		}
    		send_bit('\n',pid);
  	}
	else
		printf("incorrect format <./client pid messege>");
  	return 0;
}
