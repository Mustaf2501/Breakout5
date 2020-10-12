/*
 * Minh Bui (bui00011@umn.edu): 
 * William Henning (henni187@umn.edu):
 * Andrius Adomavicius (adoma010@umn.edu):
 * Mustaf Ahmed (ahmed719@umn.edu):
 * Member name (email address):
 * Member name (email address):
 * Member name (email address):
 */

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
  DIR *dir;
  struct dirent *dir_entry;
    
  
  int count = 0;

  if (!(dir = opendir(path)))
        return -1;

  while ((dir_entry = readdir(dir)) != NULL) {



      count++;
      
  }
  closedir(dir);
  return count;

}

void print_info(char * name, struct stat entry_stat) {
    printf("Name: %s\n", name);
    printf("\tI-node number:            %ld\n", (long) entry_stat.st_ino);
    printf("\tOwnership:                UID=%ld\n", (long) entry_stat.st_uid);
    printf("\tLink count:               %ld\n", (long) entry_stat.st_nlink);
    printf("\tFile size:                %lld bytes\n", (long long) entry_stat.st_size);
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
    
    struct dirent* dir_entry;

  while ((dir_entry = readdir(dir)) != NULL) { 

    struct stat entry_stat;
    char this_entry[1024] = {'\0'};
    strcat(this_entry, path);
    strcat(this_entry, "/");
    strcat(this_entry, dir_entry->d_name);
    stat(this_entry, &entry_stat);

    if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0) {
        continue;
    }

    if (S_ISDIR(entry_stat.st_mode)) {
        int file_count = numOfEntries(this_entry);
        printf("Directory: %s\n", dir_entry->d_name);
        //print_info(dir_entry->d_name, entry_stat);
        printf("Number of files: %d\n", file_count);
    } else if (S_ISREG(entry_stat.st_mode)) {
        printf("Regular file: %s\n", dir_entry->d_name);
        //print_info(dir_entry->d_name, entry_stat); 
        printf("Ownership: %ld\n", (long) entry_stat.st_uid);
        printf("File size: %lld bytes\n", (long long) entry_stat.st_size);
        printf("I-node number: %ld\n", (long) entry_stat.st_ino);
    } else {
        printf("other file type: %s\n", dir_entry->d_name);
    }
  }
    closedir(dir);
    return 0;
}