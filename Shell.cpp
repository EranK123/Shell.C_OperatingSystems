#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
#include <string.h>
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
    // cout << filename << endl;
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
    char *curr , *src, *dest, *filename;
	string input;
	char path[256];
    getcwd(path, 256);
    printf("Current working directory: %s\n\n", path);
    curr = getcwd(path, 256);
while(1){
    cout << input.substr(0,5);
    cout << ">>> ";
	getline(cin, input);
    // cout << input << endl;
	if(input.compare("EXIT") == 0){
		exit(1);
        // system("exit");
	}else if(input.substr(0,4).compare("ECHO") == 0){
		cout << input.substr(5, input.length()) << endl;
	}else if(input.compare("TCP PORT") == 0){
		cout << "tcp\n";
	}else if(input.compare("DIR") == 0){
		// list_dir(getcwd(path, 256));
        system("ls");
	}else if(input.substr(0,2).compare("CD") == 0){
        string new_dir = input.substr(3, input.length());
         int r = chdir(new_dir.c_str());
         if(r < 0){
             cout << "ERROR" << endl;
         }else{
        char path[256];
        getcwd(path, 256);
        printf("Current working directory: %s\n\n", path);
         }
	}else if(input.substr(0,4).compare("COPY") == 0){
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
        cout << filename;
        if(remove(filename) != 0){
            perror("Error deleting file");
    }
}
}
}
