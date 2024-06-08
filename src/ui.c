#include <string.h>
#include <tonc.h>

#include "link.h"

void initScreen()
{
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
    tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
    tte_init_con();
}

void clearScreen()
{
    tte_erase_screen();
    tte_set_pos(0, 152);
    //         ----+----1----+----2----+----3
    tte_write("mattiebee.dev/4-e         v2.0");
    tte_set_pos(0, 0);
}

void status(const char *message, const char *name)
{
    clearScreen();

    if (name != NULL) tte_write(name);

    int len = strlen(message);
    int x = 120 - (len * 4);

    tte_set_pos(x, 76);
    tte_write(message);
}

void done(const char *message, const char *name)
{
    clearScreen();

    if (name != NULL) tte_write(name);

    int len = strlen(message);
    int x = 120 - (len * 4);

    tte_set_pos(x, 68);
    tte_write(message);

    tte_set_pos(16, 84);
    tte_write("Press any button to reset.");

    while (REG_KEYINPUT == KEY_MASK)
        VBlankIntrWait();
    while (REG_KEYINPUT != KEY_MASK)
        VBlankIntrWait();

    SoftReset();
}
