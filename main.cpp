#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;
using std::cout; using std::cin;
using std::string;
using std::vector;
int sock = 0;
int temp = dup(1);
int is_open = 0;
void open_tcp_client(){
  const char *ip = "127.0.0.1";
  int port = 5566;

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
  dup2(sock , 1);
  bzero(buffer, 1024);
  strcpy(buffer, "HELLO, THIS IS CLIENT.");
  printf("Client: %s\n", buffer);
  bzero(buffer, 1024);
  printf("Server: %s\n", buffer);
  is_open = 1;  

}


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

char* get_file_name(const char *path) {
   struct dirent *entry;
   DIR *dir = opendir(path);
   char *t;
   if (dir == NULL) {
      return NULL;
   }
   while ((entry = readdir(dir)) != NULL) {
     t = entry->d_name;
   }
   closedir(dir);
   return t;
}

void copyFile(char* filename, char* directory_from,char* directory_to, char* cwd) {
    FILE *file, *copyfile;
    char c;
    cout << "cwd: " << cwd << endl;
    chdir(directory_from);
    
    file = fopen(filename,"r");
    if(file == NULL) {
        printf("Cannot open the file %s in copyFile.\n", filename);
    }
    chdir(cwd);
    chdir(directory_to);
    copyfile = fopen(filename, "w+");
    
    if(copyfile == NULL) {
        printf("Cannot open copy of the file %s in copyFile.\n", filename);
    }

    c = fgetc(file);
    while(c != EOF){
        fputc(c, copyfile);
        c = fgetc(file);
    }

    printf("Contents copied successfully.\n");

    fclose(file);
    fclose(copyfile);
    chdir(cwd);
    return;

}



int main(){
    int parentd_pid = getpid();
    char *curr , *src, *dest, *filename;
	string input;
	char path[256];
    getcwd(path, 256);
    printf("Current working directory: %s\n\n", path);
    curr = getcwd(path, 256);
while(1){
    cout << ">>> ";
	getline(cin, input);
    // cout << input << endl;
	if(input.compare("EXIT") == 0){
		exit(1);
	}else if(input.substr(0,4).compare("ECHO") == 0){
		cout << input.substr(5, input.length()) << endl;
	}else if(input.compare("TCP PORT") == 0){
        if(is_open){
            cout << "Socket is already connected" << '\n';
            continue;
        }else{
            open_tcp_client();
        }
	}else if(input.compare("DIR") == 0){
		list_dir(getcwd(path, 256));
	}else if(input.substr(0,2).compare("CD") == 0){ //The chdir command is a system function which is used to change the current working directory.
        string new_dir = input.substr(3, input.length());
         int r = chdir(new_dir.c_str());
         if(r < 0){
             cout << "ERROR" << endl;
         }else{
        char path[256];
        getcwd(path, 256);
        printf("Current working directory: %s\n\n", path);
         }
	}else if(input.substr(0,4).compare("COPY") == 0){ //our implementaion is using fopen and fclose which are library 
    //function but also uses chdir which is a system call as said earlier.
        int last_space = input.find_last_of(" ");
        src = &(input.substr(5, last_space - 5))[0];
        dest = &input.substr(last_space + 1, input.length())[0];
        char cwd[256];
        strcpy(cwd, curr);
        chdir(src);
        curr = getcwd(path, 256);
        filename = get_file_name(curr);
        copyFile(filename, src, dest, cwd);
    }else if(input.substr(0,6).compare("DELETE") == 0){
        filename = &input.substr(7, input.length())[0];
        if(remove(filename) != 0){ //remove is a library function
            perror("Error deleting file");
    }
    }else if(input.substr(0,5).compare("LOCAL") == 0){
        cout << "LOCAL" << endl;
        dup2(temp,1);
        is_open = 0;
    }else{
      string temp = "";
      int index = 0;
     int count_spaces = 0;
        for(int i = 0; i < input.length(); i++){
            if (input.at(i) == ' '){
                count_spaces++;
            }
        }
    char *args[count_spaces + 2];
      for(int i=0; i<(int)input.size(); i++){
         if(input[i] != ' '){
            temp += input[i];
        }
          else{
            args[index] = strcpy(new char[temp.length() + 1], temp.c_str());
            index++;
            temp = "";
        }
    }   
       args[index++] = strcpy(new char[temp.length() + 1], temp.c_str());
        char *cmd = args[0];
        args[index] = NULL;
        fork();
        wait(NULL);
        if(getpid() != parentd_pid){
            execvp(cmd,args);
        }
        // system(input.c_str()); //system is a library function
    }
}
}
