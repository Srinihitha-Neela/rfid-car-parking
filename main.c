#include <reg51.h>

sbit doorp = P2^0;
sbit doorn = P2^1;
sbit rs = P2^5;
sbit rw = P2^6;
sbit en = P2^7;

void lcddat(unsigned char);
void lcdcmd(unsigned char);
void lcddis(unsigned char *);
void lcd_init();
void serial_init();
void check();
void delay();
void mdelay();

unsigned char rfid[12], v1;

void main() {
    doorp = doorn = 0;
    serial_init();
    lcd_init();
    lcddis("RFID BASED");
    lcdcmd(0xc0);
    lcddis("CAR PARKING SYSTEM");
    mdelay();
    lcdcmd(0x01);

    while (1) {
        lcdcmd(0x01);
        lcddis("SWIPE YOUR CARD");
        for (v1 = 0; v1 < 12; v1++) {
            while (RI == 0);
            rfid[v1] = SBUF;
            RI = 0;
            SBUF = rfid[v1];
            while (TI == 0);
            TI = 0;
        }
        check();
    }
}

void check() {
    if (rfid[0] == '1' && rfid[1] == 'A' && rfid[2] == '3' && rfid[3] == '4' && rfid[4] == '5' && rfid[5] == '6' &&
        rfid[6] == '7' && rfid[7] == '8' && rfid[8] == '9' && rfid[9] == 'X' && rfid[10] == 'Y' && rfid[11] == 'Z') {
        
        lcdcmd(0x01);
        lcddis("MEMBER");    
        lcdcmd(0xc0);
        lcddis("Mr.A");
        delay(); delay();
        lcdcmd(0x01);
        doorp = 1; doorn = 0;
        lcddis("OPENING DOOR");
        lcdcmd(0xc0);
        lcddis("ALLOW INSIDE");
        mdelay();
        doorp = 0; doorn = 0;
        delay();
        lcdcmd(0x01);
        doorp = 0; doorn = 1;
        lcddis("DOOR CLOSING");
        mdelay();
        doorp = 0; doorn = 0;
    }
    else if (rfid[0] == '1' && rfid[1] == '2' && rfid[2] == 'B' && rfid[3] == '4' && rfid[4] == '5' && rfid[5] == '6' &&
             rfid[6] == '7' && rfid[7] == '8' && rfid[8] == '9' && rfid[9] == 'X' && rfid[10] == 'Y' && rfid[11] == 'Z') {

        lcdcmd(0x01);
        lcddis("MEMBER");    
        lcdcmd(0xc0);
        lcddis("Mr.B");
        delay(); delay();
        lcdcmd(0x01);
        doorp = 1; doorn = 0;
        lcddis("OPENING DOOR");
        lcdcmd(0xc0);
        lcddis("ALLOW INSIDE");
        mdelay();
        doorp = 0; doorn = 0;
        delay();
        lcdcmd(0x01);
        doorp = 0; doorn = 1;
        lcddis("DOOR CLOSING");
        mdelay();
        doorp = 0; doorn = 0;
    }
    else if (rfid[0] == '1' && rfid[1] == '2' && rfid[2] == '3' && rfid[3] == 'C' && rfid[4] == '5' && rfid[5] == '6' &&
             rfid[6] == '7' && rfid[7] == '8' && rfid[8] == '9' && rfid[9] == 'X' && rfid[10] == 'Y' && rfid[11] == 'Z') {

        lcdcmd(0x01);
        lcddis("MEMBER");    
        lcdcmd(0xc0);
        lcddis("Mr.C");
        delay(); delay();
        lcdcmd(0x01);
        doorp = 1; doorn = 0;
        lcddis("OPENING DOOR");
        lcdcmd(0xc0);
        lcddis("ALLOW INSIDE");
        mdelay();
        doorp = 0; doorn = 0;
        delay();
        lcdcmd(0x01);
        doorp = 0; doorn = 1;
        lcddis("DOOR CLOSING");
        mdelay();
        doorp = 0; doorn = 0;
    }
    else if (rfid[0] == '1' && rfid[1] == '2' && rfid[2] == '3' && rfid[3] == '4' && rfid[4] == 'D' && rfid[5] == '6' &&
             rfid[6] == '7' && rfid[7] == '8' && rfid[8] == '9' && rfid[9] == 'X' && rfid[10] == 'Y' && rfid[11] == 'Z') {

        lcdcmd(0x01);
        lcddis("MEMBER");    
        lcdcmd(0xc0);
        lcddis("Mr.D");
        delay(); delay();
        lcdcmd(0x01);
        doorp = 1; doorn = 0;
        lcddis("OPENING DOOR");
        lcdcmd(0xc0);
        lcddis("ALLOW INSIDE");
        mdelay();
        doorp = 0; doorn = 0;
        delay();
        lcdcmd(0x01);
        doorp = 0; doorn = 1;
        lcddis("DOOR CLOSING");
        mdelay();
        doorp = 0; doorn = 0;
    }
    else {
        lcdcmd(0x01);
        lcddis("NOT A MEMBER");
        lcdcmd(0xc0);
        lcddis("NO SLOT");
        mdelay();
    }
}

void lcd_init() {
    lcdcmd(0x38);
    lcdcmd(0x01);
    lcdcmd(0x10);
    lcdcmd(0x0c);
    lcdcmd(0x80);
}

void lcdcmd(unsigned char val) {
    P1 = val;
    rs = 0;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void lcddat(unsigned char val) {
    P1 = val;
    rs = 1;
    rw = 0;
    en = 1;
    delay();
    en = 0;
}

void delay() {
    unsigned int v5;
    for (v5 = 0; v5 < 6000; v5++);
}

void lcddis(unsigned char *s) {
    unsigned char w;
    for (w = 0; s[w] != '\0'; w++) {
        lcddat(s[w]);
    }
}

void serial_init() {
    SCON = 0x50;
    TMOD = 0x20;
    TH1 = -3;
    TR1 = 1;
}

void mdelay() {
    unsigned int v6, v7;
    for (v6 = 0; v6 < 2; v6++) {
        for (v7 = 0; v7 < 60000; v7++);
    }
}
