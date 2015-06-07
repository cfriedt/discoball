#include "discoball/discoball.h"

#include "linux_pinctrl_data.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( ( x )[ 0 ] ) )
#endif

#undef _
#define _( x, y ) PINCTRL_PIN( x, y )
const struct pinctrl_pin_desc foo_pins[] = {
	_(  0, "A8" ), _(  1, "B8" ), _(  2, "C8" ), _(  3, "D8" ), _(  4, "E8" ), _(  5, "F8" ), _(  6, "G8" ), _(  7, "H8" ),
	_(  8, "A7" ), _(  9, "B7" ), _( 10, "C7" ), _( 11, "D7" ), _( 12, "E7" ), _( 13, "F7" ), _( 14, "G7" ), _( 15, "H7" ),
	_( 16, "A6" ), _( 17, "B6" ), _( 18, "C6" ), _( 19, "D6" ), _( 20, "E6" ), _( 21, "F6" ), _( 22, "G6" ), _( 23, "H6" ),
	_( 24, "A5" ), _( 25, "B5" ), _( 26, "C5" ), _( 27, "D5" ), _( 28, "E5" ), _( 29, "F5" ), _( 30, "G5" ), _( 31, "H5" ),
	_( 32, "A4" ), _( 33, "B4" ), _( 34, "C4" ), _( 35, "D4" ), _( 36, "E4" ), _( 37, "F4" ), _( 38, "G4" ), _( 39, "H4" ),
	_( 40, "A3" ), _( 41, "B3" ), _( 42, "C3" ), _( 43, "D3" ), _( 44, "E3" ), _( 45, "F3" ), _( 46, "G3" ), _( 47, "H3" ),
	_( 48, "A2" ), _( 49, "B2" ), _( 50, "C2" ), _( 51, "D2" ), _( 52, "E2" ), _( 53, "F2" ), _( 54, "G2" ), _( 55, "H2" ),
	_( 56, "A1" ), _( 57, "B1" ), _( 58, "C1" ), _( 59, "D1" ), _( 60, "E1" ), _( 61, "F1" ), _( 62, "G1" ), _( 63, "H1" ),
};
#undef _

struct foo_group {
	const char *name;
	const unsigned int *pins;
	const unsigned num_pins;
};

const unsigned int spi0_pins[] = { 0, 8, 16, 24, };
const unsigned int i2c0_pins[] = { 24, 25, };

const struct foo_group foo_groups[] = {
	{
		.name = "spi0_grp",
		.pins = spi0_pins,
		.num_pins = ARRAY_SIZE(spi0_pins),
	},
	{
		.name = "i2c0_grp",
		.pins = i2c0_pins,
		.num_pins = ARRAY_SIZE(i2c0_pins),
	},
};


int foo_get_groups_count( struct pinctrl_dev *pctldev ) {
	return ARRAY_SIZE(foo_groups);
}

const char *foo_get_group_name( struct pinctrl_dev *pctldev, unsigned selector) {
	return foo_groups[selector].name;
}

int foo_get_group_pins( struct pinctrl_dev *pctldev, unsigned selector, const unsigned **pins, unsigned *num_pins) {
	*pins = (unsigned *) foo_groups[selector].pins;
	*num_pins = foo_groups[selector].num_pins;
	return 0;
}

struct pinctrl_ops foo_pctrl_ops = {
	.get_groups_count = foo_get_groups_count,
	.get_group_name = foo_get_group_name,
	.get_group_pins = foo_get_group_pins,
};

int foo_pin_config_get( struct pinctrl_dev *pctldev, unsigned offset, unsigned long *config ) {
	*config = PIN_CONFIG_BIAS_HIGH_IMPEDANCE;
}

int foo_pin_config_set( struct pinctrl_dev *pctldev, unsigned offset, unsigned long config ) {
	switch ( config ) {
	case PIN_CONFIG_BIAS_DISABLE:
		break;
	case PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		break;
	case PIN_CONFIG_DRIVE_PUSH_PULL:
		break;
	case PIN_CONFIG_DRIVE_OPEN_DRAIN:
		break;
	case PIN_CONFIG_DRIVE_OPEN_SOURCE:
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		break;
	case PIN_CONFIG_INPUT_SCHMITT:
		break;
	case PIN_CONFIG_INPUT_DEBOUNCE:
		break;
	case PIN_CONFIG_POWER_SOURCE:
		break;
	case PIN_CONFIG_SLEW_RATE:
		break;
	case PIN_CONFIG_LOW_POWER_MODE:
		break;
	case PIN_CONFIG_OUTPUT:
		break;
	default:
		break;
	}

	return 0;
}

int foo_pin_config_group_get( struct pinctrl_dev *pctldev, unsigned selector, unsigned long *config ) {
	return 0;
}

int foo_pin_config_group_set( struct pinctrl_dev *pctldev, unsigned selector, unsigned long config ) {
	return 0;
}

struct pinconf_ops foo_pconf_ops = {
	.pin_config_get = foo_pin_config_get,
	.pin_config_set = foo_pin_config_set,
	.pin_config_group_get = foo_pin_config_group_get,
	.pin_config_group_set = foo_pin_config_group_set,
};

struct pinctrl_desc foo_desc = {
	.name = "foo",
	.pins = foo_pins,
	.npins = ARRAY_SIZE(foo_pins),
	.owner = NULL,
	.pctlops = &foo_pctrl_ops,
	.confops = &foo_pconf_ops,
};
