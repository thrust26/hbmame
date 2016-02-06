// license:BSD-3-Clause
// copyright-holders:Kevin Horton,Jonathan Gevaryahu,Sandro Ronco,hap
/******************************************************************************

    Fidelity Electronics Z80 based board driver
    for 6502 based boards, see drivers/fidel6502.cpp (documentation is in this driver)

    TODO:
    - Figure out why it says the first speech line twice; it shouldn't?
      It sometimes does this on Voice Sensory Chess Challenger real hardware.
      It can also be heard on Advanced Voice Chess Challenger real hardware, but not the whole line:
      "I I am Fidelity's chess challenger", instead.
    - correctly hook up VBRC speech so that the z80 is halted while words are being spoken

    Chess pieces are required, but theoretically blindfold chess is possible.
    Chessboard artwork is provided for boards with pressure/magnet sensors.
    Read the official manual(s) on how to play.
    
    Keypad legend:
    - RE: Reset
    - CL: Clear
    - EN: Enter
    - PB: Problem Mode
    - PV: Position Verification
    - LV: Playing Levels
    - TB: Take Back
    - DM: Display Move/Double Move
    - RV: Reverse
    - ST: Set/Stop
    - TM: Time
    
    Peripherals, compatible with various boards:
    - Fidelity Challenger Printer - thermal printer, MCU=?
    
    Program/data cartridges, for various boards, some cross-compatible:
    - CG6: Greatest Chess Games 1
    - CAC: Challenger Advanced Chess - 8KB 101-1038A01
    - CB9: Challenger Book Openings 1 - 8KB?
    - CB16: Challenger Book Openings 2 - 8+8KB 101-1042A01,02
    - others are alt. titles of these?
    
    Board hardware descriptions below.
    Detailed RE work done by Kevin 'kevtris' Horton, except where noted

******************************************************************************

Voice Chess Challenger (VCC) (version A and B?)
Advanced Voice Chess Challenger (UVC)
Grandmaster Voice Chess Challenger
Decorator Challenger (FCC)

(which share the same hardware)
----------------------
The CPU is a Z80 running at 4MHz.  The TSI chip runs at around 25KHz, using a
470K / 100pf RC network.  This system is very very basic, and is composed of just
the Z80, 4 ROMs, the TSI chip, and an 8255.

The Z80's interrupt inputs are all pulled to VCC, so no interrupts are used.

Reset is connected to a power-on reset circuit and a button on the keypad (marked RE).

The TSI chip connects to a 4K ROM.  All of the 'Voiced' Chess Challengers
use this same ROM  (three or four).  The later chess boards use a slightly different part
number, but the contents are identical.

Memory map (VCC):
-----------
0000-0FFF: 4K 2332 ROM 101-32103
1000-1FFF: 4K 2332 ROM VCC2
2000-2FFF: 4K 2332 ROM VCC3
4000-5FFF: 1K RAM (2114 SRAM x2)
6000-FFFF: empty

Memory map (UVC):
-----------
0000-1FFF: 8K 2364 ROM 101-64017
2000-2FFF: 4K 2332 ROM 101-32010
4000-5FFF: 1K RAM (2114 SRAM x2)
6000-FFFF: empty

Port map:
---------
00-03: 8255 port chip, mirrored over the 00-FF range; program accesses F4-F7

8255 connections:
-----------------
PA.0 - segment G, TSI A0 (W)
PA.1 - segment F, TSI A1 (W)
PA.2 - segment E, TSI A2 (W)
PA.3 - segment D, TSI A3 (W)
PA.4 - segment C, TSI A4 (W)
PA.5 - segment B, TSI A5 (W)
PA.6 - segment A, language latch Data (W)
PA.7 - TSI START line, language latch clock (W, see below)

PB.0 - dot commons (W)
PB.1 - NC
PB.2 - digit 0, bottom dot (W)
PB.3 - digit 1, top dot (W)
PB.4 - digit 2 (W)
PB.5 - digit 3 (W)
PB.6 - enable language switches (W, see below)
PB.7 - TSI BUSY line (R)

(button rows pulled up to 5V through 2.2K resistors)
PC.0 - button row 0, German language jumper (R)
PC.1 - button row 1, French language jumper (R)
PC.2 - button row 2, Spanish language jumper (R)
PC.3 - button row 3, special language jumper (R)
PC.4 - button column A (W)
PC.5 - button column B (W)
PC.6 - button column C (W)
PC.7 - button column D (W)

language switches:
------------------
When PB.6 is pulled low, the language switches can be read.  There are four.
They connect to the button rows.  When enabled, the row(s) will read low if
the jumper is present.  English only VCC's do not have the 367 or any pads stuffed.
The jumpers are labelled: French, German, Spanish, and special.

language latch:
---------------
There's an unstuffed 7474 on the board that connects to PA.6 and PA.7.  It allows
one to latch the state of A12 to the speech ROM.  The English version has the chip
missing, and a jumper pulling "A12" to ground.  This line is really a negative
enable.

To make the VCC multi-language, one would install the 74367 (note: it must be a 74367
or possibly a 74LS367.  A 74HC367 would not work since they rely on the input current
to keep the inputs pulled up), solder a piggybacked ROM to the existing English
speech ROM, and finally install a 7474 dual flipflop.

This way, the game can then detect which secondary language is present, and then it can
automatically select the correct ROM(s).  I have to test whether it will do automatic
determination and give you a language option on power up or something.


******************************************************************************

Chess Challenger 10 (CC10)
-------------------
4 versions are known to exist: A,B,C,D. Strangely, version C has an 8080
instead of Z80. Chess Challenger 1,3 and 7 also run on very similar hardware.

This is an earlier hardware upon which the VCC and UVC above were based on;
The hardware is nearly the same; in fact the only significant differences are
the RAM being located in a different place, the lack of a speech chip, and
the connections to ports A and B on the PPI:

8255 connections:
-----------------
PA.0 - segment G (W)
PA.1 - segment F (W)
PA.2 - segment E (W)
PA.3 - segment D (W)
PA.4 - segment C (W)
PA.5 - segment B (W)
PA.6 - segment A (W)
PA.7 - 'beeper' direct speaker output (W)

The beeper is via a 556 timer, fixed-frequency at around 1300-1400Hz.
Not all hardware configurations include the beeper.

PB.0 - dot commons (W)
PB.1 - NC
PB.2 - digit 0, bottom dot (W)
PB.3 - digit 1, top dot (W)
PB.4 - digit 2 (W)
PB.5 - digit 3 (W)
PB.6 - NC
PB.7 - Mode select (cc3 vs cc10, R) - note: there is no CC3 with 16 buttons

(button rows pulled up to 5V through 2.2K resistors)
PC.0 - button row 0 (R)
PC.1 - button row 1 (R)
PC.2 - button row 2 (R)
PC.3 - button row 3 (R)
PC.4 - button column A (W)
PC.5 - button column B (W)
PC.6 - button column C (W)
PC.7 - button column D (W)


******************************************************************************

Chess Challenger 7 (BCC)
------------------------
RE information from netlist by Berger

Zilog Z80A, 3.579MHz from XTAL
Z80 IRQ/NMI unused, no timer IC.
This is a cost-reduced design from CC10, no special I/O chips.

Memory map:
-----------
0000-0FFF: 4K 2332 ROM CN19103N BCC-REVB.
2000-2FFF: ROM/RAM bus conflict!
3000-3FFF: 256 bytes RAM (2111 SRAM x2)
4000-FFFF: Z80 A14/A15 not connected

Port map (Write):
---------
D0-D3: digit select and keypad mux
D4: LOSE led
D5: CHECK led
A0-A2: NE591 A0-A2
D7: NE591 D (_C not used)
NE591 Q0-Q6: digit segments A-G
NE591 Q7: buzzer

Port map (Read):
---------
D0-D3: keypad row


******************************************************************************

Voice Bridge Challenger (Model VBRC, later reissued as Model 7002)
and Bridge Challenger 3 (Model 7014)
(which both share the same* hardware)
--------------------------------
* The Bridge Challenger 3 does not actually have the 8 LEDs nor the
latches which operate them populated and the plastic indicator cap locations
are instead are covered by a piece of plastic, but they do work if manually
added.

This unit is similar in construction kinda to the chess challengers, however it
has an 8041 which does ALL of the system I/O.  The Z80 has NO IO AT ALL other than
what is performed through the 8041!

The main CPU is a Z80 running at 2.5MHz

INT connects to VCC (not used)
NMI connects to VCC (not used)
RST connects to power on reset, and reset button

The 8041 runs at 5MHz.

Memory Map:
-----------
0000-1FFF: 8K 101-64108 ROM
2000-3FFF: 8K 101-64109 ROM
4000-5FFF: 8K 101-64110 ROM
6000-7FFF: 1K of RAM (2114 * 2)
8000-DFFF: unused
E000-FFFF: write to TSI chip

NOTE: when the TSI chip is written to, the CPU IS STOPPED.  The CPU will run again
when the word is done being spoken.  This is because D0-D5 run to the TSI chip directly.

The TSI chip's ROM is 4K, and is marked 101-32118.  The clock is the same as the Chess
Challengers- 470K/100pf which gives a frequency around 25KHz or so.

Port Map:
---------
00-FF: 8041 I/O ports (A0 selects between the two)

8041 pinout:
------------
(note: columns are pulled up with 10K resistors)

P10 - column H, RD LED, VFD grid 0
P11 - column G, DB LED, VFD grid 1
P12 - column F, <>V LED, VFD grid 2
P13 - column E, ^V LED, VFD grid 3
P14 - column D, W LED, VFD grid 4
P15 - column C, S LED, VFD grid 5
P16 - column B, E LED, VFD grid 6
P17 - column A, N LED, VFD grid 7

P20 - I/O expander
P21 - I/O expander
P22 - I/O expander
P23 - I/O expander
P24 - row 0 through inverter
P25 - row 1 through inverter
P26 - row 2 through inverter
P27 - row 3 through inverter

PROG - I/O expander

T0 - optical card sensor (high = bright/reflective, low = dark/non reflective)
T1 - connects to inverter, then nothing?

D8243C I/O expander:
--------------------
P4.0 - segment M
P4.1 - segment L
P4.2 - segment N
P4.3 - segment E

P5.0 - segment D
P5.1 - segment I
P5.2 - segment K
P5.3 - segment J

P6.0 - segment A
P6.1 - segment B
P6.2 - segment F
P6.3 - segment G

P7.0 - LED enable (high = LEDs can be lit.  low = LEDs will not light)
P7.1 - goes through inverter, to pads that are not used
P7.2 - segment C
P7.3 - segment H

button matrix:
--------------
the matrix is composed of 8 columns by 4 rows.

     A  B  C  D     E  F  G  H
     -------------------------
0-   RE xx CL EN    J  Q  K  A
1-   BR PB DB SC    7  8  9 10
2-   DL CV VL PL    3  4  5  6
3-   cl di he sp   NT  P  1  2

xx - speaker symbol
cl - clubs symbol
di - diamonds symbol
he - hearts symbol
sp - spades symbol

NOTE: RE is not wired into the matrix, and is run separately out.

There are 8 LEDs, and an 8 digit 14 segment VFD with commas and periods.
This display is the same one as can be found on the speak and spell.

       A       * comma
  ***********  *
 * *I  *J K* *
F*  *  *  *  *B
 *   * * *   *
  G**** *****H
 *   * * *   *
E*  *  *  *  *C
 * *N  *M L* *
  ***********  *decimal point
       D

The digits of the display are numbered left to right, 0 through 7 and are controlled
by the grids.  hi = grid on, hi = segment on.

A detailed description of the hardware can be found also in the patent 4,373,719.


******************************************************************************

Champion Sensory Chess Challenger (CSC)
---------------------------------------

Memory map:
-----------
0000-07FF: 2K of RAM
0800-0FFF: 1K of RAM (note: mirrored twice)
1000-17FF: PIA 0 (display, TSI speech chip)
1800-1FFF: PIA 1 (keypad, LEDs)
2000-3FFF: 101-64019 ROM (also used on the regular sensory chess challenger)
4000-7FFF: mirror of 0000-3FFF
8000-9FFF: not used
A000-BFFF: 101-1025A03 ROM
C000-DFFF: 101-1025A02 ROM
E000-FDFF: 101-1025A01 ROM
FE00-FFFF: 512 byte 74S474 PROM

CPU is a 6502 running at 1.95MHz (3.9MHz resonator, divided by 2)

NMI is not used.
IRQ is connected to a 600Hz oscillator (38.4KHz divided by 64).
Reset is connected to a power-on reset circuit.

PIA 0:
------
PA0 - 7seg segments E, TSI A0
PA1 - 7seg segments D, TSI A1
PA2 - 7seg segments C, TSI A2
PA3 - 7seg segments H, TSI A3
PA4 - 7seg segments G, TSI A4
PA5 - 7seg segments F, TSI A5
PA6 - 7seg segments B
PA7 - 7seg segments A

PB0 - A12 on speech ROM (if used... not used on this model, ROM is 4K)
PB1 - START line on TSI
PB2 - white wire
PB3 - BUSY line from TSI
PB4 - hi/lo TSI speaker volume
PB5 - button row 9
PB6 - selection jumper (resistor to 5V)
PB7 - selection jumper (resistor to ground)

CA1 - NC
CA2 - violet wire

CB1 - NC
CB2 - NC (connects to pin 14 of soldered connector)

PIA 1:
------
PA0 - button row 1
PA1 - button row 2
PA2 - button row 3
PA3 - button row 4
PA4 - button row 5
PA5 - button row 6
PA6 - 7442 selector bit 0
PA7 - 7442 selector bit 1

PB0 - LED row 1
PB1 - LED row 2
PB2 - LED row 3
PB3 - LED row 4
PB4 - LED row 5
PB5 - LED row 6
PB6 - LED row 7
PB7 - LED row 8

CA1 - button row 7
CA2 - selector bit 3

CB1 - button row 8
CB2 - selector bit 2

Selector: (attached to PIA 1, outputs 1 of 10 pins low.  7442)
---------
output # (selected turns this column on, and all others off)
0 - LED column A, button column A, 7seg digit 1
1 - LED column B, button column B, 7seg digit 2
2 - LED column C, button column C, 7seg digit 3
3 - LED column D, button column D, 7seg digit 4
4 - LED column E, button column E
5 - LED column F, button column F
6 - LED column G, button column G
7 - LED column H, button column H
8 - button column I
9 - Tone line (toggle to make a tone in the buzzer)

The rows/columns are indicated on the game board:

 ABCDEFGH   I
--------------
|            | 8
|            | 7
|            | 6
|            | 5
|            | 4
|            | 3
|            | 2
|            | 1
--------------

The "lone LED" is above the control column.
column I is the "control column" on the right for starting a new game, etc.

The upper 6 buttons are connected as such:

column A - speak
column B - RV
column C - TM
column D - LV
column E - DM
column F - ST

these 6 buttons use row 9 (connects to PIA 0)

LED display:
------------
43 21 (digit number)
-----
88:88

The LED display is four 7 segment digits.  normal ABCDEFG lettering is used for segments.

The upper dot is connected to digit 3 common
The lower dot is connected to digit 4 common
The lone LED is connected to digit 1 common

All three of the above are called "segment H".


******************************************************************************

Voice Sensory Chess Challenger (VSC)
------------------------------------
The display/button/LED/speech technology is identical to the above product.
Only the CPU board was changed.  As such, it works the same but is interfaced
to different port chips this time.

Hardware:
---------
On the board are 13 chips.

The CPU is a Z80A running at 3.9MHz, with 20K of ROM and 1K of RAM mapped.
I/O is composed of an 8255 triple port adaptor, and a Z80A PIO parallel I/O
interface.

There's the usual TSI S14001A speech synth with its requisite 4K ROM which is the
same as on the other talking chess boards.  The TSI chip is running at 26.37KHz.
It uses a 470K resistor and a 100pf capacitor.

The "perfect" clock would be 1/RC most likely (actually this will be skewed a tad by
duty cycle of the oscillator) which with those parts values gives 21.27KHz.  The
formula is probably more likely to be 1/1.2RC or so.

Rounding out the hardware are three driver chips for the LEDs, a 7404 inverter to
run the crystal osc, a 555 timer to generate a clock, and a 74138 selector.

NMI runs to a 555 oscillator that generates a 600Hz clock (measured: 598.9Hz.  It has a multiturn pot to adjust).
INT is pulled to 5V
RST connects to a power-on reset circuit

Memory map:
-----------
0000-1FFF: 8K ROM 101-64018
2000-3FFF: 8K ROM 101-64019 (also used on the sensory champ. chess challenger)
4000-5FFF: 4K ROM 101-32024
6000-7FFF: 1K of RAM (2114 * 2)
8000-FFFF: not used, maps to open bus

Port map:
---------
There's only two chips in the portmap, an 8255 triple port chip, and a Z80A PIO
parallel input/output device.

Decoding isn't performed using a selector, but instead address lines are used.

A2 connects to /CE on the 8255
A3 connects to /CE on the Z80A PIO

A0 connects to port A/B select on PIO & A0 of 8255
A1 connects to control/data select on PIO & A1 of 8255

So to enable only the 8255, you'd write/read to 08-0Bh for example
To enable only the PIO, you'd write/read to 04-07h for example.

writing to 00-03h will enable and write to BOTH chips, and reading 00-03h
will return data from BOTH chips (and cause a bus conflict).  The code probably
never does either of these things.

Likewise, writing/reading to 0Ch-0Fh will result in open bus, because neither chip's
enable line will be low.

This sequence repeats every 16 addresses.  So to recap:

00-03: both chips enabled (probably not used)
04-07: PIO enabled
08-0B: 8255 enabled
0C-0F: neither enabled

10-FF: mirrors of 00-0F.

Refer to the Sensory Champ. Chess Chall. above for explanations of the below
I/O names and labels.  It's the same.

8255:
-----
PA.0 - segment D, TSI A0
PA.1 - segment E, TSI A1
PA.2 - segment F, TSI A2
PA.3 - segment A, TSI A3
PA.4 - segment B, TSI A4
PA.5 - segment C, TSI A5
PA.6 - segment G
PA.7 - segment H

PB.0 - LED row 1
PB.1 - LED row 2
PB.2 - LED row 3
PB.3 - LED row 4
PB.4 - LED row 5
PB.5 - LED row 6
PB.6 - LED row 7
PB.7 - LED row 8

PC.0 - LED column A, button column A, 7seg digit 1
PC.1 - LED column B, button column B, 7seg digit 2
PC.2 - LED column C, button column C, 7seg digit 3
PC.3 - LED column D, button column D, 7seg digit 4
PC.4 - LED column E, button column E
PC.5 - LED column F, button column F
PC.6 - LED column G, button column G
PC.7 - LED column H, button column H

Z80A PIO:
---------
PA.0 - button row 1
PA.1 - button row 2
PA.2 - button row 3
PA.3 - button row 4
PA.4 - button row 5
PA.5 - button row 6
PA.6 - button row 7
PA.7 - button row 8

PB.0 - button column I
PB.1 - button column J
PB.2 - hi/lo TSI speaker volume
PB.3 - violet wire
PB.4 - white wire (and TSI BUSY line)
PB.5 - selection jumper input (see below)
PB.6 - TSI start line
PB.7 - TSI ROM A12 line

selection jumpers:
------------------
These act like another row of buttons.  It is composed of two diode locations,
so there's up to 4 possible configurations.  My board does not have either diode
stuffed, so this most likely is "English".  I suspect it selects which language to use
for the speech synth.  Of course you need the other speech ROMs for this to function
properly.

Anyways, the two jumpers are connected to button columns A and B and the common
connects to Z80A PIO PB.5, which basically makes a 10th button row.  I would
expect that the software reads these once on startup only.


******************************************************************************

Sensory Chess Challenger (SC12-B, 6086)
4 versions are known to exist: A,B,C, and X, with increasing CPU speed.
---------------------------------
RE information from netlist by Berger

8*(8+1) buttons, 8+8+2 red LEDs
DIN 41524C printer port
36-pin edge connector
CPU is a R65C02P4, running at 4MHz

NE556 dual-timer IC:
- timer#1, one-shot at power-on, to CPU _RESET
- timer#2: R1=82K, R2=1K, C=22nf, to CPU _IRQ: ~780Hz, active low=15.25us

Memory map:
-----------
6000-0FFF: 4K of RAM (2016 * 2)
2000-5FFF: cartridge
6000-7FFF: control(W)
8000-9FFF: 8K ROM SSS SCM23C65E4
A000-BFFF: keypad(R)
C000-DFFF: 4K ROM TI TMS2732AJL-45
E000-FFFF: 8K ROM Toshiba TMM2764D-2

control: (74LS377)
--------
Q0-Q3: 7442 A0-A3
Q4: enable printer port pin 1 input
Q5: printer port pin 5 output
Q6,Q7: LEDs common anode

7442 0-8: input mux and LEDs cathode
7442 9: buzzer

The keypad is read through a 74HC251, where S0,1,2 is from CPU A0,1,2, Y is connected to CPU D7.
If control Q4 is set, printer data can be read from I0.


******************************************************************************

Voice Excellence (model 6092)
----------------
PCB 1: 510.1117A02, appears to be identical to other "Excellence" boards
CPU: GTE G65SC102P-3, 32 KB PRG ROM: AMI 101-1080A01(IC5), 8192x8 SRAM SRM2264C10(IC6)
2 rows of LEDs on the side: 1*8 green, 1*8 red

PCB 2: 510.1117A01
Speech: TSI S14001A, 32 KB ROM: AMI 101-1081A01(IC2)
Dip Switches set ROM A13 and ROM A14, on the side of the board

ROM A12 is tied to S14001A's A11 (yuck)
ROM A11 is however tied to the CPU's XYZ

0000_07FF - Spanish 1/4
0800_0FFF - Spanish 3/4
1000_17FF - Spanish 2/4
1800_1FFF - Spanish 4/4

2000_27FF - French 1/4
2800_2FFF - French 3/4
3000_3FFF - French 2/4
3800_3FFF - French 4/4

4000_47FF - German 1/4
4800_4FFF - German 3/4
5000_57FF - German 2/4
5800_5FFF - German 4/4

6000_67FF - English 1/2
6800_6FFF - Bridge Challenger 1/2
7000_77FF - English 2/2
7800_7FFF - Bridge Challenger 2/2

******************************************************************************/

