#include "zxz.h"

void sys_err(int exitcode, const char *desc)
{
	perror(desc);
	exit(exitcode);
}
