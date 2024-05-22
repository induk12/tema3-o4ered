#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdio.h"
#include "string.h"

#define NAMEDPIPE "/tmp/calc_pipe"
#define BUFSIZE 600

int main()
{
    int fd, len;
    char buf[BUFSIZE];
    char arg[3][BUFSIZE];
    int result;
    char *token;
    char rec[BUFSIZE];
    if (mkfifi(NAMEDPIPE, 0777)){
        perror("mkinfo");
        return 1;
    }
    if ((fd = open(NAMEDPIPE, O_RDONLY)) <=0){
        perror("open");
        return 1;
    }
    do {
        if ((len = read(fd, buf, BUFSIZE-1)) <=0){
            perror("read");
            close(fd);
            remove(NAMEDPIPE);
            break;
        }
    } while(1);
    strncpy(rec, buf, sizeof(buf));
    
    token = strtok(rec, " ");
    
    strcpy(arg[0], token);
    token = strtok(NULL, " ");
    
    strcpy(arg[1], token);
    token = strtok(NULL, " ");
    
    strcpy(arg[2], token);
    token = strtok(NULL, " ");
    
    char op;
    strcpy(&op, arg[1]);
    
    switch(op){
        case '+':
            result = atoi(arg[0]) + atoi(arg[2]);
            break;
        case '-':
            result = atoi(arg[0]) - atoi(arg[2]);
            break;
        case '*':
            result = atoi(arg[0]) * atoi(arg[2]);
            break;
        case '/':
            if (atoi(arg[2]) != 0){
                result = atoi(arg[0]) / atoi(arg[2]);
                break
            }
            else{
                printf("cant divide by zero(0)\n");
                return 0;
            }
            default:
                printf("Incorrect operatror!\n");
                return 0;
        }
            printf("INCOMMING MESSEGE(%d): %s\n", len, buf);
            printf("RESULT:%i\n", result);
        

}
