#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>


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
  if(s < 0){
    perror("Error while socketing");
    return 1;
  }

  int opt = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  int binded = bind(s, (struct sockaddr *)&addr, sizeof(addr));
  if(binded < 0){
    perror("Error while binding");
    return 1;
  }

  int result = listen(s, 1);
  if(result < 0){
    perror("Error while listening\n");
    return 1;
  }

  socklen_t addr_len = sizeof(addr);
  for(;;){

    int client_fd = accept(s, (struct sockaddr *)&addr, &addr_len);

    char buffer[1024];
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer)-1, 0);
    if (bytes_received > 0){
      buffer[bytes_received] = '\0';
      printf("Received:\n%s\n", buffer);
    }
    write(client_fd, response, strlen(response));
    close(client_fd);
  }
  close(s);
  return 0;
}
