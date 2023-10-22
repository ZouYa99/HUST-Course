#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<thread>
#include "sessionClient.h"
using namespace std;
string fileposition;
#pragma comment(lib,"ws2_32.lib")
void sessionToClient(SOCKET sessionSocket);
int main() {
	WSAData wsaData;
	int nRc = WSAStartup(0x0202, &wsaData);
	if (nRc) {
		cout << "startup winsock error" << endl;
		return 0;
	}
	int addrLen;
	int nSocketError;
	//create socket
	SOCKET srvSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (srvSocket == INVALID_SOCKET)
		cout << "create socket error" << endl;
	//set port and ip
	sockaddr_in addr;
	int port;
	char ip[20];
	char content[20];
	cout << "input ip" << endl;
	cin >> ip;
	cout << "input port" << endl;
	cin >> port;
	cout << "input content" << endl;
	cin >> content;
	fileposition = content;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip);
	//binding
	int rtn = bind(srvSocket, (LPSOCKADDR)&addr, sizeof(addr));
	if (rtn == SOCKET_ERROR) {
		nSocketError = WSAGetLastError();
		cout << "bind error = " << nSocketError;
		return 0;
	}
	//listen
	rtn = listen(srvSocket, 5);
	if (rtn == SOCKET_ERROR) {
		nSocketError = WSAGetLastError();
		cout << "listen error code = " << nSocketError;
		return 0;
	}
	while (true) {
		int length = sizeof(sockaddr);
		sockaddr_in clientaddr;
		SOCKET sessionSocket = accept(srvSocket, (sockaddr *)&clientaddr, &length);
		if (sessionSocket == INVALID_SOCKET) {
			nSocketError = WSAGetLastError();
			cout << "Accept session error = " << nSocketError;
			return 0;
		}
		string str(content);
		thread sessionThread(sessionToClient,sessionSocket);
		std::cout << "request IP:" << (int)clientaddr.sin_addr.S_un.S_un_b.s_b1 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b2 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b3 << "." << (int)clientaddr.sin_addr.S_un.S_un_b.s_b4<<endl;
		std::cout << "request Port:" << clientaddr.sin_port << endl;
		sessionThread.detach();
	}
	return 0;

}