#include <stdio.h>
#include <dirent.h>
#include <sys/types.h> 
#include <string.h>
#include <ctype.h>

#define ERROR -1
#define SUCCESS 0

#define ACTUALDIR "."
#define ANTEDIR ".."
#define FLAG "-i"

#define BADARG "bad argument"

const int ARG_FLAG = 3;
const int ARG = 2;

void my_find(const char *dir_target, const char *find, int mayus);

int
main(int argc, char *argv[])
{
    int flag_i = 0;
    if (argc == ARG)
    {
        my_find(ACTUALDIR, argv[ARG-1], flag_i);
    }
    else if (argc == ARG_FLAG)
    {   
        if(strcmp(argv[ARG-1] , FLAG) != 0){
            perror(BADARG);
        }
        int flag_i = 1;
        my_find(ACTUALDIR, argv[ARG_FLAG-1], flag_i);
    }
    else
    {
        return ERROR;
    }
    return SUCCESS;
}


void 
my_find(const char* dir_target, const char * find, int mayus){
    DIR* dir = opendir(dir_target);
    if (dir == NULL) {
        return;
    }
    struct dirent *entry;
    entry = readdir(dir);
    while (entry != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ACTUALDIR) != 0 && strcmp(entry->d_name, ANTEDIR) != 0) {    
            if(strcmp(dir_target, ACTUALDIR) == 0){
                my_find(entry->d_name, find, mayus);
            } else {
                char path[100] = { 0 };
                strcat(path, dir_target);
                strcat(path, "/");
                strcat(path, entry->d_name);
                my_find(path, find, mayus);
            }

        }
    
	if (mayus ? strcasestr(entry->d_name, find) : strstr(entry->d_name, find)) {
		if (strcmp(dir_target, ACTUALDIR) != 0) {
			printf("%s/%s\n", dir_target, entry->d_name);
		} else {
			printf("%s\n", entry->d_name);
		}
	}
	entry = readdir(dir);
    }
    closedir(dir);
}