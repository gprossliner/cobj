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

#ifndef COBJ_COMMON_H_
#define COBJ_COMMON_H_

//////////////////////////////////////////////////////////////////////////
// standard includes (we need size_t and bool)
#include <stddef.h>

//////////////////////////////////////////////////////////////////////////
// base declarations
typedef void * cobj_mt;

//////////////////////////////////////////////////////////////////////////
// core descriptor types

typedef const char * cobj_descriptor_string;

typedef struct {
	cobj_descriptor_string interface_name;
	size_t methods_count;
} cobj_interface_descriptor;

typedef struct {
	cobj_descriptor_string class_name;
	cobj_mt (*queryinterface)(const cobj_interface_descriptor * interface);
	size_t object_size;
} cobj_class_descriptor;

//////////////////////////////////////////////////////////////////////////
// core object and reference types

typedef struct {
	
	// the first member of an object is always a pointer to it's class_descriptor
	const cobj_class_descriptor * class_descriptor;
	
	// object data follows here, but they are never accessed in a generic way.
	//
	//	* when an interface method is called on an cobj_object, the following steps are taken
	//		- the user always need a reference to the interface, which is retrieved by theinterface_queryinterface
	//		theinterface_queryinterface(object, theinterface_reference);
	//		- user calls the interface method implemented in the interface-registry, it takes the reference as the argument
	//		theinterface_foo(theinterface_reference);
	//		- in the generated method, the method is called indirectly from the method-table:
	//		theinterface->mt->foo(theinterface->object);
	//		- in the generated thunk, the cobj_object* object is casted to the struct containing the variables,
	//		this is used to call the implementation method:
	//		return theinterface_foo_impl((theclass*)object)
	char object_data[];
	
} cobj_object;

typedef struct {
	cobj_mt mt;
	cobj_object * object;
} cobj_reference;



#endif /* COBJ_COMMON_H_ */