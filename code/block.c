#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buf[1024];
	int len;
		
	len = read(STDIN_FILENO,buf,sizeof(buf));
	if (len < 0){
	    perror("read STDIN_FILENO");
	    exit(1);
	}
	write(STDOUT_FILENO,buf,len);
	return 0;
}
