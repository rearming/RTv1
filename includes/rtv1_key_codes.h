/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_codes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleonard <sleonard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:56:01 by sleonard          #+#    #+#             */
/*   Updated: 2019/06/03 10:01:06 by sleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_CODES_H
# define KEY_CODES_H

# ifdef __APPLE__

/*
**	MOUSE
*/

#  define SCROLL_UP 4
#  define SCROLL_DOWN 5

/*
**	ALPHABET
*/

#  define A 0x00
#  define S 0x01
#  define D 0x02
#  define F 0x03
#  define H 0x04
#  define G 0x05
#  define Z 0x06
#  define X 0x07
#  define C 0x08
#  define V 0x09
#  define B 0x0B
#  define Q 0x0C
#  define W 0x0D
#  define E 0x0E
#  define R 0x0F
#  define Y 0x10
#  define T 0x11
#  define O 0x1F
#  define U 0x20
#  define I 0x22
#  define P 0x23
#  define L 0x25
#  define J 0x26
#  define K 0x28
#  define N 0x2D
#  define M 0x2E

#  define RIGHT_SQ_BRACKE 0x1E
#  define LEFT_SQ_BRACKET 0x21

/*
**	SYMBOLS
*/

#  define DOT 0x2F
#  define COLON 41
#  define EQUAL 0x18
#  define MINUS 0x1B

/*
**	TOP PANEL NUMBERS
*/

#  define T_1 0x12
#  define T_2 0x13
#  define T_3 0x14
#  define T_4 0x15
#  define T_5 0x17
#  define T_6 0x16
#  define T_7 0x1A
#  define T_8 0x1C
#  define T_9 0x19
#  define T_0 0x1D

/*
**	COMMAND KEYS
*/

#  define TAB 48
#  define SPACE 49
#  define TILDA 50
#  define DEL 51
#  define ESC 53
#  define CMD 259
#  define SHIFT 257
#  define CAPS_LOCK 272
#  define OPTION 261
#  define CTRL 256
#  define ENTER 36

/*
**	ARROWS
*/

#  define ARR_UP 126
#  define ARR_LEFT 123
#  define ARR_RIGHT 124
#  define ARR_DOWN 125

/*
**	NUM_KEYS
*/

#  define NUM_PLUS 69
#  define NUM_MINUS 78

#  define NUM_LEFT 86
#  define NUM_RIGHT 88
#  define NUM_UP 91
#  define NUM_DOWN 84

#  define NUM_0 0x52
#  define NUM_1 0x53
#  define NUM_2 0x54
#  define NUM_3 0x55
#  define NUM_4 0x56
#  define NUM_5 0x57
#  define NUM_6 0x58
#  define NUM_7 0x59
#  define NUM_8 0x5B
#  define NUM_9 0x5C

/*
**	F - KEYS
*/

#  define F1 0x7A
#  define F2 0x78
#  define F3 0x63
#  define F4 0x76
#  define F5 0x60
#  define F6 0x61
#  define F7 0x62
#  define F8 0x64
#  define F9 0x65
#  define F10 0x6D
#  define F11 0x67
#  define F12 0x6F
#  define F13 0x69
#  define F14 0x6B
#  define F15 0x71

# else
/*
**	linux keymap
*/

/*
**	MOUSE
*/

#  define SCROLL_UP 4
#  define SCROLL_DOWN 5

/*
**	ALPHABET
*/

#  define A 97
#  define S 115
#  define D 100
#  define F 102
#  define H 104
#  define G 103
#  define Z 122
#  define X 120
#  define C 99
#  define V 118
#  define B 98
#  define Q 113
#  define W 119
#  define E 101
#  define R 114
#  define Y 121
#  define T 116
#  define O 111
#  define U 117
#  define I 105
#  define P 112
#  define L 108
#  define J 106
#  define K 107
#  define N 110
#  define M 109

#  define RIGHT_SQ_BRACKE 0x1E
#  define LEFT_SQ_BRACKET 0x21

/*
**	SYMBOLS
*/

#  define DOT 4667
#  define COLON 59
#  define EQUAL 61
#  define MINUS 45

/*
**	TOP PANEL NUMBERS
*/

#  define T_1 49
#  define T_2 50
#  define T_3 51
#  define T_4 52
#  define T_5 53
#  define T_6 54
#  define T_7 55
#  define T_8 56
#  define T_9 57
#  define T_0 48

/*
**	COMMAND KEYS
*/

#  define TAB 65289
#  define SPACE 32
#  define TILDA 96
#  define DEL 65288
#  define ESC 65307
#  define CMD 259
#  define SHIFT 65505
#  define CAPS_LOCK 65509
#  define OPTION 261
#  define CTRL 65507
#  define ENTER 65293

/*
**	ARROWS
*/

#  define ARR_UP 65362
#  define ARR_LEFT 65361
#  define ARR_RIGHT 65363
#  define ARR_DOWN 65364

/*
**	NUM_KEYS
*/

#  define NUM_PLUS 65451
#  define NUM_MINUS 65453

#  define NUM_0 65438
#  define NUM_1 65436
#  define NUM_2 65433
#  define NUM_3 65435
#  define NUM_4 65430
#  define NUM_5 65437
#  define NUM_6 65432
#  define NUM_7 65429
#  define NUM_8 65431
#  define NUM_9 65434

/*
**	F - KEYS
*/

#  define F1 0x7A
#  define F2 0x78
#  define F3 0x63
#  define F4 0x76
#  define F5 0x60
#  define F6 0x61
#  define F7 0x62
#  define F8 0x64
#  define F9 0x65
#  define F10 0x6D
#  define F11 0x67
#  define F12 0x6F
#  define F13 0x69
#  define F14 0x6B
#  define F15 0x71

# endif

#endif
