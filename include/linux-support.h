#ifndef INCLUDE_SUPPORT_H_
#define INCLUDE_SUPPORT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef DISCOBALL_INTERNAL_H_
#error support.h is not meant to be included on its own. Please include discoball_internal.h instead
#endif

// PINCONF

#define CONFIG_GENERIC_PINCONF
#define CONFIG_OF
#define CONFIG_PINCONF
#define CONFIG_PINCTRL
#define CONFIG_PINMUX

#include "linux/pinctrl/consumer.h"
#include "linux/pinctrl/devinfo.h"
#include "linux/pinctrl/machine.h"
#include "linux/pinctrl/pinconf.h"
#include "linux/pinctrl/pinconf-generic.h"
#include "linux/pinctrl/pinctrl.h"
#include "linux/pinctrl/pinctrl-state.h"
#include "linux/pinctrl/pinmux.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCLUDE_SUPPORT_H_ */
