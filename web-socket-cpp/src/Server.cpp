#include "Server.h"


//Constructor but just IP and PORT
Server::Server(const char* ip, int p)
{
	IP = ip;
	port = p;
}

//Initialize the server
int Server::init()
{
	//init winsock
	//cout << "\nInitializing Winsock...";
	WSADATA ws;
	WORD Dllver = MAKEWORD(2, 2);
	if (WSAStartup(Dllver, &ws) != 0)
	{
		ExitProcess(EXIT_FAILURE);
	}
	//cout << "Initialized.";				//inform that the initializtion has been done

	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}
	//cout << "\nSocket created.";		//inform that the socket creation has been done

	//bind ip and port to socket
	sockaddr_in serverIP; //IP
	serverIP.sin_family = AF_INET;
	serverIP.sin_port = htons(port);
	inet_pton(AF_INET, IP, &serverIP.sin_addr);

	if (bind(sock, (sockaddr*)&serverIP, sizeof(serverIP)) == SOCKET_ERROR)
	{
		//cout << "\nBind failed.";		
		return WSAGetLastError();
	}
	//cout << "\nBind done.";				//inform that the binding has been done

	//Tell server to start listening
	int lis = listen(sock, SOMAXCONN);
	if (lis == SOCKET_ERROR)
	{
		//cout << "\nFailed to listen.\n";
		return WSAGetLastError();
	}
	//cout << "\nListening...";
	cout << "\n...Waiting for incoming connection...\n";

	char buffer[4096];
	struct sockaddr_in client;
	int sz = sizeof(struct sockaddr_in);
	SOCKET ClientSock;
	while ((ClientSock = accept(sock, (struct sockaddr*)&client, &sz)) != INVALID_SOCKET)
	{
		cout << "\nConnection accepted.";	//inform that the connection has been set

		int len = recv(ClientSock, buffer, sizeof(buffer), 0); //receive message

		CHECK = strstr(buffer, "uname=admin&psw=admin");

		if (len == SOCKET_ERROR)
		{
			//cout << "\nReceiving failed.\n";
			closesocket(ClientSock);
			return WSAGetLastError();
		}
		else
		{
			//cout << "\nMessage received \n" /*<< buffer << endl*/; //inform that the message has been received

			//Handle the connection to client
			HandleConnection(ClientSock, buffer, len);
		}
	}
	if (ClientSock == INVALID_SOCKET)
	{
		cout << "\nConnection failed.\n";
		closesocket(ClientSock);
		WSACleanup();
		return WSAGetLastError();
	}
	closesocket(sock);
	closesocket(ClientSock);
	WSACleanup();

	return 0;
}

//handle the connection to client
void Server::HandleConnection(SOCKET s, const char* msg, int len)
{
	//analyze the client's request string. EX: GET /index.html HTTP/1.1......
	istringstream iss(msg);
	vector<string> analy((istream_iterator<string>(iss)), istream_iterator<string>());

	string content = "<h1>404 Not Found</h1>";
	string htmlFile = "/index.html";
	int responseCode = 404;

	if (analy.size() >= 3 && analy[0] == "GET")
	{
		//cout << "\nMethod being used: GET";	//inform the HTTP method being used
		if (analy[1] == "/" || analy[1] == "/index.html")
		{
			htmlFile = "/index.html";
		}
		else htmlFile = "/404.html";
	}

	else if (analy.size() >= 3 && analy[0] == "POST")
	{
		//cout << "\nMethod being used: POST";	//inform the HTTP method being used
		if (CHECK == NULL) {

			htmlFile = "/404.html";
		}
		else {

			htmlFile = "/info.html";
		}
	}


	ifstream f(".\\www" + htmlFile);

	if (f.good()) //if the file is opened
	{
		string str((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
		content = str;
		responseCode = 200;
		//cout << "\nThe htmlFile has been reached";			//inform that the html file in folder "www" is available
	}
	f.close();

	//Response to the client
	ostringstream oss;
	oss << "HTTP/1.1 " << responseCode << " OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	string output = oss.str();
	int size = output.size() + 1;
	//cout << "\nLoading....";

	int sen = send(s, output.c_str(), size, 0);
	if (sen == SOCKET_ERROR)
	{
		cout << "\nSend to client failed. Error code: " << WSAGetLastError() << endl;
	}
	//cout << "\nSend to client successfully.";		//inform that the response has been sent to client	

}

