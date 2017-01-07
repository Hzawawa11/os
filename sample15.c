/* sample15.c */

#define BSIZE 512
char send_buf[] = "UNIX workstations";

int main(){
  int p_fd[2], n_send, n_recv;
  char recv_buf[BSIZE];

  pipe(p_fd);

  n_send = strlen(send_buf) + 1;
  write(p_fd[1], send_buf, n_send);
  close(p_fd[1]);

  n_recv = read(p_fd[0], recv_buf, BSIZE);
  close(p_fd[0]);

  printf("%d bytes sent, %d bytes received.\n", n_send, n_recv);
  printf("received data: %s\n", recv_buf);

  exit(0);
}