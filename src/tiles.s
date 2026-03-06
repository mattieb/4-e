/*
 * This file is part of 4-e <https://mattiebee.dev/4-e>.
 *
 * Copyright 2024-2026 Mattie Behrens.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * “Software”), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

@{{BLOCK(tiles)

    // tiles are flipped left-to-right

    .section .rodata
    .align 2
    .global tile_diamond_quadrant
tile_diamond_quadrant:
    .word 0x00000000
    .word 0x10000000
    .word 0x11000000
    .word 0x11100000
    .word 0x11110000
    .word 0x11111000
    .word 0x11111100
    .word 0x11111110

    .section .rodata
    .align 2
    .global tile_frame
tile_frame:
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222

    .section .rodata
    .align 2
    .global tile_frame_horizontal_edge
tile_frame_horizontal_edge:
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x33333333
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000
    .word 0x00000000

    .section .rodata
    .align 2
    .global tile_frame_vertical_edge
tile_frame_vertical_edge:
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222
    .word 0x00003222


    .section .rodata
    .align 2
    .global tile_frame_corner
tile_frame_corner:
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x22222222
    .word 0x33222222
    .word 0x00322222
    .word 0x00032222
    .word 0x00032222

    .section .rodata
    .align 2
    .global tile_window
tile_window:
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444

    .section .rodata
    .align 2
    .global tile_window_horizontal_edge
tile_window_horizontal_edge:
    .word 0x55555555
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444
    .word 0x44444444

    .section .rodata
    .align 2
    .global tile_window_vertical_edge
tile_window_vertical_edge:
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445

    .section .rodata
    .align 2
    .global tile_window_corner
tile_window_corner:
    .word 0x55550000
    .word 0x44445500
    .word 0x44444450
    .word 0x44444450
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445
    .word 0x44444445

@}}BLOCK(tiles)
