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
// Define common names
#include "cobjpvt-generator-class-defines.h"
#include "cobjpvt-generator-helper.h"

//////////////////////////////////////////////////////////////////////////
// Validate specific Symbols

//	COBJ_CLASS_PARAMETERS --> COBJ_CLASS_PARAMETER(GEN_PARAM_SPEC): X-Macro for the provided Parameters
#ifndef COBJ_CLASS_PARAMETERS
#	error "cobj-classheader-generator.h was included without defining COBJ_CLASS_PARAMETERS"
#endif

//	COBJ_CLASS_INTERFACES --> COBJ_CLASS_INTERFACE(GEN_INTERFACE_NAME): X-Macro for the implemented Interfaces
#ifndef COBJ_CLASS_INTERFACES
#	error "cobj-classheader-generator.h was included without defining COBJ_CLASS_INTERFACES"
#endif

//////////////////////////////////////////////////////////////////////////
// (1) strong typed implementation object_struct
#define COBJ_CLASS_IMPLEMENTATION_MODE()	\
	COBJ_PP_CONCAT(COBJ_IMPLEMENTATION_FILE, _COBJ_ID) == COBJ_PP_CONCAT(COBJ_CLASS_NAME, _COBJ_ID)
#if COBJ_CLASS_IMPLEMENTATION_MODE()
	// if we are in an implementation-file, this struct has already been rendered
	// on the first interface-implementation, because the thunks need the type
	// to be defined already.

	#ifndef COBJPVT_GEN_OBJECT_STRUCT_GENERATED
		#define COBJPVT_GEN_OBJECT_STRUCT_GENERATED
	
	typedef struct {
		cobj_class_descriptor * class_desriptor;
		#define COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE(GEN_VARIABLE_TYPE, GEN_VARIABLE_NAME)	\
			GEN_VARIABLE_TYPE GEN_VARIABLE_NAME;
		COBJPVT_GEN_CLASS_VARIABLE_GENERATOR()
		#undef COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE	
	} genclass_object_impl;

	#endif
#endif

//////////////////////////////////////////////////////////////////////////
// (2) public object struct
typedef union {
	struct {
		const cobj_class_descriptor * class_desriptor;
		struct {
			#define COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE(GEN_VARIABLE_TYPE, GEN_VARIABLE_NAME)	\
				struct { GEN_VARIABLE_TYPE _; };
			COBJPVT_GEN_CLASS_VARIABLE_GENERATOR()
			#undef COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE	
		} class_data;
	} private_data;
	
	cobj_object object;
	
} genclass_object;


//////////////////////////////////////////////////////////////////////////
// (3) descriptor
extern const cobj_class_descriptor * const genclass_descriptor;

//////////////////////////////////////////////////////////////////////////
// (4) init-function
#ifdef COBJ_CLASS_PARAMETERS

	bool genclass_initialize(
		genclass_object * self
		#define COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE(GEN_PARAM_TYPE, GEN_PARAM_NAME)	\
			,GEN_PARAM_TYPE GEN_PARAM_NAME
		COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()
		#undef COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE
	);

#endif

//////////////////////////////////////////////////////////////////////////
// This code is generated, when we are in the genclass.c file.
//	This will implement the functions and variables
#define COBJ_CLASS_IMPLEMENTATION_MODE()	\
	COBJ_PP_CONCAT(COBJ_IMPLEMENTATION_FILE, _COBJ_ID) == COBJ_PP_CONCAT(COBJ_CLASS_NAME, _COBJ_ID)
#if COBJ_CLASS_IMPLEMENTATION_MODE()

	//////////////////////////////////////////////////////////////////////////
	// (1) fw-declare the initializer_impl
	static bool initialize_impl(
		genclass_object_impl * self
		#define COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE(GEN_PARAM_TYPE, GEN_PARAM_NAME)	\
			,GEN_PARAM_TYPE GEN_PARAM_NAME
		COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()
		#undef COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE
	);
	
	//////////////////////////////////////////////////////////////////////////
	// (2) implement the public initializer
	bool genclass_initialize(
		genclass_object * self
		#define COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE(GEN_PARAM_TYPE, GEN_PARAM_NAME)	\
			,GEN_PARAM_TYPE GEN_PARAM_NAME
		COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()
		#undef COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE
	) {
		
		self->private_data.class_desriptor = genclass_descriptor;
		
		return initialize_impl(
		(genclass_object_impl*)self
		#define COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE(GEN_PARAM_TYPE, GEN_PARAM_NAME)	\
			,GEN_PARAM_NAME
		COBJPVT_GEN_CLASS_PARAMETER_GENERATOR()
		#undef COBJPVT_GEN_CLASS_PARAMETER_TEMPLATE
	);
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	// (3) declare and implement queryinterface
	static cobj_mt queryinterface(const cobj_interface_descriptor * interface);
	static cobj_mt queryinterface(const cobj_interface_descriptor * interface){
				
		#define COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE(GEN_INTERFACE_NAME)	\
			if(interface == COBJ_PP_CONCAT(GEN_INTERFACE_NAME, _descriptor)) \
				return (cobj_mt)(&COBJ_PP_CONCAT(COBJ_CLASS_NAME, _ , GEN_INTERFACE_NAME, _mt));
			
			COBJPVT_GEN_CLASS_INTERFACE_GENERATOR()
		#undef COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE
		
		return (cobj_mt*)0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// (4) generate the class-descriptor
	static const cobj_class_descriptor genclass_descriptor_instance = {
		.class_name = COBJPVT_PP_STRINGIFY(COBJ_CLASS_NAME),
		.queryinterface = &queryinterface		
	};
	
	const cobj_class_descriptor * const genclass_descriptor = &genclass_descriptor_instance;	



#endif


// #undef properties passed
#undef COBJ_CLASS_NAME
#undef COBJ_CLASS_PARAMETERS
#undef COBJ_CLASS_VARIABLES
#undef COBJ_CLASS_INTERFACES
