#include <stdio.h>
#include <stdlib.h>

int n, nf;
int in[100];
int p[50];
int comparePF[3];
int hit = 0;
int i, j, k;
int pgfaultcnt = 0;

void getData()
{
    printf("\nEnter length of page reference sequence:");
one:
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("\nLength cannot be 0 or negative. Re-enter!\n");
        goto one;
    }
    printf("\nEnter the page reference sequence:\n");
two:
    for (i = 0; i < n; i++)
    {
        scanf("%d", &in[i]);
        if (in[i] < 0)
        {
            printf("\nPage reference sequence cannot be negative. Re-enter! \n");
            goto two;
        }
    }
    printf("\nEnter no of frames:");
three:
    scanf("%d", &nf);
    if (nf <= 0)
    {
        printf("\nNumber of frames cannot be 0 or negative. Re-enter!\n");
        goto three;
    }
}

void initialize()
{
    pgfaultcnt = 0;
    for (i = 0; i < nf; i++)
        p[i] = 9999;
}

int isHit(int data)
{
    hit = 0;
    for (j = 0; j < nf; j++)
    {
        if (p[j] == data)
        {
            hit = 1;
            break;
        }
    }

    return hit;
}

int getHitIndex(int data)
{
    int hitind;
    for (k = 0; k < nf; k++)
    {
        if (p[k] == data)
        {
            hitind = k;
            break;
        }
    }
    return hitind;
}

void dispPages()
{
    for (k = 0; k < nf; k++)
    {
        if (p[k] != 9999)
            printf(" %d", p[k]);
    }
}

void dispPgFaultCnt()
{
    printf("\nTotal no of page faults:%d", pgfaultcnt);
    printf("\nPercentage page fault: %.3f%%", ((float)pgfaultcnt / (float)n) * 100);
}

void fifo()
{
    initialize();
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (isHit(in[i]) == 0)
        {
            for (k = 0; k < nf - 1; k++)
                p[k] = p[k + 1];

            p[k] = in[i];
            pgfaultcnt++;
            dispPages();
        }
        else
            printf("No page fault");
    }
    comparePF[0] = pgfaultcnt;
    dispPgFaultCnt();
}

void optimal()
{
    initialize();
    int near[50];
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (isHit(in[i]) == 0)
        {
            for (j = 0; j < nf; j++)
            {
                int pg = p[j];
                int found = 0;
                for (k = i; k < n; k++)
                {
                    if (pg == in[k])
                    {
                        near[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    near[j] = 9999;
            }
            int max = -9999;
            int repindex;
            for (j = 0; j < nf; j++)
            {
                if (near[j] > max)
                {
                    max = near[j];
                    repindex = j;
                }
            }
            p[repindex] = in[i];
            pgfaultcnt++;

            dispPages();
        }
        else
            printf("No page fault");
    }
    comparePF[1] = pgfaultcnt;
    dispPgFaultCnt();
}

void lru()
{
    initialize();

    int least[50];
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (isHit(in[i]) == 0)
        {

            for (j = 0; j < nf; j++)
            {
                int pg = p[j];
                int found = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (pg == in[k])
                    {
                        least[j] = k;
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    least[j] = -9999;
            }
            int min = 9999;
            int repindex;
            for (j = 0; j < nf; j++)
            {
                if (least[j] < min)
                {
                    min = least[j];
                    repindex = j;
                }
            }
            p[repindex] = in[i];
            pgfaultcnt++;
            dispPages();
        }
        else
            printf("No page fault!");
    }
    comparePF[2] = pgfaultcnt;
    dispPgFaultCnt();
}

int main()
{
    for (int i = 0; i < 3; i++)
        comparePF[i] = -1;

    int choice;
    while (1)
    {
    start:
        printf("\n\nPage Replacement Algorithms\n1.Enter data\n2.FIFO\n3.Optimal\n4.LRU\n5.Compare performance of Algorithms\n6.Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            getData();
            break;
        case 2:
            fifo();
            break;
        case 3:
            optimal();
            break;
        case 4:
            lru();
            break;
        case 5:
        {
            printf("%d\t%d\t%d\t", comparePF[0], comparePF[1], comparePF[2]);
            if (comparePF[0] < 0 || comparePF[1] < 0 || comparePF[2] < 0)
            {
                printf("Run all the algorithms atleast once to compare them.");
                goto start;
            }
            else
            {
                if (comparePF[1] == comparePF[0])
                {
                    printf("FIFO and OPTIMAL have minimum page fault = %d", comparePF[1]);
                    printf("Minimum page fault: FIFO = OPTIMAL < LRU");
                }
                else if (comparePF[1] == comparePF[2])
                {
                    printf("LRU and OPTIMAL have minimum page fault = %d", comparePF[1]);
                    printf("Minimum page fault: LRU = OPTIMAL < FIFO");
                }
                else
                {
                    if (comparePF[0] == comparePF[2])
                    {
                        printf("OPTIMAL has minimum page fault = %d", comparePF[1]);
                        printf("Minimum page fault: OPTIMAL < LRU = FIFO");
                    }
                    if (comparePF[0] < comparePF[2])
                    {
                        printf("OPTIMAL has minimum page fault = %d", comparePF[1]);
                        printf("Minimum page fault: OPTIMAL < FIFO < LRU");
                    }
                }
                if (comparePF[0] > comparePF[2])
                {
                    printf("OPTIMAL has minimum page fault = %d", comparePF[1]);
                    printf("Minimum page fault: OPTIMAL < LRU < FIFO");
                }
            }
        }
        break;
        case 6:
            exit(0);
        default:
            return 0;
            break;
        }
    }
}
