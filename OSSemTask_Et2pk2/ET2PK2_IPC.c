#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	int pipefd[2];	
     	int pipefd2[2];	
     	pid_t cpid;	
	int tmp,tmp1,tmp2,tmp3;

    	if (pipe(pipefd) == -1)	
	{
		perror("pipe");
	   	exit(-1);
     	}
    	if (pipe(pipefd2) == -1) 
	{
		perror("pipe");
		exit(-1);
     	}

     cpid = fork();
     if (cpid == -1)
	{
		perror("fork");
	   	exit(-1);
     	}

     	if (cpid == 0)
	{   
	close(pipefd[1]);    /* a gyerek csak olvasni fog az elso csovon */
	close(pipefd2[0]); 	/* a gyerek csak irni fog a masodik csovon */

	read(pipefd[0], &tmp, sizeof(tmp));
	printf("gyerek altal kiolvasott: %d\n",tmp);
	close(pipefd[0]);	/* olvasas vegetert, becsukom */

	tmp3=getpid();
	write(pipefd2[1], &tmp3, sizeof(tmp3));
	close(pipefd2[1]); 	/* iras vegetert, becsukom */ 

	exit(0);
     } else
	{	
  	close(pipefd[0]);    /* a szulo csak irni fog az elso csovon*/
	close(pipefd2[1]);	/* a szulo csak olvasni fog a masodik csovon*/

	tmp1=getppid();
	write(pipefd[1], &tmp1, sizeof(tmp1));	
	close(pipefd[1]);   	/*iras vegetert, becsukom*/ 

	read(pipefd2[0], &tmp2, sizeof(tmp2));
	printf("szulo altal kiolvasott: %d",tmp2);
	close(pipefd2[0]); /*olvasas vegetert, becsukom*/

	   wait(NULL);   /* varakozas a gyerek processzre*/
	   exit(0);
     }
}