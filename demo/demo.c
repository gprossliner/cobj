
#include "classes/stdconsole.h"
#include "classes/hw_gpio_pin.h"
#include "classes/gpio_pin_inverter.h"
#include "application/application.h"

// this are the objects needed for the demo on real hardware
static stdconsole console_object;
static hw_gpio_pin input_pin_object;
static hw_gpio_pin output_pin_object;
static gpio_pin_inverter inverted_pin_object;

int main()
{

	// initialize the hardware objects
	stdconsole_initialize(&console_object);
	hw_gpio_pin_initialize(&input_pin_object, 13);
	hw_gpio_pin_initialize(&output_pin_object, 14);

	// get references to interfaces used by the application
	console_queryinterface(&console_object.object, &application_resources.console);
	gpio_pin_queryinterface(&input_pin_object.object, &application_resources.input_pin);

	// the output-pin is driven logically inverted by the electronic schema,
	// so we wrap it in a gpio_pin_inverter to perform this transparent to the application
	gpio_pin pin_physical;
	gpio_pin_queryinterface(&output_pin_object.object, &pin_physical);

	gpio_pin_inverter_initialize(&inverted_pin_object, &pin_physical);
	gpio_pin_queryinterface(&inverted_pin_object.object, &application_resources.output_pin);
	
	// start the show!
	application_run();
}