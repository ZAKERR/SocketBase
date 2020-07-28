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
	//1. ����һ��socket�׽���
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == _sock) {
		printf("Failed,������Socket����ʧ�ܣ�\n");
	}
	else {
		printf("Success!������Socket�����ɹ�...\n");
	}

	//����Ϣ
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(330);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//2. �󶨽��տͻ������ӵĶ˿� bind
	int ret = bind(_sock, (sockaddr *)&_sin, sizeof(_sin));
	if (SOCKET_ERROR == ret) {
		printf("Failed,�˿ڱ�ռ��!\n");
		return 0;
	}
	else {
		printf("Success!�˿ڰ󶨳ɹ�...\n");
	}
	//3. ��������˿� listen
	ret = listen(_sock, 5);
	if (SOCKET_ERROR == ret) {
		printf("Failed,�����˿�ʧ��\n");
		return 0;
	}
	else {
		printf("Success!�����˿ڳɹ�...\n");
	}

	sockaddr_in clientAddr = {};
	int nAddrlen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char recvBuf[256] = {};
	char sendBuf[256] = {};
	//4. �ȴ��ͻ���(��������� accept
	_cSock = accept(_sock, (sockaddr *)&clientAddr,
		&nAddrlen);

	if (_cSock == INVALID_SOCKET) {
		printf("Error,��Ч�ͻ�������!\n");
		getchar();
		return 0;
	}
	else {
		printf("Success!�ͻ������ӳɹ�...\n");
	}

	printf("�¿ͻ�������! IP = %s\n", inet_ntoa(clientAddr.sin_addr));


	while (true) {
		
		//5. ���տͻ��˵���Ϣ
		int nLen = recv(_cSock, recvBuf, 256, 0);
		if (nLen <= 0) {
			printf("�ͻ����˳���\n");
			break;
		}

		//6. �������Կͻ��˵���Ϣ
		if (strcmp(recvBuf, "GetName") == 0) {
			strcpy_s(sendBuf, "dajiao");
		}
		else if (strcmp(recvBuf, "GetAge") == 0) {
			strcpy_s(sendBuf, "18");
		}
		else if (strcmp(recvBuf, "exit") == 0) {
			printf("�ͻ������˳�");
			break;
		}
		else
		{
			strcpy_s(sendBuf, "???");
		}

		//8. ���Ϳͻ��˵���Ϣ send
		send(_cSock, sendBuf, strlen(sendBuf) + 1,
			0);
	}
	//6. �ر�socket
	closesocket(_sock);
	WSACleanup();
	getchar();
}