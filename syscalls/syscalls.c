/*
******************************************************************************
File:     syscalls.c
Info:     Generated by Atollic TrueSTUDIO(R) 6.0.0   2016-09-19

The MIT License (MIT)
Copyright (c) 2009-2016 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************
*/
//--------------------------------------------------------------------------------
/*
 * https://sites.google.com/site/stm32discovery/open-source-development-with-the-stm32-discovery/getting-newlib-to-work-with-stm32-and-code-sourcery-lite-eabi
 *
 * newlib_stubs.c
 *
 *  Created on: 2 Nov 2010
 *      Author: nanoage.co.uk
 */
//--------------------------------------------------------------------------------
/*
 * ДОРАБОТАНО!!!
 *
*/
//--------------------------------------------------------------------------------
/* Includes */
#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#include <sys/unistd.h>

#include "stm32f4xx_hal.h"
#include "usart.h"

#ifndef STDOUT_USART
#define STDOUT_USART 1
#endif

#ifndef STDERR_USART
#define STDERR_USART 1
#endif

#ifndef STDIN_USART
#define STDIN_USART 1
#endif
//--------------------------------------------------------------------------------
/*
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
*/
//--------------------------------------------------------------------------------
// Variables
#undef errno
extern int32_t errno;

//--------------------------------------------------------------------------------
// environ
// A pointer to a list of environment variables and their values.
// For a minimal environment, this empty list is adequate:
//uint8_t *__env[1] = { 0 };
//uint8_t **environ = __env;
char *__env[1] = { 0 };
char **environ = __env;

