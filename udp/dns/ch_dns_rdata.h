/*
 *
 *      Filename: ch_dns_rdata.h
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-04-25 16:46:19
 * Last Modified: 2018-04-25 16:46:19
 */

#ifndef CH_DNS_RDATA_H
#define CH_DNS_RDATA_H

typedef struct ch_dns_rdata_t ch_dns_rdata_t;

#include "ch_dns_data_input.h"
#include "ch_dns_name.h"
#include "ch_dns_class.h"
#include "ch_dns_types.h"
#include "ch_list.h"

struct ch_dns_rdata_t {

	struct list_head node;

	void (*rdata_dump)(ch_dns_rdata_t *rdata,FILE *fp,void *priv_data);

	ssize_t (*rdata_write)(ch_dns_rdata_t *rdata,ch_data_output_t *dout,void *priv_data);

	ch_dns_name_t name;

	uint16_t  type;
	uint16_t dclass;

	uint32_t ttl;

	void *base;
	void *data;
	uint16_t dlen;
};

static inline void 
ch_dns_rdata_input_init(ch_dns_data_input_t *din,ch_dns_rdata_t *rdata) {

	ch_dns_data_input_init(din,rdata->base,rdata->data,rdata->data+rdata->dlen); 

}

static inline int ch_dns_rdata_name_parse(ch_pool_t *mp,ch_dns_rdata_t *rdata,ch_dns_name_t *name){

	ch_dns_data_input_t din;

	ch_dns_rdata_input_init(&din,rdata);

	return ch_dns_name_parse(mp,&din,name);
}

static inline void ch_dns_rdata_dump(ch_dns_rdata_t *rdata,FILE *fp){

	fprintf(fp,"\n\n");
	ch_dns_name_dump(&rdata->name,fp);
	fprintf(fp,"rdata.type:%u\n",rdata->type);
	fprintf(fp,"rdata.class:%u\n",rdata->dclass);
	fprintf(fp,"rdata.ttl:%lu\n",(unsigned long)rdata->ttl);
	fprintf(fp,"rdata.dlen:%u\n",rdata->dlen);
	fprintf(fp,"rdata.data:\n");
	if(rdata->rdata_dump)
		rdata->rdata_dump(rdata,fp,NULL);
	else
		fprintf(fp,"%s\n",rdata->data?(const char*)rdata->data:"");

}

static inline ssize_t ch_dns_rdata_write(ch_dns_rdata_t *rdata,ch_data_output_t *dout){

	ssize_t len = 0,rc;
	
	CH_DNS_NAME_WRITE(dout,&rdata->name,len,rc);
	CH_DOUT_UINT16_WRITE(dout,rdata->type,len,rc);
	CH_DOUT_UINT16_WRITE(dout,rdata->dclass,len,rc);
	CH_DOUT_UINT32_WRITE(dout,rdata->ttl,len,rc);

	if(rdata->rdata_write){
		
		CH_DOUT_UINT8_WRITE(dout,1,len,rc);

		if(-1 == (rc = rdata->rdata_write(rdata,dout,NULL)))
			return -1;
		len+=rc;

	}else{
	
		CH_DOUT_UINT8_WRITE(dout,0,len,rc);
		CH_DOUT_STRING16_WRITE(dout,(unsigned char*)rdata->data,rdata->dlen,len,rc);
	}

	return len;
}
#define CH_DNS_RDATA_WRITE(dout,rdata,len,rc) do {  \
	if(-1 == (rc = ch_dns_rdata_write(rdata,dout))) \
		return -1;                                  \
	len+=rc;                                        \
}while(0)

#endif /*CH_DNS_RDATA_H*/
