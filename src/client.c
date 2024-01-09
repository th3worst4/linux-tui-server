#include "includes.h"
#define CLIENT

void error(const char* msg){
    perror(msg);
    exit(1);
}

int main(int argc, char** argv){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if(argc < 3){
	fprintf(stderr, "Wrong usage!\nUse: %s <HOSTNAME> <PORT>\nIf using same computer as server and client, use 127.0.0.1 as HOSTNAME\n", *argv);
	exit(1);
    }

    portno = atoi(*(argv+2));
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) error("Error opening the socket\n");

    server = gethostbyname(*(argv+1));
    if(server == NULL) fprintf(stderr, "Error, no such host\n");
    
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char*) &serv_addr.sin_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("Conection failed\n");

    while(1){
	bzero(buffer, 255);
	fgets(buffer, 255, stdin);
	n = write(sockfd, buffer, strlen(buffer));
	if(n < 0) error("Error on writing\n");
	
	bzero(buffer, 255);
	n = read(sockfd, buffer, 255);
	if(n < 0) error("Error on reading\n");
	printf("Server: %s", buffer);
	
	int i = strcmp("Bye", buffer);
	if(!i) break;
    }

    close(sockfd);
    return 0;
}
