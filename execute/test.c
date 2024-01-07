
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int hello(int a)
{
	return (a);
}

int main()
{
	int pid = fork();

	int status;
	if(pid == 0)
	{
		return (hello(123));
	}
	waitpid(pid, &status, 0);

	printf("status: %d\n", WEXITSTATUS(status));
}