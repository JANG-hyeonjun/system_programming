#include<stdio.h>

int main()
{
	double pi=0, temp=1,p=-1,num=1;

	while(num < 10000000)
	{
		p*= -1;
		pi += p * 1.0 / temp;
		if((int)num % 1000 == 0)
		printf("%f\n",pi);
		temp += 2;
		num++;
	}
}
