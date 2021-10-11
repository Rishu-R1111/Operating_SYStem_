#include <stdio.h>
#include <stdlib.h>
int mat[10][6];
void fcfs()
{
    printf("-------------------------------First Come First Serve------------------------\n");
    int n;
    printf("Enter number of process :");
    scanf("%d", &n);
    if (n == 0)
    {
        printf("\nZero Process\n");
        return;
    }
    int at[n];
    int bt[n];
    int p[n];
    printf("\nEnter arrival time and burst time for %d processes\n", n);
    int i = 0;
    while (i < n)
    {
        printf("at[%d]: ", i + 1);
        scanf("%d", &at[i]);
        printf("bt[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;
        if (at[i] < 0 || bt[i] < 0)
        {
            printf("\n Time cannot be negative\n ");
        }
        else
        {
            i++;
        }
    }
    printf("\n----------------Printing input  data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t %d\t\t  %d", p[i], at[i], bt[i]);
        printf("\n");
    }
    int j, position, swap;
    for (i = 0; i < (n - 1); i++)
    {
        position = i;
        for (j = i + 1; j < n; j++)
        {
            if (at[position] > at[j])
                position = j;
        }
        if (position != i)
        {
            swap = at[i];
            at[i] = at[position];
            at[position] = swap;
            swap = bt[i];
            bt[i] = bt[position];
            bt[position] = swap;
            swap = p[i];
            p[i] = p[position];
            p[position] = swap;
        }
    }
    int ct[n];
    int x = at[0];
    for (i = 0; i < n; i++)
    {
        if (x >= at[i])
        {
            ct[i] = x + bt[i];
            x = ct[i];
        }
        else
        {
            x = at[i];
            ct[i] = x + bt[i];
            x = ct[i];
        }
    }
    int tat[n];
    int wt[n];
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
    }
    int shortat = tat[0];
    int shortwt;
    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i];
    }
    shortwt = wt[0];
    for (i = 0; i < (n - 1); i++)
    {
        position = i;
        for (j = i + 1; j < n; j++)
        {
            if (p[position] > p[j])
                position = j;
        }
        if (position != i)
        {
            swap = p[i];
            p[i] = p[position];
            p[position] = swap;
            swap = at[i];
            at[i] = at[position];
            at[position] = swap;
            swap = bt[i];
            bt[i] = bt[position];
            bt[position] = swap;
            swap = tat[i];
            tat[i] = tat[position];
            tat[position] = swap;
            swap = wt[i];
            wt[i] = wt[position];
            wt[position] = swap;
        }
    }
    printf("\n----------------Printing Output data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\tTurnAroundTime\tWaitingTime\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t %d\t\t  %d\t\t   %d\t\t %d", p[i], at[i], bt[i], tat[i], wt[i]);
        printf("\n");
    }
    float avg1 = 0;
    float avg2 = 0;
    for (i = 0; i < n; i++)
    {
        avg1 += tat[i];
        avg2 += wt[i];
    }
    avg1 /= n;
    avg2 /= n;
    printf("\n Average turn Around Time is: %f\n", avg1);
    printf(" Average Waiting Time is: %f", avg2);
    printf("\n shortest  Around Time is: %d \n", shortat);
    printf(" shortest Waiting Time is: %d", shortwt);
}
void srtf()
{
    printf("------------SRTF------------------------------------------\n");
    int at[10], bt[10], rt[10], endTime, i, smallest, processGantt[100];
    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;
    printf("Enter no of Processes : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time for Process P%d : ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for Process P%d : ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    printf("\n----------------Printing input data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t %d\t\t  %d", i + 1, at[i], bt[i]);
        printf("\n");
    }
    printf("\n----------------Printing Output data in tabular form------------------------------\n");
    printf("\n\nProcess\tTurnaround Time Waiting Time\n\n");
    rt[9] = 9999;
    for (time = 0; remain != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)
            {
                processGantt[time] = i;
                smallest = i;
            }
        }
        rt[smallest]--;
        if (rt[smallest] == 0)
        {
            remain++;
            endTime = time + 1;
            printf("\nP[%d]\t\t%d\t\t%d", smallest + 1, endTime - at[smallest], endTime - bt[smallest] - at[smallest]);
            sum_wait += endTime - bt[smallest] - at[smallest];
            sum_turnaround += endTime - at[smallest];
        }
    }
    printf("\n\nAverage waiting time = %f\n", sum_wait * 1.0 / n);
    printf("Average Turnaround time = %f\n\n", sum_turnaround * 1.0 / 5);
}
void roundRobin()
{
    printf("-----------------------ROUND ROBIN---------\n");
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
    printf(" Total number of process in the system: ");
    scanf("%d", &NOP);
    y = NOP;

    for (i = 0; i < NOP; i++)
    {
        printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf(" Arrival time is: \t");
        scanf("%d", &at[i]);
        printf(" \nBurst time is: \t");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quant);

    printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");
    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1)
        {
            y--;
            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (i == NOP - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }

    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("\n Average Turn Around Time: \t%f", avg_wt);
    printf("\n Average Waiting Time: \t%f", avg_tat);
}

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
void sjn()
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
    printf("\n Average turn Around Time in ms is : %f\n", avg2);
    printf(" Average Waiting Time in ms is: %f", avg1);
    printf("\n shortest Turn  Around Time in ms is: %d \n", shortat);
    printf(" shortest Waiting Time in ms is: %d", shortwt);
}
void main()
{
    int ch;
    do
    {
        printf("\n Enter the choice \n");
        printf("\n 1. FCFS \n");
        printf("\n 2. SJF \n");
        printf("\n 3. Round robin \n");
        printf("\n 4. SRTF\n");
        printf("\n 5. QUIT \n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjn();

            break;
        case 3:
            roundRobin();

            break;
        case 4:
            srtf();

            break;

        case 5:
            printf("\n QUITING .. \n");
            exit(0);
            break;
        default:
            printf("Enter Valid choice \n");
        }
    } while (ch != 9);
}
