#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <io.h>
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class Server
{
private:
	const char* IP;			// IP address 
	int port;				//Port for the webserver
	SOCKET sock;
	char* CHECK;			//IF UNAME&PSW INCORRECT, RETURN NULL
public:
	//Constructor but just IP and Port
	Server(const char* ip, int p);

	//Initialize the server
	int init();

	//Handle the connection to client
	void HandleConnection(SOCKET s, const char* msg, int len);
};
