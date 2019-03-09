#include "native_check.h"
#include <string.h>
#include <stdio.h>
#include "../config.h"
#include "../../../bfd/bfd.h"
#include <sys/utsname.h>

unsigned get_host_mach(char *name_of_arch){
	unsigned result;

	if(strstr(name_of_arch, "x86_64") != NULL)
		result = bfd_arch_i386;
	else if(strstr(name_of_arch, "i386") != NULL)
		result = bfd_arch_i386;
	else if(strstr(name_of_arch, "mips") != NULL)
		result = bfd_arch_mips;
	else if(strstr(name_of_arch, "arm") != NULL)
		result = bfd_arch_arm;
	else if(strstr(name_of_arch, "powerpc") != NULL)
		result = bfd_arch_powerpc;
	else if(strstr(name_of_arch, "aarch64") != NULL)
		result = bfd_arch_aarch64;
	else
		result = -1;

	return result;
}

int native_check(unsigned bfd_arch){
    struct utsname buf;
    if(uname(&buf) == 0){
    unsigned host_mach = get_host_mach(buf.machine);

    if(host_mach == bfd_arch)
        return 0; //zero if it's host
    else
        return 1;
	}
	return -1;
}