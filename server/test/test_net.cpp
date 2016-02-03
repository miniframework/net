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
	
	mini_confdata_t *confdata;
	confdata = mini_initconf(1);	
	if(confdata == NULL ) {
		mini_writelog(MINI_LOG_WARNING, "mini_initconf(1) error)");
		return -1;
	}
	mini_readconf("./conf", "netserver.conf", confdata);
	mini_server_t *server;	
	mini_server_conf_t *server_conf;
	

	server = mini_server_create("mini_server_net");
	if(server == NULL ) {
		mini_writelog(MINI_LOG_WARNING, "mini_server create fail!");
	}
	server_conf = mini_server_conf(confdata, "update");

	mini_server_load(server, server_conf);	



	free(server);
	free(server_conf);
	mini_freeconf(confdata);
	mini_closelog(0);
	return 0;

}
