#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include<fcntl.h>

int main(int argc,char* argv[])
{
    int pipe1[2]; 
    int pipe2[2];
    int fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        printf("Error in opening txt file\n");
    }
    // int savedstdout = dup(STDOUT_FILENO);
    
    if(pipe(pipe1) == -1)
    {
        printf("Error in creating a pipe\n");
        return -1; 
    }
    if(pipe(pipe2) == -1)
    {
        printf("Error in creating a pipe\n");
        return -1; 
    }
    int child = fork();
    if(child == -1)
    {
        printf("Error in creating a child process\n");
        return -1;
    }else if(child == 0)
    {   close(pipe1[1]); // Doesn't write to pipe 1's write
        close(pipe2[0]); // Doesn't read from pipe 2's read
        int a = 0,b = 0,c = 0;
        if(read(pipe1[0],&a,sizeof(a))  == -1)
        {
            printf("Error while reading from pipe\n");
        }
        if(read(pipe1[0],&b,sizeof(b))  == -1)
        {
            printf("Error while reading from pipe\n");
        }
        
        c = a+b;
        if(write(pipe2[1],&c,sizeof(c))  == -1)
        {
            printf("Error in writing to pipe\n");
            return -1;
        }
        close(pipe1[0]);
        close(pipe2[1]);
        
    }else{
        close(pipe1[0]); // Doesn't read from pipe 1's read
        close(pipe2[1]); // Doesn't write to pipe 2's write
        int x = 0, y = 0,sum = 0;
        printf("Enter value of x : ");
        scanf("%d",&x);
        printf("Enter value of y : ");
        scanf("%d",&y);
        dup2(fd,STDOUT_FILENO);
        // write(fd, &x, sizeof(int));
        // write(fd, &y, sizeof(int));
        
        if(write(pipe1[1],&x,sizeof(x)) == -1)
        {
            printf("Error in writing to pipe\n");
            return -1;
        }
        if(write(pipe1[1],&y,sizeof(y))  == -1)
        {
            printf("Error in writing to pipe\n");
            return -1;
        }
        
        if(read(pipe2[0],&sum,sizeof(sum))  == -1)
        {
            printf("Error while reading from pipe\n");
        }
        dup2(fd,STDOUT_FILENO); 
        printf("The sum returned from Child : %d\n",sum);
        close(pipe1[1]);
        close(pipe2[0]);
        
    }
    close(fd);
    // close(savedstdout);
    return 0;
}