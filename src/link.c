#include <tonc.h>

#include "link.h"

void activateLink()
{
    irq_enable(II_SERIAL);

    REG_RCNT = REG_RCNT & ~R_MODE_GPIO;
    REG_SIOCNT = SIO_MODE_MULTI;
    REG_SIOCNT = REG_SIOCNT | SIO_IRQ | SIOM_CONNECTED | SIOM_SLAVE | SIOM_115200;
}

void waitForPlayerAssignment()
{
    do
        IntrWait(1, IRQ_SERIAL);
    while ((REG_SIOCNT & SIOM_ID_MASK) == 0);
}

void send(u16 data)
{
    IntrWait(1, IRQ_SERIAL);
    REG_SIOMLT_SEND = data;
}

void sendAndExpect(u16 data, u16 expect)
{
    u16 received;
    do
    {
        send(data);
        received = REG_SIOMULTI0;
    } while (received != expect);
}

u16 sendAndReceiveExcept(u16 data, u16 except)
{
    u16 received;
    do
    {
        send(data);
        received = REG_SIOMULTI0;
    } while (received == except);
    return received;
}
