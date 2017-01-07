#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int pid, p_fd[2];
  char *new_program, **new_argv;

  if(argc < 3){
    fprintf(stderr, "usage: %s string command arg...\n", argv[0]);
    exit(1);
  }

  int fd, num;
  char buf[BUFSIZ] = {'\0'};
  if((fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666)) < 0){
    perror(argv[1]);
    exit(1);
  }

  pipe(p_fd);

  // while(1){
    // if((num =read(0, buf, BUFSIZ)) == 0) break;
  num = read(0, buf, BUFSIZ);
  printf("Input : [%s]\n", buf);
  write(p_fd[1], buf, num);
  write(fd, buf, num);

  if((pid = fork()) == 0){
    close(p_fd[1]);
    close(0);
    dup(p_fd[0]);
    close(p_fd[0]);

    new_program = argv[2];
    new_argv = &argv[2];
    execvp(new_program, new_argv);
    perror(new_program);
    exit(1);
  }

  if(pid == -1){
    perror("fork");
    exit(1);
  }

  close(p_fd[0]);
    // close(0);
    // dup(p_fd[0]);
    // close(p_fd[0]);
  // }

  exit(1);
}