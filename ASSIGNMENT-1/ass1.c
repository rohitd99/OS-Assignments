#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>

int main(int argc,char *argv[])
{
    if(strcmp(argv[1],"ls") == 0)
    {
        if(argc == 4)
        {
            execlp("/bin/ls", "ls", argv[2] ,argv[3], NULL);
        }else if(argc == 3)
        {
            execlp("/bin/ls", "ls", argv[2], NULL); 
        }
    }else if(strcmp(argv[1],"cp") == 0)
    {
        execlp("/bin/cp", "cp",argv[2], argv[3], NULL);
    }else if(strcmp(argv[1],"grep") == 0)
    {
        if(argc == 5)
        {
            execlp("/bin/grep", "grep",argv[2],argv[3],argv[4], NULL); 
        }else if(argc == 4){
            execlp("/bin/grep", "grep",argv[2],argv[3], NULL);
        }
    }else{
        printf("Invalid command cp,ls,grep only allowed\n");
    }
    
    return 0;
}