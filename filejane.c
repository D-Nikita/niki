#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main(int argc, char *argv[])
{
FILE *f;
int cnt=0, tid;
char sword[100], filename[10]="words.txt";

#pragma omp parallel num_threads(2) firstprivate(cnt) private(f,sword,tid) shared(filename) 
{
tid=omp_get_thread_num();
#pragma omp sections
{
#pragma omp section
{
	printf("This is thread %d in section 1\n", tid);
	f=fopen(filename, "r");
	if(f)
	{
		while(!feof(f))
		{
			fscanf(f, "%s", sword);
			if(feof(f))
				break;
			if(strcmp(sword,"JANE")==0)
			cnt=cnt+1;
			//printf("%s\n", sword);
		}
	}
	printf("The word JANE has been repeated %d times\n",cnt);
	fclose(f);
}

#pragma omp section
{
	printf("This is thread %d in section 2\n", tid);
	f=fopen(filename, "r");
	if(f)
	{
		while(!feof(f))
		{
			fscanf(f, "%s", sword);
			if(feof(f))
				break;
			if(strcmp(sword,"Elizabeth")==0)
			cnt=cnt+1;
			printf("%s\n", sword);
//cnt=cnt+1;

		}
	}
	printf("The word Elizabeth has been repeated %d times\n",cnt);
	fclose(f);
}
}
}
}
