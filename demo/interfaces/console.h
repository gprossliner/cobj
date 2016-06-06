
#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdarg.h>

#define COBJ_INTERFACE_NAME	console

#define COBJ_INTERFACE_METHODS	\
	COBJ_INTERFACE_METHOD(int, vprintf, const char *, string, va_list, vlist)	\
	
#include "cobj-interface-generator.h"

static inline int console_printf(console * self, const char * format, ...)
{
	va_list vlist;
	va_start(vlist, format);
	int res = console_vprintf(self, format, vlist);
	va_end(vlist);

	return res;
}


#endif /* CONSOLE_H_ */