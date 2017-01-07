/* sample14.c */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv){
  int fd, n, num;
  char buf[BUFSIZ] = {'\0'};

  if(argc != 2){
    fprintf(stderr, "usage: %s file\n", argv[0]);
    exit(1);
  }

  /* ----------- */
  /* 1 */
  /*
  if((fd = open(argv[1], O_WRONLY|O_APPEND)) < 0){
      perror(argv[1]);
      exit(1);
  }

  while((num = read(0, buf, BUFSIZ)) != -1){
    write(fd, buf, num);
    write(1, buf, num);
  }
  */
  /* ----------- */
  /* 2 */
  if((fd = open(argv[1], O_RDWR)) < 0){
    perror(argv[1]);
    exit(1);
  }
  unlink(argv[1]);
  // printf("file discriptor : %d\n", fd); /*4*/

  while((num = read(0, buf, BUFSIZ)) != 0){
    if(buf[0] == '\n')  break;
    write(fd, buf, num);
  }

  // write(1, " ---- ここからファイル内容 ---- \n", 100);
  // lseek(fd, 0, SEEK_SET);
  // while((num = read(fd, buf, BUFSIZ)) != 0)
    // write(1, buf, num);

  /* ----------- */
  close(fd);
  exit(0);
}

// int main(int argc, char** argv){
//   int n = atoi(argv[1]);
//   char c[BUFSIZ] = {'\0'};
//   int num;
//     while((num = read(0, c, n)) != 0)
//       write(1, c, n);
// }