/*
 *
 *      Filename: ./app/tcp_app/telnet/ch_telnet.c
 *
 *        Author: g.goodian@gmail.com
 *   Description: ---
 *        Create: 2016-12-30 10:28:11
 * Last Modified: 2018-02-06 10:50:00
 */


#include <stdio.h>
#include <stdlib.h>

#include "ch_telnet.h"
#include "ch_util.h"
#include "ch_tcp_data_writer.h"
#include "ch_app_context_tcp.h"

static int 
telnet_recognize_by_port(ch_app_t *app, 
	uint16_t src_port, uint16_t dst_port, void *priv_data)
{
	ch_app_context_tcp_t *tcontext = (ch_app_context_tcp_t*)app->app_context;

    return ch_ports_equal(tcontext->telnet_ports,PORT_MAX_SIZE,src_port,dst_port);
}

static int 
telnet_recognize_by_content(ch_app_t *app,void *data,size_t dlen,void *priv_data)
{
    return 1;
}

static int 
telnet_content_process(ch_app_t *app,ch_shm_format_t *fmt,ch_shm_record_t *rcd)
{
    return ch_tcp_data_write(fmt,rcd,PROTOCOL_TELNET);
}

static void 
telnet_content_flush(ch_app_t *app,ch_shm_format_t *fmt,ch_shm_record_t *rcd)
{
    ch_tcp_data_write(fmt,rcd,PROTOCOL_TELNET);
}

static void 
telnet_content_close(ch_app_t *app,ch_shm_format_t *fmt,ch_shm_record_t *rcd)
{

	ch_tcp_data_write(fmt,rcd,PROTOCOL_TELNET);
}

static ch_app_t telnet_app = {
    .app_recognize_by_port = telnet_recognize_by_port,
    .app_recognize_by_content = telnet_recognize_by_content,
    .app_content_process = telnet_content_process,
    .app_content_flush = telnet_content_flush,
    .app_content_close = telnet_content_close,
};

int ch_telnet_init(ch_app_context_t *app_context)
{
    ch_app_context_register(app_context,&telnet_app);

    return 0;
}
