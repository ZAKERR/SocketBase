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
	//1. ����һ��socket�׽���	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	if (INVALID_SOCKET == sock) {		printf("������Socket����ʧ�ܣ�\n");	}	else {		printf("������Socket�����ɹ���\n");	}	//����Ϣ	sockaddr_in _sin = {};	_sin.sin_family = AF_INET;	_sin.sin_port = htons(4567);	_sin.sin_addr.S_un.S_addr = INADDR_ANY;	//2. �󶨽��տͻ������ӵĶ˿� bind	int ret = bind(sock, (sockaddr *)&_sin, sizeof(_sin));	if (SOCKET_ERROR == ret) {		printf("�˿ڱ�ռ��!\n");	}	//3. ��������˿� listen	ret = listen(sock, 5);	if (SOCKET_ERROR == ret) {		printf("�޷�����\n");	}	sockaddr_in clientAddr = {};	int nAddrlen = sizeof(sockaddr_in);	SOCKET _cSock = INVALID_SOCKET;	char msgBuf[256] = "Hello,My name is dajiao";	while (true) {		//4. �ȴ��ͻ���(��������� accept		_cSock = accept(sock, (sockaddr *)&clientAddr,			&nAddrlen);		if (_cSock == INVALID_SOCKET) {			printf("��Ч�ͻ�������!\n");		}				printf("�¿ͻ�������! IP = %s\n",inet_ntoa(clientAddr.sin_addr));		//5. ���Ϳͻ��˵���Ϣ send		send(_cSock, msgBuf, strlen(msgBuf) + 1,					 0);	}	//6. �ر�socket	closesocket(sock);	
	WSACleanup();
}