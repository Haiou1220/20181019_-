NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0022   0007 =      7. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0022  __idata_start
       0029  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   002A   031C =    796. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0015  __text_start
       0015  __start
       0036  _exit
       0037  _port_init
       0040  _delay
       0046  _system_init
       004B  _LED
       005E  _Delay_LED
       0069  _led_blink
       0075  _control_sound
       00A4  _buttons_once_press
       00B6  _get_key
       0130  _key_control
       0190  _main
       0199  push_xgset300C
       019E  pop_xgset300C
       01A3  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0007 =      7. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _sound
       0060  __data_start
       0061  TS3A5017_control.c:buttons_once_press_num
       0062  TS3A5017_control.c:mu_count
       0063  TS3A5017_control.c:do_mu_flag
       0064  TS3A5017_control.c:mu_count_ok
       0065  TS3A5017_control.c:return_num
       0066  TS3A5017_control.c:FlagBit_EN_MU
       0067  __data_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0002 =      2. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtAVR.o	[ crtavr.s ]
TS3A5017_control.o	[ TS3A5017_control.c ]
<library>	[ gpushx.s ]

User Global Definitions

ram_end = 0xdf
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x22
data = 0x60
eeprom:0.128

