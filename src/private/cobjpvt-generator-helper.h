/*

MIT License

Copyright (c) 2016 Guenter Prossliner

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef COBJPVT_GEN_BASE_H_
#define COBJPVT_GEN_BASE_H_

#include "private/cobjpvt-generator-framework.h"

//////////////////////////////////////////////////////////////////////////
//	Method-Generation
//	This macros defines how interface methods are named in public code
#define COBJ_INTERFACE_METHOD(GEN_RETURN_TYPE, GEN_METHOD_NAME, ...)	\
	COBJPVT_GEN_INTERFACE_METHOD(GEN_RETURN_TYPE, GEN_METHOD_NAME, __VA_ARGS__)

#define COBJPVT_GEN_METHOD_GENERATOR() \
	COBJ_INTERFACE_METHODS
	
//////////////////////////////////////////////////////////////////////////
//	Variables-Generation
//	This macros defines the naming of the variables
#define COBJ_CLASS_VARIABLE(GEN_VARIABLE_TYPE, GEN_VARIABLE_NAME)	\
	COBJPVT_GEN_CLASS_VARIABLE(GEN_VARIABLE_TYPE, GEN_VARIABLE_NAME)

#define COBJPVT_GEN_CLASS_VARIABLE_GENERATOR()	\
	COBJ_CLASS_VARIABLES

//////////////////////////////////////////////////////////////////////////
//	Parameters-Generation
//	This macros defines the naming of the variables
#define COBJ_CLASS_PARAMETER(GEN_PARAMETER_TYPE, GEN_PARAMETER_NAME)	\
	COBJPVT_GEN_CLASS_PARAMETER(GEN_PARAMETER_TYPE, GEN_PARAMETER_NAME)

#define COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()	\
	COBJ_CLASS_PARAMETERS


/*
	How to use:
	//////////////////////////////////////////////////////////////////////////
	
	// define the template, by using the args:
	//	GEN_PARAM_TYPE: contains the type of the parameter
	//	GEN_PARAM_NAME:	contains the name of the parameter
	#define COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE(GEN_PARAM_TYPE, GEN_PARAM_NAME)	\
		GEN_PARAM_TYPE GEN_PARAM_NAME;
	COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()	// call the generator
	#undef COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE	// to cleanup, undefine the template
*/

/*
	How it works:
	//////////////////////////////////////////////////////////////////////////
	
	(0.1) the configuration in cobjpvt-generator-helper.h defines the public entry-macros
	COBJ_CLASS_PARAMETER(GEN_PARAMETER_TYPE, GEN_PARAMETER_NAME)	=>	COBJPVT_GEN_CLASS_PARAMETER(GEN_PARAMETER_TYPE, GEN_PARAMETER_NAME)
	COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()	=> COBJ_CLASS_PARAMETERS
	(0.2) in the source-code, the user uses this macros to declare the parameters of the class
	...
*/


//////////////////////////////////////////////////////////////////////////
//	Interfaces-Generation
//	This macros defines the naming of the interfaces
#define COBJ_CLASS_INTERFACE(GEN_INTERFACE_NAME)	\
	COBJPVT_GEN_CLASS_INTERFACE(GEN_INTERFACE_NAME)

#define COBJPVT_GEN_CLASS_INTERFACE_GENERATOR()	\
	COBJ_CLASS_INTERFACES


#endif