#include "Socket.h"

int main(){
  string ip = "localhost";
  string port = "9876";
  Socket *socket1 = new Socket(AF_INET,SOCK_STREAM,0);
  int optVal = 1;
  socket1->socket_set_opt(SOL_SOCKET, SO_REUSEADDR, &optVal);
  socket1->bind(ip, port);
  socket1->listen(10);

  while (true) {
    vector<Socket> lee(1);
    lee[0] = *socket1;
    int seconds = 10;
    if(Socket::select(&lee, NULL, NULL, seconds) < 1){
      //No hay coneccion
      continue;
    }else{
      //algo se recivio
      break;
    }
  }
  Socket *socket2 = socket1->accept();

  while (true) {
    vector<Socket> lee(1);
    lee[0] = *socket2;
    int seconds = 10;
    if(Socket::select(&lee, NULL, NULL, seconds) < 1){
      //No hay Input
      continue;
    }else{
      string buffer;
      socket2->socket_read(buffer, 1024);

      socket2->socket_write(buffer);
    }
  }
  socket2->socket_shutdown(2);
  socket2->close();

  socket1->socket_shutdown(2);
  socket1->close();


  return  0;
}
