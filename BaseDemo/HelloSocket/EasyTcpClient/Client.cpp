#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <cstdio>

#pragma comment(lib,"ws2_32.lib")
int main(int argc, char * argv)
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	WSAStartup(ver, &dat);
	// 1. 建立一个 socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (SOCKET_ERROR == _sock) {
		printf("Client socket create Failed!\n");
	}
	else {
		printf("Client socket create Successfully\n");
	}

	//创建连接Socket服务器的信息
	sockaddr_in _sun = {};
	_sun.sin_family = AF_INET;
	_sun.sin_port = htons(4567);
	_sun.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//2. 连接服务器 connect
	int ret = connect(_sock, (sockaddr*)&_sun,
		sizeof(_sun));

	if (INVALID_SOCKET == ret) {
		printf("Connet Server Socket has failed!\n");
	}
	else {
		printf("Connet Server Socket has success!\n");
	}

	//3. 接收服务器信息 recv
	char recvBuf[256] = {};
	int nLen = recv(_sock, recvBuf, 256, 0);
	if (nLen > 0)
	{
		printf("From Server Socket message is %s \n", recvBuf);
	}
	else {
		printf("Invalid Data\n", recvBuf);
	}
	//4. 关闭socket closesocket
	closesocket(_sock);
	WSACleanup();
	getchar();
	return 0;
}