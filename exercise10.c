/* sample15.c */

#define BSIZE 512
char send_buf[] = "UNIX workstations";

int main(){
  int p_fd[2], n_send, n_recv;
  char recv_buf[BSIZE];

  pipe(p_fd);
  printf("p_fd[0]: %d\np_fd[1]: %d\n",p_fd[0], p_fd[1]); // input 4, output 5

  // n_recv = read(p_fd[0], recv_buf, BSIZE);
  n_recv = read(4, recv_buf, BSIZE);
  close(p_fd[0]);

  n_send = strlen(send_buf) + 1;
  write(p_fd[1], send_buf, n_send);
  close(p_fd[1]);

  printf("%d bytes sent, %d bytes received.\n", n_send, n_recv);
  printf("received data: %s\n", recv_buf);

  exit(0);
}