#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int child;
	mkfifo("ET2PK2", S_IRUSR | S_IWUSR);
	child = fork();
	if (child > 0)
	{
		char buf[516];
		int fd;
		fd = open("ET2PK2", O_RDONLY);
		read(fd, buf, sizeof(buf));
		printf("%s", buf);
		close(fd);
		unlink("ET2PK2");
	}

	else if (child == 0)
	{
		int fd;
		fd = open("ET2PK2", O_WRONLY);
		write(fd, "Bajzath Aron\n", 100);
	}

	return 0;
}