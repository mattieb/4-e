# 4-e

A project to send [Super Mario Advance
4](https://www.mariowiki.com/Super_Mario_Advance_4:_Super_Mario_Bros._3)
[e-Reader](https://www.mariowiki.com/E-Reader) cards from one Game
Boy Advance running 4-e to another running the game, using homebrew
and decoded .bin versions of those cards instead of printed cards
an an actual e-Reader.

It can currently send a level card between two mGBA instances or
between two Analogue Pockets.

I've written more about 4-e [on my blog](https://mattiebee.io/52283/introducing-4-e-super-mario-advance-4-e-cards-without-an-e-reader).

## Usage

1.  Build the .gba ROM or download it from
    [releases](https://github.com/mattieb/4-e/releases).

2.  [Create a GBFS file](./vendor/gbfs/readme.txt) from a the e-Card
    .bin file you wish to send.  The required tools are [in this
    repository](./vendor/gbfs/tools/), and also ship with gba-tools
    in devkitPro, if you have a GBA toolchain installed.

3.  Concatenate the ROM and the GBFS file into the new ROM you will
    use. On Unix-like systems, you can do something like this:

    ```
    cat 4-e.gba card.gbfs >4-e.card.gba
    ```

    On Windows systems, you can do something like this:

    ```
    copy /b 4-e.gba+card.gbfs 4-e.card.gba
    ```

4.  Link two Game Boy Advance systems with a link cable.

5.  On the first system, run Super Mario Advance 4.

6.  On the second system, run your custom 4-e ROM.

7.  On the first system, start the e-Reader communication process.
    4-e will connect to the game automatically and try to send your
    card.

## Thanks

4-e wouldn't exist without:

- [devkitPro](https://devkitpro.org)

- [gba-makefile-template](https://github.com/gbadev-org/gba-makefile-template)

- GBATEK (specifically the section on [GBA Communication
Ports](https://problemkaputt.de/gbatek.htm#gbacommunicationports))

- [GBFS](https://pineight.com/gba/#gbfs)

- [mGBA](https://mgba.io)
