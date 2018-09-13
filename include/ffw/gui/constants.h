/*** This file is part of FineFramework project ***/

// This was borrowed from FineGraphics
#ifndef FFW_GRAPHICS_CONSTANTS
#define FFW_GRAPHICS_CONSTANTS

namespace ffw {
    enum class MouseButton {
        LEFT = 0,
        RIGHT = 1,
        MIDDLE = 2,
        EXTRA1 = 3,
        EXTRA2 = 4,
    };
    enum class MouseMode {
        RELEASED = 0,
        PRESSED = 1,
        NONE = -1,
    };
    enum class KeyMode {
        RELEASED = 0,
        PRESSED = 1,
        REPEAT = 2,
        NONE = -1,
    };
    enum class Key {
        UNKNOWN = -1,
        SPACE = 32,
        APOSTROPHE = 39,
        COMMA = 44,
        MINUS = 45,
        PERIOD = 46,
        SLASH = 47,
        NUM_0 = 48,
        NUM_1 = 49,
        NUM_2 = 50,
        NUM_3 = 51,
        NUM_4 = 52,
        NUM_5 = 53,
        NUM_6 = 54,
        NUM_7 = 55,
        NUM_8 = 56,
        NUM_9 = 57,
        SEMICOLON = 59,
        EQUAL = 61,
        LETTER_A = 65,
        LETTER_B = 66,
        LETTER_C = 67,
        LETTER_D = 68,
        LETTER_E = 69,
        LETTER_F = 70,
        LETTER_G = 71,
        LETTER_H = 72,
        LETTER_I = 73,
        LETTER_J = 74,
        LETTER_K = 75,
        LETTER_L = 76,
        LETTER_M = 77,
        LETTER_N = 78,
        LETTER_O = 79,
        LETTER_P = 80,
        LETTER_Q = 81,
        LETTER_R = 82,
        LETTER_S = 83,
        LETTER_T = 84,
        LETTER_U = 85,
        LETTER_V = 86,
        LETTER_W = 87,
        LETTER_X = 88,
        LETTER_Y = 89,
        LETTER_Z = 90,
        BRACKETLEFT = 91,
        BACKSLASH = 92,
        BRACKETRIGHT = 93,
        GRAVEACCENT = 96,
        WORLD_1 = 161,
        WORLD_2 = 162,
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        FUNCTION_INSERT = 260,
        FUNCTION_DELETE = 261,
        ARROW_RIGHT = 262,
        ARROW_LEFT = 263,
        ARROW_DOWN = 264,
        ARROW_UP = 265,
        FUNCTION_PAGEUP = 266,
        FUNCTION_PAGEDOWN = 267,
        FUNCTION_HOME = 268,
        FUNCTION_END = 269,
        FUNCTION_CAPSLOCK = 280,
        FUNCTION_SCROLLLOCK = 281,
        FUNCTION_NUMLOCK = 282,
        FUNCTION_PRINTSCREEN = 283,
        FUNCTION_PAUSE = 284,
        FUNCTION_F1 = 290,
        FUNCTION_F2 = 291,
        FUNCTION_F3 = 292,
        FUNCTION_F4 = 293,
        FUNCTION_F5 = 294,
        FUNCTION_F6 = 295,
        FUNCTION_F7 = 296,
        FUNCTION_F8 = 297,
        FUNCTION_F9 = 298,
        FUNCTION_F10 = 299,
        FUNCTION_F11 = 300,
        FUNCTION_F12 = 301,
        FUNCTION_F13 = 302,
        FUNCTION_F14 = 303,
        FUNCTION_F15 = 304,
        FUNCTION_F16 = 305,
        FUNCTION_F17 = 306,
        FUNCTION_F18 = 307,
        FUNCTION_F19 = 308,
        FUNCTION_F20 = 309,
        FUNCTION_F21 = 310,
        FUNCTION_F22 = 311,
        FUNCTION_F23 = 312,
        FUNCTION_F24 = 313,
        FUNCTION_F25 = 314,
        NUMPAD_0 = 320,
        NUMPAD_1 = 321,
        NUMPAD_2 = 322,
        NUMPAD_3 = 323,
        NUMPAD_4 = 324,
        NUMPAD_5 = 325,
        NUMPAD_6 = 326,
        NUMPAD_7 = 327,
        NUMPAD_8 = 328,
        NUMPAD_9 = 329,
        NUMPAD_DECIMAL = 330,
        NUMPAD_DIVIDE = 331,
        NUMPAD_MULTIPLY = 332,
        NUMPAD_SUBSTRACT = 333,
        NUMPAD_ADD = 334,
        NUMPAD_ENTER = 335,
        NUMPAD_EQUAL = 336,
        SHIFT_LEFT = 340,
        CONTROL_LEFT = 341,
        ALT_LEFT = 342,
        SUPER_LEFT = 343,
        SHIFT_RIGHT = 344,
        CONTROL_RIGHT = 345,
        ALT_RIGHT = 346,
        SUPER_RIGHT = 347,
        FUNCTION_MENU = 348,
        FUNCTION_LAST = 348,
        FUNCTION_CLEAR = 348,
        FUNCTION_SEPARATOR = 349,
        FUNCTION_SELECT = 350,
        FUNCTION_ZOOM = 351,
        BROWSER_BACK = 352,
        BROWSER_FAVORITES = 353,
        BROWSER_FORWARD = 354,
        BROWSER_HOME = 353,
        BROWSER_REFRESH = 354,
        BROWSER_SEARCH = 355,
        BROWSER_STOP = 356,
        MEDIA_MUTE = 357,
        MEDIA_VOLUMEDOWN = 358,
        MEDIA_VOLUMEUP = 359,
        MEDIA_NEXT = 360,
        MEDIA_PREV = 361,
        MEDIA_STOP = 362,
        MEDIA_PLAY = 363,
        MEDIA_MAIL = 364,
        MEDIA_SELECT = 365,
        MEDIA_APP1 = 366,
        MEDIA_APP2 = 367,
    };
};

#ifndef M_E
#define M_E         2.71828182845904523536
#endif
#ifndef M_LOG2E
#define M_LOG2E     1.44269504088896340736
#endif
#ifndef M_LOG10E
#define M_LOG10E    0.434294481903251827651
#endif
#ifndef M_LN2
#define M_LN2       0.693147180559945309417
#endif
#ifndef M_LN10
#define M_LN10      2.30258509299404568402
#endif
#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4      0.785398163397448309616
#endif
#ifndef M_1_PI
#define M_1_PI      0.318309886183790671538
#endif
#ifndef M_2_PI
#define M_2_PI      0.636619772367581343076
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI  1.12837916709551257390
#endif
#ifndef M_SQRT2
#define M_SQRT2     1.41421356237309504880
#endif
#ifndef M_SQRT3
#define M_SQRT3     1.73205080757
#endif
#ifndef M_SQRT4
#define M_SQRT4     2.0
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2   0.707106781186547524401
#endif
#ifndef PI_OVER_180
#define PI_OVER_180    0.017453292519943295769236907684886
#endif
#ifndef PI_OVER_360
#define PI_OVER_360    0.0087266462599716478846184538424431
#endif
#ifndef RAD_TO_DEG
#define RAD_TO_DEG  57.2957795131
#endif
#ifndef DEG_TO_RAD
#define DEG_TO_RAD  0.01745329251
#endif

#endif