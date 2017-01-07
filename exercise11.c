#include <stdio.h>

int main(int argc, char** argv){
  int pid, p_fd[2];
  char *new_program, **new_argv;

  if(argc < 3){
    fprintf(stderr, "usage: %s string command arg...\n", argv[0]);
    exit(1);
  }

  pipe(p_fd);

  if((pid = fork()) == 0){
    /*child process*/
    close(p_fd[0]);
    close(1);
    dup(p_fd[1]);
    close(p_fd[1]);

    new_program = argv[2];
    new_argv = &argv[2];
    execvp(new_program, new_argv);
    perror(new_program);
    exit(1);
  }
  /*parrent process*/
  if(pid == -1){
    perror("fork");
    exit(1);
  }

  close(p_fd[1]);
  // close(0);
  dup(p_fd[0]);
  close(p_fd[0]);

  execl("/usr/bin/grep", "grep", argv[1], NULL);
  perror("/usr/bin/grep");
  exit(1);
}