#include "emu.h"
#include "cpu/z80/z80.h"
#include "cpu/mcs48/mcs48.h"
#include "machine/i8255.h"
#include "machine/i8243.h"
#include "machine/z80pio.h"
#include "sound/beep.h"

#include "includes/fidelz80.h"

// internal artwork
#include "fidel_cc.lh"
#include "fidel_bcc.lh"
#include "fidel_vcc.lh"
#include "fidel_vbrc.lh"
#include "fidel_vsc.lh" // clickable


class fidelz80_state : public fidelz80base_state
{
public:
	fidelz80_state(const machine_config &mconfig, device_type type, const char *tag)
		: fidelz80base_state(mconfig, type, tag),
		m_mcu(*this, "mcu"),
		m_z80pio(*this, "z80pio"),
		m_ppi8255(*this, "ppi8255"),
		m_i8243(*this, "i8243"),
		m_beeper_off(*this, "beeper_off"),
		m_beeper(*this, "beeper")
	{ }

	// devices/pointers
	optional_device<i8041_device> m_mcu;
	optional_device<z80pio_device> m_z80pio;
	optional_device<i8255_device> m_ppi8255;
	optional_device<i8243_device> m_i8243;
	optional_device<timer_device> m_beeper_off;
	optional_device<beep_device> m_beeper;

