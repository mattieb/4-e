# 4-e

A project to send [Super Mario Advance
4](https://www.mariowiki.com/Super_Mario_Advance_4:_Super_Mario_Bros._3)
[e-Reader](https://www.mariowiki.com/E-Reader) cards from one Game
Boy Advance running 4-e to another running the game, using homebrew
and decoded .bin versions of those cards instead of printed cards
an an actual e-Reader.

It has been tested to successfully and reliably send demo, power-up,
and level cards between mGBA multiplayer windows as well as real
Game Boys Advance and [Analogue Pockets](https://www.analogue.co/pocket).

I've written more about 4-e [on my
blog](https://mattiebee.io/52283/introducing-4-e-super-mario-advance-4-e-cards-without-an-e-reader).

## Usage

1.  Build the 4-e.gba ROM or download it from
    [releases](https://github.com/mattieb/4-e/releases).

2.  Using [gbfs-web](https://mattiebee.app/gbfs-web), attach the
    e-Card .bin files you wish to use to 4-e.gba, and save a new
    ROM.

    -   You can also use the standard tools from
        [GBFS](https://pineight.com/gba/#gbfs) to create a GBFS
        file, then concatenate it to 4-e.gba.  (These tools are
        also included in the "gba-tools" package in devkitARM.)

3.  Link two Game Boy Advance systems with a link cable.  The game
    must be player 1, and 4-e must be player 2.

4.  On the first system, run Super Mario Advance 4.

5.  On the second system, run your custom 4-e ROM.

6.  Pick the e-Card you wish you send from the list. If your GBFS
    file only had one e-Card in it, it will be selected automatically.
    From this point on, you can cancel and reset by pressing B.

7.  On the first system, start the e-Reader communication process.
    4-e will connect to the game automatically and try to send your
    card.

8.  When the game has finished, press any button on 4-e to reset
    so you can send another card if you wish.

## Troubleshooting

### 4-e doesn't respond when I start communication

Check that your link cable is connected firmly and correctly.

-   If you're using the official Nintendo link cable, it must be
    connected with the purple end to the game and the gray end to
    4-e.

-   If you're using the Analogue Pocket link cable, it must be
    switched to GBA mode, not GB/C mode.

## Thanks

4-e wouldn't exist without:

- [devkitARM](https://devkitpro.org/wiki/devkitARM)

- [gba-makefile-template](https://github.com/gbadev-org/gba-makefile-template)

- GBATEK (specifically the section on [GBA Communication
Ports](https://problemkaputt.de/gbatek.htm#gbacommunicationports))

- [GBFS](https://pineight.com/gba/#gbfs)

- [mGBA](https://mgba.io)
