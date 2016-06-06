
#define COBJ_IMPLEMENTATION_FILE

#include "hw_gpio_pin.h"

//////////////////////////////////////////////////////////////////////////
// hardware configuration symbols (just those needed for the demo)

#define HW_GPIO_REGISTER_ADDRESS				0xFFFF1000
#define HW_GPIO_REGISTER_SIZE					0x100

typedef struct gpio_port_registerfile {
          unsigned long                  reserved[16];
          unsigned long                  oder      ;//0x0040
          unsigned long                  oders     ;//0x0044
          unsigned long                  oderc     ;//0x0048
          unsigned long                  odert     ;//0x004c
          unsigned long                  ovr       ;//0x0050
          unsigned long                  ovrs      ;//0x0054
          unsigned long                  ovrc      ;//0x0058
          unsigned long                  ovrt      ;//0x005c
          const unsigned long            pvr       ;//0x0060
          unsigned int                   :32       ;//0x0064
          unsigned int                   :32       ;//0x0068
          unsigned int                   :32       ;//0x006c
          unsigned long                  puer      ;//0x0070
          unsigned long                  puers     ;//0x0074
          unsigned long                  puerc     ;//0x0078
          unsigned long                  puert     ;//0x007c
          unsigned long                  pder      ;//0x0080
          unsigned long                  pders     ;//0x0084
          unsigned long                  pderc     ;//0x0088
          unsigned long                  pdert     ;//0x008c
} gpio_port_registerfile;

// helper macros to make the methods easy to read, the depend on the argument "self"
#define GPIO_PORT	((volatile gpio_port_registerfile *)(self->port_address))
#define GPIO_MASK	(self->port_mask)

static bool initialize_impl(hw_gpio_pin_impl * self, int pin_nr)
{
	int port_nr = pin_nr >> 5;
	int pin_offset = pin_nr & 0x1F;

	self->port_address = HW_GPIO_REGISTER_ADDRESS + port_nr * HW_GPIO_REGISTER_SIZE;
	self->port_mask = 1 << pin_offset;

	return true;
}


static bool gpio_pin_get_value_impl(hw_gpio_pin_impl * self)
{
	return (GPIO_PORT->pvr & GPIO_MASK);
}

static void gpio_pin_set_value_impl(hw_gpio_pin_impl * self, bool value)
{
	// enable the output driver
	GPIO_PORT->oders = GPIO_MASK;

	if(value){
		// set the value
		GPIO_PORT->ovrs = GPIO_MASK;
	} else {
		// clear the value
		GPIO_PORT->ovrc = GPIO_MASK;
	}
}

static void gpio_pin_set_options_impl(hw_gpio_pin_impl * self, gpio_pin_options options)
{	
	// reset previous state
	GPIO_PORT->puerc = self->port_mask;
	GPIO_PORT->pderc = self->port_mask;

	switch(options){
		
		case gpio_pin_options_default:
			break;
		
		case gpio_pin_options_pullup:
			GPIO_PORT->puers = self->port_mask;
			break;

		case gpio_pin_options_pulldown:
			GPIO_PORT->pders = self->port_mask;
			break;
	}
}

static void gpio_pin_toggle_impl(hw_gpio_pin_impl * self)
{
	// enable the output driver
	GPIO_PORT->oders = GPIO_MASK;

	// toggle the value
	GPIO_PORT->odert = GPIO_MASK;
}