	DECLARE_INPUT_CHANGED_MEMBER(reset_button);

	// CC10 and VCC/UVC
	void vcc_prepare_display();
	DECLARE_READ8_MEMBER(vcc_speech_r);
	DECLARE_WRITE8_MEMBER(vcc_ppi_porta_w);
	DECLARE_READ8_MEMBER(vcc_ppi_portb_r);
	DECLARE_WRITE8_MEMBER(vcc_ppi_portb_w);
	DECLARE_READ8_MEMBER(vcc_ppi_portc_r);
	DECLARE_WRITE8_MEMBER(vcc_ppi_portc_w);
	DECLARE_WRITE8_MEMBER(cc10_ppi_porta_w);
	TIMER_DEVICE_CALLBACK_MEMBER(beeper_off_callback);
	
	// BCC
	DECLARE_READ8_MEMBER(bcc_input_r);
	DECLARE_WRITE8_MEMBER(bcc_control_w);

	// VSC
	void vsc_prepare_display();
	DECLARE_READ8_MEMBER(vsc_io_trampoline_r);
	DECLARE_WRITE8_MEMBER(vsc_io_trampoline_w);
	DECLARE_WRITE8_MEMBER(vsc_ppi_porta_w);
	DECLARE_WRITE8_MEMBER(vsc_ppi_portb_w);
	DECLARE_WRITE8_MEMBER(vsc_ppi_portc_w);
	DECLARE_READ8_MEMBER(vsc_pio_porta_r);
	DECLARE_READ8_MEMBER(vsc_pio_portb_r);
	DECLARE_WRITE8_MEMBER(vsc_pio_portb_w);

	// VBRC/7014
	void vbrc_prepare_display();
	DECLARE_WRITE8_MEMBER(vbrc_speech_w);
	DECLARE_WRITE8_MEMBER(vbrc_mcu_p1_w);
	DECLARE_READ8_MEMBER(vbrc_mcu_t_r);
	DECLARE_READ8_MEMBER(vbrc_mcu_p2_r);
	DECLARE_WRITE8_MEMBER(vbrc_ioexp_port_w);
};


// machine start/reset

void fidelz80base_state::machine_start()
{
	// zerofill
	memset(m_display_state, 0, sizeof(m_display_state));
	memset(m_display_cache, ~0, sizeof(m_display_cache));
	memset(m_display_decay, 0, sizeof(m_display_decay));
	memset(m_display_segmask, 0, sizeof(m_display_segmask));

	m_inp_mux = 0;
	m_led_select = 0;
	m_led_data = 0;
	m_7seg_data = 0;
	m_speech_data = 0;
	m_speech_bank = 0;

	// register for savestates
	save_item(NAME(m_display_maxy));
	save_item(NAME(m_display_maxx));
	save_item(NAME(m_display_wait));

	save_item(NAME(m_display_state));
	/* save_item(NAME(m_display_cache)); */ // don't save!
	save_item(NAME(m_display_decay));
	save_item(NAME(m_display_segmask));

	save_item(NAME(m_inp_mux));
	save_item(NAME(m_led_select));
	save_item(NAME(m_led_data));
	save_item(NAME(m_7seg_data));
	save_item(NAME(m_speech_data));
	save_item(NAME(m_speech_bank));
}

void fidelz80base_state::machine_reset()
{
}



/***************************************************************************

  Helper Functions

***************************************************************************/

// The device may strobe the outputs very fast, it is unnoticeable to the user.
// To prevent flickering here, we need to simulate a decay.

void fidelz80base_state::display_update()
{
	UINT32 active_state[0x20];

	for (int y = 0; y < m_display_maxy; y++)
	{
		active_state[y] = 0;

		for (int x = 0; x <= m_display_maxx; x++)
		{
			// turn on powered segments
			if (m_display_state[y] >> x & 1)
				m_display_decay[y][x] = m_display_wait;

			// determine active state
			UINT32 ds = (m_display_decay[y][x] != 0) ? 1 : 0;
			active_state[y] |= (ds << x);
		}
	}

	// on difference, send to output
	for (int y = 0; y < m_display_maxy; y++)
		if (m_display_cache[y] != active_state[y])
		{
			if (m_display_segmask[y] != 0)
				output().set_digit_value(y, active_state[y] & m_display_segmask[y]);

			const int mul = (m_display_maxx <= 10) ? 10 : 100;
			for (int x = 0; x <= m_display_maxx; x++)
			{
				int state = active_state[y] >> x & 1;
				char buf1[0x10]; // lampyx
				char buf2[0x10]; // y.x

				if (x == m_display_maxx)
				{
					// always-on if selected
					sprintf(buf1, "lamp%da", y);
					sprintf(buf2, "%d.a", y);
				}
				else
				{
					sprintf(buf1, "lamp%d", y * mul + x);
					sprintf(buf2, "%d.%d", y, x);
				}
				output().set_value(buf1, state);
				output().set_value(buf2, state);
			}
		}

	memcpy(m_display_cache, active_state, sizeof(m_display_cache));
}

