#ifndef _MINI_NET_SERVER_H
#define _MINI_NET_SERVER_H
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
struct mini_server_t
{
	u_int 	err_no;			//错误号	
	char 	server_name[50]; 		//服务名称
	u_int 	listen_port;		//连接端口
	int 	connect_type; 		//连接类型
	int 	connect_timeout;		//连接超时
	int 	read_timeout; 		//读超时
	int 	write_timeout;		//写超时
	int 	thread_num; 		//线程数
	u_int 	read_size;		//读缓存区大小
	u_int 	write_size;		//写缓存缓存大小
	void 	**read_buf;			//读缓存区
	void 	**write_buf;		//写缓存区
};

struct mini_server_conf_t {	

	char	server_name[50];		/**< 服务名*/
	u_int	listen_port;               /**< 提供服务的端口 */
	int 	connect_type; 		//连接类型
	u_int	connect_timeout;	/**<    连接超时，ms    */
	u_int	read_timeout;       /**< 读超时　*/
	u_int	write_timeout;      /**< 写超时 */
	u_int	thread_num;         /**< 线程数 */
	u_int	read_size;		/**<    用户读缓冲区大小    */
	u_int	write_size;	  	/**<    用户写缓冲区大小    */

    
};
enum {
	MINI_NET_SHORT_CONNECT = 0,	//短连接		  /**<        */
	MINI_NET_LONG_CONNECT		  /**<        */
};

mini_server_t *mini_server_create(const char *server_name);
int mini_server_set_server_name(mini_server_t *sev, const char *name);
int mini_server_load(mini_server_t *sev, mini_server_conf_t *server_conf);
#endif
