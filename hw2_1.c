#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

#define childnum 2;

int main(int argc , char *argv[])
{
	int fd1,n; //file descriptor 
	char buf[10];
	int child1,child2;
	//fork two process
	//int processnum = 0;
	int status1,status2;

	fd1 = open(argv[1],O_RDONLY);
	//file reading argv[1] =>myinput.dat

	child1 = fork();
	if(child1 < 0)
		exit(1);
	if(child1 == 0)
	{
		while((n = read(fd1,&buf,10))!= 0)
		{
			printf("child1_char = %s\n",buf);
			printf("child1_pid = %d\n",getpid());
			sleep(1);
			//memset(buf,0x00,sizeof(buf));
			//prints pids,and the character
			//and then clear the buffer
		}
		close(fd1);
		exit(0);
	}
	child2 = fork();
	if(child2 < 0)
		exit(1);
	if(child2 == 0)
	{
	  while((n = read(fd1,&buf,10)) != 0)
		{
		  printf("child2_char = %s\n",buf);
		  printf("child2_pid = %d\n",getpid());	  
		  sleep(1);
		  //memset(buf,0x00,sizeof(buf));
		}
		close(fd1);
		exit(0);
	}
	//parent process
	if(child1 != 0 && child2 != 0)
	{
		while(n = read(fd1,&buf,10) != 0)
		{
			printf("parent_char = %s\n",buf);
			printf("parent_pid = %d\n",getpid());
			sleep(1);
			memset(buf,0x00,sizeof(buf));
		}
		close(fd1);
		waitpid(child1,&status1,0);
		waitpid(child2,&status2,0);

	}
	return 0;
}
