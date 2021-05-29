#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

#define MAX 1024
#define PORT 30000
#define BACKLOG 5

int main(int argc,int argv[])
{
  int sd,nsd,pid,bytes,cliaddrsize;
  struct sockaddr_in cliaddr, servaddr;
  socklen_t len;
  int n;
  char data[MAX];

  printf("create socket..");
  if((sd = socket(PF_INET,SOCK_DGRAM,0)) < 0){
	fprintf(stderr,"can't open socket\n");
	exit(1);
  }

  printf("done\n");

  bzero((char*) &servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);

  printf("bind socket...");
  if(bind(sd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0){
	fprintf(stderr,"can't bind to socket\n");
	exit(1);
  }
  printf("done\n");
  while(1){
	memset(data,0,sizeof(char)* MAX);
	len = sizeof(cliaddr);
	printf("wait for client data\n");
	bytes = recvfrom(sd,data,MAX,0,(struct sockaddr *)&cliaddr,&cliaddrsize);

	printf("receive data from client..%s",data);
	printf("send back data to client..%s",data);
	
	if((n = sendto(sd,data,bytes,0,(struct sockaddr *)&cliaddr,cliaddrsize)) != bytes)
	{
		fprintf(stderr,"can't bind to socket\n");
		exit(1);
	}
	printf("done\n");
  }
}

