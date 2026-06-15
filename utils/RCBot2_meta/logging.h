/**
 * Copyright 2021 nosoop
 * 
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE 
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
 * OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __RCBOT2_LOGGER_H__
#define __RCBOT2_LOGGER_H__

#include <cstdint>

// Undefine potential conflicting macros
#ifdef FATAL
#undef FATAL
#endif

#ifdef ERROR
#undef ERROR
#endif

#ifdef WARN
#undef WARN
#endif

#ifdef INFO
#undef INFO
#endif

#ifdef DEBUG
#undef DEBUG
#endif

#ifdef TRACE
#undef TRACE
#endif

/**
 * Log levels in ascending order.
 */
enum LogLevel : std::uint8_t {
	FATAL, ERROR, WARN, INFO, DEBUG, TRACE
};

class CBotLogger {
	public:
	void Log(LogLevel level, const char* fmt, ...);
};

extern CBotLogger *logger;

#endif
