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

#include "cobj.h"
#include "cobjpvt-pp.h"
#include "cobjpvt-generator-helper.h"

//////////////////////////////////////////////////////////////////////////
// #define the names used generators for interface "geninterface"
// 

#define geninterface_mt COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _mt)
#define geninterface_reference COBJ_INTERFACE_NAME
#define geninterface_descriptor COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _descriptor)
#define geninterface_descriptor_instance COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _descriptor_instance)
#define geninterface_queryinterface COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _queryinterface)


//////////////////////////////////////////////////////////////////////////
// Generate the declarations. They are always generated when the geninterface.h is included.
// They don't require a special state of the generator.

// (1) mt (methodtable) struct declaration
typedef struct {
	
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		GEN_RETURN_TYPE (*GEN_METHODNAME)(cobj_object * self GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE);
			COBJPVT_GEN_METHOD_GENERATOR()
		
			/*
				Common Error:
				expected ';', ',' or ')' before 'COBJPVT_GEN_METHOD_ARGS_SEPERATOR_1' or any odd number:

				Cause:
				The syntax of the COBJ_INTERFACE_METHOD is invalid, because the parameter list must always contain pairs values.
				You may be missing the comma between the type and the name.

				Resolution:
				Insert a comma between the type and the name, like:
				Wrong: COBJ_INTERFACE_METHOD(void, foo, int i)
				Right: COBJ_INTERFACE_METHOD(void, foo, int, i)
			*/

			/*
				Common Error:
				expected ';', ',' or ')' before 'COBJPVT_GEN_METHOD_ARGS_SEPERATOR_36':

				Cause:
				You have defined a COBJ_INTERFACE_METHOD with more than 16 arguments. This is currently not supported,
				if you need it, please file an issue!

				Resolution:
				Refactor the method to use not more than 16 arguments, for example put some arguments into a struct.

			*/

	#undef COBJPVT_GEN_METHOD_TEMPLATE	
	
} geninterface_mt;

// (2) strong-typed reference-struct
typedef struct {
	geninterface_mt * mt;
	cobj_object * object;
} geninterface_reference;

// (3) forward-declaration to the descriptor
extern const cobj_interface_descriptor * const geninterface_descriptor;

// (4) forward-declaration to strong-typed query-interface
bool geninterface_queryinterface(cobj_object * object, geninterface_reference * reference);

// (5) forward declarations to thunks
#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
	GEN_RETURN_TYPE COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME)(const geninterface_reference * reference GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE);
	
	COBJPVT_GEN_METHOD_GENERATOR()
#undef COBJPVT_GEN_METHOD_TEMPLATE

//////////////////////////////////////////////////////////////////////////
// Create the implementation

//////////////////////////////////////////////////////////////////////////
//	Context selective selection macros, see issues #8 & #13
//	These replace COBJ_INTERFACE_IMPLEMENTATION_MODE, and updates COBJ_IMPLEMENTATION_FILE with an arg

#ifndef COBJ_CLASS_INTERFACES
#	define COBJPVT_CLASS_INTERFACES_EMPTY_DEFINE
#	define COBJ_CLASS_INTERFACES	// this is to avoid that if COBJ_CLASS_INTERFACES not not defined, the preprocessor in #if expands to #if 0 0
#endif

#define COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE(GEN_INTERFACE_NAME) \
	|| COBJ_PP_CONCAT(GEN_INTERFACE_NAME, _COBJ_ID) == COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _COBJ_ID)

#define COBJ_INTERFACE_IMPLEMENTATION_MODE()	\
	0 COBJPVT_GEN_CLASS_INTERFACE_GENERATOR()

#if COBJ_INTERFACE_IMPLEMENTATION_MODE()
// cleanup COBJ_INTERFACE_IMPLEMENTATION_MODE()
#undef  COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE
#ifdef COBJPVT_CLASS_INTERFACES_EMPTY_DEFINE
#	undef COBJ_CLASS_INTERFACES
#	undef COBJPVT_CLASS_INTERFACES_EMPTY_DEFINE
#endif
#undef COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE

#define COBJ_CLASS_IMPLEMENTATION_MODE()	\
	COBJ_PP_CONCAT(COBJ_IMPLEMENTATION_FILE, _COBJ_ID) == COBJ_PP_CONCAT(COBJ_CLASS_NAME, _COBJ_ID)
