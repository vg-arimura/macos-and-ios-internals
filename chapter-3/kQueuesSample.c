#include "stdio.h"
#include <sys/types.h>
#include <sys/event.h>
#include "stdlib.h"
#include "string.h"

int main(int argc, char **argv) {
  pid_t pid;
  int kq;
  int rc;
  int done;
  struct kevent ke;

  pid = atoi(argv[1]);
  kq = kqueue();

  if (kq == -1){
    perror("kqueue");
    exit(2);
  }

  //set process fork/exec norification
  EV_SET(&ke, pid, EVFILT_PROC, EV_ADD, NOTE_EXIT | NOTE_FORK | NOTE_EXEC, 0, NULL);

  //register event
  rc = kevent(kq, &ke, 1, NULL, 0, NULL);
  if (rc < 0) {
    perror ("kevent");
    exit(3);
  }

  done = 0;
  while (!done){
    memset(&ke, '\0', sizeof(struct kevent));
    //This blocks until an event matching the fillter occurs
    rc = kevent(kq, NULL, 0,&ke,1, NULL);
    if (rc < 0) {
      perror("kevent");
      exit(4);
    }

    if (ke.fflags & NOTE_FORK)
      printf("PID %lu fork()ed\n", ke.ident);

    if (ke.fflags & NOTE_EXEC)
      printf("PID %lu has exec()ed\n", ke.ident);

    if (ke.fflags & NOTE_EXIT){
      printf("PID %lu has exited\n", ke.ident);
    }
  }
}
