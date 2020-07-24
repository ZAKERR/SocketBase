EasyTcpServer
====
以此例子介绍一个发送消息给客户端的TcpServer
----
### 步骤
1. 创建一个socket套接字
2. 绑定接收客户端连接的端口 bind
3. 监听网络端口 listen
4. 等待客户端连接 accept
/*5. 接收到客户端的消息 */
5. 发送客户端的消息 send
6. 关闭socket


### 示例代码
```
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
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == sock) {
		printf("服务器Socket建立失败！\n");
	}
	else {
		printf("服务器Socket建立成功！\n");
	}

	//绑定信息
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;

	//2. 绑定接收客户端连接的端口 bind
	int ret = bind(sock, (sockaddr *)&_sin, sizeof(_sin));
	if (SOCKET_ERROR == ret) {
		printf("端口被占用!\n");
	}
	//3. 监听网络端口 listen
	ret = listen(sock, 5);
	if (SOCKET_ERROR == ret) {
		printf("无法监听\n");
	}

	sockaddr_in clientAddr = {};
	int nAddrlen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char msgBuf[256] = "Hello,My name is dajiao";
	while (true) {
		//4. 等待客户端(多个）连接 accept
		_cSock = accept(sock, (sockaddr *)&clientAddr,
			&nAddrlen);

		if (_cSock == INVALID_SOCKET) {
			printf("无效客户端连接!\n");
		}
		
		printf("新客户端连接! IP = %s\n",inet_ntoa(clientAddr.sin_addr));
		//5. 发送客户端的消息 send
		send(_cSock, msgBuf, strlen(msgBuf) + 1,
					 0);
	}
	//6. 关闭socket
	closesocket(sock);
	
	WSACleanup();
}
```

部分疑惑介绍
----
1. socket编程为什么需要htons(), ntohl(), ntohs()，htons() <BR>
**头文件**<BR>
<winsock2.h>

**概述**<BR>
在C/C++写网络程序的时候，往往会遇到字节的网络顺序和主机顺序的问题。这是就可能用到htons(), ntohl(), ntohs()，htons()这4个函数。

**原因**<BR>
计算机数据表示存在两种字节顺序：
* NBO （Network Byte Order）按从高到低的顺序存储，在网络上使用统一的网络字节顺序
* HBO （HBO，Host Byte Order） 不同的机器HBO不相同，与CPU设计有关


大小尾顺序介绍
----
int a = 0x403214;
int b = htonl(a);
&a的值为：0x0012ff44
其中0x0012ff44、0x0012ff45、0x0012ff46、0x0012ff47这四个单元的值依次为：14、32、40、00，即0x403214这个数的高位部分存放在高位地址中，低位部分存放在低位地址中，即小（低）尾（低）顺序

&b的值为：0x0012ff40
其中0x0012ff40、0x0012ff41、0x0012ff42、0x0012ff43这四个单元的值依次为：00、40、32、14，即把原数0x403214的高位部分存放在低位地址中，低位部分存放在高位地址中。即大（高）尾（低）顺序


2. inet_ntoa() 在vs 2017无法调用<BR>
**头文件**<BR>
<Winsock2.h> <BR>
**概述**<BR>
inet_ntoa()是编程语言，功能是将网络地址转换成“.”点隔的字符串格式。

**解决方案**<BR>
增加宏（设置->预处理) `_WINSOCK_DEPRECATED_NO_WARNINGS`


EasyTcpClient
====
以此例子介绍一个接收服务端的TcpClient
----
### 步骤
1. 建立一个 socket
2. 连接服务器 connect
3. 接收服务器信息 recv
4. 关闭socket closesocket


### 示例代码
```
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
```

