#include <sys/disk.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char **argv){
  int64_t bs, bc, rc;
  char fp[BUFSIZE];
  char p[BUFSIZE];

  if(argv[1][0] != '/') {
    snprintf(p, BUFSIZE, "/dev/%s", argv[1]);
  }else{
    strncpy (p, argv[1], BUFSIZE);    
  }

  int fd = open(p, O_RDONLY);
  if(fd == -1){
    fprintf(stderr, "%s: unable to open %s\n", argv[0], p);
    perror("open");
    exit(1);
  }

  rc = ioctl(fd, DKIOCGETBLOCKSIZE, &bs);
  if (rc < 0){
    fprintf(stderr, "DKIOCGETBLOCKSIZE failed\n");
    exit(2);
  }else{
    fprintf(stderr, "Block size:\t%lld\n", bs);
  }

  rc = ioctl(fd, DKIOCGETBLOCKCOUNT, &bc);
  fprintf(stderr, "Block count:\t%lld\n", bc);

  rc = ioctl(fd, DKIOCGETFIRMWAREPATH, &fp);
  fprintf(stderr, "Fw path:\t%s\nTotal size:\t%lldM\n", fp, (bs * bc) / (1024 * 1024));
}
