#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>
struct reg_struct
{
    char reg_user[20];
    char reg_passwd[20];
    int reg_age;
    int reg_sex;
};
struct result_struct
{
    int result;
};

int main()
{
	
	struct result_struct result;
	char sql_str[200];
	MYSQL conn;
	MYSQL *mysql;	
	int udpsock = socket(AF_INET, SOCK_DGRAM, 0);
	while(1)
{
	
	if(udpsock < 0)
	{
		printf("socket is error.\n");
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(1234);
	int ret = bind(udpsock, (struct sockaddr *)&addr, sizeof(addr));
	if(ret < 0)
	{
		printf("bind erro\n");
		goto ERR;	
	}
	//接收数据

	struct reg_struct buf;
	struct sockaddr_in snd_addr;
	socklen_t addrlen=sizeof(struct sockaddr_in);
	memset(&buf,0,sizeof(buf));
	memset(&snd_addr,0,sizeof(snd_addr));
	ret = recvfrom(udpsock, &buf, sizeof(buf), 0, (struct sockaddr *)&snd_addr, &addrlen);
	if(ret < 0)
	{
		printf("recvfrom erro\n");
		goto ERR;	
	}
	//打印
	printf("user=%s,passwd=%s,sex=%d,age=%d\n",buf.reg_user,buf.reg_passwd,buf.reg_sex,buf.reg_age);
	//将接受数据存入数据库中
	MYSQL *mysql = mysql_init(NULL);
	if(mysql == NULL)
	{
		printf("mysql_init erro\n");
		goto ERR;
	}
	mysql_real_connect(mysql, "127.0.0.1", 
				"root","123456","yuangong_db", 0, NULL, 0);
	//执行sql语句
	snprintf(sql_str,200,"create table if not exists user_tbl(id integer primary key auto_increment,user text,passwd text,sex int,age int,type int);");

	ret = mysql_query(mysql,sql_str);
	if(ret!=0)
	{
		printf("query sql is error.\n");
		goto SQL_ERR;
	}
	printf("create is success\n");
	mysql_close(mysql);
	mysql = mysql_init(&conn);
	if(mysql == NULL)
	{
		printf("mysqlinit is error\n");
		goto ERR;
	}
	mysql = mysql_real_connect			 (mysql,"127.0.0.1","root","********","yuangong_db",0,NULL,0);
	if(mysql==NULL)
	{
		printf("error\n");
		goto ERR;
	}	
	memset(sql_str,0,sizeof(sql_str));
	snprintf(sql_str,200,"insert into user_tbl(user,passwd,sex,age,type) values(\"%s\",\"%s\",%d,%d,1);",buf.reg_user,buf.reg_passwd,buf.reg_sex,buf.reg_age);
	ret = mysql_query(mysql,sql_str);
	if(ret!=0)
	{
		printf("insert is error.\n");
		result.result = -1;
	}
	else
	{
		result.result = 1;
	}
	mysql_close(mysql);

	ret = sendto(udpsock,&result,sizeof(struct result_struct),0,(struct sockaddr *)&snd_addr,sizeof(snd_addr));
	printf("server snd result is success!\n");
		}




SQL_ERR:
	mysql_close(mysql);
	

ERR:
	close(udpsock);
	return 0;
}
