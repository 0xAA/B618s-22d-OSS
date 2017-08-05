/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2013-2015. All rights reserved.
 *
 * mobile@huawei.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
 #ifndef __ATP_DEPRECATED_H__
#define __ATP_DEPRECATED_H__
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/socket.h>


#undef __FD_ZERO
#define __FD_ZERO(fdsetp)   (memset_s (fdsetp, sizeof (*(fd_set *)(fdsetp)), 0, sizeof (*(fd_set *)(fdsetp))))

// mem
void *memcpy(void *dest, const void *src, size_t n) __attribute__ ((deprecated));
void *memset(void *s, int c, size_t n) __attribute__ ((deprecated));
void *memmove(void *dest, const void *src, size_t n) __attribute__ ((deprecated));


// string
char *strcpy(char *dest, const char *src) __attribute__ ((deprecated));
char *strncpy(char *dest, const char *src, size_t n) __attribute__ ((deprecated));
char *strcat(char *dest, const char *src) __attribute__ ((deprecated));
char *strncat(char *dest, const char *src, size_t n) __attribute__ ((deprecated));
char *strtok(char *str, const char *delim) __attribute__ ((deprecated));

// printf out
int sprintf(char *str, const char *format, ...)__attribute__ ((deprecated));
int snprintf(char *str, size_t size, const char *format, ...) __attribute__ ((deprecated));
int vsprintf(char *str, const char *format, va_list ap) __attribute__ ((deprecated));
int vsnprintf(char *str, size_t size, const char *format, va_list ap) __attribute__ ((deprecated));

// in
int scanf(const char *format, ...) __attribute__ ((deprecated));
int fscanf(FILE *stream, const char *format, ...) __attribute__ ((deprecated));
int sscanf(const char *str, const char *format, ...) __attribute__ ((deprecated));
int vscanf(const char *format, va_list ap) __attribute__ ((deprecated));
int vsscanf(const char *str, const char *format, va_list ap) __attribute__ ((deprecated));
int vfscanf(FILE *stream, const char *format, va_list ap) __attribute__ ((deprecated));
char *gets(char *s) __attribute__ ((deprecated));

// random
long int random(void) __attribute__ ((deprecated));
void srandom(unsigned int seed) __attribute__ ((deprecated));

//realloc
#ifndef realloc
void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
#endif
#endif
