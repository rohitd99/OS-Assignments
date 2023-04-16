#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    if (argc >= 3 || argc <= 1)
    {
        printf("Invalid argument \n");
        return -1;
    }
    else
    {
        struct dirent *de;

        DIR *dr = opendir(argv[1]);

        if (dr == NULL)
        {
            printf("Could not open current directory");
            return 0;
        }

        while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);

        closedir(dr);
    }
    return 0;
}