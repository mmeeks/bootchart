#ifndef BOOTCHART_MACRO_H
#define BOOTCHART_MACRO_H

#include <assert.h>

/* In order to easy debug, override glibc assert() and define log()
 * function
 */
#undef assert
#define PREFIX				"[bootchart] "

#ifdef CONFIG_DEBUG

#include <stdlib.h>
#define log_debug(fmt,...)		fprintf(stderr, PREFIX "%s:%d " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#ifdef unlikely
#define bootchart_unlikely unlikely
#else /* ndef unlikely */
#define bootchart_unlikely(x) (x)
#endif /* ndef unlikely */
#define assert_debug(expr)				\
	do {						\
		if (bootchart_unlikely(!(expr))){			\
			log_debug("Assertion failed");	\
			abort();			\
		}					\
	} while(0)
#define log			log_debug
#define assert(expr)		assert_debug(expr)

#else /* ndef CONFIG_DEBUG */

#define log(fmt,...)		fprintf(stderr, PREFIX fmt, ##__VA_ARGS__)
#define assert(expr)		do {} while(0)

#endif /* CONFIG_DEBUG */

#endif /* BOOTCHART_MACRO_H */
