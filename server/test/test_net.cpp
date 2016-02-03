#include "mini_log.h"
#include "mini_conf.h"
#include "mini_net_server.h"


int main() {
	struct mini_logstat_t logstat; 

	logstat.events = MINI_LOG_ALL;
	logstat.to_syslog =  0;
	logstat.spec = 0;
	if(mini_openlog("./log", "netserver", &logstat, 1024, NULL) != 0) {
		printf("open log error\r\n");
		return -1;
	}
	
	struct mini_confdata_t *confdata;
	confdata = mini_initconf(1);	
	if(confdata == NULL ) {
		mini_writelog(MINI_LOG_WARNING, "mini_initconf(1) error)");
		return -1;
	}
	mini_readconf("./conf", "netserver.conf", confdata);
	mini_server_t *server;	
	mini_server_conf_t *server_conf = NULL;
	server_conf = (mini_server_conf_t *) malloc(sizeof(mini_server_conf_t));	
	mini_getconfstr(confdata, "update_server_name", server_conf->server_name);
	mini_getconfint(confdata, "update_listen_port", (int *)&server_conf->listen_port);
	mini_getconfint(confdata, "update_connect_type", (int *)&server_conf->connect_type);
	mini_getconfint(confdata, "update_read_timeout", (int *)&server_conf->read_timeout);
	mini_getconfint(confdata, "update_write_timeout", (int *)&server_conf->write_timeout);
	mini_getconfint(confdata, "update_thread_num", (int *)&server_conf->thread_num);
	mini_getconfint(confdata, "update_read_size", (int *)&server_conf->read_size);
	mini_getconfint(confdata, "update_write_size", (int *) &server_conf->write_size);
	printf("server_name:%s\n", server_conf->server_name);
	printf("listen_port:%d\n", server_conf->listen_port);


	server = mini_server_create("mini_server_net");
	if(server == NULL ) {
		mini_writelog(MINI_LOG_WARNING, "mini_server create fail!");
	}
	mini_writelog(MINI_LOG_NOTICE, "read_timeout:%d", server->read_timeout);
	mini_server_load(server, server_conf);	
	free(server_conf);
	mini_freeconf(confdata);
	mini_closelog(0);
	return 0;

}
