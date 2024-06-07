/* test.c
   test program for GBFS

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


#include "minigba.h"  /* essentials from pin8gba.h */
MULTIBOOT

#include <stdio.h>
#include <stdlib.h>
#include "gbfs.h"


/* if you change it to use the bin2s method, set this to 0 */
#define USE_APPENDED_GBFS 1

/* if you want to access files by number instead, set this to 0 */
#define BY_NAME 1



#if USE_APPENDED_GBFS == 0
extern const char *const test_gbfs;
#endif

/* expand_gb_to_gba4bit() *********
   Expand tiles from Game Boy format to Game Boy Advance
   format in 4-bits
*/
void expand_gb_to_gba4bit(void *in_dst, const u8 *src, size_t len, const unsigned char gbpal[4])
{
  u32 *dst = in_dst;
  const unsigned char stdgbpal[] = {0, 1, 2, 3};

  len >>= 1;  /* convert from bytes to scanlines */
  if(!gbpal)
    gbpal = stdgbpal;

  for(; len > 0; len--)
  {
    unsigned int sr0 = *src++;
    unsigned int sr1 = *src++;
    unsigned int dstbits = 0;
    unsigned int bits = 8;

    for(; bits > 0; bits--)
    {
      unsigned int gb_color = ((sr1 & 1) << 1) | (sr0 & 1);
      sr0 >>= 1;
      sr1 >>= 1;
      dstbits = (dstbits << 4) | gbpal[gb_color];
    }
    *dst++ = dstbits;
  }
}


void setup_display(void)
{
  unsigned int x;

  LCDMODE = LCDMODE_BLANK;
  PALRAM[0] = RGB(0, 0, 20);
  PALRAM[1] = RGB(11, 11, 11);
  PALRAM[2] = RGB(24, 24, 24);
  PALRAM[3] = RGB(31, 31, 31);

  BGSCROLL[0].x = 0;
  BGSCROLL[0].y = 0;
  BGCTRL[0] =  BGCTRL_PAT(0) | BGCTRL_16C | BGCTRL_NAME(8)
               | BGCTRL_H32 | BGCTRL_V32;
  for(x = 0; x < 1024; x++)
    MAP[8][0][x] = ' ';
}

int main(void)
{
  const char *txt = NULL;
  u32 txt_left = 0;
#if USE_APPENDED_GBFS
  const GBFS_FILE *dat = find_first_gbfs_file(find_first_gbfs_file);
#else
  const GBFS_FILE *dat = (const GBFS_FILE *)test_gbfs;
#endif
  int y = 0;
  int cursor_line = ((y >> 6) + 19) & 0x1f;

  /* set up hardware */
  setup_display();
  /* load font */
#if BY_NAME
  expand_gb_to_gba4bit(VRAM + (16 * ' '),
                       gbfs_get_obj(dat, "test.chr", NULL),
                       96*16, NULL);
#else
  expand_gb_to_gba4bit(VRAM + (16 * ' '),
                       gbfs_get_nth_obj(dat, 0, NULL, NULL),
                       96*16, NULL);
#endif
  while(LCD_Y < 160) ;
  LCDMODE = 0 | LCDMODE_BG0;

  while(1)
  {
    int bottom_line = ((y >> 6) + 20) & 0x1f;

    if(txt == NULL)
#if BY_NAME
      txt = gbfs_get_obj(dat, "test.txt", &txt_left);
#else
      txt = gbfs_get_nth_obj(dat, 1, NULL, &txt_left);
#endif

    while(LCD_Y < 160);

    while(cursor_line != bottom_line)
    {
      unsigned int x = 0;

      cursor_line = (cursor_line + 1) & 0x1f;

      /* draw a new row of text */
      for(x = 0; x < 30 && txt_left > 0; txt++, txt_left--)
      {
        if(*txt == '\n')
          while(x < 32)
            MAP[8][cursor_line][x++] = ' ';
        else if(*txt >= ' ')
          MAP[8][cursor_line][x++] = *txt;
      }
    }

    BGSCROLL[0].x = 252;
    BGSCROLL[0].y = (y >> 3) & 0xff;

    while(LCD_Y >= 160);

    ++y;

    /* restart scrolling text at end */
    if(txt_left == 0)
      txt = NULL;
  }
}
