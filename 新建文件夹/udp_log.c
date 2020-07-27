#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
struct login_struct
{
    char log_user[20];
    char log_passwd[20];
};
struct log_result_struct
{
    int result;
    int type;
};

int main()
{
	struct log_result_struct result;
	char sql_str[200];
	MYSQL_RES *res;
	MYSQL_ROW *row;
	MYSQL conn;
	MYSQL *mysql;
	printf("running!\n");
	//从网络UDP中接受数据
	//socket函数
	//功能：创建一个UDP对象，套接字
	//参数：协议足、类型、协议
	//返回之：-1为失败，大于-1表示成功
	struct login_struct buf;
	memset(&buf,0,sizeof(buf));
	struct sockaddr_in snd_addr;
	memset(&snd_addr,0,sizeof(snd_addr));
	socklen_t addrlen = sizeof(struct sockaddr_in);
	int udpsock = socket(AF_INET,SOCK_DGRAM,0);
	if(udpsock<0)
	{
		printf("socket is error\n");
		return -1;
	}
	//绑定
	//bind函数
	//功能：绑定
	//参数：socket函数的返回值、绑定的IP和端口号、地址的长度
	//返回值：0为成功，-1失败
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);//转换高低位，网络中的格式
	addr.sin_port = htons(2345);
	int ret;
	udpsock = socket(AF_INET,SOCK_DGRAM,0);
		if(udpsock<0)
		{
			printf("socket is error\n");
			return -1;
		}
		ret = bind(udpsock,(struct sockaddr *)&addr,sizeof(addr));
		memset(&buf,0,sizeof(buf));
		memset(&snd_addr,0,sizeof(snd_addr));
		if(ret<0)
		{
			printf("bind is error\n");
			goto ERR;
		}
	while(1)
	{
		memset(&buf,0,sizeof(buf));
		memset(&snd_addr,0,sizeof(snd_addr));	
		从udp网络接收
		ret = recvfrom(udpsock,&buf,sizeof(buf),0,(struct sockaddr *)&snd_addr,&addrlen);
		if(ret<0)
		{
			printf("recv is error\n");
			goto ERR;
		}
		else
		{
			printf("OK\n");
		}
		//检查发送数据是否正确
		//printf("[ip=%s,port=%d]user=%s,passwd=%s\n",inet_ntoa(snd_addr.sin_addr),ntohs(snd_addr.sin_port),buf.log_user,buf.log_passwd);
	//数据库
	//1、头文件
	//2、初始化句柄
		mysql = mysql_init(&conn);
		if(mysql == NULL)
		{
			printf("mysqlinit is error\n");
			goto ERR;
		}

	//链接数据库
		mysql = mysql_real_connect(mysql,"127.0.0.1","root","123456","yuangong_db",0,NULL,0);
		if(mysql==NULL)
		{
			printf("error\n");
			goto ERR;
		}
	//执行 sql 语句 
		snprintf(sql_str,200,"create table if not exists user_tbl(id integer primary key auto_increment,user text,passwd text,sex int,age int,type int);");
		
	//printf("3");
		ret = mysql_query(mysql,sql_str);
	//printf("4");
		if(ret!=0)
		{
			printf("query sql is error.\n");
			goto SQL_ERR;
		}
		printf("create is success\n");
		mysql_close(mysql);
	//插入数据，关闭数据库，重新链接，再执行sql语句，再关闭数据库
	//char sql_str[] = "insert into reg_tbl(name,passwd,sex,age) values(?,?,?,?);";
		mysql = mysql_init(&conn);
		if(mysql == NULL)
		{
			printf("mysqlinit is error\n");
			goto ERR;
		}
		mysql = mysql_real_connect(mysql,"127.0.0.1","root","123456","yuangong_db",0,NULL,0);
		if(mysql==NULL)
		{
			printf("error\n");
			goto ERR;
		}	

		
		memset(sql_str,0,sizeof(sql_str));
		snprintf(sql_str,200,"select type from user_tbl where user=\"%s\" AND passwd=\"%s\";",buf.log_user,buf.log_passwd);
		//snprintf(sql_str,200,"select * from reg_tbl;");
		ret = mysql_query(mysql,sql_str);
		if(ret!=0)
		{
			printf("find is error.\n");
			result.result = -1;
		}
		else
		{
			result.result = -1;
			res = mysql_use_result(mysql);
			row = mysql_fetch_row(res);
			
			if(row!=NULL)
				{
					result.result = 1;
					result.type = row[6];
				}
		}
		mysql_close(mysql);

		ret = sendto(udpsock,&result,sizeof(struct log_result_struct),0,(struct sockaddr *)&snd_addr,sizeof(snd_addr));
		printf("server snd result is success!\n");
		}
	
SQL_ERR:
	mysql_close(mysql);
ERR:
	close(udpsock);
	return 0;
}
