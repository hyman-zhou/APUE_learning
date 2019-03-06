#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "timeout\n"

int main()
{
	char buf[10];
	int fd, n, i;
	fd = open("/dev/tty",O_RDONLY|O_NONBLOCK);
	if(fd<0) {
	  perror("open /dev/tty");
	  exit(1);
	}
	for (i=0; i<5; i++) {
	   n = read(fd, buf, sizeof(buf));
	     if (n >=0) 
		break;
	     if (errno != EAGAIN) {//当设置了非阻塞式 O_NONBLOCK后读取却没有数据时 errno会被设置为EAGAIN
		   perror("read /dev/tty");
		   exit(1);
		}
	     sleep(1);
	     write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TIMEOUT));	
	}
	if(i==5)
	   write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
	else
	  write(STDOUT_FILENO, buf, n);
	close(fd);
	return 0;
}
