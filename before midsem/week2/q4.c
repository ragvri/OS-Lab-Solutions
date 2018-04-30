#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int stringToInt(char *s) {
  int n = 0;
  int i;
  for(i = 0;s[i];i++) {
    n = n * 10;
    n += (s[i] - '0');
  }
  return n;
}
int main(int argc, char *argv[]) {
  if(argc != 2) {
    printf("Wrong number of parameter.\n");
    return 0;
  }
  int t = stringToInt(argv[1]);
  if(fork() == 0) {
    sleep(t);
    printf("\nAll the processes of child: \n");
    system("ps -l");
  }
  else {
    printf("\nAll the processes of parent: \n");
    system("ps -l");
    wait(NULL); // wait(&status) status is the return value. waits for the first  child to die
    printf("\nAll the processes of parent: \n");
    system("ps -l");
  }
  return 0;
}
