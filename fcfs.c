#include<stdio.h>
int main()
{
    int  p[10],at[10],bt[10],ct[10],tat[10],wt[10],i,j,temp=0,n;
    float awt=0,atat=0;
    printf("enter no of proccess you want:");
    scanf("%d",&n);
    printf("enter %d process:",n);
    for(i=0;i<n;i++)
    {
    scanf("%d",&p[i]);
    }
    printf("enter %d arrival time:",n);
    for(i=0;i<n;i++)
    {
    scanf("%d",&at[i]);
    }
    printf("enter %d burst time:",n);
    for(i=0;i<n;i++)
    {
    scanf("%d",&bt[i]);
    }
    // sorting at,bt, and process according to at
    for(i=0;i<n;i++)
    {
     for(j=0;j<(n-i);j++)
    {
      if(at[j]>at[j+1])
     {
        temp=p[j+1];
        p[j+1]=p[j];
        p[j]=temp;
        temp=at[j+1];
        at[j+1]=at[j];
        at[j]=temp;
        temp=bt[j+1];
        bt[j+1]=bt[j];
        bt[j]=temp;
      }
     }
    }
    /* calculating 1st ct */
    ct[0]=at[0]+bt[0];
    /* calculating 2 to n ct */
    for(i=1;i<n;i++)
    {
      //when proess is ideal in between i and i+1
      temp=0;
     if(ct[i-1]<at[i])
     {
        temp=at[i]-ct[i-1];
     }
     ct[i]=ct[i-1]+bt[i]+temp;
    }
    /* calculating tat and wt */
    printf("\np\t A.T\t B.T\t C.T\t TAT\t WT");
    for(i=0;i<n;i++)
    {
    tat[i]=ct[i]-at[i];
    wt[i]=tat[i]-bt[i];
    atat+=tat[i];
    awt+=wt[i];
    }
    atat=atat/n;
    awt=awt/n;
    for(i=0;i<n;i++)
    {
      printf("\nP%d\t %d\t %d\t %d \t %d \t %d",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("\naverage turnaround time is %f",atat);

    printf("\naverage wating timme is %f",awt);
    return 0;
}

// enter no of proccess you want:5
// enter 5 process:1 2 3 4 5
// enter 5 arrival time:5 3 4 1 2
// enter 5 burst time:5 4 4 3 7

// p        A.T     B.T     C.T     TAT     WT
// P4       1       3       4       3       0
// P5       2       7       11      9       2
// P2       3       4       15      12      8
// P3       4       4       19      15      11
// P1       5       5       24      19      14
// average turnaround time is 11.600000
// average wating timme is 7.000000
