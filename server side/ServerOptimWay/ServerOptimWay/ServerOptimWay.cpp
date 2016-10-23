// ServerOptimWay.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>

#define _WIN32_WINNT 0x501

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Servlet.h"

#pragma comment(lib, "Ws2_32.lib")
using std::cerr;




int main()
{
	//loading library for working with http connection
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (result != 0) {
		cerr << "Load Ws2_32.lib is failed" << result << std::endl;
		return result;
	}

	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	result = getaddrinfo("127.0.0.1", "8080", &hints, &addr);

	if (result != 0) {
		cerr << "Lock address 127.0.0.1:8080 is failed" << result << std::endl;
		WSACleanup();
		return result;
	}
	

	int listen_socket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);

	if (listen_socket == INVALID_SOCKET) {

		cerr << "Error soket " << WSAGetLastError() << std::endl;
		freeaddrinfo(addr);
		WSACleanup();
		return 1;
	}


	bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen);

	if (result == SOCKET_ERROR) {
		cerr << "bind failed with error: " << WSAGetLastError() << "\n";
		freeaddrinfo(addr);
		closesocket(listen_socket);
		WSACleanup();
		return 1;
	}

	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		cerr << "listen failed with error: " << WSAGetLastError() << "\n";
		closesocket(listen_socket);
		WSACleanup();
		return 1;
	}

	
	char buf[max_client_buffer_size];
	ThreadPool* pool = new ThreadPool(10);

	while (1) {

		int client_socket = accept(listen_socket, NULL, NULL);
		
		if (client_socket == INVALID_SOCKET) {
			cerr << "accept failed: " << WSAGetLastError() << "\n";
			closesocket(listen_socket);
			WSACleanup();
			return 1;
		}
		result = recv(client_socket, buf, max_client_buffer_size, 0);	

		if (result == SOCKET_ERROR) {
			// ошибка получения данных
			cerr << "recv failed: " << result << "\n";
			closesocket(client_socket);
		}
		else if (result == 0) {
			// соединение закрыто клиентом
			cerr << "connection closed...\n";
		}
		else if (result > 0) {
			pool->startThreds(buf, client_socket);
		}
	}

    return 0;
}

