Files and functions taken from GLIBC source code (${glibc_src}/nptl_db/) necessary for getting
TLS variables (from coredump file) when cross GDB using GLIBC version 2.22 and higher are stored into
${gdb_src}/glibc-dep/nptl_db directory.

gdb_td_ta_new() is stored into ${gdb_src}/glibc-dep/ because functionality of function (td_ta_new())
from GLIBC source has changed in order to get current version of GLIBC from coredump file.

gdb_td_thr_tlsbase is function taken from nptl_db/td_thr_tlsbase.c,
which has modified in GLIBC 2.22 and higher, so all dependent files had to be included into GDB source.

------------------------

${gdb_src}/glibc-dep/nptl_db

* thread_dbP.h
Taken needed definitions and macros.

* db-symbols.h
Unmodified.

* fetch-value.c
Taken needed functions.

* structs.def
Unmodified.

* td_symbol_list.c
Taken necessary definitions and modified td_lookup function.

* td_ta_map_lwp2thr.c
Taken only __td_ta_lookup_th_unique function unmodified.

* td_thr_tlsbase.c
gdb_td_thr_tlsbase(), modified in order to work with all GLIBC versions.
${gdb_src}/gdb/config/${arch}/tls.h depending on architecture got different
values of TLS_TCB_AT_TP and TLS_DTV_AT_TP macros taken
from ${glibc_src}/sysdeps/${arch}/nptl/tls.h.

* td_thr_tls_get_addr.c
Unmodified.

-------------------------