TIMER_DEVICE_CALLBACK_MEMBER(fidelz80base_state::display_decay_tick)
{
	// slowly turn off unpowered segments
	for (int y = 0; y < m_display_maxy; y++)
		for (int x = 0; x <= m_display_maxx; x++)
			if (m_display_decay[y][x] != 0)
				m_display_decay[y][x]--;

	display_update();
}

void fidelz80base_state::set_display_size(int maxx, int maxy)
{
	m_display_maxx = maxx;
	m_display_maxy = maxy;
}

void fidelz80base_state::set_display_segmask(UINT32 digits, UINT32 mask)
{
	// set a segment mask per selected digit, but leave unselected ones alone
	for (int i = 0; i < 0x20; i++)
	{
		if (digits & 1)
			m_display_segmask[i] = mask;
		digits >>= 1;
	}
}

void fidelz80base_state::display_matrix(int maxx, int maxy, UINT32 setx, UINT32 sety)
{
	set_display_size(maxx, maxy);

	// update current state
	UINT32 mask = (1 << maxx) - 1;
	for (int y = 0; y < maxy; y++)
		m_display_state[y] = (sety >> y & 1) ? ((setx & mask) | (1 << maxx)) : 0;

	display_update();
}


// generic input handlers

UINT16 fidelz80base_state::read_inputs(int columns)
{
	UINT16 ret = 0;

	// read selected input rows
	for (int i = 0; i < columns; i++)
		if (m_inp_mux >> i & 1)
			ret |= m_inp_matrix[i]->read();

	return ret;
}

INPUT_CHANGED_MEMBER(fidelz80_state::reset_button)
{
	// when RE button is directly wired to RESET pin(s)
	m_maincpu->set_input_line(INPUT_LINE_RESET, newval ? ASSERT_LINE : CLEAR_LINE);

	if (m_mcu)
		m_mcu->set_input_line(INPUT_LINE_RESET, newval ? ASSERT_LINE : CLEAR_LINE);
}



// Devices, I/O

/******************************************************************************
    CC10 and VCC/UVC
******************************************************************************/

// misc handlers

void fidelz80_state::vcc_prepare_display()
{
	// 4 7seg leds (note: sel d0 for extra leds)
	UINT8 outdata = (m_7seg_data & 0x7f) | (m_led_select << 7 & 0x80);
	set_display_segmask(0xf, 0x7f);
	display_matrix(8, 4, outdata, m_led_select >> 2 & 0xf);
}

READ8_MEMBER(fidelz80_state::vcc_speech_r)
{
	return m_speech_rom[m_speech_bank << 12 | offset];
}


// I8255 PPI

WRITE8_MEMBER(fidelz80_state::vcc_ppi_porta_w)
{
	// d0-d6: digit segment data, bits are xABCDEFG
	m_7seg_data = BITSWAP8(data,7,0,1,2,3,4,5,6);
	vcc_prepare_display();

	// d0-d5: TSI C0-C5
	// d7: TSI START line
	m_speech->data_w(space, 0, data & 0x3f);
	m_speech->start_w(data >> 7 & 1);

	// d6: language latch data
	// d7: language latch clock (latch on high)
	if (data & 0x80)
	{
		m_speech->force_update(); // update stream to now
		m_speech_bank = data >> 6 & 1;
	}
}

READ8_MEMBER(fidelz80_state::vcc_ppi_portb_r)
{
	// d7: TSI BUSY line
	return (m_speech->busy_r()) ? 0x80 : 0x00;
}

WRITE8_MEMBER(fidelz80_state::vcc_ppi_portb_w)
{
	// d0,d2-d5: digit/led select
	// _d6: enable language switches
	m_led_select = data;
	vcc_prepare_display();
}

READ8_MEMBER(fidelz80_state::vcc_ppi_portc_r)
{
	// d0-d3: multiplexed inputs (active low), also language switches
	UINT8 lan = (~m_led_select & 0x40) ? m_inp_matrix[4]->read() : 0;
	return ~(lan | read_inputs(4)) & 0xf;
}

WRITE8_MEMBER(fidelz80_state::vcc_ppi_portc_w)
{
	// d4-d7: input mux (inverted)
	m_inp_mux = ~data >> 4 & 0xf;
}


// CC10-specific (no speech chip, 1-bit beeper instead)

TIMER_DEVICE_CALLBACK_MEMBER(fidelz80_state::beeper_off_callback)
{
	m_beeper->set_state(0);
}

WRITE8_MEMBER(fidelz80_state::cc10_ppi_porta_w)
{
	// d7: enable beeper on falling edge
	if (m_beeper && ~data & m_7seg_data & 0x80)
	{
		m_beeper->set_state(1);
		m_beeper_off->adjust(attotime::from_msec(80)); // duration is approximate
	}

	// d0-d6: digit segment data (same as VCC)
	m_7seg_data = BITSWAP8(data,7,0,1,2,3,4,5,6);
	vcc_prepare_display();
}



/******************************************************************************
    BCC
******************************************************************************/

// TTL

WRITE8_MEMBER(fidelz80_state::bcc_control_w)
{
	// a0-a2,d7: digit segment data via NE591, Q7 is speaker out
	UINT8 mask = 1 << (offset & 7);
	m_7seg_data = (m_7seg_data & ~mask) | ((data & 0x80) ? mask : 0);
	m_speaker->level_w(m_7seg_data >> 7 & 1);

	// d0-d3: led select, input mux
	// d4,d5: check,lose leds(direct)
	set_display_segmask(0xf, 0x7f);
	display_matrix(7, 6, m_7seg_data & 0x7f, data & 0x3f);
	m_inp_mux = data & 0xf;
}

READ8_MEMBER(fidelz80_state::bcc_input_r)
{
	// d0-d3: multiplexed inputs
	return read_inputs(4);
}



/******************************************************************************
    VSC
******************************************************************************/

// misc handlers

void fidelz80_state::vsc_prepare_display()
{
	// 4 7seg leds + H
	for (int i = 0; i < 4; i++)
		m_display_state[i] = (m_led_select >> i & 1) ? m_7seg_data : 0;

	// 8*8 chessboard leds
	for (int i = 0; i < 8; i++)
		m_display_state[i+4] = (m_led_select >> i & 1) ? m_led_data : 0;

	set_display_size(8, 12);
	set_display_segmask(0xf, 0x7f);
	display_update();
}


// I8255 PPI

WRITE8_MEMBER(fidelz80_state::vsc_ppi_porta_w)
{
	// d0-d5: TSI C0-C5
	m_speech->data_w(space, 0, data & 0x3f);

	// d0-d7: data for the 4 7seg leds, bits are HGCBAFED (H is extra led)
	m_7seg_data = BITSWAP8(data,7,6,2,1,0,5,4,3);
	vsc_prepare_display();
}

WRITE8_MEMBER(fidelz80_state::vsc_ppi_portb_w)
{
	// d0-d7: led row data
	m_led_data = data;
	vsc_prepare_display();
}

WRITE8_MEMBER(fidelz80_state::vsc_ppi_portc_w)
{
	// d0-d3: select digits
	// d0-d7: select leds, input mux low bits
	m_inp_mux = (m_inp_mux & ~0xff) | data;
	m_led_select = data;
	vsc_prepare_display();
}


// Z80 PIO

READ8_MEMBER(fidelz80_state::vsc_pio_porta_r)
{
	// d0-d7: multiplexed inputs
	return read_inputs(11);
}

READ8_MEMBER(fidelz80_state::vsc_pio_portb_r)
{
	UINT8 data = 0;

	// d4: TSI BUSY line
	data |= (m_speech->busy_r()) ? 0 : 0x10;
	
	return data;
}

WRITE8_MEMBER(fidelz80_state::vsc_pio_portb_w)
{
	// d0,d1: input mux highest bits
	// d5: enable language switch
	m_inp_mux = (m_inp_mux & 0xff) | (data << 8 & 0x300) | (data << 5 & 0x400);
	
	// d7: TSI ROM A12
	m_speech->force_update(); // update stream to now
	m_speech_bank = data >> 7 & 1;
	
	// d6: TSI START line
	m_speech->start_w(data >> 6 & 1);
	
	// d2: lower TSI volume
	m_speech->set_output_gain(0, (data & 4) ? 0.5 : 1.0);
}



/******************************************************************************
    VBRC/7014
******************************************************************************/

// misc handlers

void fidelz80_state::vbrc_prepare_display()
{
	// 14seg led segments, d15 is extra led, d14 is unused (tone on prototype?)
	UINT16 outdata = BITSWAP16(m_7seg_data,12,13,1,6,5,2,0,7,15,11,10,14,4,3,9,8);
	set_display_segmask(0xff, 0x3fff);
	display_matrix(16, 8, outdata, m_led_select);
}


// I8243 I/O expander

WRITE8_MEMBER(fidelz80_state::vbrc_ioexp_port_w)
{
	// P4-P7: digit segment data
	m_7seg_data = (m_7seg_data & ~(0xf << (4*offset))) | ((data & 0xf) << (4*offset));
	vbrc_prepare_display();
}


// I8041 MCU

WRITE8_MEMBER(fidelz80_state::vbrc_mcu_p1_w)
{
	// d0-d7: select digits, input mux
	m_inp_mux = m_led_select = data;
	vbrc_prepare_display();
}

