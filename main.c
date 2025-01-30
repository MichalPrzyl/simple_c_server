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
  if(s < 0){
    printf("Error while socketing\n");
  }

  int binded = bind(s, (struct sockaddr *)&addr, sizeof(addr));
  if(binded < 0){
    printf("Error while binding\n");
  }

  int result = listen(s, 1);
  if(result < 0){
    printf("Error while listening\n");
  }

  socklen_t addr_len = sizeof(addr);
  for(;;){

    int client_fd = accept(s, (struct sockaddr *)&addr, &addr_len);

    write(client_fd, response, strlen(response));
    /* close(client_fd); */
    /* close(s); */
  }
  return 0;
}
