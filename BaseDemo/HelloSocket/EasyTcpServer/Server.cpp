#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <Windows.h>
#include <WinSock2.h>
#include <cstdio>
//#pragma comment(lib,"ws2_32.lib")

int main(int argc, char *argv[]) {
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//1. 创建一个socket套接字	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	if (INVALID_SOCKET == sock) {		printf("服务器Socket建立失败！\n");	}	else {		printf("服务器Socket建立成功！\n");	}	//绑定信息	sockaddr_in _sin = {};	_sin.sin_family = AF_INET;	_sin.sin_port = htons(4567);	_sin.sin_addr.S_un.S_addr = INADDR_ANY;	//2. 绑定接收客户端连接的端口 bind	int ret = bind(sock, (sockaddr *)&_sin, sizeof(_sin));	if (SOCKET_ERROR == ret) {		printf("端口被占用!\n");	}	//3. 监听网络端口 listen	ret = listen(sock, 5);	if (SOCKET_ERROR == ret) {		printf("无法监听\n");	}	sockaddr_in clientAddr = {};	int nAddrlen = sizeof(sockaddr_in);	SOCKET _cSock = INVALID_SOCKET;	char msgBuf[256] = "Hello,My name is dajiao";	while (true) {		//4. 等待客户端(多个）连接 accept		_cSock = accept(sock, (sockaddr *)&clientAddr,			&nAddrlen);		if (_cSock == INVALID_SOCKET) {			printf("无效客户端连接!\n");		}				printf("新客户端连接! IP = %s\n",inet_ntoa(clientAddr.sin_addr));		//5. 发送客户端的消息 send		send(_cSock, msgBuf, strlen(msgBuf) + 1,					 0);	}	//6. 关闭socket	closesocket(sock);	
	WSACleanup();
}