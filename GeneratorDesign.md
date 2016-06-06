# Design notes
This file documents the overall design of the cobj generator.

## Nameing conventions
All code entities declared by cobj start with the cobj_ prefix. It follows the
general C conventions, to use uppercase (COBJ_) for macros.

### Private declarations
As most frameworks, cobj needs some things for it's own, private, use. These
use the COBJPVT_, or cobjpvt_ (there are currently none) prefix.

You should not use the private declarations in your code!

## The x-macro technique
The cobj generator is based on the x-macro technique. This may be the only
way to express something as lists in macros (like the list or methods, variables, ...).

It's base on the following pattern:

* You define a symbol which uses another macro for the definition of the list:

```C
#define METHODS METHOD(foo) METHOD(bar)
```

* By a definition of the METHOD(name) macro, to provide a "pattern" for
a following instantiation:

```C
#define METHOD(name) void name(void);
```

* You call the METHODS symbol, which is expanded in two METHOD() macros,
which themself get expanded the way definied by METHOD(name):

```C
METHODS

// this yields to:
void(foo);
void(bar);
```

* The METHODS symbol is still definied, so you can redefine the METHOD(name) macro, to generate code again, based on another pattern:

```C
#define METHOD(name) void name(void) { }

METHODS

// this yields to:
void(foo);
void(bar);
```

## The \ character to make the improve readability of definitions
C allows preprocessor definitions to span multiple lines, while the backslash character
is used as a line-continuation marker (https://gcc.gnu.org/onlinedocs/gcc-3.0.1/cpp_3.html)

cobj makes use of it, and you may also use it for your definitions, because it's more
readable. Otherwise for example you would have to put all method definitions into a
single line.

The previous example could be written as:

```C
#define METHODS \
  METHOD(foo) \
  METHOD(bar)
```

Please note that you can't use c++ style comments (// comment ) in middle of multiline
macros, because the compiler would not "see" the \ within the comment. So

```C
#define METHODS \
  METHOD(foo) // not ok \
  METHOD(bar)

  #define METHODS \
    METHOD(foo) /* ok */ \
    METHOD(bar)
```

## Overall declaration pattern

For declarations you always use the same pattern:

```C

// define symbols used by the generator:
#define COBJ_INTERFACE_NAME gpio_pin
#define COBJ_INTERFACE_METHODS	\
	COBJ_INTERFACE_METHOD(bool, get_value) \
	COBJ_INTERFACE_METHOD(void, set_value, bool, value)

// call the generator by #include:
#include "cobj-interface-generator.h"

```

Please note that the generator #undef the COBY_ symbols automatically,
you don't use them directly after calling the generator.

To learn how to use the interface or class generator, checkout this links:

[InterfaceGenerator: How to define interfaces](InterfaceGenerator.md)
[ClassGenerator: How to define classes](ClassGenerator.md)
