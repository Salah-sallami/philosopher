#include <stdlib.h>
#include <unistd.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    if (!argv || !file || ( type != 'r' && type != 'w'))
        return -1;

    int fd[2];

    pipe(fd);

    if (type == 'r')
    {
        if (fork() == 0)
        {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            execv(file, argv);
            exit(-1);
        }
        close(fd[1]);
        return fd[0];
    }
     if (type == 'w')
    {
        if (fork() == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            close(fd[0]);
            execv(file, argv);
            exit(-1);
        }
        close(fd[0]);
        return fd[1];
    }
    return -1;
}
#include <stdio.h>
int main()
{
    int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');

    
}