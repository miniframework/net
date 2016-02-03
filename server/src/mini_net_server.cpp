#include "mini_net_server.h"
#include "mini_log.h"



mini_server_t *mini_server_create(const char *server_name) 
{
	mini_server_t *sev = (mini_server_t *)malloc(sizeof(mini_server_t));
	if (sev == NULL) return NULL;
	sev->err_no = 0;
	sev->connect_type = MINI_NET_SHORT_CONNECT;
	sev->connect_timeout = 100;
	sev->read_timeout = 500;
	sev->write_timeout = 500;
	sev->thread_num = 0;
	sev->listen_port = 0;
	sev->read_size = 0;
	sev->write_size = 0;
	sev->read_buf = NULL;
	sev->write_buf = NULL;
	if (server_name == NULL) {
		mini_server_set_server_name(sev, "mini_net_server_default");
	} else {
		mini_server_set_server_name(sev, server_name);
	}
	return sev;
	
}
int mini_server_set_server_name(mini_server_t *sev, const char *name)
{
	if (sev == NULL) return -1;
	strncpy(sev->server_name, name, sizeof(sev->server_name));
	sev->server_name[sizeof(sev->server_name) - 1] = '\0';
	return 0;
}
int mini_server_set_listen_port(mini_server_t *sev, int port)
{
	if (sev == NULL) return -1;
	sev->listen_port = port;
	return 0;
}
int mini_server_set_timeout(mini_server_t *sev, int connect_timeout, int read_timeout, int write_timeout)
{
	if (sev == NULL) return -1;
	sev->connect_timeout = connect_timeout;
	sev->read_timeout = read_timeout;
	sev->write_timeout = write_timeout;

	return 0;
}
int mini_server_set_pthread_num(mini_server_t *sev, int pnum)
{
	if (sev == NULL) return -1;
	if (pnum <= 0) {
		mini_writelog(MINI_LOG_WARNING, "mini_server_set_pthread_num thread_num <0  create fail!");   
		return -1;
	}
	if (pnum == sev->thread_num) {
		return 0;
	}
	sev->thread_num = pnum;
	return 0;
}
int mini_server_set_connect_type(mini_server_t *sev, int type)
{
	if (sev == NULL) return -1;
	sev->connect_type = type;
	return 0;
}
int mini_server_load(mini_server_t *sev, mini_server_conf_t *server_conf) 
{
	//初始化端口
	mini_server_set_server_name(sev, server_conf->server_name);
	mini_server_set_listen_port(sev, server_conf->listen_port);
	//设置网络交互超时
	mini_server_set_timeout(sev, server_conf->connect_timeout, server_conf->read_timeout, server_conf->write_timeout);
	//设置连接类型
	if (server_conf->connect_type == MINI_NET_SHORT_CONNECT) { //短连接
		mini_server_set_connect_type(sev, MINI_NET_SHORT_CONNECT);
	} else { //长连接
		mini_server_set_connect_type(sev, MINI_NET_LONG_CONNECT);
	}
	//设置线程数
	mini_server_set_pthread_num(sev, server_conf->thread_num);
	return 0;
}
int mini_server_bind(mini_server_t *sev) {
	
	return 0;
}
