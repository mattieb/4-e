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

@}}BLOCK(tiles)
