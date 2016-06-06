
#include "application.h"

struct application_resources application_resources;

void application_run()
{
	console_printf(&application_resources.console, "hello world!");

	bool value = gpio_pin_get_value(&application_resources.input_pin);
	gpio_pin_set_value(&application_resources.output_pin, !value);
}