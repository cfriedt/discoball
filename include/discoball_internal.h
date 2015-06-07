#ifndef DISCOBALL_BUILD_H_
#define DISCOBALL_BUILD_H_

/****************************************************************************
 *                       STANDARD / SYSTEM HEADERS
 ****************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <errno.h>

#include <string.h>

/****************************************************************************
 *                       LINUX INCLUDES
 ****************************************************************************/

#ifdef __APPLE__

#ifndef _LINUX_ERR_H
#define _LINUX_ERR_H
#endif /* _LINUX_ERR_H */
#ifndef _UAPI_LINUX_TYPES_H
#define _UAPI_LINUX_TYPES_H
#endif /* _UAPI_LINUX_TYPES_H */
#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H
#endif /* _LINUX_TYPES_H */
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H
#endif /* _LINUX_STDDEF_H */
#ifndef _LINUX_SEQ_FILE_H
#define _LINUX_SEQ_FILE_H
#endif /* _LINUX_SEQ_FILE_H */
#ifndef _LINUX_RADIX_TREE_H
#define _LINUX_RADIX_TREE_H
#endif /* _LINUX_RADIX_TREE_H */
#ifndef _SECURE__STRING_H_
#define _SECURE__STRING_H_
#endif /* _SECURE__STRING_H_ */

#include "linux_types.h"

#endif

/////////////////////////////////////////////////////////////////////////////
//                       LINUX INCLUDES
//////////////////////////////////////////////////////////////////////////////

#define CONFIG_GENERIC_PINCONF
#define CONFIG_OF
#define CONFIG_PINCONF
#define CONFIG_PINCTRL
#define CONFIG_PINMUX

#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/devinfo.h>
#include <linux/pinctrl/machine.h>
#include <linux/pinctrl/pinconf.h>
#include <linux/pinctrl/pinconf-generic.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinctrl-state.h>
#include <linux/pinctrl/pinmux.h>

#endif /* DISCOBALL_BUILD_H_ */
