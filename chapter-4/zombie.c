#include <stdio.h>
#include "unistd.h"

int main(int argc, char **argv) {
  int rc = fork();
  int child = 0;
  switch (rc) {
  case -1:
    fprintf(stderr, "Unable to fork");
    return (1);
  case 0:
    printf("I am the child! I am born\n");
    child++;
    break;
  default:
    printf("I am the parent! Going to sleep and now wait\n");
    sleep(60);
  }
  printf("%s existing\n", (child?"child":"parent"));
  return (0);
}
