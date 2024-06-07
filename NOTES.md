# Notes

## Connection

The game and e-Reader (specifically, the game's custom e-Reader dotcode scanner, which is separately sent by the game to the e-Reader and saved there for future use) communicate over [SIO multiplayer mode](https://problemkaputt.de/gbatek.htm#siomultiplayermode).

The game is player 0 and master; the e-Reader is player 1.

Baud rate is 115200.

As master, the game drives the serial clock. The e-Reader waits for the game to be ready before sending any data. Having our program wait for serial interrupts before sending data appears to work very reliably.

## Card scanning protocol

When the e-Reader detects that the connection has been established, it starts the protocol:

1.  The e-Reader sends FBFB until the game replies FBFB.

2.  The e-Reader sends 5841 until the game replies 5841.

3.  The e-Reader sends 4534 until the game replies 4534.

4.  Next, the game takes control, sending one of the following:

    -   ECEC to request a demo card

    -   EDED to request a power-up card

    -   EEEE to request a level card

    The e-Reader replies F3F3. Both the game and the e-Reader continue to send F3F3 and the request message while Lakitu flies off the game screen.

5.  The game sends F2F2 and the e-Reader replies F2F2.  Both the game and the e-Reader continue to send F2F2 while Lakitu flies onto the e-Reader screen. 

6.  The e-Reader sends F1F1.

7.  The game begins sending one of the following, expecting a scan to begin:

    -   EFEF when ready to receive a demo card

    -   F0F0 when ready to receive a power-up card

    -   FAFA when ready to receive a level card

8.  The e-Reader can cancel at this point by sending F7F7, if B is pressed.  It will then start [shutdown](#shutdown-protocol).

It will then switch to F2F2 while Lakitu flies off the e-Reader screen, and send F3F3 to end communication on its side.

9.  Once the e-Reader is ready to send, it sends F9F9.  The game begins sending FEFE repeatedly.

10. The e-Reader sends FDFD.  The game stops sending, but is still responsible for the serial clock.

11. The e-Reader sends the contents of the card, minus the 114-byte header, in two-byte packets.  They appear byteswapped in mGBA logs (e.g. bytes "CE CF" in the decoded card appear as "CFCE") but, in code, should be loaded as they appear (e.g. "0xcecf").

12. While transmitting, the e-Reader calculates a checksum by adding each 16-bit packet value (e.g. "0xcecf" as in the last example) to a 32-bit value that was initialized as zero. At the conclusion of the card, this checksum is transmitted into two 16-bit packets; least-significant first, most-significant second.

13. The e-Reader sends FCFC to end the card transmission 

14. If there was an transmission error (e.g. checksum failure), the game sends F4F4. _What happens now?_

15. The game sends F5F5 to acknowledge a successful transmission, and the e-Reader begins [shutdown](#shutdown-protocol).

## Shutdown protocol

The e-Reader will do a clean shutdown of the communication session in certain circumstances.

1.  The e-Reader sends F2F2 while Lakitu flies off the screen.

2.  The e-Reader sends F3F3 as its last packet, then stops transmitting.

3.  The game then sends F1F1 as its last packet, then stops transmitting.

At the conclusion of this protocol, the e-Reader is ready to restart communications [from the beginning](#card-scanning-protocol) as if it has just been started.
