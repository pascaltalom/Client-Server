#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

//Prototypen
int startWinsock(void)
{
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2,0),&wsa);
}

int main()
{
  long rc;
  SOCKET s;
  char buf[256];
  char buf2[300];
  SOCKADDR_IN addr;
  SOCKADDR_IN remoteAddr;
  int remoteAddrLen=sizeof(SOCKADDR_IN);

  rc=startWinsock();
  if(rc!=0)
  {
    printf("Error: startWinsock, error code: %d\n",rc);
    return 1;
  }
  else
  {
    printf("Winsock started!\n");
  }

  ///UDP Create socket
  s=socket(AF_INET,SOCK_DGRAM,0);
  if(s==INVALID_SOCKET)
  {
    printf("Error: The socket could not be created, error code: %d\n",WSAGetLastError());
    return 1;
  }
  else
  {
    printf("UDP Socket Created!\n");
  }

  addr.sin_family=AF_INET;
  addr.sin_port=htons(1234);
  addr.sin_addr.s_addr=ADDR_ANY;

  rc=bind(s,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
  if(rc==SOCKET_ERROR)
  {
    printf("Error: bind, error code: %d\n",WSAGetLastError());
    return 1;
  }
  else
  {
    printf("Socket bound on port 1234\n");
  }

  while(1)
  {
    rc=recvfrom(s,buf,256,0,(SOCKADDR*)&remoteAddr,&remoteAddrLen);
    if(rc==SOCKET_ERROR)
    {
      printf("Error: recvfrom, error code: %d\n",WSAGetLastError());
      return 1;
    }
    else
    {
      printf("%d Bytes Received!\n", rc);
      buf[rc]='\0';
    }
    printf("Received data: %s\n",buf);

    //Answer
    sprintf(buf2,"You too %s",buf);
    rc=sendto(s,buf2,strlen(buf2),0,(SOCKADDR*)&remoteAddr,remoteAddrLen);
    if(rc==SOCKET_ERROR)
    {
      printf("Error: Sendto, error code: %d\n",WSAGetLastError());
      return 1;
    }
    else
    {
      printf("%d Bytes sent!\n", rc);
    }
  }
  return 0;
}


