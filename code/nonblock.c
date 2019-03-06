#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"

int main()
{
	char buf[10];
	int fd, n;
	fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
	if(fd<0) {
	  perror("open /dev/tty");
	  exit(1);
	}

	tryagain:
	   n = read(fd, buf, sizeof(buf));
	     if (n < 0) {
		if (errno == EAGAIN) {//当设置了非阻塞式 O_NONBLOCK后读取却没有数据时 errno会被设置为EAGAIN
		   sleep(5);
		   write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
		   goto tryagain;
		}

		perror("read /dev/tty");
		exit(1);
	}

	write(STDOUT_FILENO, buf, n);
	close(fd);
	return 0;
}
