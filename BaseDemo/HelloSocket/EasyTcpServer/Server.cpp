#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Windows.h>
#include <WinSock2.h>
#include <cstdio>
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]) {
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//1. 创建一个socket套接字
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == _sock) {
		printf("服务器Socket建立失败！\n");
	}
	else {
		printf("服务器Socket建立成功！\n");
	}

	//绑定信息
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(330);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//2. 绑定接收客户端连接的端口 bind
	int ret = bind(_sock, (sockaddr *)&_sin, sizeof(_sin));
	if (SOCKET_ERROR == ret) {
		printf("端口被占用!\n");
		return 0;
	}
	//3. 监听网络端口 listen
	ret = listen(_sock, 5);
	if (SOCKET_ERROR == ret) {
		printf("无法监听\n");
		return 0;
	}

	sockaddr_in clientAddr = {};
	int nAddrlen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char recvBuf[256] = {};
	char sendBuf[256] = {};


	while (true) {
		//4. 等待客户端(多个）连接 accept
		_cSock = accept(_sock, (sockaddr *)&clientAddr,
			&nAddrlen);

		if (_cSock == INVALID_SOCKET) {
			printf("Error,无效客户端连接!\n");
			return 0;
		}

		printf("新客户端连接! IP = %s\n", inet_ntoa(clientAddr.sin_addr));

		//5. 接收客户端的消息
		int nLen = recv(_cSock, recvBuf, 256, 0);
		if (nLen <= 0) {
			printf("客户端退出！\n");
		}

		//6. 处理来自客户端的消息
		if (strcmp(recvBuf, "GetName") == 0) {
			strcpy_s(sendBuf, "dajiao");
		}
		else if (strcmp(recvBuf, "GetAge") == 0) {
			strcpy_s(sendBuf, "18");
		}
		else if (strcmp(recvBuf, "exit") == 0) {
			printf("客户端已退出");
			break;
		}
		else
		{
			strcpy_s(sendBuf, "???");
		}

		//8. 发送客户端的消息 send
		send(_cSock, sendBuf, strlen(sendBuf) + 1,
			0);
	}
	//6. 关闭socket
	closesocket(_sock);
	WSACleanup();
	getchar();
}