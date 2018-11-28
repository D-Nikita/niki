#include<stdio.h>

#include<stdlib.h>

#include<mpi.h>

const int MAX=1023;
void insert_sorted(long *sorted, int count, long value)
{
	int i=0;
	sorted[count]=value;
	if(count==0)
		return;
	for(i=count; i>0; i--)
	{
		if (value>sorted[i-1])
		{
			sorted[i]=sorted[i-1];
		}
		else
			break;
	}
	sorted[i]=value;
}



int main(int argc, char *argv[])

{ 

	int temp[10], size, rank, gatherbuf[10];
	char *s;
	FILE *fp;
	long sorted[1024];
	long value;
	int count=0;
	int mpi_err, tot, i=0;
	
	mpi_err = mpi_init(&argc,&argv); 

	mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &size); 

	mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
 	fp=fopen("cust.txt", "r");
 	if(NULL==fp)
 	{
 		perror("fopen");
 		return -1;
 	}

	mpi_err = MPI_Scatter(&fp, 1, MPI_INT, &tot,1,MPI_INT, 0, MPI_COMM_WORLD);
	while(!feof(fp))
	{
		fscanf(fp, "%d\n",&value);
		insert_sorted(sorted, count, value);
		++count;
	}
	for(i=0;i<count;i++)
	{
		temp[i]=sorted[i];
	}


	mpi_err = MPI_Gather(&temp,1,MPI_INT,&gatherbuf,1,MPI_INT,0,MPI_COMM_WORLD); 

	if(rank== 0) 

	{
		
  
		for(i = 0; i < count; i++)   
			printf("results from all processors = %d\n",temp[i]); 

	} 
	if(fp)
	{
		fclose(fp);
		fp=NULL;
	}

	mpi_err = MPI_Finalize();

}
