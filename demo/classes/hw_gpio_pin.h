
#ifndef HW_GPIO_PIN_H_
#define HW_GPIO_PIN_H_


#define COBJ_CLASS_NAME	hw_gpio_pin

#define COBJ_CLASS_PARAMETERS	\
	COBJ_CLASS_PARAMETER(int, pin_nr)

#define COBJ_CLASS_VARIABLES	\
	COBJ_CLASS_VARIABLE(int, port_address)	\
	COBJ_CLASS_VARIABLE(int, port_mask)	\

#define COBJ_CLASS_INTERFACES	\
	COBJ_CLASS_INTERFACE(gpio_pin)	\

#define COBJ_INTERFACE_IMPLEMENTATION_MODE
#include "interfaces/gpio_pin.h"
#undef  COBJ_INTERFACE_IMPLEMENTATION_MODE

#include "cobj-classheader-generator.h"



#endif /* HW_GPIO_PIN_H_ */