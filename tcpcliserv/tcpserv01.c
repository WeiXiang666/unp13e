#include	"unp.h"

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	int n;
	char buf[MAXLINE];
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
		//	str_echo(connfd);	/* process the request */
			while((n=read(connfd,buf,MAXLINE))>0)
			{
				fprintf(stdout,"%s",buf);
				Writen(connfd,buf,n);
				bzero(buf,sizeof(buf));
			}
		    if(n<0)
				err_sys("read error");
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
