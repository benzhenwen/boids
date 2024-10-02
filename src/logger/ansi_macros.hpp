#ifndef PL_ANSI_MACROS_HPP_
#define PL_ANSI_MACROS_HPP_

/**
 * i stole this lmao
 **/

// Styles
#define ANSI_RESET       0
#define ANSI_BOLD        1
#define ANSI_LIGHT       2
#define ANSI_ITALIC      3
#define ANSI_UNDERLINE   4
#define ANSI_SLOW_BLINK  5
#define ANSI_FAST_BLINK  6
#define ANSI_INVERT      7
#define ANSI_STRIKE      9

// Text Colors
#define ANSI_TEXT_DEFAULT 39
#define ANSI_TEXT_BLACK   30
#define ANSI_TEXT_RED     31
#define ANSI_TEXT_GREEN   32
#define ANSI_TEXT_YELLOW  33
#define ANSI_TEXT_BLUE    34
#define ANSI_TEXT_MAGENTA 35
#define ANSI_TEXT_CYAN    36
#define ANSI_TEXT_WHITE   37

// Background Colors
#define ANSI_BACK_DEFAULT 49
#define ANSI_BACK_BLACK   40
#define ANSI_BACK_RED     41
#define ANSI_BACK_GREEN   42
#define ANSI_BACK_YELLOW  43
#define ANSI_BACK_BLUE    44
#define ANSI_BACK_MAGENTA 45
#define ANSI_BACK_CYAN    46
#define ANSI_BACK_WHITE   47

// Codes can be nested up to 10 times (up to 10 ANSI_* macros in the variadic function)
#define _ANSI_MERGE_CODES_0(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_1(__VA_ARGS__))
#define _ANSI_MERGE_CODES_1(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_2(__VA_ARGS__))
#define _ANSI_MERGE_CODES_2(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_3(__VA_ARGS__))
#define _ANSI_MERGE_CODES_3(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_4(__VA_ARGS__))
#define _ANSI_MERGE_CODES_4(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_5(__VA_ARGS__))
#define _ANSI_MERGE_CODES_5(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_6(__VA_ARGS__))
#define _ANSI_MERGE_CODES_6(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_7(__VA_ARGS__))
#define _ANSI_MERGE_CODES_7(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_8(__VA_ARGS__))
#define _ANSI_MERGE_CODES_8(a, ...) \
  #a __VA_OPT__(";" _ANSI_MERGE_CODES_9(__VA_ARGS__))
#define _ANSI_MERGE_CODES_9(a) \
  #a


// Create an ANSI escape string for the style requested.
// Supports up to 10 style macros (ANSI_*).
#define ANSI_ESCAPE(...) \
  __VA_OPT__("\033[" _ANSI_MERGE_CODES_0(__VA_ARGS__) "m") ""

#endif