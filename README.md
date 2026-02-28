# 4-e

4-e sends [_Super Mario Advance
4_](https://www.mariowiki.com/Super_Mario_Advance_4:_Super_Mario_Bros._3)
[e-Reader cards](https://www.mariowiki.com/Super_Mario_Advance_4:_Super_Mario_Bros._3_e-Reader_cards) from the [Game
Boy Advance](https://en.wikipedia.org/wiki/Game_Boy_Advance) it's running on to another running _Mario_. It uses decoded .bin files of those cards' data instead of printed cards an an actual [e-Reader](https://www.mariowiki.com/E-Reader).

![The picker screen, showing levels from the Smaghetti site.](./doc/picker.png) ![The sending screen, showing 4-e waiting to transmit to _Mario_.](./doc/sending.png)

It can send level, power-up, and demo cards between real Game Boys Advance and [Analogue Pockets](https://www.analogue.co/pocket) using link cables. It can also send cards between [mGBA](https://mgba.io) multiplayer windows. No e-Reader or e-Reader ROM is required.

Need .bin files? The latest versions of the [Smaghetti](https://smaghetti.mattgreer.dev) editor for _Mario_ can save .bin files. Head to the flask icon in the lower-right corner of the editor to access Experiments—you can download your levels as .bin files there!

## Usage

1.  Build the base "4-e.gba" ROM with [devkitARM](https://devkitpro.org/wiki/devkitARM), or download it from [releases](https://github.com/mattieb/4-e/releases).

2.  Using [gbfs-web](https://mattiebee.app/gbfs-web), attach the e-Card .bin files you wish to use to 4-e.gba, and save a new ROM.

    -   You can also use the standard tools from [GBFS](https://pineight.com/gba/#gbfs) to create a GBFS file, then concatenate it to 4-e.gba.  (These tools are also included in the "gba-tools" package in devkitARM.)

    -   *New in v3.0!* If you're using the command-line "gbfs" tool to build your GBFS files, and you use "padbin" to pad each GBFS file to 256 bytes, you can attach multiple GBFS files and quickly page through them to organize your cards.

3.  On one Game Boy Advance, run _Super Mario Advance 4_. Connect the player 1 end of a link cable to this system.

4.  On another Game Boy Advance, run 4-e. Connect the player-2 end of the link cable to this system.

5.  Pick the e-Card you wish you send from the list. (If your GBFS file only had one e-Card in it, it will be selected automatically; you won't see the list.) From this point on, you can cancel and reset by pressing B.

6.  On the first system, start the e-Reader communication process. 4-e will connect to the game automatically and try to send your card.

7.  When 4-e has finished its work, press any button to reset it. Now you can send another card, if you wish!

## Troubleshooting

Check that your link cable is connected firmly and correctly.

-   If you're using the official Nintendo link cable, it must be connected with the purple end to the game and the gray end to 4-e.

-   If you're using the Analogue Pocket link cable, it must be switched to GBA mode, not GB/C mode. The end closest to the switch is player 1 (the _Mario_ end); the other end is player 2 (the 4-e end).

## Thanks

4-e wouldn't exist without:

- [devkitARM](https://devkitpro.org/wiki/devkitARM)

- [gba-makefile-template](https://github.com/gbadev-org/gba-makefile-template)

- GBATEK (specifically the section on [GBA Communication
Ports](https://problemkaputt.de/gbatek.htm#gbacommunicationports))

- [GBFS](https://pineight.com/gba/#gbfs)

- [mGBA](https://mgba.io)

A huge special thanks to the community over the past decades for digging into the e-Reader and _Super Mario Advance 4_. Without your work, I never could have pulled this off.

And, of course, Nintendo. You didn't help any of us make _this_, but you did make the game I loved so much in the first place—inspiring me to see if I could take it further.
