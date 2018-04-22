#include <string.h>                                                                   
#include <netinet/in.h>                                                               
#include <sys/socket.h>                                                               
#include <arpa/inet.h>                                                                
// #include <iostream>                                                                   
#include <stdio.h>                                                                    
#include <errno.h> 
// #include <unistd.h>
// #include <stdlib.h>                                                                
#include <unistd.h>                                                   
// using namespace std;                                                               
                                                                                   
#define MAXLINE     4096    /* max text line length */                             
int main(int argc, char ** argv)                                                   
{                                                                                  
    int sockfd, n;                                                                 
    char recvline[MAXLINE+1];                                                      
    struct sockaddr_in serveraddr;                                                 
    if(argc != 2)                                                                  
    {                                                                              
        // cout << "para error " << endl;    
        printf("para error ;%d \n",argc);                                            
        return 0;                                                                  
    }                                                                              
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0))<0)                                 
    {                                                                              
        // cout << "socket error" << endl;      
        printf("socket error \n");                                         
        return 0;                                                                  
    }                                                                              
    memset(&serveraddr,0, sizeof(serveraddr));                                     
    serveraddr.sin_family = AF_INET;                                               
    serveraddr.sin_port = htons(10000);                                            
    if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr)<=0)                       
    {                                                                              
        // cout << "inet_pton error for " << argv[1] << endl;   
          printf("inet_pton error for  %s \n",argv[1] );                        
        return 0;                                                                  
    }                                                                              
    int tmp = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));  
    if(tmp <0)                                                                                                                                                                                              
    {                                                                                 
        // cout << "connect error" << tmp << endl;    
        printf("connect error  %d \n",tmp);      
        printf("error info   %d \n",errno);                                         
        // cout << "error info " << errno << endl;                                       
        return 0;                                                                     
    }   
    while((n=read(sockfd, recvline, MAXLINE)) > 0)                                 
    {                                                                              
        recvline[n] = 0;                                                           
        if(fputs(recvline, stdout) == EOF)                                         
        {                                                                          
            // cout << "fputs error" << endl;    
            printf("fputs error \n");                                             
        }                                                                          
    }                                                                              
    close(sockfd);                                                                 
    if(n<0)                                                                        
    {                                                                              
        // cout << "read error" << endl;     
        printf("read error \n");        
                                                
    }                                                                              
    return 1;                                                                      
}   