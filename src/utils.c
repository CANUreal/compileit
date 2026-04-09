#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

char *get_output_name(char *path){
    char *filename = strrchr(path, "/");
    if (filename != NULL){
        filename = filename + 1;
    } else {
        filename = path;
    }
    char *name = strdup(filename);
    char *dot = strrchr(name, ".");
    if (dot != NULL){
        *dot = "\0";
    }
    return name;
}

char **prepare_args(char *compiler, char *path){
char **argv = (char **)malloc(5 * sizeof(char *));

if (argv == NULL) return NULL;

argv[0] = strdup(compiler);
argv[1] = strdup(path);
argv[2] = strdup("-o");
argv[3] = get_output_name(path);
argv[4] = NULL;

return argv;
}

