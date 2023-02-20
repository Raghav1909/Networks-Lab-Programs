#include <stdio.h>
#include <stdlib.h>

struct dva
{
    char nodname;
    int delay;
    char nexthop;
} mod[10][10], rt[10][10];

void main()
{
    int dm[10][10];
    int i, n, j, k, l;
    printf("Enter the number of routers and the matrix table: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &dm[i][j]);
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            rt[i][j].nodname = j + 65;
            rt[i][j].delay = dm[i][j];
            rt[i][j].nexthop = i + 65;
        }
    }
    printf("\nInitial states of the routing tables\n\n");

    for (i = 0; i < n; i++)
    {
        printf("Router %c\n", i + 65);
        for (j = 0; j < n; j++)
        {
            printf("%c\t%d\t%c\n", rt[i][j].nodname, rt[i][j].delay, rt[i][j].nexthop);
        }
        printf("\n\n");
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j || dm[i][j] == 99)
                continue;
            for (l = 0; l < n; l++)
            {
                mod[j][l].delay = dm[i][j] + rt[j][l].delay;
                mod[j][l].nodname = rt[j][l].nodname;
                mod[j][l].nexthop = j + 65;
            }
            for (k = 0; k < n; k++)
            {
                if (mod[j][k].delay < rt[i][k].delay)
                {
                    rt[i][k].delay = mod[j][k].delay;
                    rt[i][k].nexthop = mod[j][k].nexthop;
                }
            }
        }
    }

    printf("\nFinal states of the routing tables\n\n");
    for (i = 0; i < n; i++)
    {
        printf("Router %c\n", i + 65);
        for (j = 0; j < n; j++)
        {
            printf("%c\t%d\t%c\n", rt[i][j].nodname, rt[i][j].delay, rt[i][j].nexthop);
        }
        printf("\n\n");
    }
}
