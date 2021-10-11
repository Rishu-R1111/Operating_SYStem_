#include<stdio.h>
#include <stdlib.h>
 void fcfs(){
     //printf("-------------------------------First Come First Serve------------------------\n");
     int n;
     printf("Enter number of process :");
     scanf("%d",&n);
     if(n==0){
         printf("\nZero Process\n");
         return ;
     }
     int at[n];
     int bt[n];
     int p[n];
     printf("\nEnter arrival time and burst time for %d processes\n",n);
     int i=0;
     while(i<n){
         printf("at[%d]: ",i+1);
         scanf("%d",&at[i]);
         printf("bt[%d]: ",i+1);
         scanf("%d",&bt[i]);
         p[i]=i+1;
         if(at[i]<0 ||bt[i]<0 ){
             printf("\n Time cannot be negative\n ");
         }
         else{
             i++;
         }
     }
     //printf("\n----------------Printing input  data in tabular form------------------------------\n");
     printf("Process\t\tArrivalTime\tBurstTime\n");
     for(i=0;i<n;i++){
         printf("%d\t\t %d\t\t  %d",p[i],at[i],bt[i]);
         printf("\n");
     }
     int  j, position, swap;
   for (i = 0; i < (n - 1); i++) {
      position = i;
      for (j = i + 1; j < n; j++) {
         if (at[position] > at[j])
            position = j;
      }
      if (position != i) {
         swap = at[i];
         at[i] = at[position];
         at[position] = swap;
         swap=bt[i];
         bt[i]=bt[position];
         bt[position]=swap;
         swap=p[i];
         p[i]=p[position];
         p[position]=swap;
      }
   }
    int ct[n];
    int x=at[0];
    for(i=0;i<n;i++){
        if(x>=at[i]){
          ct[i]=x+bt[i];
          x=ct[i];
        }
        else{
            x=at[i];
            ct[i]=x+bt[i];
            x=ct[i];
        }
    }
    int tat[n];
    int wt[n];
    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];

    }
    int shortat=tat[0];
    int shortwt;
    for(i=0;i<n;i++){
        wt[i]=tat[i]-bt[i];

    }
    shortwt=wt[0];
    for (i = 0; i < (n - 1); i++) {
      position = i;
      for (j = i + 1; j < n; j++) {
         if (p[position] > p[j])
            position = j;
      }
      if (position != i) {
         swap=p[i];
         p[i]=p[position];
         p[position]=swap;
         swap = at[i];
         at[i] = at[position];
         at[position] = swap;
         swap=bt[i];
         bt[i]=bt[position];
         bt[position]=swap;
         swap=tat[i];
         tat[i]=tat[position];
         tat[position]=swap;
         swap=wt[i];
         wt[i]=wt[position];
         wt[position]=swap;
         
      }
   }
    //printf("\n----------------Printing Output data in tabular form------------------------------\n");
    printf("Process\t\tArrivalTime\tBurstTime\tTurnAroundTime\tWaitingTime\n");
    for(i=0;i<n;i++){
         printf("%d\t\t %d\t\t  %d\t\t   %d\t\t %d",p[i],at[i],bt[i],tat[i],wt[i]);
         printf("\n");
     }
     float avg1=0;
     float avg2=0;
     for(i=0;i<n;i++){
         avg1+=tat[i];
         avg2+=wt[i];
     }
     avg1/=n;
     avg2/=n;
    printf("\n Average turn Around Time is: %f\n",avg1);
    printf(" Average Waiting Time is: %f",avg2);
    printf("\n shortest  Around Time is: %d \n",shortat);
    printf(" shortest Waiting Time is: %d",shortwt);

 }
 void main(){
    fcfs();
 }

