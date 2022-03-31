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

  ///Create UDP socket
  s=socket(AF_INET,SOCK_DGRAM,0);
  if(s==INVALID_SOCKET)
  {
    printf("Error: The socket could not be created, error code: %d\n",WSAGetLastError());
    return 1;
  }
  else
  {
    printf("UDP Socket created!\n");
  }

  ///prepare addr
  addr.sin_family=AF_INET;
  addr.sin_port=htons(1234);
  addr.sin_addr.s_addr=inet_addr("127.0.0.1");


  ///Data exchange
  while(1)
  {
    printf("Enter text: ");
    gets(buf);
    rc=sendto (s,buf,strlen(buf),0,(SOCKADDR*)&addr,sizeof(SOCKADDR_IN));
    if(rc==SOCKET_ERROR)
    {
      printf("Error: sendto, error code: %d\n",WSAGetLastError());
      return 1;
    }
    else
    {
      printf("%d Bytes sent!\n", rc);
    }

    rc=recvfrom(s,buf,256,0,(SOCKADDR*)&remoteAddr,&remoteAddrLen);
    if(rc==SOCKET_ERROR)
    {
      printf("Error: recvfrom, error code: %d\n",WSAGetLastError());
      return 1;
    }
    else
    {
      printf("%d Bytes received!\n", rc);
      buf[rc]='\0';
      printf("Received Data: %s\n",buf);
    }
  }

  return 0;
}
