
#define COBJ_IMPLEMENTATION_FILE

#include "gpio_pin_inverter.h"

static bool initialize_impl(gpio_pin_inverter_impl * self, gpio_pin * pin)
{
	self->pin = pin;
	return true;
}

static bool gpio_pin_get_value_impl(gpio_pin_inverter_impl * self)
{
	return !gpio_pin_get_value(self->pin);	
}

static void gpio_pin_set_value_impl(gpio_pin_inverter_impl * self, bool value)
{
	gpio_pin_set_value(self->pin, !value);
}

static void gpio_pin_set_options_impl(gpio_pin_inverter_impl * self, gpio_pin_options options)
{
	gpio_pin_set_options(self->pin, options);
}

static void gpio_pin_toggle_impl(gpio_pin_inverter_impl * self)
{
	gpio_pin_toggle(self->pin);
}