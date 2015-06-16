/*
 * The compilation of software known as DiscoBall is distributed under the
 * following terms:
 *
 * Copyright (c) 2015 Christopher Friedt. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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
