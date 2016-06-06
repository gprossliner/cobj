# The class generator (cobj-classheader-generator.h)
This is a tutorial / reference about the class generator. Please check out
[GeneratorDesign](GeneratorDesign.md) for general information about the
generators.

## What makes a class?
A Class has the following properties:
* COBJ_CLASS_NAME: specifies the name of the class. The same rule applies as for the name of interfaces
* COBJ_CLASS_PARAMETERS: x-macro to specify arguments for the initialize
method.
* COBJ_CLASS_VARIABLES: x-macro to specify the variables private to each
instance of the class (each object).
* COBJ_CLASS_INTERFACES: x-macro to specify which interfaces are implemented
by the class.

## Limits
cobj introduces no specific limits for the properties of a class.

## Syntax

### Class Name
The name of the interface is defined by the "COBJ_INTERFACE_NAME" symbol. I must
expand to a valid identifier.

The parameters of the interface are defined by the "COBJ_CLASS_PARAMETERS" x-macro,
which use the COBJ_CLASS_PARAMETER macro, with the following arguments:

### Parameters of the initialize method
To specify parameters of the initialize() method, use the COBJ_CLASS_PARAMETERS
x-macro, and define zero or more COBJ_CLASS_PARAMETER(return_type, parameter_name)
macros.

### Class Variables
To specify private variables for the class, use the COBJ_CLASS_VARIABLES
x-macro, and define zero or more COBJ_CLASS_VARIABLE(return_type, parameter_name)
macros.

### Implemented Interfaces
A single must implement one to many interfaces. This requires two actions:

1. The interfaces must be specified in the COBJ_CLASS_INTERFACES x-macro, using
the COBJ_CLASS_INTERFACE(interface_name). The interface_name argument must match
the COBJ_INTERFACE_NAME definition in the .h file.

2. You must include the .h file of the interface, while defining the COBJ_INTERFACE_IMPLEMENTATION_MODE symbol.

## Example

```C

// include guard
#ifndef HW_GPIO_PIN_H_
#define HW_GPIO_PIN_H_

// define the name of the class
// It's recommended that is matches the name of the .h file.
#define COBJ_CLASS_NAME	hw_gpio_pin

// define the parameters of the initialize method
#define COBJ_CLASS_PARAMETERS	\
	COBJ_CLASS_PARAMETER(int, pin_nr)

// define the private variables
#define COBJ_CLASS_VARIABLES	\
	COBJ_CLASS_VARIABLE(int, port_address)	\
	COBJ_CLASS_VARIABLE(int, port_mask)	\

// define the implemented interfaces
#define COBJ_CLASS_INTERFACES	\
	COBJ_CLASS_INTERFACE(gpio_pin)	\

// include the implemented interfaces
#define COBJ_INTERFACE_IMPLEMENTATION_MODE
#include "interfaces/gpio_pin.h"
#undef  COBJ_INTERFACE_IMPLEMENTATION_MODE

// call the generator
#include "cobj-classheader-generator.h"


#endif /* HW_GPIO_PIN_H_ */
```

## The .c file
Classes must have there implementation within a single .c file. It's recommended
to use the name of the class for the filename.

## Guildlines:
* All cobj methods within the implementation uses the "_impl" suffix
* Every _impl method has a pointer to instance of  the class (the object)
as the first argument named "self". It also uses the _impl suffix, so "hw_pin"
becomes "hw_pin_impl".
* Every method in each implemented interface needs to be implemented. The name
is build by using this pattern: INTERFACENAME_METHODNAME_impl, so the "get_value"
method of the "gpio_pin" interfaces becomes "gpio_pin_get_value(hw_gpio_pin * self)"
* You have to implement the "initialize" method as "initialize_impl(self, args)".
The class_descriptor is initialize automatically, all private variables need
to be initialized by the implementation.
* All _impl method are static.
* You must define the COBJ_IMPLEMENTATION_FILE symbol before including any
.h files of implemented interfaces.

## Example

```C

#define COBJ_IMPLEMENTATION_FILE

#include "hw_gpio_pin.h"

static bool initialize_impl(hw_gpio_pin_impl * self, int pin_nr)
{
  // implementation
}

static bool gpio_pin_get_value_impl(hw_gpio_pin_impl * self)
{
	// implementation
}

static void gpio_pin_set_value_impl(hw_gpio_pin_impl * self, bool value)
{
  // implementation
}

static void gpio_pin_set_options_impl(hw_gpio_pin_impl * self, gpio_pin_options options)
{
  // implementation
}

static void gpio_pin_toggle_impl(hw_gpio_pin_impl * self)
{
  // implementation
}


```
