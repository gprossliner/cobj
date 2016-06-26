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

## cobj is easy, safe and natural to use
Easy: Once you get the macros done (there will be templates provided), everything beside the
implementation is created by the cobj generator (some .h files).

Natural: It generates global functions for each interface, so you don't mess around
with calling functions out of a struct of function pointers.

Safe: Everything is strong typed, so you don't have to cast anywhere to use cobj.

# Entities

cobj basically defines this kind of entities:

## Descriptors
Descriptors are a way for cobj to identity a class or interface. Normally you don't need
to use them directly in your code, but they play an important role how cobj works.
If you are interested, please check out the [CobjPattern](CobjPattern.md) document.
Each descriptor is generated as global variable. Because they are const, they are
normally compiled into program memory. So they use no ram.

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

Further readings:

* [General information about how to use cobj](GeneratorDesign.md)
* [How to define interfaces](InterfaceGenerator.md)
* [How to define classes](ClassGenerator.md)
* [What happends at runtime](CobjPattern.md)
