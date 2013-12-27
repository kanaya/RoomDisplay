//=========================================
// TLC5940 (16channel led driver)
//      This program supports the cascading of the TLC5940.
//       This program is not tested. 
// 
// cascad number, please be set between 1 and 20 N_LEDS.
//  Display data D_grayData [N_LEDS] [16] Please set to.
//==========================================

#include "mbed.h"

#define N_TEXTS (127+16)

char *texts[] = {
    " JUL-07-2005",
    " SEP-09-2005", " FULL SQUAD ",
    " NOV-27-2005",
    " DEC-25-2005",
    " JAN-22-2006",
    " FEB-26-2006",
    " APR-23-2006",
    " JUN-25-2006", " THE FIRST>>", " ANIVERSARY ",
    " AUG-26-2006", " TROPICAL >>", " GROOVERS   ",
    " OCT-22-2006", " PUMPKIN  >>", " RASTA      ",
    " DEC-29-2006", " 2006 FINAL ",
    " JAN-27-2007", " SOUL SPIDER", " 007        ",
    " APR-22-2007", " GREENBREAKS",
    " JUN-15-2007", " THE SECOND>", " ANIVERSARY ",
    " AUG-26-2007", " COSMICDISCO",
    " OCT-28-2007", " VS HUMAN >>", " ELEMENTS   ",
    " DEC-30-2007", " 2007 FINAL ",
    " FEB-24-2008", " WITH DJ  >>", " SHAKEY     ",
    " APR-28-2008", " VS BLACK >>", " EDITION    ",
    " JUN-22-2008", " THE THIRD>>", " ANIVERSARY ",
    " AUG-31-2008", " REBIRTH    ",
    " OCT-26-2008",
    " DEC-28-2008", " MATSURI    ",
    " FEB-22-2009", " CHANGE     ",
    " JUN-28-2009", " THE FOURTH>", " ANIVERSARY ",
    " SEP-21-2009", " GOLDEN     ",
    " DEC-27-2009", " NEW WAVE   ",
    " APR-18-2010", " NEW SCHOOL ",
    " JUN-27-2010", " THE FIFTH>>", " ANIVERSARY ",
    " SEP-22-2010", " DEEP INSIDE",
    " DEC-22-2010", " BLACK    >>", " EMPEROR    ",
    " MAR-04-2011",
    " JUN-22-2011", " FANFARE    ",
    "  0731  2005", "  1222  2013",
    "  SENSE OF  ", "   GROOVE   ",
    " SOG SOG SOG",
    " THE    ROOM",
    "    *TODAY* ",
    " SABI TECH>>", " RIDERS     ",
    " TSUYOSHI >>", " SAITO BLA>>", " CK EDITION ",
    " *TAKEYA* >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " DANJOH   >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " KAJITSU  >>", " SOG/DISCO>>", " VIKING     ",
    " 3S       >>", " SOG/UNIT >>", " 3S         ",
    " ACCHI    >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " 428GRAFFI>>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " TOMO     >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " MITCHY   >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " TAKE-C   >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " SHIGE    >>", " SOG        ", " SOG >>>    ", " SOG >>> >>>",
    " AI FOUGY >>", " PHUTURISTIC", " BLUES      ",
    " DJ FLIGHT  ",
    " DJ ADDICT>>", " ION        ",
    " DJ SUV     ",
    " NATURAL MC ",
    " BAGGS    >>", " BREAKBEAT>>", " SCIENCE    ",
    " MARK HOLMES", " AS KNOWN AS", " MC PROOF   ",
    " INFLUXDATUM", " FORMATION>>", " RECORDS  >>", " [US/UK]    ",
    " TIGI     >>", " BREAKBEAT>>", " SCIENCE    ",
    " JESSE MANN+", " WIZE       " };
    

#define b0000 0
#define b0001 1
#define b0010 2
#define b0011 3
#define b0100 4
#define b0101 5
#define b0110 6
#define b0111 7
#define b1000 8
#define b1001 9
#define b1010 10
#define b1011 11
#define b1100 12
#define b1101 13
#define b1110 14
#define b1111 15

#define pack4(a, b, c, d) (((a) << 12) | ((b) << 8) | ((c) << 4) | (d)) 

#define N_LEDS 12   // cascade No (1 - 20)
#define MAX_BRIGHTNESS 4096
#define WAIT 1

