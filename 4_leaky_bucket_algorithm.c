#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

int main()
{
    int bucket_size, output_rate, num_packets, i, j, num_seconds, packets_left, packets_dropped;
    printf("LEAKY BUCKET ALGORITHM\n");
    printf("Enter the bucket size: ");
    scanf("%d", &bucket_size);
    printf("Enter the output rate: ");
    scanf("%d", &output_rate);
    printf("Enter the number of seconds: ");
    scanf("%d", &num_seconds);

    int packets_received[num_seconds];
    for (i = 0; i < num_seconds; i++)
    {
        printf("Enter the number of packets entering at second %d: ", i + 1);
        scanf("%d", &packets_received[i]);
    }

    packets_left = 0;
    packets_dropped = 0;
    printf("\n(SECOND):\t(PACKETS RECEIVED):\t(PACKETS SENT):\t(PACKETS LEFT):\t(PACKETS DROPPED):\n");
    for (i = 0; i < num_seconds; i++)
    {
        int packets_sent = MIN(packets_received[i] + packets_left, output_rate);
        packets_dropped += packets_received[i] + packets_left - packets_sent;
        packets_left = MAX(packets_sent - output_rate, 0);
        printf("(%d):\t\t(%d)\t\t\t(%d)\t\t(%d)\t\t(%d)\n", i + 1, packets_received[i], packets_sent, packets_left, packets_dropped);
    }

    while (packets_left > 0)
    {
        int packets_sent = MIN(packets_left, output_rate);
        packets_left = MAX(packets_sent - output_rate, 0);
        printf("(%d):\t\t(0)\t\t\t(%d)\t\t(%d)\t\t(0)\n", i + 1, packets_sent, packets_left);
        i++;
    }

    return 0;
}
