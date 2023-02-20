#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    FILE *fd;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);
    printf("SERVER: waiting for client...\n");

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");

    printf("SERVER: received filename '%s'\n", buffer);

    if ((fd = fopen(buffer, "r")) != NULL)
    {
        printf("SERVER: sending file '%s'\n", buffer);

        while ((n = fread(buffer, 1, 256, fd)) > 0)
        {
            if (write(newsockfd, buffer, n) < 0)
                error("ERROR writing to socket");
        }

        fclose(fd);
    }
    else
    {
        printf("SERVER: file '%s' not found\n", buffer);
        n = write(newsockfd, "File not found!", 15);
        if (n < 0)
            error("ERROR writing to socket");
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}