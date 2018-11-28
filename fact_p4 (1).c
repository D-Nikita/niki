#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
typedef long long ABC;
int main(int argc, char *argv[])
{
int rank, num, i, n=0, first, last;
ABC prod=1, result=1, root=0;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &num);
if(rank==root)
{
printf("\nenter the value of n");
scanf("%d", &n);
}
MPI_Bcast(&n, 1, MPI_LONG_LONG, root, MPI_COMM_WORLD);
first=(rank*n)/num;
last=((rank+1)*n)/num;
for(i=first+1; i<=last; i++)
prod*=i;
MPI_Reduce(&prod, &result, 1, MPI_LONG, MPI_PROD, root, MPI_COMM_WORLD);
if(rank==root)
printf("\nfactorial of %d is  %d \n", n, result);
MPI_Finalize();
return 0;
}

