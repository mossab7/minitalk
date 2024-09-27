#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handel_signal(int signal)
{
  static int bit = 0;
  static int chars = 0;

  if(signal == SIGUSR1)
    chars |= (0x01 << bit);
  bit++;
  if(bit == 8)
  {
    printf("%c",chars);
    bit = 0;
    chars = 0;
  }
}

int main(int argc, char *argv[])
{

  int pid = getpid();
	printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
  
  signal(SIGUSR1,handel_signal);
  signal(SIGUSR2,handel_signal);
  while(argc == 1)
  {
    pause();
  }
  
  return 0;
}
