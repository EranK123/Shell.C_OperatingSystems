#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
using namespace std;
using std::cout; using std::cin;
using std::string;
using std::vector;





// void open_tcp_client(){
//   char *ip = "127.0.0.1";
//   int port = 5566;

//   int sock;
//   struct sockaddr_in addr;
//   socklen_t addr_size;
//   char buffer[1024];
//   int n;

//   sock = socket(AF_INET, SOCK_STREAM, 0);
//   if (sock < 0){
//     perror("[-]Socket error");
//     exit(1);
//   }
//   printf("[+]TCP server socket created.\n");

//   memset(&addr, '\0', sizeof(addr));
//   addr.sin_family = AF_INET;
//   addr.sin_port = port;
//   addr.sin_addr.s_addr = inet_addr(ip);

//   connect(sock, (struct sockaddr*)&addr, sizeof(addr));
//   printf("Connected to the server.\n");

//   bzero(buffer, 1024);
//   strcpy(buffer, "HELLO, THIS IS CLIENT.");
//   printf("Client: %s\n", buffer);
//   send(sock, buffer, strlen(buffer), 0);

//   bzero(buffer, 1024);
//   recv(sock, buffer, sizeof(buffer), 0);
//   printf("Server: %s\n", buffer);

//   close(sock);
//   printf("Disconnected from the server.\n");

// }

void get_files(){
	DIR *dir;
          dirent *pdir;
          dir=opendir(".");
          while(readdir(dir))
           {
              pdir=readdir(dir);
              cout<< pdir->d_name<<endl;
            }
          closedir(dir);
          
}
void list_dir(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   
   if (dir == NULL) {
      return;
   }
   while ((entry = readdir(dir)) != NULL) {
   cout << entry->d_name << endl;
   }
   closedir(dir);
}


int main(){
	string input;
	char path[256];
    getcwd(path, 256);
    printf("Current working directory: %s\n\n", path);
while(1){
    cout << ">>> ";
	getline(cin, input);
    // cout << input << endl;
	if(input.compare("EXIT") == 0){
		exit(1);
	}else if(input.substr(0,4).compare("ECHO") == 0){
		cout << input.substr(5, input.length()) << endl;
	}else if(input.compare("TCP PORT") == 0){
		cout << "tcp\n";
	}else if(input.compare("DIR") == 0){
		list_dir(getcwd(path, 256));
	}
}
}
