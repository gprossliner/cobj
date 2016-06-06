# The interface generator (cobj-interface-generator.h)
This is a tutorial / reference about the interface generator. Please check out
[GeneratorDesign](GeneratorDesign.md) for general information about the
generators.

## What makes an interface?

An interface is a simple structure, as it only consists or a name (COBJ_INTERFACE_NAME) and  one or more method (COBJ_INTERFACE_METHODS).

An interface has to be placed in a single .h file.

## Limits
* The number of methods for a single interface is unlimited.
* Because cobj needs to handle the number of arguments explicitly, there is
currently a limit of 16 arguments for a single method. If you need more
please file an issue.

## Syntax
### Interface Name
The name of the interface is defined by the "COBJ_INTERFACE_NAME" symbol. I must
expand to a valid identifier.

### Methods
The methods of the interface are defined by the "COBJ_INTERFACE_METHODS" x-macro,
which use the COBJ_INTERFACE_METHOD macro, with the following arguments:

COBJ_INTERFACE_METHOD(return_type, method_name [, arguments] )

Each argument must specify a type and a name, separated by a comma. You can use
any modifier on the type (like * ,const, unsigned, ....).

** IMPORTANT: ** Please note that is required to put the comma between the type and the name! Otherwise cobj would not be able to extract the name, because there is no ways
(at least not known to me), to split a "string" by whitespace in a macro.

```C
COBJ_INTERFACE_METHOD(void, foo)  /* the most basic method */
COBJ_INTERFACE_METHOD(void, foo, int, j) /* method taking a single int arg */
COBJ_INTERFACE_METHOD(void*, foo, const int*, a, unsigned long, b) /* with modifiers */

```


## Example:

```C
#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

// define the name of the interface.
// It's recommended that is matches the name of the .h file.
#define COBJ_INTERFACE_NAME	gpio_pin

// define the methods of the interface
#define COBJ_INTERFACE_METHODS	\
	COBJ_INTERFACE_METHOD(bool, get_value) \
	COBJ_INTERFACE_METHOD(void, set_value, bool, value)

// call the generator
#include "cobj-interface-generator.h"


#endif /* GPIO_PIN_H_ */
```

## More advanced example

A interface may need to declare other things, beside the code that is generated
by cobj. This just have to follow the rules in C. So if you need another included header,
or a forward declaration, or a typedef, ... just put it before the generator:

In the modified example we need a typedef for an enum, and a the stdbool.h header:

```C
#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

#include <stdbool.h>

typedef enum gpio_pin_options {
	gpio_pin_options_default,
	gpio_pin_options_pullup,
	gpio_pin_options_pulldown
} gpio_pin_options;

#define COBJ_INTERFACE_NAME	gpio_pin

#define COBJ_INTERFACE_METHODS	\
	COBJ_INTERFACE_METHOD(bool, get_value) \
	COBJ_INTERFACE_METHOD(void, set_value, bool, value)	\
	COBJ_INTERFACE_METHOD(void, set_options, gpio_pin_options, options) \
	COBJ_INTERFACE_METHOD(void, toggle)	\

#include "cobj-interface-generator.h"


#endif /* GPIO_PIN_H_ */
```
## What about varargs (...)?
Because cobj need to perform indirect calls for every interface method, using ...
directly is not possible, as it's not possible in C. So you can't write a function
with ... and pass it for example to printf. You have to use the vprintf function, taking
a va_list.

This is very possible in cobj. You may declare an "entry method" with ..., which
calls the va_list version, like:

```C
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

```

## The interface registry
cobj needs to generate some code for each interface, the descriptor and the callable
(none-static) entry methods.

You don't need to create one .c file for each interface, because normally you don't
need to write any own code for this. You can split it up to serveral files, as long
as each interface is included in exact one registry file.

If you use a single .c file, it's recommended to name it "interface_registry.c".
You don't need a .h file for this, because the declarations are within every
.h file.

You have to define the COBJ_INTERFACE_REGISTRY_MODE symbol before including the
.h files of the interfaces.

### Example
```C

// define the COBJ_INTERFACE_REGISTRY_MODE symbol
#define COBJ_INTERFACE_REGISTRY_MODE

// include the interfaces
#include "gpio_pin.h"

```
