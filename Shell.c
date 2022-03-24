#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include <dirent.h>


#define LEN 1024

int takeInput(char* str)
{
    char* buf;
    buf = readline("\n>>> ");
    if (strlen(buf) != 0) {
        // add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

void open_tcp_client(){
  char *ip = "127.0.0.1";
  int port = 5566;

  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");

  bzero(buffer, 1024);
  strcpy(buffer, "HELLO, THIS IS CLIENT.");
  printf("Client: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);

  bzero(buffer, 1024);
  recv(sock, buffer, sizeof(buffer), 0);
  printf("Server: %s\n", buffer);

  close(sock);
  printf("Disconnected from the server.\n");

}

void get_files(){
	struct dirent *de; 
    DIR *dr = opendir(".");
  
    if (dr == NULL)  
    {
        printf("Could not open current directory" );
    }
  
    while ((de = readdir(dr)) != NULL){
            printf("%s\n", de->d_name);
	}
    closedir(dr);
}

char* substring(char *destination, char *source, int beg, int n){
	// printf("%s", source);
    while (n > 0)
    {
        *destination = *(source + beg);
 
        destination++;
        source++;
        n--;
		

    }
    *destination = '\0';
    return destination;
}

int main(){
	char input[LEN];
	char path[LEN];
    getcwd(path, LEN);
    printf("Current working directory: %s\n", path);
	char echo_string[4]; 
while(1){
	if(takeInput(input)){
		continue;
	}
	printf("%s", substring(echo_string, input, 0, 4));
	if(strcmp(input, "EXIT") == 0){
		exit(1); 
	}else if(input[0] == 'E' && input[1] == 'C' && input[2] == 'H'){
		printf("%s", input + 5);
	}else if(strcmp(input, "TCP PORT") == 0){
		printf("%d", 103);
	}else if(strcmp(input, "DIR") == 0){
		get_files();
	}
}
}