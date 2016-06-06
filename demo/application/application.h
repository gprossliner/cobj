
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "interfaces/console.h"
#include "interfaces/gpio_pin.h"

struct application_resources{

	console console;
	gpio_pin input_pin;
	gpio_pin output_pin;

};

extern struct application_resources application_resources;

void application_run();


#endif /* APPLICATION_H_ */