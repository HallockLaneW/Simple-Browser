#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>

int main(int argc, char *argv[]){


	struct sockaddr_in serv_addr;
	struct hostent *server;
	int sockfd, n; 
    struct sockaddr_in servaddr; 
	char buffer[256];
	
//check that correct number of arguments are input
if(argc!=4){
	
printf("Incorrect number of arguments\n");return 0;

}

int portnum = argv[3];


bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    

char *my_string;

//Compose string for HTTP request
asprintf(&my_string, "GET %s HTTP/1.1\r\nHost:%s\r\n\r\n",argv[2],argv[1]);


struct hostent *he;
struct in_addr **addr_list;

//gethostbyname check
if((he = gethostbyname(argv[1]))==NULL){
	printf("could not gethostbyname");
	exit(0);
}



 bzero((char *)&serv_addr, sizeof(serv_addr));
 
    int data_port = atoi(argv[3]);
	
    serv_addr.sin_port = htons(data_port);

	
	
    
	//fix to memory issue by using memcpy
	//link (1)
	memcpy(&serv_addr.sin_addr, he->h_addr,he->h_length);
	
    serv_addr.sin_family = AF_INET;
	
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	
	
	//sockfd seems to stall code
	 if(sockfd<1){
		 printf("No socket created\n");
		 exit(0);
	 }
	 
	 
	 
	 //Establish TCP connection
	 if(connect(sockfd, (struct sockaddr_in *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\n Error : Connect Failed \n"); 
        exit(0); 
    } 
	
	//send http request
	//send help (2)
	send(sockfd,my_string,strlen(my_string),0);
	
	//read the page and print it out
	while(read(sockfd,buffer,255)>0){
	printf("%s\n",buffer);
	bzero(buffer, 256);
	}
	

return 0;

}

/*
Links for annotations, all stack overflow answers
1) https://stackoverflow.com/questions/2652634/c-socket-programming-connect-hangs
2)https://stackoverflow.com/questions/30470505/http-request-using-sockets-in-c

*/