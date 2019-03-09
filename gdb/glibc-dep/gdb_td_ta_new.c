#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <version.h>

#include "nptl_db/thread_dbP.h"
#include "../nat/gdb_thread_db.h"
#include "../../../bfd/bfd.h"
#include "nptl_db/tls.h"

static td_err_e
init_target_dep_constants()
{
	struct bfd_arch_info *bfdarch = gdbarch_bfd_arch_info (target_gdbarch ());
	unsigned arch = bfdarch->arch;
	switch(arch){
		case bfd_arch_mips:
			tls_tcb_at_tp = 0;
			tls_dtv_at_tp = 1;
			forced_dynamic_tls_offset = -2;
			no_tls_offset = -1;
			tcb_alignment = 16;
			break;
		case bfd_arch_arm:
			tls_tcb_at_tp = 0;
			tls_dtv_at_tp = 1;
			forced_dynamic_tls_offset = -2;
			no_tls_offset = -1;
			tcb_alignment = 0; //set to zero because not in use for TLS_PRE_TCB_SIZE
			break;
		case bfd_arch_i386:
			tls_tcb_at_tp = 1;
			tls_dtv_at_tp = 0;
			forced_dynamic_tls_offset = -1;
			no_tls_offset = 0;
			tcb_alignment = 0; //set to zero because not in use for TLS_PRE_TCB_SIZE
			break;
		case bfd_arch_powerpc:
			tls_tcb_at_tp = 0;
			tls_dtv_at_tp = 1;
			forced_dynamic_tls_offset = -2;
			no_tls_offset = -1;
			tcb_alignment = 48;
			break;
		case bfd_arch_aarch64:
			tls_tcb_at_tp = 0;
			tls_dtv_at_tp = 1;
			forced_dynamic_tls_offset = -1;
			no_tls_offset = 0;
			tcb_alignment = 0; //set to zero because not in use for TLS_PRE_TCB_SIZE
			break;
		default:
			return TD_ERR;
	}
	return TD_OK;
}


td_err_e
gdb_td_ta_new (struct ps_prochandle *ps, td_thragent_t **ta)
{
  psaddr_t versaddr;

  /* Check whether the versions match.  */
  if (td_lookup (ps, SYM_nptl_version, &versaddr) != PS_OK)
    return TD_NOLIBTHREAD;
  if (ps_pdread (ps, versaddr, versbuf, sizeof (versbuf)) != PS_OK)
    return TD_ERR;
  if(init_target_dep_constants() != TD_OK)
	return TD_ERR;
  return TD_OK;
}
