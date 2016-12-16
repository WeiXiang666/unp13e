#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int			listenfd, connfd;
	struct sockaddr_in	servaddr;
	char			buff[MAXLINE];
//	time_t			ticks;
	char                    recvline[MAXLINE-1];
	int n;
	int a=0;
	int b=0;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		while(strcmp(recvline, "exit")){
			if( (n = read(connfd, recvline, MAXLINE)) >0 ){
				recvline[n] = 0;
				n = 0;
		while(*recvline>='0' && *recvline<='9' && *recvline!=' '){						a=a*10+(*recvline-'0');
					n++;
				}
				n++;
		while(*recvline>='0' && *recvline<='9' && *recvline!='\0'){
					b=b*10+(*recvline-'0');
					n++;
				}
				fputs("server recv:",stdout);
				printf("+%d,-%d,/%f,*%d\n",a+b,a-b,a/b*1.0,a*b);
				if(fputs(recvline, stdout) == EOF)
					err_sys("fputs error");
			}
			fputs("server said:", stdout);
			fgets(buff, MAXLINE-1, stdin);
			write(connfd, buff, strlen(buff));
		}
	Close(connfd);
	}
}