#if COBJ_CLASS_IMPLEMENTATION_MODE()

	// we need the #defines for the names here
	#include "cobjpvt-generator-class-defines.h"

	//////////////////////////////////////////////////////////////////////////
	// (1) strong typed object_struct
	//	This struct is also in cobj-classheader-generator.h! See the comments here and there!
	#ifndef COBJPVT_GEN_OBJECT_STRUCT_GENERATED
		#define COBJPVT_GEN_OBJECT_STRUCT_GENERATED
		// here we are already define our object-struct, because we need it for the thunks
	typedef struct {
		cobj_class_descriptor * class_desriptor;
		#define COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE(GEN_VARIABLE_TYPE, GEN_VARIABLE_NAME)	\
			GEN_VARIABLE_TYPE GEN_VARIABLE_NAME;
		COBJPVT_GEN_CLASS_VARIABLE_GENERATOR()
		#undef COBJPVT_GEN_CLASS_VARIABLE_TEMPLATE	
	} genclass_object_impl;
	#endif

	//////////////////////////////////////////////////////////////////////////
	// (1) declare the implementation methods
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		static GEN_RETURN_TYPE COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME, _impl)(genclass_object_impl* self GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE);
			
		COBJ_INTERFACE_METHODS
	#undef COBJPVT_GEN_METHOD_TEMPLATE

	//////////////////////////////////////////////////////////////////////////
	// (2) declare thunks
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		static GEN_RETURN_TYPE COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME, _thunk)(cobj_object* self GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE);
			
		COBJ_INTERFACE_METHODS
	#undef COBJPVT_GEN_METHOD_TEMPLATE

	//////////////////////////////////////////////////////////////////////////
	// (3) implement thunks
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		static GEN_RETURN_TYPE COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME, _thunk)(cobj_object * self GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE) {	\
			GEN_RETURN_STATEMENT COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME, _impl)((genclass_object_impl*)self GEN_ARGS_SEPERATOR GEN_ARGS_NAME);	\
		}
			
		COBJ_INTERFACE_METHODS

		/*
			Common Error:
			src.o: In function `interface_method_thunk':
			undefined reference to `interface_method_impl'

			Cause:
			You are missing the implementation of the method of an interface in a class. The .o file specifies which class.

			Solution:
			Implement the method with the following signature:

			static RETURN_TYPE interface_method_impl(CLASS_NAME_impl * self [argument-list])
			{
				...
			}
		*/




	#undef COBJPVT_GEN_METHOD_TEMPLATE
	
	//////////////////////////////////////////////////////////////////////////
	// (4) build the MethodTable, to the thunks
	
	static const geninterface_mt COBJ_PP_CONCAT(COBJ_CLASS_NAME, _ , geninterface_mt) = {
	
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		.GEN_METHODNAME = &COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME, _thunk),
			
		COBJ_INTERFACE_METHODS
	#undef COBJPVT_GEN_METHOD_TEMPLATE
	
	};
	
#endif
#else
// cleanup COBJ_INTERFACE_IMPLEMENTATION_MODE()
#undef  COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE
#ifdef COBJPVT_CLASS_INTERFACES_EMPTY_DEFINE
#	undef COBJ_CLASS_INTERFACES
#	undef COBJPVT_CLASS_INTERFACES_EMPTY_DEFINE
#endif
#undef COBJPVT_GEN_CLASS_INTERFACE_TEMPLATE
#endif

//////////////////////////////////////////////////////////////////////////
//	Generate interface-registry for this interface
#ifdef COBJ_INTERFACE_REGISTRY_MODE
	
	// (1) implement strong-typed query-interface
	bool geninterface_queryinterface(cobj_object * object, geninterface_reference * reference) {
		cobj_mt mt = object->class_descriptor->queryinterface(geninterface_descriptor);
		if(!mt){
			return false;
		}
		
		reference->mt = (geninterface_mt*)mt;
		reference->object = object;
		
		return true;
	}

	// (2) implement thunks
	#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
		GEN_RETURN_TYPE COBJ_PP_CONCAT(COBJ_INTERFACE_NAME, _, GEN_METHODNAME)(const geninterface_reference * reference GEN_ARGS_SEPERATOR GEN_ARGS_SIGNATURE) {	\
			GEN_RETURN_STATEMENT reference->mt->GEN_METHODNAME(reference->object GEN_ARGS_SEPERATOR GEN_ARGS_NAME);	\
		}
	
	COBJPVT_GEN_METHOD_GENERATOR()
	#undef COBJPVT_GEN_METHOD_TEMPLATE
	
	// (3) implement the descriptor
	static const cobj_interface_descriptor geninterface_descriptor_instance = {
		.interface_name = COBJPVT_PP_STRINGIFY(COBJ_INTERFACE_NAME),
		.methods_count = 0
		#define COBJPVT_GEN_METHOD_TEMPLATE(GEN_RETURN_STATEMENT, GEN_RETURN_TYPE, GEN_METHODNAME,  GEN_ARGS_SEPERATOR, GEN_ARGS_SIGNATURE, GEN_ARGS_NAME)	\
			+1	
		COBJPVT_GEN_METHOD_GENERATOR()
		#undef COBJPVT_GEN_METHOD_TEMPLATE		
	};
	
	const cobj_interface_descriptor * const geninterface_descriptor = &geninterface_descriptor_instance;

#endif

// cleanup dynamic names
#undef geninterface_mt
#undef geninterface_mt_struct
#undef geninterface_reference
#undef geninterface_descriptor

// #undef properties passed
#undef COBJ_INTERFACE_NAME
#undef COBJ_INTERFACE_METHODS

