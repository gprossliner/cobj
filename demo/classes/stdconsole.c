
#define COBJ_IMPLEMENTATION_FILE

#include "stdconsole.h"

#include "utils.h"
#include <stdio.h>


static bool initialize_impl(stdconsole_impl * self)
{
	UNUSED_PARAMETER(self);
	return true;
}

static int console_vprintf_impl(stdconsole_impl * self, const char * format, va_list vlist)
{
	UNUSED_PARAMETER(self);
	return vprintf(format, vlist);
}