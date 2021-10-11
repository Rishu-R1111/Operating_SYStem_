#include <stdio.h>
#include <stdlib.h>
int mat[10][6];
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void arrangeArrival(int n, int mat[][6])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (mat[j][1] > mat[j + 1][1])
            {
                for (int k = 0; k < 5; k++)
                {
                    swap(&mat[j][k], &mat[j + 1][k]);
                }
            }
        }
    }
}
void completionTime(int n, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for (int i = 1; i < n; i++)
    {
        temp = mat[i - 1][3];
        int low = mat[i][2];
        for (int j = i; j < n; j++)
        {
            if (temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for (int k = 0; k < 6; k++)
        {
            swap(&mat[val][k], &mat[i][k]);
        }
    }
}
void main()
{
    int n;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("\nEnter Arrival Time and burst time for %d process\n", n);
    for (int i = 0; i < n; i++)
    {
        mat[i][0] = i + 1;
        printf("Enter Arrival time for process %d: ", i + 1);
        scanf("%d", &mat[i][1]);
        printf("Enter Burst time for process %d: ", i + 1);
        scanf("%d", &mat[i][2]);
    }
    printf("\n----------------Printing input  data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t %d\t\t  %d", mat[i][0], mat[i][1], mat[i][2]);
        printf("\n");
    }
    arrangeArrival(n, mat);
    completionTime(n, mat);
    printf("\n----------------Printing Output data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\tWaitingTime\tTurnAroundTime\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t %d\t\t  %d\t\t   %d\t\t %d", mat[i][0], mat[i][1], mat[i][2], mat[i][4], mat[i][5]);
        printf("\n");
    }
    float avg1 = 0;
    float avg2 = 0;
    for (int i = 0; i < n; i++)
    {
        avg1 += mat[i][4];
        avg2 += mat[i][5];
    }
    avg1 /= n;
    avg2 /= n;
    int shortwt = mat[0][4];
    for (int i = 1; i < n; i++)
    {
        if (mat[i][4] < shortwt)
        {
            shortwt = mat[i][4];
        }
    }
    int shortat = mat[0][5];
    for (int i = 1; i < n; i++)
    {
        if (mat[i][5] < shortat)
        {
            shortat = mat[i][5];
        }
    }
    printf("\n Average turn Around Time is: %f\n", avg2);
    printf(" Average Waiting Time is: %f", avg1);
    printf("\n shortest Turn  Around Time is: %d \n", shortat);
    printf(" shortest Waiting Time is: %d", shortwt);
}
