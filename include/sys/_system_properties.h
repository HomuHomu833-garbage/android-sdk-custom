/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _INCLUDE_SYS__SYSTEM_PROPERTIES_H
#define _INCLUDE_SYS__SYSTEM_PROPERTIES_H

#include <stdint.h>

#ifndef _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#error "You should #include <sys/system_properties.h> instead."
#endif

#include <sys/system_properties.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROP_SERVICE_NAME "property_service"
#define PROP_FILENAME "/dev/__properties__"

#define PROP_MSG_SETPROP 1
#define PROP_MSG_SETPROP2 0x00020001

#define PROP_SUCCESS 0
#define PROP_ERROR_READ_CMD 0x0004
#define PROP_ERROR_READ_DATA 0x0008
#define PROP_ERROR_READ_ONLY_PROPERTY 0x000B
#define PROP_ERROR_INVALID_NAME 0x0010
#define PROP_ERROR_INVALID_VALUE 0x0014
#define PROP_ERROR_PERMISSION_DENIED 0x0018
#define PROP_ERROR_INVALID_CMD 0x001B
#define PROP_ERROR_HANDLE_CONTROL_MESSAGE 0x0020
#define PROP_ERROR_SET_FAILED 0x0024

/**
 * This was previously for testing, but now that SystemProperties is its own
 * testable class, there is never a reason to call this function and its
 * implementation simply returns -1.
 */
int __system_property_set_filename(const char* __filename);

/**
 * Initialize the area to be used to store properties. Can only be done by a
 * single process that has write access to the property area.
 */
int __system_property_area_init(void);

/**
 * Read the global serial number of the system properties.
 *
 * Called to predict if a series of cached __system_property_find objects will
 * have seen __system_property_serial values change. Also helps determine if a
 * failed __system_property_find could now find a new object.
 *
 * Returns the serial number on success, -1 on error.
 */
uint32_t __system_property_area_serial(void);

/**
 * Add a new system property. Can only be done by a single process with write
 * access to the property area, ensuring the property does not already exist.
 *
 * Returns 0 on success, -1 if the property area is full.
 */
int __system_property_add(const char* __name, unsigned int __name_length,
                          const char* __value, unsigned int __value_length);

/**
 * Update the value of a system property returned by __system_property_find.
 * Can only be done by a single process with write access to the property area.
 *
 * Returns 0 on success, -1 if the parameters are incorrect.
 */
int __system_property_update(prop_info* __pi, const char* __value,
                             unsigned int __value_length);

/**
 * Read the serial number of a system property returned by __system_property_find.
 *
 * Returns the serial number on success, -1 on error.
 */
uint32_t __system_property_serial(const prop_info* __pi);

/**
 * Initialize the system properties area in read-only mode. Should be done by
 * all processes that need to read system properties.
 *
 * Returns 0 on success, -1 otherwise.
 */
int __system_properties_init(void);

/**
 * Deprecated: use __system_property_wait instead.
 */
uint32_t __system_property_wait_any(uint32_t __old_serial);

#ifdef __cplusplus
}
#endif

#endif  // _INCLUDE_SYS__SYSTEM_PROPERTIES_H
