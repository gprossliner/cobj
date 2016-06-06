
#ifndef GPIO_PIN_INVERTER_H_
#define GPIO_PIN_INVERTER_H_

#define COBJ_CLASS_NAME	gpio_pin_inverter

#define COBJ_CLASS_PARAMETERS	\
	COBJ_CLASS_PARAMETER(gpio_pin *, pin)

#define COBJ_CLASS_VARIABLES	\
	COBJ_CLASS_VARIABLE(gpio_pin *, pin)	\

#define COBJ_CLASS_INTERFACES	\
	COBJ_CLASS_INTERFACE(gpio_pin)	\


#define COBJ_INTERFACE_IMPLEMENTATION_MODE
#	include "interfaces/gpio_pin.h"
#undef  COBJ_INTERFACE_IMPLEMENTATION_MODE


#include "cobj-classheader-generator.h"


#endif /* GPIO_PIN_INVERTER_H_ */