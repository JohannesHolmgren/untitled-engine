#ifndef KEY_H
#define KEY_H

// These wicked small keys with bad names (,./;' etc) not included yet
enum class Key : int {
    K_1 = 49,
    K_2 = 50,
    K_3 = 51,
    K_4 = 52,
    K_5 = 53,
    K_6 = 54,
    K_7 = 55,
    K_8 = 56,
    K_9 = 57,
    K_0 = 48,
    K_Q = 113,
    K_W = 119,
    K_E = 101,
    K_R = 114,
    K_T = 116,
    K_Y = 121,
    K_U = 117,
    K_I = 105,
    K_O = 111,
    K_P = 112,
    K_A = 97,
    K_S = 115,
    K_D = 100,
    K_F = 102,
    K_G = 103,
    K_H = 104,
    K_J = 106,
    K_K = 107,
    K_L = 108,
    K_Z = 122,
    K_X = 120,
    K_C = 99,
    K_V = 118,
    K_B = 98,
    K_N = 110,
    K_M = 109,
    K_Space = 32,
    K_Left = 1073741904,
    K_Up = 1073741906,
    K_Down = 1073741905,
    K_Right = 1073741903,
    K_Escape = 27,
    K_Tab = 9,
    K_CapsLock = 1073741881,
    K_Return = 13,
    K_Backspace = 8,
    K_Ctrl = 1073742048,
    K_LShift = 1073742049,
    K_RShift = 1073742053,
    K_LOption = 1073742050,
    K_ROption = 1073742054,
    K_LCommand = 1073742051,
    K_RCommand = 1073742055
};

/**
 * Turns integer to enum key. NOTE that no validity check is occuring.
 */
Key intToKey(int keycode);

#endif