#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
	int child;
	int pipefd[2];
	if (pipe(pipefd))
	{
		perror("pipe");
		return 1;
	}

	child = fork();
	if (child > 0)
	{
		char buf[516];
		close(pipefd[1]);
		read(pipefd[0], buf, sizeof(buf));
		printf("%s", buf);
		close(pipefd[0]);
	}

	else if(child == 0)
	{
		close(pipefd[0]);
		write(pipefd[1], "ET2PK2\n", 12);
		close(pipefd[1]);
	}

	return 0;
}