READ8_MEMBER(fidelz80_state::vbrc_mcu_p2_r)
{
	// d0-d3: I8243 P2
	// d4-d7: multiplexed inputs (active low)
	return (m_i8243->i8243_p2_r(space, offset) & 0x0f) | (read_inputs(8) << 4 ^ 0xf0);
}

READ8_MEMBER(fidelz80_state::vbrc_mcu_t_r)
{
	// T0: card scanner?
	if (offset == 0)
		return 0;

	// T1: ?
	else
		return rand() & 1;
}



/******************************************************************************
    Address Maps
******************************************************************************/

// CC10 and VCC/UVC

static ADDRESS_MAP_START( cc10_map, AS_PROGRAM, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_HIGH
	ADDRESS_MAP_GLOBAL_MASK(0x3fff)
	AM_RANGE(0x0000, 0x0fff) AM_ROM
	AM_RANGE(0x3000, 0x31ff) AM_MIRROR(0x0e00) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( vcc_map, AS_PROGRAM, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x0000, 0x2fff) AM_ROM
	AM_RANGE(0x4000, 0x43ff) AM_MIRROR(0x1c00) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( vcc_io, AS_IO, 8, fidelz80_state )
	ADDRESS_MAP_GLOBAL_MASK(0x03)
	AM_RANGE(0x00, 0x03) AM_DEVREADWRITE("ppi8255", i8255_device, read, write)
ADDRESS_MAP_END


// BCC

static ADDRESS_MAP_START( bcc_map, AS_PROGRAM, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_HIGH
	ADDRESS_MAP_GLOBAL_MASK(0x3fff)
	AM_RANGE(0x0000, 0x0fff) AM_ROM
	AM_RANGE(0x3000, 0x30ff) AM_MIRROR(0x0f00) AM_RAM
ADDRESS_MAP_END

static ADDRESS_MAP_START( bcc_io, AS_IO, 8, fidelz80_state )
	ADDRESS_MAP_GLOBAL_MASK(0x07)
	AM_RANGE(0x00, 0x07) AM_READWRITE(bcc_input_r, bcc_control_w)
ADDRESS_MAP_END


// VSC

static ADDRESS_MAP_START( vsc_map, AS_PROGRAM, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x0000, 0x3fff) AM_ROM
	AM_RANGE(0x4000, 0x4fff) AM_MIRROR(0x1000) AM_ROM
	AM_RANGE(0x6000, 0x63ff) AM_MIRROR(0x1c00) AM_RAM
ADDRESS_MAP_END

// VSC io: A2 is 8255 _CE, A3 is Z80 PIO _CE - in theory, both chips can be accessed simultaneously
READ8_MEMBER(fidelz80_state::vsc_io_trampoline_r)
{
	UINT8 data = 0xff; // open bus
	if (~offset & 4)
		data &= m_ppi8255->read(space, offset & 3);
	if (~offset & 8)
		data &= m_z80pio->read(space, offset & 3);

	return data;
}

WRITE8_MEMBER(fidelz80_state::vsc_io_trampoline_w)
{
	if (~offset & 4)
		m_ppi8255->write(space, offset & 3, data);
	if (~offset & 8)
		m_z80pio->write(space, offset & 3, data);
}

static ADDRESS_MAP_START( vsc_io, AS_IO, 8, fidelz80_state )
	ADDRESS_MAP_GLOBAL_MASK(0x0f)
	AM_RANGE(0x00, 0x0f) AM_READWRITE(vsc_io_trampoline_r, vsc_io_trampoline_w)
ADDRESS_MAP_END


// VBRC/7014

WRITE8_MEMBER(fidelz80_state::vbrc_speech_w)
{
	//printf("%X ",data);

	// todo: HALT THE z80 here, and set up a callback to poll the s14001a BUSY line to resume z80
	m_speech->data_w(space, 0, data & 0x3f);
	m_speech->start_w(1);
	m_speech->start_w(0);

	//m_speech->start_w(BIT(data, 7));
}

static ADDRESS_MAP_START( vbrc_main_map, AS_PROGRAM, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_HIGH
	AM_RANGE(0x0000, 0x5fff) AM_ROM
	AM_RANGE(0x6000, 0x63ff) AM_MIRROR(0x1c00) AM_RAM
	AM_RANGE(0xe000, 0xffff) AM_MIRROR(0x1fff) AM_WRITE(vbrc_speech_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START( vbrc_main_io, AS_IO, 8, fidelz80_state )
	ADDRESS_MAP_GLOBAL_MASK(0x01)
	AM_RANGE(0x00, 0x01) AM_DEVREADWRITE("mcu", i8041_device, upi41_master_r, upi41_master_w)
ADDRESS_MAP_END

static ADDRESS_MAP_START( vbrc_mcu_map, AS_IO, 8, fidelz80_state )
	ADDRESS_MAP_UNMAP_LOW
	AM_RANGE(MCS48_PORT_P1, MCS48_PORT_P1) AM_WRITE(vbrc_mcu_p1_w)
	AM_RANGE(MCS48_PORT_P2, MCS48_PORT_P2) AM_READ(vbrc_mcu_p2_r) AM_DEVWRITE("i8243", i8243_device, i8243_p2_w)
	AM_RANGE(MCS48_PORT_PROG, MCS48_PORT_PROG) AM_DEVWRITE("i8243", i8243_device, i8243_prog_w)
	AM_RANGE(MCS48_PORT_T0, MCS48_PORT_T1) AM_READ(vbrc_mcu_t_r)
ADDRESS_MAP_END



/******************************************************************************
    Input Ports
******************************************************************************/

static INPUT_PORTS_START( vcc_base )
	PORT_START("IN.0")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_UNUSED)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("LV") PORT_CODE(KEYCODE_L)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("A1") PORT_CODE(KEYCODE_1) PORT_CODE(KEYCODE_1_PAD) PORT_CODE(KEYCODE_A)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("E5") PORT_CODE(KEYCODE_5) PORT_CODE(KEYCODE_5_PAD) PORT_CODE(KEYCODE_E)

	PORT_START("IN.1")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Speak") PORT_CODE(KEYCODE_SPACE)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("DM") PORT_CODE(KEYCODE_M)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("B2") PORT_CODE(KEYCODE_2) PORT_CODE(KEYCODE_2_PAD) PORT_CODE(KEYCODE_B)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("F6") PORT_CODE(KEYCODE_6) PORT_CODE(KEYCODE_6_PAD) PORT_CODE(KEYCODE_F)

	PORT_START("IN.2")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CL") PORT_CODE(KEYCODE_DEL)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PB") PORT_CODE(KEYCODE_P)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("C3") PORT_CODE(KEYCODE_3) PORT_CODE(KEYCODE_3_PAD) PORT_CODE(KEYCODE_C)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("G7") PORT_CODE(KEYCODE_7) PORT_CODE(KEYCODE_7_PAD) PORT_CODE(KEYCODE_G)

	PORT_START("IN.3")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("EN") PORT_CODE(KEYCODE_ENTER)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PV") PORT_CODE(KEYCODE_O)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("D4") PORT_CODE(KEYCODE_4) PORT_CODE(KEYCODE_4_PAD) PORT_CODE(KEYCODE_D)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("H8") PORT_CODE(KEYCODE_8) PORT_CODE(KEYCODE_8_PAD) PORT_CODE(KEYCODE_H)

	PORT_START("RESET") // is not on matrix IN.0 d0
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("RE") PORT_CODE(KEYCODE_R) PORT_CHANGED_MEMBER(DEVICE_SELF, fidelz80_state, reset_button, 0)
INPUT_PORTS_END

static INPUT_PORTS_START( cc10 )
	PORT_INCLUDE( vcc_base )

	PORT_START("IN.4")
	PORT_BIT(0x0f, IP_ACTIVE_HIGH, IPT_UNUSED)

	PORT_START("LEVEL") // hardwired (VCC/GND?)
	PORT_CONFNAME( 0x80, 0x00, "Maximum Levels" )
	PORT_CONFSETTING(    0x00, "10" ) // factory setting
	PORT_CONFSETTING(    0x80, "3" )
INPUT_PORTS_END

static INPUT_PORTS_START( vcc )
	PORT_INCLUDE( vcc_base )

	PORT_START("IN.4") // PCB jumpers, not consumer accessible
	PORT_CONFNAME( 0x01, 0x00, "Language: French" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x01, DEF_STR( On ) )
	PORT_CONFNAME( 0x02, 0x00, "Language: Spanish" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x02, DEF_STR( On ) )
	PORT_CONFNAME( 0x04, 0x00, "Language: German" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x04, DEF_STR( On ) )
	PORT_CONFNAME( 0x08, 0x00, "Language: Special" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x08, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( vccfr )
	PORT_INCLUDE( vcc )

	PORT_MODIFY("IN.4")
	PORT_CONFNAME( 0x01, 0x01, "Language: French" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x01, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( vccsp )
	PORT_INCLUDE( vcc )

	PORT_MODIFY("IN.4")
	PORT_CONFNAME( 0x02, 0x02, "Language: Spanish" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x02, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( vccg )
	PORT_INCLUDE( vcc )

	PORT_MODIFY("IN.4")
	PORT_CONFNAME( 0x04, 0x04, "Language: German" )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x04, DEF_STR( On ) )
INPUT_PORTS_END


static INPUT_PORTS_START( bcc )
	PORT_START("IN.0")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("EN") PORT_CODE(KEYCODE_ENTER)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PV") PORT_CODE(KEYCODE_O)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("d4") PORT_CODE(KEYCODE_4) PORT_CODE(KEYCODE_4_PAD) PORT_CODE(KEYCODE_D)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("H8") PORT_CODE(KEYCODE_8) PORT_CODE(KEYCODE_8_PAD) PORT_CODE(KEYCODE_H)

	PORT_START("IN.1")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CL") PORT_CODE(KEYCODE_DEL)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PB") PORT_CODE(KEYCODE_P)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("C3") PORT_CODE(KEYCODE_3) PORT_CODE(KEYCODE_3_PAD) PORT_CODE(KEYCODE_C)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("g7") PORT_CODE(KEYCODE_7) PORT_CODE(KEYCODE_7_PAD) PORT_CODE(KEYCODE_G)

	PORT_START("IN.2")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CB") PORT_CODE(KEYCODE_SPACE)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("DM") PORT_CODE(KEYCODE_M)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("b2") PORT_CODE(KEYCODE_2) PORT_CODE(KEYCODE_2_PAD) PORT_CODE(KEYCODE_B)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("F6") PORT_CODE(KEYCODE_6) PORT_CODE(KEYCODE_6_PAD) PORT_CODE(KEYCODE_F)

	PORT_START("IN.3")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("RE") PORT_CODE(KEYCODE_R)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("LV") PORT_CODE(KEYCODE_L)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("A1") PORT_CODE(KEYCODE_1) PORT_CODE(KEYCODE_1_PAD) PORT_CODE(KEYCODE_A)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("E5") PORT_CODE(KEYCODE_5) PORT_CODE(KEYCODE_5_PAD) PORT_CODE(KEYCODE_E)
INPUT_PORTS_END


static INPUT_PORTS_START( vsc )
	PORT_START("IN.0")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square a8")

	PORT_START("IN.1")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square b8")

	PORT_START("IN.2")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square c8")

	PORT_START("IN.3")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square d8")

	PORT_START("IN.4")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square e8")

	PORT_START("IN.5")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square f8")

	PORT_START("IN.6")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square g8")

	PORT_START("IN.7")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h1")
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h2")
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h3")
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h4")
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h5")
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h6")
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h7")
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Square h8")

	PORT_START("IN.8") // buttons on the right
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Pawn") PORT_CODE(KEYCODE_1) PORT_CODE(KEYCODE_1_PAD)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Rook") PORT_CODE(KEYCODE_2) PORT_CODE(KEYCODE_2_PAD)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Knight") PORT_CODE(KEYCODE_3) PORT_CODE(KEYCODE_3_PAD)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Bishop") PORT_CODE(KEYCODE_4) PORT_CODE(KEYCODE_4_PAD)
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Queen") PORT_CODE(KEYCODE_5) PORT_CODE(KEYCODE_5_PAD)
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("King") PORT_CODE(KEYCODE_6) PORT_CODE(KEYCODE_6_PAD)
	PORT_BIT(0x40, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CL") PORT_CODE(KEYCODE_DEL)
	PORT_BIT(0x80, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("RE") PORT_CODE(KEYCODE_R)

	PORT_START("IN.9") // buttons beside the display
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("TM") PORT_CODE(KEYCODE_T)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("RV") PORT_CODE(KEYCODE_V)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Speak") PORT_CODE(KEYCODE_SPACE)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("LV") PORT_CODE(KEYCODE_L)
	PORT_BIT(0x10, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("DM") PORT_CODE(KEYCODE_M)
	PORT_BIT(0x20, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("ST") PORT_CODE(KEYCODE_S)
	PORT_BIT(0xc0, IP_ACTIVE_HIGH, IPT_UNUSED)

	PORT_START("IN.10") // hardwired (2 diodes)
	PORT_CONFNAME( 0x01, 0x00, "Language" )
	PORT_CONFSETTING(    0x00, "English" )
	PORT_CONFSETTING(    0x01, "Other" )
	PORT_CONFNAME( 0x02, 0x00, DEF_STR( Unknown ) )
	PORT_CONFSETTING(    0x00, DEF_STR( Off ) )
	PORT_CONFSETTING(    0x02, DEF_STR( On ) )
INPUT_PORTS_END

static INPUT_PORTS_START( vscg )
	PORT_INCLUDE( vsc )

	PORT_MODIFY("IN.10")
	PORT_CONFNAME( 0x01, 0x01, "Language" )
	PORT_CONFSETTING(    0x00, "English" )
	PORT_CONFSETTING(    0x01, "Other" )
INPUT_PORTS_END


static INPUT_PORTS_START( vbrc )
	PORT_START("IN.0")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("A") PORT_CODE(KEYCODE_A)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("10") PORT_CODE(KEYCODE_0)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("6") PORT_CODE(KEYCODE_6)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("2") PORT_CODE(KEYCODE_2)

	PORT_START("IN.1")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("K") PORT_CODE(KEYCODE_K)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("9") PORT_CODE(KEYCODE_9)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("5") PORT_CODE(KEYCODE_5)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("1") PORT_CODE(KEYCODE_1)

	PORT_START("IN.2")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Q") PORT_CODE(KEYCODE_Q)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("8") PORT_CODE(KEYCODE_8)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("4") PORT_CODE(KEYCODE_4)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("P") PORT_CODE(KEYCODE_Z)

	PORT_START("IN.3")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("J") PORT_CODE(KEYCODE_J)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("7") PORT_CODE(KEYCODE_7)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("3") PORT_CODE(KEYCODE_3)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("NT") PORT_CODE(KEYCODE_N)

	PORT_START("IN.4")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("EN") PORT_CODE(KEYCODE_E)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("SC") PORT_CODE(KEYCODE_S)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PL") PORT_CODE(KEYCODE_X)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Spades") PORT_CODE(KEYCODE_1_PAD)

	PORT_START("IN.5")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CL") PORT_CODE(KEYCODE_C)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("DB") PORT_CODE(KEYCODE_D)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("VL") PORT_CODE(KEYCODE_V)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Hearts") PORT_CODE(KEYCODE_2_PAD)

	PORT_START("IN.6")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Beep on/off") PORT_CODE(KEYCODE_SPACE)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("PB") PORT_CODE(KEYCODE_B)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("CV") PORT_CODE(KEYCODE_G)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Diamonds") PORT_CODE(KEYCODE_3_PAD)

	PORT_START("IN.7")
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_UNUSED)
	PORT_BIT(0x02, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("BR") PORT_CODE(KEYCODE_T)
	PORT_BIT(0x04, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("DL") PORT_CODE(KEYCODE_L)
	PORT_BIT(0x08, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("Clubs") PORT_CODE(KEYCODE_4_PAD)

	PORT_START("RESET") // is not on matrix IN.7 d0
	PORT_BIT(0x01, IP_ACTIVE_HIGH, IPT_KEYPAD) PORT_NAME("RE") PORT_CODE(KEYCODE_R) PORT_CHANGED_MEMBER(DEVICE_SELF, fidelz80_state, reset_button, 0)
INPUT_PORTS_END



/******************************************************************************
    Machine Drivers
******************************************************************************/

static MACHINE_CONFIG_START( bcc, fidelz80_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, XTAL_3_579545MHz)
	MCFG_CPU_PROGRAM_MAP(bcc_map)
	MCFG_CPU_IO_MAP(bcc_io)

	MCFG_TIMER_DRIVER_ADD_PERIODIC("display_decay", fidelz80base_state, display_decay_tick, attotime::from_msec(1))
	MCFG_DEFAULT_LAYOUT(layout_fidel_bcc)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("speaker", SPEAKER_SOUND, 0)
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)
MACHINE_CONFIG_END

static MACHINE_CONFIG_START( cc10, fidelz80_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, XTAL_4MHz)
	MCFG_CPU_PROGRAM_MAP(cc10_map)
	MCFG_CPU_IO_MAP(vcc_io)

	MCFG_DEVICE_ADD("ppi8255", I8255, 0)
	MCFG_I8255_OUT_PORTA_CB(WRITE8(fidelz80_state, cc10_ppi_porta_w))
	MCFG_I8255_IN_PORTB_CB(IOPORT("LEVEL"))
	MCFG_I8255_OUT_PORTB_CB(WRITE8(fidelz80_state, vcc_ppi_portb_w))
	MCFG_I8255_IN_PORTC_CB(READ8(fidelz80_state, vcc_ppi_portc_r))
	MCFG_I8255_OUT_PORTC_CB(WRITE8(fidelz80_state, vcc_ppi_portc_w))

	MCFG_TIMER_DRIVER_ADD_PERIODIC("display_decay", fidelz80base_state, display_decay_tick, attotime::from_msec(1))
	MCFG_DEFAULT_LAYOUT(layout_fidel_cc)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("beeper", BEEP, 1360) // approximation, from 556 timer ic
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.25)
	MCFG_TIMER_DRIVER_ADD("beeper_off", fidelz80_state, beeper_off_callback)
MACHINE_CONFIG_END

static MACHINE_CONFIG_START( vcc, fidelz80_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, XTAL_4MHz)
	MCFG_CPU_PROGRAM_MAP(vcc_map)
	MCFG_CPU_IO_MAP(vcc_io)

	MCFG_DEVICE_ADD("ppi8255", I8255, 0)
	MCFG_I8255_OUT_PORTA_CB(WRITE8(fidelz80_state, vcc_ppi_porta_w))
	MCFG_I8255_IN_PORTB_CB(READ8(fidelz80_state, vcc_ppi_portb_r))
	MCFG_I8255_OUT_PORTB_CB(WRITE8(fidelz80_state, vcc_ppi_portb_w))
	MCFG_I8255_IN_PORTC_CB(READ8(fidelz80_state, vcc_ppi_portc_r))
	MCFG_I8255_OUT_PORTC_CB(WRITE8(fidelz80_state, vcc_ppi_portc_w))

	MCFG_TIMER_DRIVER_ADD_PERIODIC("display_decay", fidelz80base_state, display_decay_tick, attotime::from_msec(1))
	MCFG_DEFAULT_LAYOUT(layout_fidel_vcc)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("speech", S14001A, 25000) // R/C circuit, around 25khz
	MCFG_S14001A_EXT_READ_HANDLER(READ8(fidelz80_state, vcc_speech_r))
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.75)
MACHINE_CONFIG_END

static MACHINE_CONFIG_START( vsc, fidelz80_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, XTAL_4MHz)
	MCFG_CPU_PROGRAM_MAP(vsc_map)
	MCFG_CPU_IO_MAP(vsc_io)
	MCFG_CPU_PERIODIC_INT_DRIVER(fidelz80base_state, nmi_line_pulse, 600) // 555 timer, approx 600hz

	MCFG_DEVICE_ADD("ppi8255", I8255, 0)
	MCFG_I8255_OUT_PORTA_CB(WRITE8(fidelz80_state, vsc_ppi_porta_w))
	MCFG_I8255_OUT_PORTB_CB(WRITE8(fidelz80_state, vsc_ppi_portb_w))
	MCFG_I8255_OUT_PORTC_CB(WRITE8(fidelz80_state, vsc_ppi_portc_w))

	MCFG_DEVICE_ADD("z80pio", Z80PIO, XTAL_4MHz)
	MCFG_Z80PIO_IN_PA_CB(READ8(fidelz80_state, vsc_pio_porta_r))
	MCFG_Z80PIO_IN_PB_CB(READ8(fidelz80_state, vsc_pio_portb_r))
	MCFG_Z80PIO_OUT_PB_CB(WRITE8(fidelz80_state, vsc_pio_portb_w))

	MCFG_TIMER_DRIVER_ADD_PERIODIC("display_decay", fidelz80base_state, display_decay_tick, attotime::from_msec(1))
	MCFG_DEFAULT_LAYOUT(layout_fidel_vsc)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("speech", S14001A, 25000) // R/C circuit, around 25khz
	MCFG_S14001A_EXT_READ_HANDLER(READ8(fidelz80_state, vcc_speech_r))
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.75)
MACHINE_CONFIG_END

