
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

#define ERROR -1
#define SUCES 0

const int ARG = 3;

int copy_fd(int fd_src, int fd_dst);

int my_cp(const char *src, const char *dst);

int
main(int argc, char *argv[]){
    if(argc != ARG){
        return ERROR;
    }
    return my_cp(argv[ARG - 2], argv[ARG - 1]);
}

int copy_fd(int fd_src, int fd_dst){
    
    struct stat stat_src;
    if(fstat(fd_src, &stat_src) == ERROR){
        perror("errro size <src>");
        return errno;
    }
   if(ftruncate(fd_dst,stat_src.st_size)){
       return errno;
   }
    char * map_src = mmap(NULL, stat_src.st_size, PROT_READ, MAP_SHARED, fd_src, 0);
    char * map_dst = mmap(NULL, stat_src.st_size,  PROT_READ | PROT_WRITE, MAP_SHARED, fd_dst, 0);
    if(map_dst == NULL || map_src == NULL){
        perror("error al crear mmap");
        return errno;
    }
    memcpy(map_dst, map_src, stat_src.st_size);
    return SUCES;
}

int my_cp(const char* src, const char* dst){

    int fd_src = open(src, O_RDONLY, 0644);
    if (errno == ERROR) {
        close(fd_src);
        perror("El archivo  <src> no existe.\n");
        return ERROR;
    }

    if  (access(dst, F_OK) == 0){
        perror("El archivo <dst>  existe.\n");
        return ERROR;
    }
    int fd_dst = open(dst, O_RDWR | O_CREAT, 0644 );
    if (fd_dst == ERROR) { 
        close(fd_src);
        close(fd_dst);
        perror("Error al crear el archivo <dst> ");
        return ERROR;
    }
    int returner = copy_fd(fd_src, fd_dst);
    close(fd_src);
    close(fd_dst);


    return returner;
}
