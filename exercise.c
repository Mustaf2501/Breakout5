#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

int numOfEntries(char* path) {
    /*
        Count the number of entries in path
    */
}

int main(int argc, char** argv){
    if (argc < 2) {
        printf("Pass the path as an argument to the program");
        exit(1);
    }
    char* path = argv[1];

    DIR* dir = opendir(path);
    if(dir==NULL){
        printf("The path passed is invalid");
        return -1;
    }
    struct dirent* entry;
    
    /*
        Iterate through the elements in argv[1]
        Refer the ls example in slides if you have any doubts
    */
    
    closedir(dir);
    return 0;
}