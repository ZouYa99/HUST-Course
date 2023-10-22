#include "sessionClient.h"
#include<map>
extern string fileposition;
map<string, string> content_type = {
		{".png", "image/png"},
		{".jpg", "image/jpeg"},
		{".jpeg", "image/jpeg"},
		{".html", "text/html"}
};
void sessionToClient(SOCKET sessionSocket) {
	int sendre;
	const char* NOTFOUND = "HTTP/1.1 404 Not Found\r\n";
	const char* REQERROR = "HTTP/1.1 400 Bad Request\r\n";

	char* buf = (char*)malloc(1024 * sizeof(char));
	int len = 1024;
	int charnum = recv(sessionSocket, buf, len, 0);
	if (charnum == SOCKET_ERROR) {
		charnum = WSAGetLastError();
		cout << "thread falied!" << endl;
		return;
	}
	cout << buf<<endl;
	//对接受到的消息进行解析
	smatch strmatch;//正则表达式结果文本
	regex regulation("([A-Za-z]+) +(.*) +(HTTP/[0-9][.][0-9])");//正则表达式规则
	string str(buf);//需要用正则表达式的原始文本
	int match = regex_search(str, strmatch, regulation);
	if (match == 0) {
		cout << "request message error"<<endl;
		sendre = send(sessionSocket, REQERROR, strlen(REQERROR), 0);
		closesocket(sessionSocket);
		return;
	}
	printf("ThreadID: %d\n", GetCurrentThreadId());
	string msg_get = strmatch[1];//请求方法
	string msg_url = strmatch[2];//请求文件的url
	smatch filetype;
	regex regulation2("\\..*");
	match = regex_search(msg_url, filetype, regulation2);
	if (match == 0) {
		std::cout << msg_get + msg_url + "\nFORMAT ERROR\n";
		sendre = send(sessionSocket, REQERROR, strlen(REQERROR), 0);
		closesocket(sessionSocket);
		return;
	}
	string file_type = filetype[0];
	ifstream f(fileposition + msg_url, std::ios::binary);
	if (!f) {//没有找到文件
		cout << msg_url + "\nNOT FOUND"<<endl;
		sendre = send(sessionSocket, NOTFOUND, strlen(NOTFOUND), 0);
		closesocket(sessionSocket);
		return;
	}
	std::filebuf* tmp = f.rdbuf();
	int size = tmp->pubseekoff(0, f.end, f.in);
	tmp->pubseekpos(0, f.in);
	if (size <= 0) {
		sendre = send(sessionSocket, REQERROR, strlen(REQERROR), 0);
		closesocket(sessionSocket);
		return;
	}else {
		string Content_Type = content_type[file_type];
		char* buffer = new char[size];
		char* tail = buffer + size;
		tmp->sgetn(buffer, size);
		f.close();
		cout << "successfully get file " + msg_url<<endl;
		stringstream remsg;
		remsg << "HTTP/1.1 200 OK\r\n" << "Connection:close\r\n"<<"Server:ZouYa\r\n" << "Content Length:" << size
			<< "\r\n" << "Content Type:" + Content_Type << "\r\n\r\n";
		string remsgstr = remsg.str();
		const char* remsgchar = remsgstr.c_str();
		int tmpsize = strlen(remsgchar);
		sendre = send(sessionSocket, remsgchar, tmpsize, 0);
		while (buffer < tail) {
			sendre = send(sessionSocket, buffer, size, 0);
			buffer = buffer + sendre;
			size = size - sendre;
		}
		closesocket(sessionSocket);
		return;
	}
}