static MACHINE_CONFIG_START( vbrc, fidelz80_state )

	/* basic machine hardware */
	MCFG_CPU_ADD("maincpu", Z80, XTAL_5MHz/2)
	MCFG_CPU_PROGRAM_MAP(vbrc_main_map)
	MCFG_CPU_IO_MAP(vbrc_main_io)
	MCFG_QUANTUM_PERFECT_CPU("maincpu")

	MCFG_CPU_ADD("mcu", I8041, XTAL_5MHz) // or XTAL_5MHz/4?
	MCFG_CPU_IO_MAP(vbrc_mcu_map)

	MCFG_I8243_ADD("i8243", NOOP, WRITE8(fidelz80_state, vbrc_ioexp_port_w))

	MCFG_TIMER_DRIVER_ADD_PERIODIC("display_decay", fidelz80base_state, display_decay_tick, attotime::from_msec(1))
	MCFG_DEFAULT_LAYOUT(layout_fidel_vbrc)

	/* sound hardware */
	MCFG_SPEAKER_STANDARD_MONO("mono")
	MCFG_SOUND_ADD("speech", S14001A, 25000) // R/C circuit, around 25khz
	MCFG_SOUND_ROUTE(ALL_OUTPUTS, "mono", 0.75)
MACHINE_CONFIG_END



