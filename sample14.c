/* sample14.c */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BSIZE 16

int main(int argc, char** argv){
  int fd, n;
  char buf[BSIZE];

  if(argc != 2){
    fprintf(stderr, "usage: %s file\n", argv[0]);
    exit(1);
  }

  if((fd = open(argv[1], O_RDONLY)) < 0){
      perror(argv[1]);
      exit(1);
  }

  if((n = read(fd, buf, BSIZE)) > 0)
      write(1, buf, n);

  lseek(fd, 0, SEEK_SET);

  if((n = read(fd, buf, BSIZE)) > 0)
      write(1, buf, n);

  close(fd);
  exit(0);
}