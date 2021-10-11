#include <stdio.h>
#include <stdlib.h>

int n, nf;
int in[100];
int p[50];
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

void lru()
{
    initialize();

    int least[50];
    for (i = 0; i < n; i++)
    {
        printf("\nFor %d :", in[i]);

        if (isHit(in[i]) == 0) //page fault
        {

            for (j = 0; j < nf; j++) //iterate frames
            {
                int pg = p[j]; //1
                int found = 0;
                for (k = i - 1; k >= 0; k--)
                {
                    if (pg == in[k]) //1
                    {
                        least[j] = k; //1 -9999 -9999
                        found = 1;
                        break;
                    }
                    else
                        found = 0;
                }
                if (!found)
                    least[j] = -9999; //-9999 -9999 -9999
            }
            int min = 9999;
            int repindex;
            for (j = 0; j < nf; j++)
            {
                if (least[j] < min)
                {
                    min = least[j]; //1
                    repindex = j;   //0
                }
            }
            p[repindex] = in[i]; //1
            pgfaultcnt++;        //2
            dispPages();
        }
        else
            printf("No page fault!");
    }
    dispPgFaultCnt();
}

int main()
{
    getData();
    lru();
}
