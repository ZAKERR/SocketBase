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
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	if (INVALID_SOCKET == sock) {		printf("������Socket����ʧ�ܣ�\n");	}	else {		printf("������Socket�����ɹ���\n");	}	sockaddr_in _sin = {};	_sin.sin_family = AF_INET;	_sin.sin_port = htons(4567);	_sin.sin_addr.S_un.S_addr = INADDR_ANY;	int ret = bind(sock, (sockaddr *)&_sin, sizeof(_sin));	if (SOCKET_ERROR == ret) {		printf("�˿ڱ�ռ��!\n");	}	ret = listen(sock, 5);	if (SOCKET_ERROR == ret) {		printf("�޷�����\n");	}	sockaddr_in clientAddr = {};	int nAddrlen = sizeof(sockaddr_in);	SOCKET _cSock = INVALID_SOCKET;	char msgBuf[256] = "Hello,My name is dajiao";	while (true) {		_cSock = accept(sock, (sockaddr *)&clientAddr,			&nAddrlen);		if (_cSock == INVALID_SOCKET) {			printf("��Ч�ͻ�������!\n");		}		printf("�¿ͻ�������! IP = %s\n",inet_ntoa(clientAddr.sin_addr));		send(_cSock, msgBuf, strlen(msgBuf) + 1,					 0);	}	closesocket(sock);	
	WSACleanup();
}