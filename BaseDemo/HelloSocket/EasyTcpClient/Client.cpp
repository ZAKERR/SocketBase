#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <cstdio>

#pragma comment(lib,"ws2_32.lib")
int main(int argc, char * argv)
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;

	WSAStartup(ver, &dat);
	// 1. ����һ�� socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (INVALID_SOCKET == _sock) {
		printf("Client socket create Failed!\n");
	}
	else {
		printf("Client socket create Successfully\n");
	}

	//��������Socket����������Ϣ
	sockaddr_in _sun = {};
	_sun.sin_family = AF_INET;
	_sun.sin_port = htons(330);
	_sun.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	//2. ���ӷ����� connect
	int ret = connect(_sock, (sockaddr*)&_sun,
		sizeof(_sun));
	
	if (SOCKET_ERROR == ret) {
		printf("Connect Server Socket has failed!\n");
		return 0;
	}
	else {
		printf("Connect Server Socket has success!\n");
	}
    
	while (true) {
		//3. �����û�ָ��
		char cSendMsg[256] = {};
		printf("������ָ��:");
		scanf("%s",cSendMsg);
		//4�� �����û�ָ��
		if (strcmp(cSendMsg, "exit") == 0)
		{
			break;
		}
		//5. ������Ϣ�������
		send(_sock, cSendMsg, 256, 0);

		//6. ���շ�������Ϣ recv
		char recvBuf[256] = {};
		int nLen = recv(_sock, recvBuf, 256, 0);
		if (nLen > 0)
		{
			printf("From Server Socket message is %s \n", recvBuf);
		}
		else {
			printf("Invalid Data\n", recvBuf);
		}
	}
	
	//7. �ر�socket closesocket
	closesocket(_sock);
	printf("�ͻ������˳�!");
	WSACleanup();
	getchar();
	return 0;
}