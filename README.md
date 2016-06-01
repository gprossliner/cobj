# cobj

cobj allows to implement interface based polymorphism in plain C. It's a pattern, and a generator, based on the preprocessor.

## Features

cobj enables developers to use a simple and comfortable way to implement polymorphism, based on interfaces and classes.

## cobj is no runtime
This means that cobj don't care about allocation, managing lifetime, serialization or error-handling.
It's just a way to call methods on an object. In opposite to other implementations, which often require that objects are on the heap, maybe including garbage collection or reference counting, in cobj you have total control over your objects.

## cobj uses only the preprocessor
There is no external code-generator, build step or any other tool needed beside
the C compiler. The cobj generator is heavily based on the x-macro technique, to
generate the code needed.

## cobj wants to be easy, safe and natural to use
Easy: Once you get the macros done (there will be templates provided), everything beside the
implementation is created by the cobj generator (some .h files).

Natural: It generates global functions for each interface, so you don't mess around
with calling functions out of a struct of function pointers.

Safe: Everything is strong typed, so you don't have to cast anywhere to use cobj.

# Entities

cobj basically defines this kind of entities:

## Descriptors
A descriptor is a global variable, which describes an interface,
or a class. Because they are const, they are normally compiled into program memory.
So they use no ram.

## Interfaces
An interface represents a named set of method prototypes, without implementation.

## Classes

A class consists of the following parts:

* Implemented interfaces: A class is the entity implementing one ore more interfaces.
* Variables: A class may declare variables, which represent the private state of the object.
* Arguments for the initializer: To avoid that a "private interface" needs to be
defined just for the initialization of an object, cobj classes can define a single
initialization method.

## Objects

An object is an instance of a class. It's basically a struct, consisting of a pointer to the class-descriptor, and every declared variable.

## References
Beside the initializer, no method can be directly called on an object. This is what
references are for. A reference is initialized by calling a "queryinterface" method
for a specific interface, providing a pointer to an object.

Once you got a reference, you may call interface-methods, pass them around, and
do whatever you like.

# Some code
I'm sure you want to see some code, right? I'll show you how to declare interfaces
and classes afterwards. This is how to use cobj once that is done:

```C

// We have declared an interface named "gpio_pin", declaring a method:
// 	bool read_value()
// We have class named "hw_gpio_pin" implementing this interface
//	The "hw_gpio_pin" has an initializer "int pin_nr"

void foo()
{
	// create a hw_gpio_pin on the stack:
	hw_gpio_pin pinObject;

	// call the initializer for pin #13
	hw_gpio_pin_initialize(&pinObject, 13);

	// to call the "get_value" function of the "gpio_pin" interface, we have to
	// query for a reference:

	gpio_pin pinReference;
	gpio_pin_queryreference(pinObject.object, &pinReference);

	bar(pinReference);
}

void bar(gpio_pin pin)
{
	// read the pin value:
	bool val = gpio_pin_get_value(pin);
}

```

# What happens at runtime?

I'll take the previous example to show you want's going on in cobj.

## For the gpio_pin interface:
Once you have the "gpio_pin", you have the following code be generated in
every file which does a #include "gpio_pin.h":

```C
// this is the struct of function-pointers for the interface, _mt stands for
// "methodtable"
typedef struct {
   bool (* get_value)(cobj_object * self)
} gpio_pin_mt;

// this is the strong typed reference struct for any gpio-pin. Because References
// are used very often, there is no _reference suffix. A reference is an instance
// of an interface, so I find it better this way.
typedef struct {
 gpio_pin_mt * mt;
 cobj_object * object;
} gpio_pin;

// this is the declaration to the global descriptor
extern const cobj_interface_descriptor * const gpio_pin_descriptor;

// this is the declaration to the queryinterface method
bool gpio_pin_queryinterface(cobj_object * object, gpio_pin * reference);

// now the declarations of the callable methods follow, we have just one:
bool gpio_pin_get_value(const gpio_pin * reference);

```

## For the hw_gpio_pin class:
The following code is generated into files including hw_gpio_pin.h:

```C

// This is the struct for the object's data. The class_desriptor is always the
// first field in this structure. To allow inline allocation of an object,
// the size of the object must be known to the compiler, this also includes
// padding and alignment, so it's not wise to use char[sum of sizeof all variables].
// Because of this, the variables are generated as they are into a struct,
// but with symbolic names. So we know that this class as two integer fields
// for it's variables. Why don't allow C unnamed struct members in such a case...
typedef union {
 struct {
  const cobj_class_descriptor * class_desriptor;
  struct {
		int private_0;
		int private_1;
  } class_data;
 } private_data;
 cobj_object object;
} hw_gpio_pin;

// declare the descriptor for the class:
extern const cobj_class_descriptor * const hw_gpio_pin_descriptor;

// declare the initializer for the class:
void hw_gpio_pin_initialize(hw_gpio_pin * self, int pin_nr);

```

