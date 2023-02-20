#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

long int gcd(long int a, long int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long int encrypt(char ch, long int n, long int e)
{
    int i;
    long int temp = ch;
    for (i = 1; i < e; i++)
        temp = (temp * ch) % n;
    return temp;
}

char decrypt(long int ch, long int n, long int d)
{
    int i;
    long int temp = ch;
    for (i = 1; i < d; i++)
        ch = (temp * ch) % n;
    return ch;
}

int main()
{
    long int i, len;
    long int p, q, n, phi, e, d, cipher[50];
    char text[50];
    printf("Enter the text to be encrypted: ");
    gets(text);
    len = strlen(text);
    printf("Enter the first prime number: ");
    scanf("%ld", &p);
    printf("Enter the second prime number: ");
    scanf("%ld", &q);
    n = p * q;
    phi = (p - 1) * (q - 1);
    do
    {
        e = rand() % phi;
    } while (gcd(phi, e) != 1);
    do
    {
        d = rand() % phi;
    } while (((d * e) % phi) != 1);

    printf("Two prime numbers (p and q) are: %ld and %ld\n", p, q);
    printf("n (p * q) = %ld * %ld = %ld\n", p, q, n);
    printf("phi = (p-1) * (q-1) = %ld\n", phi);
    printf("Public key (n, e): (%ld, %ld)\n", n, e);
    printf("Private key (n, d): (%ld, %ld)\n", n, d);
    for (i = 0; i < len; i++)
        cipher[i] = encrypt(text[i], n, e);
    printf("Encrypted message: ");
    for (i = 0; i < len; i++)
        printf("%ld ", cipher[i]);
    printf("\n");
    for (i = 0; i < len; i++)
        text[i] = decrypt(cipher[i], n, d);
    printf("Decrypted message: %s", text);
}