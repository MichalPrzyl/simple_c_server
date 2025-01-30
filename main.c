#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void server();
void client();

int main(){
  printf("Starting server!\n");

  struct sockaddr addr = {
    .sa_family_t = AF_INET,
    /* .sin_addr.s_addr = INADDR_ANY, */
    /* .sin_port = htons(8080) */
    /* char sa_data[14]; */
  };

  char response[] = "Hello from C server!\n";

  int s = socket(AF_INET, SOCK_STREAM, 0);
  bind(s, &addr, sizeof(addr));
  listen = listen(s, 1);

  client_fd = accept(s, &addr, 14, 0);
  write(client_fd, response, strlen(response));
  /* close(client_fd); */
  /* close(s); */
  return 0;
}
