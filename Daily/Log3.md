😠😠😠😠

记录一下VALID_SOCKET和SOCKET_ERROR的区别
====
> 天哪...看视频居然居然居然记错了....我还以为是AMD的翻车了，又记录了一波断点调试，顺便查查SOCKET的相关错误码

## 关于socket的各种错误码
* INVALID_SOCKET（0)
* SOCKET_ERROR(-1)

### INVALID_SOCKET
> 表示该 socket fd 无效

**使用场景**
* accept()
* socket()

### SOCKET_ERROR
> 表示该socket执行时出错

**使用场景**
* bind()
* recv()
* listen()
* send()
* setsockopt()
* fcntl()

**额外收获1**<BR>
 表示该socket执行时出错,获取具体错误类型时使用 errno,注：多线程下它是不安全的
 
 **额外收获2**<BR>
 socket在非阻塞的情况下接收和发送数据时的错误码以及如何处理
 
 1. 判断socket是否“阻塞”（即检测错误类型 errno 是否为 EINPROGRESS 或 EWOULDBLOCK，该情况往往是由于TCP窗口导致的
 2. 若错误码 errno 为 EINTR（被信号中断了，则继续重试），则忽略该错误，继续接收或发送数据。
 3. 若recv或send调用后返回 0 ，则表示对端关闭了连接。
 
 
 DEMO
 ```
 
bool CBaseSocket::_IsBlock(int error_code)
{
#ifdef _WIN32
	return ( (error_code == WSAEINPROGRESS) || (error_code == WSAEWOULDBLOCK) );
#else
	return ( (error_code == EINPROGRESS) || (error_code == EWOULDBLOCK) );
#endif
}


while (true)
 {
        char recvbuf[32] = {0};
        int ret = recv(clientfd, recvbuf, 32, 0);
        if (ret > 0) 
        {
            //收到了数据
            std::cout << "recv successfully." << std::endl;
        } 
        else if (ret == 0)
        {
            //对端关闭了连接
            std::cout << "peer close the socket." << std::endl; 
            break;
        } 
        else if (ret == -1) 
        {
            if (errno == EWOULDBLOCK)
            {
                std::cout << "There is no data available now." << std::endl;
            } 
            else if (errno == EINTR) 
            {
                //如果被信号中断了，则继续重试recv函数
                std::cout << "recv data interrupted by signal." << std::endl;               
            } else
            {
                //真的出错了
                break;
            }
        }
 }
 
 
 ```