// TLC5940 control pin setting
SPI spi(p5, p6, p7);    //SIN (p6), SCLK,GSCLK(p7)

DigitalOut XLAT(p20);
DigitalOut BLANK(p19);

DigitalOut myled1(LED1);
DigitalOut myled3(LED3);

int letter_A = pack4(b0000, b1010, b0010, b0011);
int letter_B = pack4(b1011, b0001, b1100, b1011);
int letter_C = pack4(b1010, b0100, b1100, b1000);
int letter_D = pack4(b0011, b0110, b0101, b1010);
int letter_E = pack4(b1010, b0101, b1100, b1001);
int letter_F = pack4(b1010, b0101, b1000, b0001);
int letter_G = pack4(b1010, b0100, b1100, b1011);
int letter_H = pack4(b1000, b0011, b1000, b0011);
int letter_I = pack4(b0011, b0100, b0101, b1000);
int letter_J = pack4(b0000, b0010, b1100, b1010);
int letter_K = pack4(b1000, b1001, b1000, b0100);
int letter_L = pack4(b1000, b0000, b1100, b1000);
int letter_M = pack4(b1100, b1010, b1000, b0010);
int letter_N = pack4(b1100, b0010, b1000, b0110);
int letter_O = pack4(b1010, b0110, b1100, b1010);
int letter_P = pack4(b1010, b0111, b1000, b0001);
int letter_Q = pack4(b1010, b0110, b1100, b1110);
int letter_R = pack4(b1010, b0111, b1000, b0101);
int letter_S = pack4(b1010, b0101, b0100, b1011);
int letter_T = pack4(b0011, b0100, b0001, b0000);
int letter_U = pack4(b1000, b0010, b1100, b1010);
int letter_V = pack4(b1000, b1000, b1010, b0000);
int letter_W = pack4(b1000, b0010, b1010, b0110);
int letter_X = pack4(b0100, b1000, b0010, b0100);
int letter_Y = pack4(b0100, b1000, b0001, b0000);
int letter_Z = pack4(b0010, b1100, b0110, b1000);
int letter_0 = pack4(b1010, b1110, b1110, b1010);
int letter_1 = pack4(b0001, b0000, b0001, b0000);
int letter_2 = pack4(b0010, b0110, b0110, b1001);
int letter_3 = pack4(b0010, b0111, b0100, b1011);
int letter_4 = pack4(b1001, b0001, b0001, b0001);
int letter_5 = pack4(b1010, b0101, b0100, b1100);
int letter_6 = pack4(b1010, b0101, b1100, b1011);
int letter_7 = pack4(b0010, b1100, b0010, b0000);
int letter_8 = pack4(b1010, b0111, b1100, b1011);
int letter_9 = pack4(b1010, b0111, b0100, b1011);
int letter_minus = pack4(b0000, b0001, b0000, b0001);
int letter_plus = pack4(b0001, b0001, b0001, b0001);
int letter_slash = pack4(b0000, b1000, b0010, b0000);
int letter_asterisk = pack4(b0100, b1001, b0010, b0101);
int letter_us = pack4(b0000, b0000, b0100, b1000);
int letter_gt = pack4(b0100, b0000, b0010, b0000);
int letter_lt = pack4(b0000, b1000, b0000, b0100);
int letter_bra = pack4(b0001, b0100, b0001, b1000);
int letter_ket = pack4(b0011, b0000, b0101, b0000);
int letter_space = pack4(b0000, b0000, b0000, b0000);