To see the whole picture, you need to know the implementation of initialize,
queryinterface and the callable methods:

The first thing: You see some declarations in gpio_pin.h. But wait: This is just
a .h file, where is the implementation?

In every project there is a single file named "interface_registry.c". Technically
it don't have to be in a single file. You may split it up in several files. As long
as every used interface is in exact one registry file, it's ok:

```C

// a registry only enables registry mode, and then includes the .h files
// of all interfaces
#define COBJ_INTERFACE_REGISTRY_MODE
#include "gpio_pin.h"
#undef  COBJ_INTERFACE_REGISTRY_MODE

// this causes the following code to be generated:
/////////////////////////////////////////////////////

// queryinterface method
bool gpio_pin_queryinterface(cobj_object * object, gpio_pin * reference) {
  cobj_mt mt = object->class_descriptor->queryinterface(gpio_pin_descriptor);
  if(!mt){
   return false;
  }

  reference->mt = (gpio_pin_mt*)mt;
  reference->object = object;

  return true;
 }

// callable methods (we have just one):
bool gpio_pin_get_value(const gpio_pin * reference )
{
	return reference->mt->get_value(reference->object);
}

```
The last thing we need to know for the basic understanding, is the hw_gpio_pin.c
file:

```C

// this code I have to write
#define COBJ_IMPLEMENTATION_FILE

#include "hw_gpio_pin.h"	// technically all code below is generated here!

// this is the initialize method. It's static as every other _impl method!
static bool initialize_impl(hw_gpio_pin_impl * self, int pin_nr)
{
	// I can do what I want, just initialize some register addresses
	self->port_address = 0x7FFF1000 + (pin_nr << 5) * 0x100;
	self->port_mask = 1 << (pin_nr & 0x20);
	return true;
}

// this is our implementation of the get_value method:
static bool gpio_pin_get_value_impl(hw_gpio_pin_impl * self)
{
	// access some gpio register here to read the value
	volatile int * pvr = self->port_address + 0x10;
	return (* pvr && self->port_mask) != 0;
}

// this code is being generated:
/////////////////////////////////////////////////////

// our _impl object structure, with the real names of the variables:
typedef struct {
  cobj_class_descriptor * class_desriptor;
  int portNr;
	int portMask;
 } hw_gpio_pin_impl;

// forward declarations to the _impl functions:
static bool gpio_pin_get_value_impl(hw_gpio_pin_impl* self);

// forward declarations to the _thunk functions:
static bool gpio_pin_get_value_thunk(cobj_object* self )

// implementations of the _thunk functions (they basically perform the cast)
static bool gpio_pin_get_value_thunk(cobj_object * self ) {
	return gpio_pin_get_value_impl((hw_gpio_pin_impl*)self );
}

// a _mt struct for each implemented interface:
static const gpio_pin_mt hw_gpio_pin_gpio_pin_mt =
  .get_value = &gpio_pin_get_value_thunk,
 };

// forward declaration to the initialize_impl function:
static bool initialize_impl(hw_gpio_pin_impl * self, int portNr);

// implementation of the initialize function:
bool hw_gpio_pin_initialize(hw_gpio_pin * self, int portNr)
{
  self->private_data.class_desriptor = hw_gpio_pin_descriptor;
  return initialize_impl((hw_gpio_pin_impl*)self, portNr);
}

// forward declaration of queryinterface:
static cobj_mt queryinterface(const cobj_interface_descriptor * interface);

// implementation of queryinterface:
static cobj_mt queryinterface(const cobj_interface_descriptor * interface){
	if(interface == gpio_pin_descriptor) return (cobj_mt)(&hw_gpio_pin_gpio_pin_mt);
  return (cobj_mt*)0;
 }

// and finally, the descriptor:
static const cobj_class_descriptor hw_gpio_pin_descriptor_instance = {
  .class_name = "hw_gpio_pin",
  .queryinterface = &queryinterface
 };

 const cobj_class_descriptor * const hw_gpio_pin_descriptor = &hw_gpio_pin_descriptor_instance;

```


In the next chapter I'll show you how to declare this things!
