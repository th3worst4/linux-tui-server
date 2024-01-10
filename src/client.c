#include "includes.h"

void error(const char* msg){
    perror(msg);
    exit(1);
}

void *listening(void *vargp){
    char buffer[255];
    int *sockfd = (int *)vargp;
    while(1){
	bzero(buffer, 255);
	int rec = read(*sockfd, buffer, 255); 
	if(rec < 0) error("Error on reading\n");
	if(rec == 0) continue;
	printf(buffer);
	//printmsg("test"); 
    }
}

void *writing(void *vargp){
    char buffer[255];
    int *sockfd = (int *)vargp;
    while(1){
	bzero(buffer, 255);
	fgets(buffer, 255, stdin);
	int send = write(*sockfd, buffer, strlen(buffer));
	if(send < 0) error("Error on writing\n");		
    }
}

int main(int argc, char** argv){
    pthread_t listen_id;
    pthread_t write_id;

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

    //initiate();

    pthread_create(&write_id, NULL, writing, &sockfd);
    pthread_create(&listen_id, NULL, listening, &sockfd);
    pthread_join(listen_id, NULL);
    pthread_join(write_id, NULL);

    close(sockfd);
    return 0;
}
