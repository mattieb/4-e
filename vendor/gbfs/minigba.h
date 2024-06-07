/* minigba.h
   header file for compiling game boy advance software
   pared down to only what's necessary for the libgbfs demo

Copyright 2002 Damian Yerrick

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

*/

#ifndef PIN8GBA_H
#ifdef __cplusplus
extern "C" {
#endif
#define PIN8GBA_H

/* Information based on CowBite spec
   http://www.gbadev.org/files/CowBiteSpec.txt
   and information gleaned from gbadev list
*/

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef signed char  s8;
typedef signed short s16;
typedef signed int   s32;

/* put MULTIBOOT at the top of the main src file to get a ROM that
   will work on both mbv2 and flash carts
*/
#define MULTIBOOT int __gba_multiboot;

/* Generic areas of GBA memory */
#define EWRAM  ((u8 *)0x02000000)   /* 256 KB */
#define IWRAM  ((u8 *)0x03000000)   /* 32 KB, fast */
#define PALRAM ((u16 *)0x05000000)  /* 0x200 words */
#define VRAM   ((u16 *)0x06000000)  /* 0xc000 words */
#define ROM    ((u8 *)0x08000000)   /* up to 32 megabytes */


#define LCDMODE (*(volatile u16 *)0x04000000)
#define LCDMODE_BLANK    0x0080
#define LCDMODE_BG0      0x0100


/* LCD Y position */
#define LCD_Y (*(volatile u16 *)0x04000006)  /* 0-159: draw; 160-227 vblank */

#define BGCTRL ((volatile u16 *)0x04000008)
#define BGCTRL_PAT(m)    ((m) << 2)
#define BGCTRL_16C       0x0000
#define BGCTRL_NAME(m)   ((m) << 8)
#define BGCTRL_M7WRAP    0x2000
#define BGCTRL_H32       0x0000
#define BGCTRL_V32       0x0000


struct BGPOINT { u16 x, y; };
#define BGSCROLL ((volatile struct BGPOINT *)0x04000010)


#define RGB(r,g,b) ((r)|(g)<<5|(b)<<10)
typedef u16 NAMETABLE[32][32];
#define MAP ((NAMETABLE *)0x06000000)

#ifdef __cplusplus
}
#endif
#endif
