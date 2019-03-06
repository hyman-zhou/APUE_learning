#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

int main()
{
	char buf[10];
	int n;
	int flags;

	flags = fcntl(STDIN_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	if(fcntl(STDIN_FILENO, F_SETFL, flags) ==-1) {
		perror("fcntl");
		exit(1);
	}	
	tryagain:
	   n = read(STDIN_FILENO, buf, sizeof(buf));
	     if (n < 0) {
		if (errno == EAGAIN) {//当设置了非阻塞式 O_NONBLOCK后读取却没有数据时 errno会被设置为EAGAIN
		   sleep(1);
		   write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
		   goto tryagain;
		}

		perror("read stdin");
		exit(1);
	}

	write(STDOUT_FILENO, buf, n);
	return 0;
}
