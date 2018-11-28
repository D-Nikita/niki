#include<stdio.h>
#include<time.h>
#include<omp.h>
int main()
{
int a[10][10],b[10][10],result[10][10],r1,r2,c1,c2,tid,j,k,i;
clock_t tic, toc;

printf("enter rows andcolumns for first matrix:\n");
scanf("%d%d",&r1,&c1);
printf("enter rows and coluumns for second matrix:\n");
scanf("%d%d",&r2,&c2);

while(c1!=r2)
{
printf("error!!column of first matrix notequal to rowof second\n");

printf("enter rows and columns forfirst matrix\n");
scanf("%d%d",&r1,&c1);
printf("enter rows and coluumns for second matrix:\n");
scanf("%d%d",&r2,&c2);
}

printf("\nenter elements of matrix 1:\n");
for(i=0;i<r1;i++)
for(j=0;j<c1;j++)
{
printf("enter elements of %d %d",i+1,j+1);
scanf("%d",&a[i][j]);
}

printf("enter elements of second matrix\n");
for(i=0;i<r2;i++)
for(j=0;j<c2;j++)
{
printf("enter elements of %d %d",i+1,j+1);
scanf("%d",&b[i][j]);
}


for(i=0;i<r1;i++)
for(j=0;j<c2;j++)

result[i][j]=0;

tic=clock();
#pragma omp parallel num_threads(3) shared(a,b,result,r1,c1,r2,c2) private(i,j,k,tid)
{
int tid=omp_get_thread_num();
#pragma omp for

for(i=0;i<r1;++i)
{
printf("\n Hi I am thread %d and my value=%d\n",tid,i);

for(j=0;j<c2;++j)
for(k=0;k<c1;++k)

result[i][j]+=a[i][k]*b[k][j];

}
}

toc=clock();
printf("\n output matrix\n");
for(i=0;i<r1;++i)
for(j=0;j<c2;++j)
{
printf("%d\t",result[i][j]);
if(j==c2-1)
printf("\n\n");
}
return 0;
}
                                                                                                                                   

