/*
 *
 *      Filename: ch_dns_rdata_ptr.c
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-05-03 10:23:52
 * Last Modified: 2018-05-09 17:27:32
 */

#include "ch_dns_rdata_ptr.h"
#include "ch_log.h"

static void _rdata_ptr_dump(ch_dns_rdata_t *rdata,FILE *fp,void *priv_data ch_unused){

	ch_dns_rdata_ptr_t *ptr = (ch_dns_rdata_ptr_t*)rdata;

	fprintf(fp,"Dump The rdata.ptr:\n");

	ch_dns_name_dump(&ptr->name,fp);

}

static ssize_t  _rdata_ptr_write(ch_dns_rdata_t *rdata,ch_data_output_t *dout,void *priv_data ch_unused){

	ch_dns_rdata_ptr_t *ptr = (ch_dns_rdata_ptr_t*)rdata;

	return ch_dns_name_write(dout,&ptr->name);

}

static ch_dns_rdata_t * _rdata_ptr_create(ch_pool_t *mp,void *priv_data ch_unused){


	ch_dns_rdata_ptr_t *rdata = (ch_dns_rdata_ptr_t*)ch_pcalloc(mp,sizeof(ch_dns_rdata_ptr_t));

	ch_dns_name_t *name = &rdata->name;

	CH_DNS_NAME_INIT(name);

	rdata->rdata.rdata_dump = _rdata_ptr_dump;
	rdata->rdata.rdata_write = _rdata_ptr_write;

	return (ch_dns_rdata_t*)rdata;

}

static int _rdata_ptr_parse(ch_pool_t *mp,ch_dns_rdata_t *rdata,void *priv_data ch_unused){

	ch_dns_rdata_ptr_t *rdata_ptr = (ch_dns_rdata_ptr_t*)rdata;
	
	if(rdata->dlen ==0 || rdata->data == NULL)
		return -1;

	if(ch_dns_rdata_name_parse(mp,rdata,&rdata_ptr->name)){
	
		ch_log(CH_LOG_ERR,"Parse rdata.ptr failed!");
		return -1;
	}

	return 0;
}

static ch_dns_rdata_parser_t ptr_parser = {

	{NULL,NULL},
	dns_rdataclass_in,
	dns_rdatatype_ptr,
	_rdata_ptr_create,
	_rdata_ptr_parse
};


void ch_dns_rdata_ptr_init(ch_dns_rdata_pool_t *rdata_pool){

	ch_dns_rdata_parser_register(rdata_pool,&ptr_parser);

}

