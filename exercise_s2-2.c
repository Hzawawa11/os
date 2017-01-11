#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZ BUFSIZ

int main(int argc, char** argv){
  int pid, p_fd[2], fd, num;
  char *new_program, **new_argv;

  char buf[BUFSIZ] = {'\0'};

  if(argc < 3){
    fprintf(stderr, "usage: %s string command arg...\n", argv[0]);
    exit(1);
  }

  if((fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0){
    perror(argv[1]);
    exit(1);
  }

  printf("SIZE: [%d]\n", SIZ);

  pipe(p_fd);

  // p_fd[0]; output
  // p_fd[1]; input
  // input; 0
  // output; 1
  // num = read(0, buf, SIZ);
  int cnt = 0;
  while((num = read(0, buf, 1))&& cnt < SIZ){
    cnt += 1;
    write(p_fd[1], buf, num);
  }

  if((pid = fork()) == 0){

    close(p_fd[1]);
    close(0);
    dup(p_fd[0]);
    close(p_fd[0]);

    new_program = argv[2];
    new_argv = &argv[2];

    execvp(new_program, new_argv);

    // while((num = read(p_fd[0], buf, 1)))
      // write(fd, buf, num);

    // int i = lseek(p_fd[0], 0, SEEK_SET);
    // printf("lseek [%d]\n", i);
    exit(1);
  }

  if(pid == -1){
    perror("fork");
    exit(1);
  }

  cnt = 0;
  while((num = read(p_fd[0], buf, 1))&& cnt < SIZ){
    cnt += 1;
    write(fd, buf, num);
  }

  // close(0);
  // dup(p_fd[0]);
  // close(p_fd[0]);

  // new_program = argv[2];
  // new_argv = &argv[2];

  // execvp(new_program, new_argv);

  // printf("INPUT[%s]\n", buf);

  exit(1);
}