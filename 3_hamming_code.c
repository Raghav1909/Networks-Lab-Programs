#include <stdio.h>

void main()
{
    int orig_data[8], recv_data[8], i, p, p1, p2, p4;

    printf("Enter 4 bits of data to send: ");
    scanf("%1d%1d%1d%1d", &orig_data[7], &orig_data[6], &orig_data[5], &orig_data[3]);

    orig_data[1] = orig_data[3] ^ orig_data[5] ^ orig_data[7];
    orig_data[2] = orig_data[3] ^ orig_data[6] ^ orig_data[7];
    orig_data[4] = orig_data[5] ^ orig_data[6] ^ orig_data[7];

    printf("The encoded bits to be sent are: ");
    for (i = 7; i >= 1; i--)
        printf("%d", orig_data[i]);
    printf("\n");

    printf("Enter the received data: ");
    for (i = 7; i >= 1; i--)
        scanf("%1d", &recv_data[i]);

    printf("%1d%1d%1d%1d\n", orig_data[1], recv_data[3], recv_data[5], recv_data[7]);

    p1 = orig_data[1] ^ recv_data[3] ^ recv_data[5] ^ recv_data[7];
    p2 = orig_data[2] ^ recv_data[3] ^ recv_data[6] ^ recv_data[7];
    p4 = orig_data[4] ^ recv_data[5] ^ recv_data[6] ^ recv_data[7];
    p = p4 * 4 + p2 * 2 + p1 * 1;
    printf("p1 = %d, p2 = %d, p3 = %d\n", p1, p2, p4);
    if (p == 0)
        printf("There is no error and the received data is correct\n");
    else
    {
        printf("There is an error at position %d\n", p);
        printf("The corrected data is: ");
        recv_data[p] = recv_data[p] == 0 ? 1 : 0;
        for (i = 7; i >= 1; i--)
            printf("%d", recv_data[i]);
        printf("\n");
    }
}