#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>



int main()
{
	char buf[10];
	int fd_1[2],fd_2[2];
	int fd;
	int status1,status2;
	int n;
	int input,output;
	int idx;
	int child1,child2;

	if(pipe(fd_1) < 0)
	{
		printf("pipe_1 error\n");
		exit(1);
	}
	if(pipe(fd_2) < 0)
	{
		printf("pipe_2 error\n");
		exit(1);
	}

	pipe(fd_1);
	pipe(fd_2);

	//child_process
	if((child1 = fork())== 0)
	{
	  close(fd_1[1]);
	  close(fd_2[0]);
		
	  while((n = read(fd_1[0],buf,10)) != 0)
	  {
		for (int idx =0; idx < n; idx++)
		{
			if(buf[idx] >= 'a' && buf[idx] <= 'z'){
				buf[idx] -= 32;
			}
		}
		write(fd_2[1],buf,n);
	  }
		close(fd_1[0]);
		close(fd_2[1]);
		exit(0);
	}else{
		if((child2 = fork()) == 0)
		{
			output = creat("output.dat",0666);
			if(output < 0){
				printf("it is happen create error");
				perror("open");
			}
			close(fd_1[0]);
			close(fd_1[1]);
			close(fd_2[1]);
			// 1-write 0- read
			while((n = read(fd_2[0],buf,10))!= 0){
				write(output,buf,n);
				write(1,buf,n);
			}
			close(fd_2[0]);
			exit(0);
		}
	else{
		input  = open("myinput.dat",0);
		if(input < 0)
			printf("open error: %d\n",fd);
		
		close(fd_1[0]);	close(fd_2[0]);close(fd_2[1]);
		while((n = read(input,buf,10))!= 0){
			write(fd_1[1],buf,n);
		}
		close(fd);
		close(fd_1[1]);
		waitpid(child1,&status1,0);
		waitpid(child2,&status2,0);
	}
}
	return 0;
}




