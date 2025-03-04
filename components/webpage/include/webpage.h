#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include "esp_http_server.h"

typedef struct
{
    char web_mount_point[32];
    // char base_path[ESP_VFS_PATH_MAX + 1];
    char scratch[10240];
}webpage_obj_t;

typedef esp_err_t (*http_uri_handler)(httpd_req_t * req);

void webpage_init (webpage_obj_t *);
httpd_uri_t webpage_handler (const char * p_uri, httpd_method_t e_method, 
                                        http_uri_handler fp_handler, void * p_user_ctx);
#endif
