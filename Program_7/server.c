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
    int num, fifo_W, fifo_R, file_R;
    mknod(FIFO1, S_IFIFO | 0666, 0);
    mknod(FIFO2, S_IFIFO | 0666, 0);
    printf("SERVER ONLINE!\n\n");
    fifo_R = open(FIFO1, O_RDONLY);
    fifo_W = open(FIFO2, O_WRONLY);
    printf("\nClient ONLINE!!\nwaiting for request..\n\n");
    if ((num = read(fifo_R, p, 100)) == -1)
        perror("Read error\n");
    else
    {
        p[num] = '\0';
        if ((file_R = open(p, O_RDONLY)) < 0)
        {
            perror("\nFILE");
            write(fifo_W, "ERROR", strlen("ERROR"));
            return 1;
        }
        else
        {
            num = read(file_R, c, 5000);
            if (num == -1)
                perror("Read");
            else
            {
                printf("SERVER: !! \nTransferring the content..%s", p);
                write(fifo_W, c, 5000);
            }
        }
    }
    printf("Transfer Completed\n");
    return 1;
}