/******************************************************************************
    ROM Definitions
******************************************************************************/

ROM_START( cc10 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "cc10b", 0x0000, 0x1000, CRC(afd3ca99) SHA1(870d09b2b52ccb8572d69642c59b5215d5fb26ab) ) // 2332
ROM_END

ROM_START( cc7 )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD( "cn19103n_bcc-revb", 0x0000, 0x1000, CRC(a397d471) SHA1(9b12bc442fccee40f4d8500c792bc9d886c5e1a5) ) // 2332
ROM_END


ROM_START( vcc )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-32103.bin", 0x0000, 0x1000, CRC(257bb5ab) SHA1(f7589225bb8e5f3eac55f23e2bd526be780b38b5) ) // 32014.VCC??? at location b3?
	ROM_LOAD("vcc2.bin", 0x1000, 0x1000, CRC(f33095e7) SHA1(692fcab1b88c910b74d04fe4d0660367aee3f4f0) ) // at location a2?
	ROM_LOAD("vcc3.bin", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) ) // at location a1?

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-engl.bin", 0x0000, 0x1000, CRC(f35784f9) SHA1(348e54a7fa1e8091f89ac656b4da22f28ca2e44d) ) // at location c4?
	ROM_RELOAD(              0x1000, 0x1000)
ROM_END