//--------------------------------------------------------------------------------
// Functions
void initialise_monitor_handles()
{
}
//--------------------------------------------------------------------------------
// Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes.
// Minimal implementation, for a system without processes:
int _getpid(void)
{
    errno = ENOSYS;     // Function not implemented
	return -1;
}
//--------------------------------------------------------------------------------
//
int _gettimeofday(struct timeval  *ptimeval, void *ptimezone)
{
    (void) ptimeval;
    (void) ptimezone;

    errno = ENOSYS;     // Function not implemented
    return -1;
}
//--------------------------------------------------------------------------------
// Send a signal. Minimal implementation:
int _kill(int32_t pid, int32_t sig)
{
    (void) pid;
    (void) sig;

    errno = EINVAL;
    return (-1);
}
//--------------------------------------------------------------------------------
// Implement your write code here, this is used by puts and printf for example
// return len;
//int _write(int32_t file, uint8_t *ptr, int32_t len)
int _write(int file, char *ptr, int len)
{
    //int n;
    switch (file)
    {
    case STDOUT_FILENO: // stdout
        //for (n = 0; n < len; n++) {
#if STDOUT_USART == 1
            errno = HAL_UART_Transmit(&huart1, (uint8_t*)ptr, (uint16_t)len, 100);
            //while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            //USART1->DR = (*ptr++ & (uint16_t)0x01FF);
#elif  STDOUT_USART == 2
            errno = HAL_UART_Transmit(&huart2, (uint8_t*)ptr, (uint16_t)len, 100);

            //while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
            //USART2->DR = (*ptr++ & (uint16_t) 0x01FF);
#elif  STDOUT_USART == 3
            errno = HAL_UART_Transmit(&huart3, (uint8_t*)ptr, (uint16_t)len, 100);

            //while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            //USART3->DR = (*ptr++ & (uint16_t)0x01FF);
#endif
        //}
        break;
    case STDERR_FILENO: // stderr
        //for (n = 0; n < len; n++) {
#if STDERR_USART == 1
            errno = HAL_UART_Transmit(&huart1, (uint8_t*)ptr, (uint16_t)len, 100);
            //while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            //USART1->DR = (*ptr++ & (uint16_t)0x01FF);
#elif  STDERR_USART == 2
            errno = HAL_UART_Transmit(&huart2, (uint8_t*)ptr, (uint16_t)len, 100);
            //while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) {}
            //USART2->DR = (*ptr++ & (uint16_t) 0x01FF);
#elif  STDERR_USART == 3
            errno = HAL_UART_Transmit(&huart3, (uint8_t*)ptr, (uint16_t)len, 100);
            //while ((USART3->SR & USART_FLAG_TC) == (uint16_t)RESET) {}
            //USART3->DR = (*ptr++ & (uint16_t)0x01FF);
#endif
        //}
        break;
    default:
        errno = EBADF;      // Bad file number
        return -1;
    }
    return len;
}
//--------------------------------------------------------------------------------
//void _exit(int32_t status)
void _exit(int status)
{
    (void) status;

    _write(1, "exit", 4);
    while (1) { }
}
//--------------------------------------------------------------------------------
// Increase program data space.
// Malloc and related functions depend on this
//void * _sbrk(int32_t incr)
caddr_t _sbrk(int incr)
{
/*
    extern char   end;                  // Set by linker.
	static char * heap_end;
	char *        prev_heap_end;

	if (heap_end == 0) {
		heap_end = & end;
	}

	prev_heap_end = heap_end;
	heap_end += incr;

	return (void *) prev_heap_end;
*/
    extern char _ebss;                  // Defined by the linker
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) __get_MSP();
    if (heap_end + incr >  stack)
    {
        _write (STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return  (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}
//--------------------------------------------------------------------------------
int _close(int32_t file)
{
    (void) file;

    errno = ENOSYS;
	return -1;
}
//--------------------------------------------------------------------------------
// Status of an open file. For consistency with other minimal implementations in these examples,
// all files are regarded as character special devices.
// The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
int _fstat(int32_t file, struct stat *st)
{
    (void) file;
    st->st_mode = S_IFCHR;
    return 0;
}
//--------------------------------------------------------------------------------
// Query whether output stream is a terminal. For consistency with the other minimal implementations,
int _isatty(int32_t file)
{
    switch (file)
    {
        case STDOUT_FILENO:
        case STDERR_FILENO:
        case STDIN_FILENO:
            return 1;
        default:
            //errno = ENOTTY;
            errno = EBADF;
            return 0;
    }
}
//--------------------------------------------------------------------------------
// Set position in a file. Minimal implementation:
int _lseek(int32_t file, int32_t ptr, int32_t dir)
{
    (void) file;
    (void) ptr;
    (void) dir;

	errno = ENOSYS;
	return -1;
    //return 0;
}

//--------------------------------------------------------------------------------------------------
int _read(int32_t file, uint8_t *ptr, int32_t len)
{
    //int n;
    int num = 0;
    switch (file) {
    case STDIN_FILENO:
        //for (n = 0; n < len; n++) {
#if   STDIN_USART == 1
            errno = HAL_UART_Receive(&huart1, ptr, len, 100);
            //while ((USART1->SR & USART_FLAG_RXNE) == (uint16_t)RESET) {}
            //char c = (char)(USART1->DR & (uint16_t)0x01FF);
#elif STDIN_USART == 2
            errno = HAL_UART_Receive(&huart2, ptr, len, 1);
            //while ((USART2->SR & USART_FLAG_RXNE) == (uint16_t) RESET) {}
            //char c = (char) (USART2->DR & (uint16_t) 0x01FF);
#elif STDIN_USART == 3
            errno = HAL_UART_Receive(&huart3, ptr, len, 1);
            //while ((USART3->SR & USART_FLAG_RXNE) == (uint16_t)RESET) {}
            //char c = (char)(USART3->DR & (uint16_t)0x01FF);
#endif
            //*ptr++ = c;
            //num++;
        //}
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return num;
}
//--------------------------------------------------------------------------------------------------
int _readlink(const char *path, char *buf, size_t bufsize)
{
    (void) path;
    (void) buf;
    (void) bufsize;

    errno = ENOSYS;     // Function not implemented
    return -1;
}
//--------------------------------------------------------------------------------------------------
// предстоит реализовать
int _open(const uint8_t *path, int32_t flags, int32_t mode)
{
    (void) path;
    (void) flags;
    (void) mode;

    errno = ENOSYS;     // Function not implemented
	return -1;
}
//--------------------------------------------------------------------------------------------------
// Wait for a child process. Minimal implementation:
int _wait(int32_t *status)
{
    (void) status;

    errno = ECHILD;     // No children
	return -1;
}
//--------------------------------------------------------------------------------------------------
// Remove a file's directory entry. Minimal implementation:
int _unlink(const uint8_t *name)
{
    (void) name;

    errno = ENOENT;     // No such file or directory
	return -1;
}
//--------------------------------------------------------------------------------------------------
// Timing information for current process. Minimal implementation:
int _times(struct tms *buf)
{
    (void) buf;

    errno = ENOSYS;     // Function not implemented
	return -1;
}
//--------------------------------------------------------------------------------------------------
// Status of a file (by name). Minimal implementation:
// int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
int _stat(const uint8_t *file, struct stat *st)
{
    //errno = ENOSYS;
    //return -1;

    (void) file;

    st->st_mode = S_IFCHR;
    return 0;
}
//--------------------------------------------------------------------------------------------------
int _symlink(const char *path1, const char *path2)
{
    (void) path1;
    (void) path2;

    errno = ENOSYS;     // Function not implemented
    return -1;
}
//--------------------------------------------------------------------------------------------------
// Establish a new name for an existing file. Minimal implementation:
int _link(const uint8_t *old, const uint8_t *new)
{
    (void) old;
    (void) new;

    errno = EMLINK;     // Too many links
	return -1;
}
//--------------------------------------------------------------------------------------------------
// Create a new process. Minimal implementation (for a system without processes):
int _fork(void)
{
    errno = EAGAIN;     // No more processes
    return -1;
}
//--------------------------------------------------------------------------------------------------
// execve
// Transfer control to a new process. Minimal implementation (for a system without processes):
int _execve(const uint8_t *name, uint8_t * const *argv, uint8_t * const *env)
{
    (void) name;
    (void) argv;
    (void) env;

    errno = ENOSYS;     // Function not implemented
	return -1;
}
//--------------------------------------------------------------------------------------------------
