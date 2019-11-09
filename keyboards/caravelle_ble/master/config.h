#pragma once

#include "../board/custom_board.h"

#define THIS_DEVICE_ROWS 1
#define THIS_DEVICE_COLS 24

#define ENABLE_STARTUP_ADV_NOLIST

#define LEFT

#ifdef LEFT
#define PRODUCT         Caravelle-Left
#define MATRIX_ROW_PINS { 0 }
#define MATRIX_COL_PINS { 16, 11, 6,  3,  15, 31, \
		                      18, 12, 7,  4,  13, 19, 30, \
		                      20, 14, 8,  5,  2,  17, 29, \
		                      28, 27, 26, 25 }
#endif

#ifdef RIGHT
#define PRODUCT         Caravelle-Right
#define MATRIX_ROW_PINS { 27 }
#define MATRIX_COL_PINS { 31, 19, 13, 3,  6, 11, \
		                      30, 17,  0, 4, 7, 12, 16, \
		                      29, 15,  2, 5, 8, 14, 18, \
		                      20, 22, 23, 24 }
#endif

#define IS_LEFT_HAND  true
//#define USE_AS_I2C_SLAVE
