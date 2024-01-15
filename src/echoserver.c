#include "includes.h"

void error(const char* msg){
    perror(msg);
    exit(1);
}

void echoing(int sockfd){
    char buffer[255];
    while(1){
	bzero(buffer, 255);
	int rec = read(sockfd, buffer, 255); 
	if(rec < 0) error("Error on reading\n");
	if(rec == 0) continue;
	int send = write(sockfd, buffer, strlen(buffer));
    }
}

int main(int argc, char** argv){ 
    if(argc < 2){
	fprintf(stderr, "Wrong usage!\nUse: %s <PORT>\n", *argv);
	exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
	error("Error opening Socket.");	
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(*(argv+1));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	error("Binding failed");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
 
    printf("Waiting for connections.\n");
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); 

    if(newsockfd < 0) error("Error on Accept");
    printf("Someone connected.\n");
    
    echoing(newsockfd);
    
    close(newsockfd);
    close(sockfd);

    return 0;
}