ROM_START( vccsp )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-32103.bin", 0x0000, 0x1000, CRC(257bb5ab) SHA1(f7589225bb8e5f3eac55f23e2bd526be780b38b5) )
	ROM_LOAD("vcc2.bin", 0x1000, 0x1000, CRC(f33095e7) SHA1(692fcab1b88c910b74d04fe4d0660367aee3f4f0) )
	ROM_LOAD("vcc3.bin", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-spanish.bin", 0x0000, 0x2000, CRC(8766e128) SHA1(78c7413bf240159720b131ab70bfbdf4e86eb1e9) ) // dumped from Spanish VCC, is same as data in fexcelv
ROM_END

ROM_START( vccg )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-32103.bin", 0x0000, 0x1000, CRC(257bb5ab) SHA1(f7589225bb8e5f3eac55f23e2bd526be780b38b5) )
	ROM_LOAD("vcc2.bin", 0x1000, 0x1000, CRC(f33095e7) SHA1(692fcab1b88c910b74d04fe4d0660367aee3f4f0) )
	ROM_LOAD("vcc3.bin", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-german.bin", 0x0000, 0x2000, BAD_DUMP CRC(6c85e310) SHA1(20d1d6543c1e6a1f04184a2df2a468f33faec3ff) ) // taken from fexcelv, assume correct
ROM_END

ROM_START( vccfr )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-32103.bin", 0x0000, 0x1000, CRC(257bb5ab) SHA1(f7589225bb8e5f3eac55f23e2bd526be780b38b5) )
	ROM_LOAD("vcc2.bin", 0x1000, 0x1000, CRC(f33095e7) SHA1(692fcab1b88c910b74d04fe4d0660367aee3f4f0) )
	ROM_LOAD("vcc3.bin", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-french.bin", 0x0000, 0x2000, BAD_DUMP CRC(fe8c5c18) SHA1(2b64279ab3747ee81c86963c13e78321c6cfa3a3) ) // taken from fexcelv, assume correct
ROM_END


ROM_START( uvc )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64017.b3", 0x0000, 0x2000, CRC(f1133abf) SHA1(09dd85051c4e7d364d43507c1cfea5c2d08d37f4) ) // "MOS // 101-64017 // 3880"
	ROM_LOAD("101-32010.a1", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) ) // "NEC P9Z021 // D2332C 228 // 101-32010", == vcc3.bin on vcc

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("101-32107.c4", 0x0000, 0x1000, CRC(f35784f9) SHA1(348e54a7fa1e8091f89ac656b4da22f28ca2e44d) ) // "NEC P9Y019 // D2332C 229 // 101-32107", == vcc-engl.bin on vcc
	ROM_RELOAD(              0x1000, 0x1000)
ROM_END

ROM_START( uvcsp )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64017.b3", 0x0000, 0x2000, CRC(f1133abf) SHA1(09dd85051c4e7d364d43507c1cfea5c2d08d37f4) )
	ROM_LOAD("101-32010.a1", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-spanish.bin", 0x0000, 0x2000, CRC(8766e128) SHA1(78c7413bf240159720b131ab70bfbdf4e86eb1e9) )
ROM_END

ROM_START( uvcg )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64017.b3", 0x0000, 0x2000, CRC(f1133abf) SHA1(09dd85051c4e7d364d43507c1cfea5c2d08d37f4) )
	ROM_LOAD("101-32010.a1", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-german.bin", 0x0000, 0x2000, BAD_DUMP CRC(6c85e310) SHA1(20d1d6543c1e6a1f04184a2df2a468f33faec3ff) ) // taken from fexcelv, assume correct
ROM_END

ROM_START( uvcfr )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64017.b3", 0x0000, 0x2000, CRC(f1133abf) SHA1(09dd85051c4e7d364d43507c1cfea5c2d08d37f4) )
	ROM_LOAD("101-32010.a1", 0x2000, 0x1000, CRC(624f0cd5) SHA1(7c1a4f4497fe5882904de1d6fecf510c07ee6fc6) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-french.bin", 0x0000, 0x2000, BAD_DUMP CRC(fe8c5c18) SHA1(2b64279ab3747ee81c86963c13e78321c6cfa3a3) ) // taken from fexcelv, assume correct
ROM_END


ROM_START( vsc )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64108.bin", 0x0000, 0x2000, CRC(c9c98490) SHA1(e6db883df088d60463e75db51433a4b01a3e7626) )
	ROM_LOAD("101-64109.bin", 0x2000, 0x2000, CRC(08a3577c) SHA1(69fe379d21a9d4b57c84c3832d7b3e7431eec341) )
	ROM_LOAD("101-32024.bin", 0x4000, 0x1000, CRC(2a078676) SHA1(db2f0aba7e8ac0f84a17bae7155210cdf0813afb) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("101-32107.bin", 0x0000, 0x1000, CRC(f35784f9) SHA1(348e54a7fa1e8091f89ac656b4da22f28ca2e44d) )
	ROM_RELOAD(               0x1000, 0x1000)
ROM_END

ROM_START( vscsp )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64108.bin", 0x0000, 0x2000, CRC(c9c98490) SHA1(e6db883df088d60463e75db51433a4b01a3e7626) )
	ROM_LOAD("101-64109.bin", 0x2000, 0x2000, CRC(08a3577c) SHA1(69fe379d21a9d4b57c84c3832d7b3e7431eec341) )
	ROM_LOAD("101-32024.bin", 0x4000, 0x1000, CRC(2a078676) SHA1(db2f0aba7e8ac0f84a17bae7155210cdf0813afb) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-spanish.bin", 0x0000, 0x2000, BAD_DUMP CRC(8766e128) SHA1(78c7413bf240159720b131ab70bfbdf4e86eb1e9) ) // taken from vcc/fexcelv, assume correct
ROM_END

ROM_START( vscg )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64108.bin", 0x0000, 0x2000, CRC(c9c98490) SHA1(e6db883df088d60463e75db51433a4b01a3e7626) )
	ROM_LOAD("101-64109.bin", 0x2000, 0x2000, CRC(08a3577c) SHA1(69fe379d21a9d4b57c84c3832d7b3e7431eec341) )
	ROM_LOAD("101-32024.bin", 0x4000, 0x1000, CRC(2a078676) SHA1(db2f0aba7e8ac0f84a17bae7155210cdf0813afb) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-german.bin", 0x0000, 0x2000, BAD_DUMP CRC(6c85e310) SHA1(20d1d6543c1e6a1f04184a2df2a468f33faec3ff) ) // taken from fexcelv, assume correct
ROM_END

ROM_START( vscfr )
	ROM_REGION( 0x10000, "maincpu", 0 )
	ROM_LOAD("101-64108.bin", 0x0000, 0x2000, CRC(c9c98490) SHA1(e6db883df088d60463e75db51433a4b01a3e7626) )
	ROM_LOAD("101-64109.bin", 0x2000, 0x2000, CRC(08a3577c) SHA1(69fe379d21a9d4b57c84c3832d7b3e7431eec341) )
	ROM_LOAD("101-32024.bin", 0x4000, 0x1000, CRC(2a078676) SHA1(db2f0aba7e8ac0f84a17bae7155210cdf0813afb) )

	ROM_REGION( 0x2000, "speech", 0 )
	ROM_LOAD("vcc-french.bin", 0x0000, 0x2000, BAD_DUMP CRC(fe8c5c18) SHA1(2b64279ab3747ee81c86963c13e78321c6cfa3a3) ) // taken from fexcelv, assume correct
ROM_END


ROM_START( vbrc ) // AKA model 7002
	ROM_REGION( 0x10000, "maincpu", 0 )
	// nec 2364 mask roms; pin 27 (PGM, probably NC here due to mask roms) goes to the pcb
	ROM_LOAD("101-64108.g3", 0x0000, 0x2000, CRC(08472223) SHA1(859865b13c908dbb474333263dc60f6a32461141) )
	ROM_LOAD("101-64109.f3", 0x2000, 0x2000, CRC(320afa0f) SHA1(90edfe0ac19b108d232cda376b03a3a24befad4c) )
	ROM_LOAD("101-64110.e3", 0x4000, 0x2000, CRC(3040d0bd) SHA1(caa55fc8d9196e408fb41e7171a68e5099519813) )

	ROM_REGION( 0x1000, "mcu", 0 )
	ROM_LOAD("100-1009.a3", 0x0000, 0x0400, CRC(60eb343f) SHA1(8a63e95ebd62e123bdecc330c0484a47c354bd1a) )

	ROM_REGION( 0x1000, "speech", 0 )
	ROM_LOAD("101-32118.i2", 0x0000, 0x1000, CRC(a0b8bb8f) SHA1(f56852108928d5c6caccfc8166fa347d6760a740) )
ROM_END

ROM_START( bridgec3 ) // 510-1016 Rev.1 PCB has neither locations nor ic labels, so I declare the big heatsink is at C1, numbers count on the shorter length of pcb
	ROM_REGION( 0x10000, "maincpu", 0 )
	// TMM2764AD-20 EPROMS with tiny hole-punch sized colored stickers (mostly) covering the quartz windows. pin 27 (PGM) is tied to vcc with small rework wires and does not connect to pcb.
	ROM_LOAD("7014_white.g3", 0x0000, 0x2000, CRC(eb1620ef) SHA1(987a9abc8c685f1a68678ea4ee65ec4a99419179) ) // white sticker
	ROM_LOAD("7014_red.f3", 0x2000, 0x2000, CRC(74af0019) SHA1(8dc05950c254ca050b95b93e5d0cf48f913a6d49) ) // red sticker
	ROM_LOAD("7014_blue.e3", 0x4000, 0x2000, CRC(341d9ca6) SHA1(370876573bb9408e75f4fc797304b6c64af0590a) ) // blue sticker

	ROM_REGION( 0x1000, "mcu", 0 )
	ROM_LOAD("100-1009.a3", 0x0000, 0x0400, CRC(60eb343f) SHA1(8a63e95ebd62e123bdecc330c0484a47c354bd1a) ) // "NEC P07021-027 || D8041C 563 100-1009"

	ROM_REGION( 0x1000, "speech", 0 )
	ROM_LOAD("101-32118.i2", 0x0000, 0x1000, CRC(a0b8bb8f) SHA1(f56852108928d5c6caccfc8166fa347d6760a740) ) // "ea 101-32118 || (C) 1980 || EA 8332A247-4 || 8034"
ROM_END



/******************************************************************************
    Drivers
******************************************************************************/

/*    YEAR  NAME      PARENT  COMPAT  MACHINE  INPUT   INIT              COMPANY, FULLNAME, FLAGS */
COMP( 1978, cc10,     0,      0,      cc10,    cc10,   driver_device, 0, "Fidelity Electronics", "Chess Challenger 10 (rev. B)", MACHINE_SUPPORTS_SAVE )
COMP( 1979, cc7,      0,      0,      bcc,     bcc,    driver_device, 0, "Fidelity Electronics", "Chess Challenger 7 (rev. B)", MACHINE_SUPPORTS_SAVE )

COMP( 1979, vcc,      0,      0,      vcc,     vcc,    driver_device, 0, "Fidelity Electronics", "Voice Chess Challenger (English)", MACHINE_SUPPORTS_SAVE )
COMP( 1979, vccsp,    vcc,    0,      vcc,     vccsp,  driver_device, 0, "Fidelity Electronics", "Voice Chess Challenger (Spanish)", MACHINE_SUPPORTS_SAVE )
COMP( 1979, vccg,     vcc,    0,      vcc,     vccg,   driver_device, 0, "Fidelity Electronics", "Voice Chess Challenger (German)", MACHINE_SUPPORTS_SAVE )
COMP( 1979, vccfr,    vcc,    0,      vcc,     vccfr,  driver_device, 0, "Fidelity Electronics", "Voice Chess Challenger (French)", MACHINE_SUPPORTS_SAVE )

COMP( 1980, uvc,      vcc,    0,      vcc,     vcc,    driver_device, 0, "Fidelity Electronics", "Advanced Voice Chess Challenger (English)", MACHINE_SUPPORTS_SAVE )
COMP( 1980, uvcsp,    vcc,    0,      vcc,     vccsp,  driver_device, 0, "Fidelity Electronics", "Advanced Voice Chess Challenger (Spanish)", MACHINE_SUPPORTS_SAVE )
COMP( 1980, uvcg,     vcc,    0,      vcc,     vccg,   driver_device, 0, "Fidelity Electronics", "Advanced Voice Chess Challenger (German)", MACHINE_SUPPORTS_SAVE )
COMP( 1980, uvcfr,    vcc,    0,      vcc,     vccfr,  driver_device, 0, "Fidelity Electronics", "Advanced Voice Chess Challenger (French)", MACHINE_SUPPORTS_SAVE )

COMP( 1980, vsc,      0,      0,      vsc,     vsc,    driver_device, 0, "Fidelity Electronics", "Voice Sensory Chess Challenger (English)", MACHINE_SUPPORTS_SAVE | MACHINE_CLICKABLE_ARTWORK )
COMP( 1980, vscsp,    vsc,    0,      vsc,     vscg,   driver_device, 0, "Fidelity Electronics", "Voice Sensory Chess Challenger (Spanish)", MACHINE_SUPPORTS_SAVE | MACHINE_CLICKABLE_ARTWORK )
COMP( 1980, vscg,     vsc,    0,      vsc,     vscg,   driver_device, 0, "Fidelity Electronics", "Voice Sensory Chess Challenger (German)", MACHINE_SUPPORTS_SAVE | MACHINE_CLICKABLE_ARTWORK )
COMP( 1980, vscfr,    vsc,    0,      vsc,     vscg,   driver_device, 0, "Fidelity Electronics", "Voice Sensory Chess Challenger (French)", MACHINE_SUPPORTS_SAVE | MACHINE_CLICKABLE_ARTWORK )

COMP( 1979, vbrc,     0,      0,      vbrc,    vbrc,   driver_device, 0, "Fidelity Electronics", "Voice Bridge Challenger", MACHINE_SUPPORTS_SAVE | MACHINE_NOT_WORKING )
COMP( 1980, bridgec3, vbrc,   0,      vbrc,    vbrc,   driver_device, 0, "Fidelity Electronics", "Voice Bridge Challenger III", MACHINE_SUPPORTS_SAVE | MACHINE_NOT_WORKING )
