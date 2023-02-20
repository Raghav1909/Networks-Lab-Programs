#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
int main()
{
    char p[100], c[5000];
    int num, fifo_R, fifo_W;
    mknod(FIFO1, S_IFIFO | 0666, 0);
    mknod(FIFO2, S_IFIFO | 0666, 0);
    printf("CLIENT Working...\n");
    fifo_W = open(FIFO1, O_WRONLY);
    fifo_R = open(FIFO2, O_RDONLY);
    printf("Client:!!\nEnter the path: ");
    scanf("%s", p);
    num = write(fifo_W, p, strlen(p));
    if (num == -1)
    {
        perror("write error\n");
        return 1;
    }
    else
    {
        printf("waiting for reply.. \n");
        if ((num = read(fifo_R, c, 5000)) == -1)
            perror("Transfer error!\n");
        else
        {
            c[num] = '\0';
            if (strcmp(c, "ERROR") == 0)
            {
                printf("File not found,connection ended\n");
                return 1;
            }
            printf("File received..!! \n displaying the content..\n");
            printf("%s\n", c);
        }
    }
    return 1;
}