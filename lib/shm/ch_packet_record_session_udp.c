/*
 *
 *      Filename: ch_packet_record_session_udp.c
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-04-10 16:32:44
 * Last Modified: 2018-04-16 09:53:39
 */

#include "ch_packet_record_session_udp.h"
#include "ch_bin_format.h"

void ch_packet_record_session_udp_read(ch_packet_record_session_udp_t *pkt_udp_session,ch_packet_record_t *pkt_rcd){


	ch_bin_format_t btmp,*bfmt=&btmp;

	ch_bf_init_with_len(bfmt,pkt_rcd->shm_rcd.data,pkt_rcd->meta_data_size);

	/*start read*/
	unsigned char *db_path = NULL;
	size_t db_path_len = 0;

    pkt_udp_session->is_timeout = ch_bf_uint8_read(bfmt);
    
	pkt_udp_session->timeout_tv = ch_bf_uint16_read(bfmt);
    pkt_udp_session->src_port = ch_bf_uint16_read(bfmt);
    pkt_udp_session->dst_port = ch_bf_uint16_read(bfmt);

    
    pkt_udp_session->src_ip = ch_bf_uint32_read(bfmt);
    pkt_udp_session->dst_ip = ch_bf_uint32_read(bfmt);
    pkt_udp_session->req_data_size = ch_bf_uint32_read(bfmt);
    pkt_udp_session->res_data_size = ch_bf_uint32_read(bfmt);
    pkt_udp_session->req_data_seq = ch_bf_uint32_read(bfmt);
    pkt_udp_session->res_data_seq = ch_bf_uint32_read(bfmt);

    pkt_udp_session->session_id = ch_bf_uint64_read(bfmt);
	pkt_udp_session->req_packets = ch_bf_uint64_read(bfmt);
	pkt_udp_session->res_packets = ch_bf_uint64_read(bfmt);
	pkt_udp_session->req_bytes = ch_bf_uint64_read(bfmt);
	pkt_udp_session->res_bytes = ch_bf_uint64_read(bfmt);
	pkt_udp_session->req_start_time = ch_bf_uint64_read(bfmt);
	pkt_udp_session->req_last_time = ch_bf_uint64_read(bfmt);
	pkt_udp_session->res_start_time = ch_bf_uint64_read(bfmt);
	pkt_udp_session->res_last_time = ch_bf_uint64_read(bfmt);


	ch_bf_bytes_read(bfmt,&db_path,&db_path_len);

	pkt_udp_session->db_path = (char*)db_path;
	pkt_udp_session->db_path_len = (uint8_t)db_path_len;

}

size_t ch_packet_record_session_udp_write(ch_packet_record_session_udp_t *pkt_udp_session,void *buffer,size_t bsize,void *data,size_t dlen){


	ch_bin_format_t btmp,*bfmt=&btmp;

	ch_bf_init_with_len(bfmt,buffer,bsize);

    ch_bf_uint8_write(bfmt,pkt_udp_session->is_timeout);

    ch_bf_uint16_write(bfmt,pkt_udp_session->timeout_tv);
    ch_bf_uint16_write(bfmt,pkt_udp_session->src_port);
    ch_bf_uint16_write(bfmt,pkt_udp_session->dst_port);
    
    
	ch_bf_uint32_write(bfmt,pkt_udp_session->src_ip);
    ch_bf_uint32_write(bfmt,pkt_udp_session->dst_ip);
	ch_bf_uint32_write(bfmt,pkt_udp_session->req_data_size);
	ch_bf_uint32_write(bfmt,pkt_udp_session->res_data_size);
	ch_bf_uint32_write(bfmt,pkt_udp_session->req_data_seq);
	ch_bf_uint32_write(bfmt,pkt_udp_session->res_data_seq);

    
    ch_bf_uint64_write(bfmt,pkt_udp_session->session_id);
	ch_bf_uint64_write(bfmt,pkt_udp_session->req_packets);
	ch_bf_uint64_write(bfmt,pkt_udp_session->res_packets);
	ch_bf_uint64_write(bfmt,pkt_udp_session->req_bytes);
	ch_bf_uint64_write(bfmt,pkt_udp_session->res_bytes);
	ch_bf_uint64_write(bfmt,pkt_udp_session->req_start_time);
	ch_bf_uint64_write(bfmt,pkt_udp_session->req_last_time);
	ch_bf_uint64_write(bfmt,pkt_udp_session->res_start_time);
	ch_bf_uint64_write(bfmt,pkt_udp_session->res_last_time);


	ch_bf_bytes_write(bfmt,pkt_udp_session->db_path==NULL?"":pkt_udp_session->db_path,pkt_udp_session->db_path_len);

	if(data&&dlen>0){
	
		ch_bf_bytes_write(bfmt,data,dlen);
	}

	return ch_bf_content_size(bfmt);

}
