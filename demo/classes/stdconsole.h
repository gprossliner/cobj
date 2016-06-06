
#ifndef STDCONSOLE_H_
#define STDCONSOLE_H_

#define COBJ_CLASS_NAME	stdconsole

#define COBJ_CLASS_PARAMETERS
	
#define COBJ_CLASS_VARIABLES
	
#define COBJ_CLASS_INTERFACES	\
	COBJ_CLASS_INTERFACE(console)	\

#define COBJ_INTERFACE_IMPLEMENTATION_MODE
#	include "interfaces/console.h"
#undef  COBJ_INTERFACE_IMPLEMENTATION_MODE

#include "cobj-classheader-generator.h"



#endif /* STDCONSOLE_H_ */