int ascii2letter[128] = {
    /* 00 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 20 */ letter_space, 0, 0, 0, 0, 0, 0, 0, 0, 0, letter_asterisk, letter_plus, 0, letter_minus, 0, letter_slash,
    /* 30 */ letter_0, letter_1, letter_2, letter_3, letter_4, letter_5, letter_6, letter_7, letter_8, letter_9, 0, 0, letter_lt, 0, letter_gt, 0,
    /* 40 */ 0, letter_A, letter_B, letter_C, letter_D, letter_E, letter_F, letter_G, letter_H, letter_I, letter_J, letter_K, letter_L, letter_M, letter_N, letter_O,
    /* 50 */ letter_P, letter_Q, letter_R, letter_S, letter_T, letter_U, letter_V, letter_W, letter_X, letter_Y, letter_Z, letter_bra, 0, letter_ket, 0, letter_us,
    /* 60 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 70 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void clear(int *p) {
    for (int n = 0; n < N_LEDS * 16; ++n) {
        p[n] = 0;
    }
}

void putLetter(int *p, int letter, int column) {
    for (int i = 0; i < 16; ++i) {
        int j = 15 - i;
        int on_or_off = (letter >> j) & 0x01;
        p[column * 16 + i] = on_or_off;
    }
}

void putRandomPattern(int *p) {
    for (int i = 0; i < N_LEDS * 16; ++i) {
        p[i] = rand() % 2;
    }
}

/**********************************
* SPI Initalize (for TLC5960 control)
**********************************/
void spiInitialize(void){
    spi.format(12,0);
    spi.frequency(30000000);
}

/*********************************
* TLC5940 Gray Data clear
*********************************/
void tlc5940Clear(void){
    for(int i = 0; i < (N_LEDS * 16); ++i){
        int whoami = spi.write(0);
    }
    XLAT = 1;
    XLAT = 0;
}

/**********************************
* TLC5940 Gray Data Display & next data send
***********************************/
void tlc5940DataSend(int *p, int grayLevel) {
    BLANK = 1;
    BLANK = 0;

/*
    for(int i = 0; i < (342 - (N_LEDS * 16)); i++){
        spi.write(0);
    }
*/
    
    for (int n = 0; n < N_LEDS * 16; ++n){
        spi.write(p[n] * grayLevel);
    }
        
    XLAT = 1;
    XLAT = 0;
}

void showString16(const char *letters) {
    // length of letters must be 16
    int grayData[N_LEDS * 16];
    clear(grayData);
    for (int j = 0; j < 16 / N_LEDS; ++j) {
        for (int i = 0; i < N_LEDS; ++i) {
            putLetter((int *)grayData, ascii2letter[letters[j * N_LEDS + i]], i);
        }
        for (int g_up = 0; g_up < MAX_BRIGHTNESS; ++g_up) {
            for (int dummy = 0; dummy < WAIT; ++dummy) {
                tlc5940DataSend((int *)grayData, g_up);
            }
        }
        for (int g_down = MAX_BRIGHTNESS - 1; g_down >= 0; --g_down) {
            for (int dummy = 0; dummy < WAIT; ++dummy) {
                tlc5940DataSend((int *)grayData, g_down);
            }
        }                
    }
}

void showString12(const char *letters) {
    // length of letters must be 16
    int grayData[N_LEDS * 16];
    clear(grayData);
    for (int i = 0; i < 12; ++i) {
        putLetter((int *)grayData, ascii2letter[letters[i]], i);
    }
    for (int g_up = 0; g_up < MAX_BRIGHTNESS; ++g_up) {
        for (int dummy = 0; dummy < WAIT; ++dummy) {
            tlc5940DataSend((int *)grayData, g_up);
        }
    }
    for (int g_down = MAX_BRIGHTNESS - 1; g_down >= 0; --g_down) {
        for (int dummy = 0; dummy < WAIT; ++dummy) {
            tlc5940DataSend((int *)grayData, g_down);
        }
    }
}

void showStrings(int n_strings, char *strings[]) {
    for (int i = 0; i < n_strings; ++i) {
        showString12(strings[i]);
    }   
}

void showRandomPattern() {
    int grayData[N_LEDS * 16];
    clear(grayData);
    putRandomPattern((int *)grayData);
    for (int g_up = 0; g_up < MAX_BRIGHTNESS; ++g_up) {
        for (int dummy = 0; dummy < WAIT; ++dummy) {
            tlc5940DataSend((int *)grayData, g_up);
        }
    }
    for (int g_down = MAX_BRIGHTNESS - 1; g_down >= 0; --g_down) {
        for (int dummy = 0; dummy < WAIT; ++dummy) {
            tlc5940DataSend((int *)grayData, g_down);
        }
    }
}



/************************************
* main
************************************/
int main() {

    // SPI initalize
    spiInitialize();
    tlc5940Clear();
    
    while (1) {
        // SENS E_OF_ GROO VE
        // showString16("*SENSE_OF_GROOVE");
        // showRandomPattern();
        showStrings(N_TEXTS, texts);
    }
}
