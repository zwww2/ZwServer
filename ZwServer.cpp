// Подключение библиотек
#include <stdio.h>
#include <WS2tcpip.h>


// Указываем библиотеку линкеру
#pragma comment(lib, "Ws2_32.lib")



// Точка входа в приложение (здесь начинается выполнение программы)
int main(void)
{

	
	// Инициализация библиотеки сокетов


	WSADATA wData;
	int result = WSAStartup(MAKEWORD(2, 2), &wData); 
	if (result == SOCKET_ERROR) return -1;

	// Инициализация сокета
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in socketInfo;
	RtlZeroMemory(&socketInfo, sizeof(socketInfo));

	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(8737);
	in_addr ip;
	result = inet_pton(AF_INET, "127.0.0.1", &ip);
	if (result == SOCKET_ERROR) return -1;
	socketInfo.sin_addr = ip;

	// бинд сокета
	result = bind(serverSocket, (const sockaddr*)&socketInfo, sizeof(socketInfo));
	if (result == SOCKET_ERROR) return -1;

	// Прослушивание сокета
	result = listen(serverSocket, SOMAXCONN);
	if (result == SOCKET_ERROR) return -1;

	// Подключение клиента
	sockaddr_in client;
	RtlZeroMemory(&client, sizeof(client));
	
	int clientSocketSize = sizeof(client);
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSocketSize);


	char buffer[4096];
	char sendbuffer[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	recv(clientSocket, buffer, 4096, 0);
	printf(buffer);
	send(clientSocket, sendbuffer, 33, 0);

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;


	
}