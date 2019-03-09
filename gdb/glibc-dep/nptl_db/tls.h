#ifndef __TLS_H__
#define __TLS_H__

	unsigned tls_tcb_at_tp;
	unsigned tls_dtv_at_tp;
	int forced_dynamic_tls_offset;
	int no_tls_offset;
	unsigned tcb_alignment;


#define TLS_DTV_AT_TP	tls_dtv_at_tp
#define TLS_TCB_AT_TP	tls_tcb_at_tp
#define TCB_ALIGNMENT   tcb_alignment

#define TLS_PRE_TCB_SIZE th->th_ta_p->ta_sizeof_pthread + TCB_ALIGNMENT

#define NO_TLS_OFFSET no_tls_offset
#define FORCED_DYNAMIC_TLS_OFFSET forced_dynamic_tls_offset

#endif