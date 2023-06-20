#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

void boardcast_msg(char *mess){
   int sock;                        
   struct sockaddr_in broadcastAddr; 
   char *broadcastIP;                
   unsigned short broadcastPort;     
   char *sendString;                 
   int broadcastPermission;         
   int sendStringLen;                

   broadcastIP = "10.10.1.255";  
   broadcastPort = 33333;

   sendString = mess;             /*  string to broadcast */


   if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
       fprintf(stderr, "socket error");
        exit(1);
   }


   broadcastPermission = 1;
   if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,sizeof(broadcastPermission)) < 0){
       fprintf(stderr, "setsockopt error");
       exit(1);
   }

   /* Construct local address structure */
   memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
   broadcastAddr.sin_family = AF_INET;                 
   broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
   broadcastAddr.sin_port = htons(broadcastPort);       

   sendStringLen = strlen(sendString);  

        /* Broadcast sendString in datagram to clients */
        if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) != sendStringLen){
            fprintf(stderr, "sendto error");
            exit(1);
        }

}

int main()
{
    boardcast_msg("kaka");
    return 0;
}