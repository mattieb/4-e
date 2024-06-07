#include <stddef.h>
#include <tonc.h>

#include "gbfs.h"
#include "packets.h"

#define CARD_HEADER_OFFSET  0x72

void done()
{
    tte_write("\nPress any button to reset.\n");
    while (REG_KEYINPUT == KEY_MASK) {
        VBlankIntrWait();
    }
    SoftReset();
}

void initScreen()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
    tte_init_con();
}

void clearScreen()
{
    tte_erase_screen();
    tte_set_pos(104, 152);
    tte_write("mattiebee.dev/4-e");
    tte_set_pos(0, 0);
}

void waitForInterrupt() {
    IntrWait(1, IRQ_SERIAL);
}

void activateLink() {
    irq_enable(II_SERIAL);

    REG_RCNT = REG_RCNT & ~R_MODE_GPIO;
    REG_SIOCNT = SIO_MODE_MULTI;
    REG_SIOCNT = REG_SIOCNT
        | SIO_IRQ
        | SIOM_CONNECTED
        | SIOM_SLAVE
        | SIOM_115200;
}

void waitForPlayerAssignment() {
    while((REG_SIOCNT & SIOM_ID_MASK) == 0);
}

void send(u16 data) {
    waitForInterrupt();
    REG_SIOMLT_SEND = data;
}

void sendAndExpect(u16 data, u16 expect) {
    u16 received;
    do {
        send(data);
        received = REG_SIOMULTI0;
    } while (received != expect);
}

u16 sendAndReceiveExcept(u16 data, u16 except) {
    u16 received;
    do {
        send(data);
        received = REG_SIOMULTI0;
    } while (received == except);
    return received;
}

bool connect() {
    sendAndExpect(HANDSHAKE_1, HANDSHAKE_1);
    sendAndExpect(HANDSHAKE_2, HANDSHAKE_2);
    sendAndExpect(HANDSHAKE_3, HANDSHAKE_3);

    u16 cardRequest = sendAndReceiveExcept(HANDSHAKE_3, HANDSHAKE_3);

    sendAndExpect(GAME_ANIMATING, EREADER_ANIMATING);
    send(EREADER_ANIMATING);

    switch(cardRequest) {
        case GAME_REQUEST_DEMO:
            sendAndExpect(EREADER_READY, GAME_READY_DEMO);
            break;

        case GAME_REQUEST_POWERUP:
            sendAndExpect(EREADER_READY, GAME_READY_POWERUP);
            break;

        case GAME_REQUEST_LEVEL:
            sendAndExpect(EREADER_READY, GAME_READY_LEVEL);
            break;

        default:
            return true; 
    }

    sendAndExpect(EREADER_SEND_READY, GAME_RECEIVE_READY);
    return false;
}

void sendBin(const void* file, u32 len) {
    send(EREADER_SEND_START);
    u32 checksum = 0;
    for (off_t o = CARD_HEADER_OFFSET; o < len; o += 2) {
        u16 block = *(u16 *)(file + o);
        send(block);
        checksum += block;
    }
    send(checksum & 0xffff);
    send(checksum >> 16);
    send(EREADER_SEND_END);
}

int main(void)
{
    irq_init(NULL);
    irq_enable(II_VBLANK);

    initScreen();
    clearScreen();

    const GBFS_FILE* gbfs = find_first_gbfs_file((void *)find_first_gbfs_file);
    if (!gbfs) {
        tte_write("A GBFS archive is required.\n");
        done();
    }

    activateLink();

    tte_write("Waiting...\n");
    waitForPlayerAssignment();

    tte_write("Connecting...\n");
    if (connect()) {
        tte_write("Connection failed.\n");
        done();
    }

    tte_write("Sending...\n");
    u32 len;
    const void* file = gbfs_get_nth_obj(gbfs, 0, NULL, &len);
    sendBin(file, len);

    tte_write("Done!\n");

    done();
}
