#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdio.h"
#include "string.h"

#define NAMEDPIPE "/tmp/calc_pipe"
#define BUFSIZE 100

int main()
{
    int fd, len;
    mkfifo(NAMEDPIPE, 0777);
    fd = open(NAMEDPIPE, O_WRONLY);
    
    char buf[BUFSIZE];
        
        print("write: ");
        fgets(buf, BUFSIZE, stdin);
        buf[strlen(buf)-1] = '\0';
        write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}
