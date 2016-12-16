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
	int flag;
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
				flag=0;
				n = 0;
		while(recvline[n]>='0' && recvline[n]<='9' && recvline[n]!=' '){					a=a*10+(recvline[n]-'0');
					n++;
				}
				n++;
		while(recvline[n]>='0' && recvline[n]<='9' && recvline[n]!=EOF){
					b=b*10+(recvline[n]-'0');
					flag=1;
					n++;
				}
				fputs("server recv:",stdout);
				if(flag==1){
					if(b==0)
					{
						printf("erro b can not be zero\n");
					}
					else
						printf("a+b= %d,a-b=%d,a/b=%f,a*b=%d\n",a+b,a-b,a*1.0/b,a*b);
				}
			//	fputs("server recv:",stdout);
				if(flag==0 && fputs(recvline, stdout) == EOF)
					err_sys("fputs error");
			}
			fputs("server said:", stdout);
			fgets(buff, MAXLINE-1, stdin);
			write(connfd, buff, strlen(buff));
		}
	Close(connfd);
	}
}
