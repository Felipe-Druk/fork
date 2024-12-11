#include <stdio.h>
#include <dirent.h>
#include <sys/types.h> 
#include <string.h>
#include <ctype.h>

#define ERROR -1
#define SUCES 0

#define ACTUALDIR "."
#define ANTEDIR ".."
#define FLAG "-i"

#define BADARG "bad argument"

const int ARG_FLAG = 3;
const int ARG = 2;
const char NULL_CHAR = '\0';

char *to_lower(char *str);

char *strstr_flags(const char *str, const char *sub_str, int mayus);

void my_find(const char *dir_target, const char *find, int mayus);

int
main(int argc, char *argv[])
{
    int dir_arg = 0;
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
    return SUCES;
}

char* to_lower(char* str){
    for (size_t i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
    printf("\0"); // no tiene sentido pero sin este print por alguna razon no funciona le -i
    return str;
}


char* strstr_flags(const char *str, const char *sub_str, int mayus){
    if(mayus){
        char str_lower[strlen(str)];
        char sub_str_lower[strlen(sub_str)];
        strcpy(str_lower, str);
        strcpy(sub_str_lower, sub_str);
        return strstr(to_lower(str_lower), to_lower(sub_str_lower));
    }
    return strstr(str, sub_str);
}

void my_find(const char* dir_target, const char * find, int mayus){
    DIR* dir = opendir(dir_target);
    if (dir == NULL) {
        return;
    }
    int returner = SUCES;
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
	int entrar = strstr_flags(entry->d_name, find, mayus) != NULL;
	if (entrar) {
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