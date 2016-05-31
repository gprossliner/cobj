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

//////////////////////////////////////////////////////////////////////////
// Possible Preprocessor Symbols
//
//	COBJ_CLASS_NAME: The name of the class
//	COBJ_CLASS_PARAMETERS --> COBJ_CLASS_PARAMETER(GEN_PARAM_SPEC): X-Macro for the provided Parameters
//	COBJ_CLASS_INTERFACES --> COBJ_CLASS_INTERFACE(GEN_INTERFACE_NAME): X-Macro for the implemented Interfaces
//	COBJ_CLASS_VARIABLES --> COBJ_CLASS_VARIABLE(GEN_VARIABLE_SPEC): X-Macro for object private variables
//
// Names defined:
//	genclass_parameters_struct: Defines the name of the struct holding all parameters for the construction of an instance
//	genclass_descriptor: Defines the name of the class-descriptor
//////////////////////////////////////////////////////////////////////////

#ifndef COBJ_CLASS_NAME
#	error "COBJ_CLASS_NAME is not defined"
#endif

#ifndef genclass_descriptor

//	genclass_name: Is directly the name specified by COBJ_CLASS_NAME
#	define genclass \
		COBJ_CLASS_NAME
		
//	genclass_descriptor: used in header (extern) and implementation. The pointer represents the class.
#	define genclass_descriptor \
		COBJ_PP_CONCAT(genclass, _descriptor)

//  static variable rendered into implemenation.c, pointed to by genclass_descriptor
//	cobj_class_descriptor_ptr genclass_descriptor = &genclass_descriptor_object;
#	define genclass_descriptor_instance \
		COBJ_PP_CONCAT(genclass, _descriptor_instance)
		
//	genclass_object: 
#	define genclass_object genclass
#	define genclass_object_impl COBJ_PP_CONCAT(genclass, _impl)
#	define genclass_parameters COBJ_PP_CONCAT(genclass, _parameters)
#	define genclass_initialize COBJ_PP_CONCAT(genclass, _initialize)

#endif
