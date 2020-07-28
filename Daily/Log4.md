如何收发结构化的网络消息（不安全版）
=====
> 难点大概是类型判断（涉及到对齐等，当然次难点是类型转换
### 代码部分
**传送的结构化数据结构**
```
struct person{
	int age;
	char name[256];
};
```

**服务端发送结构化网络消息**
```
// 发送结构化的网络消息
person me = { 23,"黄杰航" };
send(_cSock, (const char*)&me, sizeof(person), 0);
```

**客户端接收结构化网络消息**
```
//6. 接收服务器信息 recv
char recvBuf[256] = {};
int nLen = recv(_sock, recvBuf, 256, 0);
if (nLen > 0)
{
	// 接收结构化的网络消息
	person* info = (person *)recvBuf;
	printf("From Server Socket message is Age:%d ,Name:%s \n", info->age,info->name);
}
```

### 小结
* 对于服务端来说，我们只是把结构化数据看成是“字节”类型进行传输
* 对于客户端来说，我们只需要将传输过来的“字节”类型进行强转即可获取结构化数据
* 无论对于客户端还是服务端来说，采用“字节”进行传输的任何一方接收结构化数据都需要进行类型的判断，否则会出现所谓的“脏消息”

