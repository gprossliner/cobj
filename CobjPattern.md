# The cobj Pattern
I'll take the previous example to show you want's going on in cobj.

## For the gpio_pin interface:
Once you have the "gpio_pin", you have the following code be generated in
every file which does a #include "gpio_pin.h":

```C
// this is the struct of function-pointers for the interface, _mt stands for
// "methodtable"
typedef struct {
   bool (* get_value)(cobj_object * self),
   void (* set_value)(cobj_object * self),
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

// now the declarations of the callable methods follow
bool gpio_pin_get_value(const gpio_pin * reference);
void gpio_pin_set_value(const gpio_pin * reference, bool value);


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
	self->port_address = 0xFFFF1000 + (pin_nr << 5) * 0x100;
	self->port_mask = 1 << (pin_nr & 0x1F);
	return true;
}

// this is our implementation of the get_value method:
static bool gpio_pin_get_value_impl(hw_gpio_pin_impl * self)
{
	// access some gpio register here to read the value
	volatile int * pvr = self->port_address + 0x60;
	return (* pvr && self->port_mask) != 0;
}

// this is our implementation of the set_value method:
static void gpio_pin_set_value_impl(hw_gpio_pin_impl * self, bool value)
{
	// enable driver
  * ((volatile int)(self->port_address + 0x44)) = self->port_mask;

  // set or clear value
  * ((volatile int)(self->port_address + (value ? 0x54 : 0x58))) = self->port_mask;
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
