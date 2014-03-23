#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int fd1[2],fd2[2],fd3[2];
	pid_t pid0,pid1,pid2,pid3;
	int i = 0,n = 0;
	char byte = '0';
	FILE* file;
//	printf("1.Main:%d\n",getpid());
	if ((pid0 = fork()) < 0)
	{
		printf("Process Create Error!\n");
		return 0;
	}
//	printf("pid0:%d\n",pid0);
	if (pid0 == 0)
	{//Multiplexing Process
		printf("Hello There. I'm going create 3 processes\n");
		printf("f:%d m:%d pid:%d\n",getppid(),getpid(),pid0);
		if (pipe(fd1) < 0)
		{
			printf("Pipe Error!\n");
		}
		if (pipe(fd2) < 0)
		{
			printf("Pipe Error!\n");
		}
		if (pipe(fd3) < 0)
		{
			printf("Pipe Error!\n");
		}
		//Create 3 pipes for commnication
		if ((pid1 = fork()) < 0)
		{
			printf("Process Create Error!\n");
			return 0;
		}
		else if (pid1 > 0)
		{
			printf("First created!\n");//main moltiplexing process
		}
		else
		{//station 1
			printf("Station 1:%d\n",getpid());
			file = fopen("./aa","r");
			close(fd1[0]);
			for (i = 0; i < 810; i++)
			{
				fread(&byte,sizeof(char),1,file);
				write(fd1[1],&byte,1);
			}
			wait(100);
			fclose(file);
			return 0;	
		}
		if ((pid2 = fork()) < 0)
		{
			printf("Process Create Error!\n");
			return 0;
		}
		else if (pid2 > 0)
		{
			printf("Second created!\n");//main moltiplexing process
		}
		else 
		{//station 2
			printf("Station 2:%d\n",getpid());
			file = fopen("./bb","r");
			close(fd2[0]);
			for (i = 0; i < 810; i++)
			{
				fread(&byte,sizeof(char),1,file);
				write(fd2[1],&byte,1);
			}		
			wait(100);	
			fclose(file);
			return 0;	
		}	
		if ((pid3 = fork()) < 0)
		{
			printf("Process Create Error!\n");
			return 0;
		}
		else if (pid3 > 0)
		{
			printf("Third created!\n");//main moltiplexing process
		}	
		else
		{//station 3
			printf("Station 3:%d\n",getpid());
			file = fopen("./cc","r");
			close(fd3[0]);
			for (i = 0; i < 810; i++)
			{
				fread(&byte,sizeof(char),1,file);
				write(fd3[1],&byte,1);
			}	
			wait(100);	
			fclose(file);
			return 0;	
		}
		close(fd1[1]);
		close(fd2[1]);
		close(fd3[1]);
		for (i = 0; i < 810; i++)
		{
		//	printf("\t%d",i);
			wait(3);
			n = read(fd1[0], &byte, 1);
			printf("%c",byte);
			n = read(fd2[0], &byte, 1);
			printf("%c",byte);
			n = read(fd3[0], &byte, 1);
			printf("%c",byte);
			if ((i+1) % 3 == 0)
			{
				n = ((i+1)/3)%90;
				n = (n==0?90:n);
				printf("\tColumn %d\n",n);
			}
			if ((i+1) % 270 == 0)
				printf("it's the end of a frame\n");
		}
	}
	else
	{
		printf("Main:%d\n",getpid());
		wait(1000);
	}	
	return 0;
}

