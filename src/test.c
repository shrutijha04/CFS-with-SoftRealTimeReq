/* Name: Shruti Jha
   Roll_Number: 2019274 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <time.h>
#include <omp.h>

void func()
{	
	
	long sum;
	for(long i=0;i<5000000000;i++)
	{
		sum++;	
	}
}

int main()
{
	int pid;
	int soft_requirement;

	double start_time;
	double time;
	int i;

	printf("Time taken without soft realtime guarantees:\n");
	
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			start_time = omp_get_wtime();
			func();
			time = omp_get_wtime() - start_time;
			printf("Processes %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}

	printf("Time taken with non-0 soft realtime guarantees:\n");
	
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			pid=getpid();
			soft_requirement=40;
			long ret = syscall(440, pid, soft_requirement);
			
			if(ret!=0)
			{
				printf("System call rt_nice did not execute as expected.\n");
				printf("Error No.: %d\n", errno);
				perror("Error ");
			}			

			start_time = omp_get_wtime();
			func();
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}

	printf("Time taken with 0 soft realtime guarantees:\n");
	
	for(i = 0; i < 4; i++)
	{
		if(fork() == 0)
		{
			pid=getpid();
			soft_requirement=0;
			long ret = syscall(440, pid, soft_requirement);
			
			if(ret!=0)
			{
				printf("System call rt_nice did not execute as expected.\n");
				printf("Error No.: %d\n", errno);
				perror("Error ");
				exit(0);
			}			

			start_time = omp_get_wtime();
			func();
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f sec\n", i + 1, time);
			exit(0);
		}
	}
	while(i > 0)
	{
		wait(NULL);
		i--;
	}

	printf("Cases to show errors handled in rt_nice syscall:\n");
	
	for(i = 0; i < 3; i++)
	{
		if(fork() == 0)
		{
			switch(i)
			{
				case 0:		soft_requirement = 10;
						pid=5000;
						break;
				case 1:		soft_requirement = 10;
						pid=-1;
						break;
				case 2:		soft_requirement = -10;
						pid=getpid();
						break;
				
			}
			
			printf("Case %d: PID %d Soft_Rq %d \n", i + 1, pid,soft_requirement);
			long ret = syscall(440, pid, soft_requirement);
			
			if(ret!=0)
			{
				printf("System call rt_nice did not execute as expected.\n");
				printf("Error No.: %d\n", errno);
				perror("Error ");
				exit(0);
			}
			else
			{
				printf("System call rt_nice executed successfully.\n");
			}			

			start_time = omp_get_wtime();
			func();
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f sec\n", i + 1, time);
			exit(0);
		}
		wait(NULL);

	}
	
	return 0;
	
	
}



