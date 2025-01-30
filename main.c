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

  struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_addr.s_addr = INADDR_ANY,
    .sin_port = htons(8080)
  };

  char response[] = "Hello from C server!\n";

  int s = socket(AF_INET, SOCK_STREAM, 0);
  bind(s, (struct sockaddr *)&addr, sizeof(addr));
  int result = listen(s, 1);

  socklen_t addr_len = sizeof(addr);
  int client_fd = accept(s, (struct sockaddr *)&addr, &addr_len);

  write(client_fd, response, strlen(response));
  /* close(client_fd); */
  /* close(s); */
  return 0;
}
