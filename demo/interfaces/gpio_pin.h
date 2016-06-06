
#ifndef GPIO_PIN_H_
#define GPIO_PIN_H_

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