#include <stdio.h>
#include <string.h>

int i, j, t, divisor_len, data_len;
char dataword[100], cs[100], divisor[] = "1011";

void crc()
{
    for (i = 0; i < divisor_len; i++)
        cs[i] = dataword[i];

    while (i < data_len + divisor_len)
    {
        if (cs[0] == '1')
        {
            for (j = 1; j < divisor_len; j++)
                cs[j] = cs[j] == divisor[j] ? '0' : '1'; // XOR Operation
        }

        for (j = 0; j < divisor_len - 1; j++)
            cs[j] = cs[j + 1]; // Leave the 1st bit and right shift
        cs[j] = dataword[i++]; // Insert next bit from dataword to checksum
    }
}

void main()
{
    printf("Enter the data: ");
    scanf("%s", dataword);
    divisor_len = strlen(divisor);
    data_len = strlen(dataword);

    // Appending 0s to dataword
    for (i = 0; i < divisor_len - 1; i++)
        dataword[data_len + i] = '0';

    printf("Data after appending 0s is: %s\n", dataword);

    crc();
    printf("The checksum is: %s\n", cs);

    // Adding checksum to the dataword
    for (i = data_len; i < data_len + divisor_len - 1; i++)
        dataword[i] = cs[i - data_len];

    printf("Final codeword is: %s\n", dataword);

    printf("Test error condition:\n1. Yes\n0. No\n");
    scanf("%d", &t);

    if (t == 1)
    {
        printf("Enter the received data: ");
        scanf("%s", dataword);
        crc();

        if (strcmp(cs, "000") == 0)
            printf("No error detected");
        else
            printf("Error detected");
    }
}