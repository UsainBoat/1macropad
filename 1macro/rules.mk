# Build Options
#   change yes to no to disable
#
# MCU name
MCU = STM32F411

# Address of the bootloader in system memory
STM32_BOOTLOADER_ADDRESS = 0x1FFF0000

# Build Options
#   change yes to no to disable
#
KEYBOARD_SHARED_EP       = yes

BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no        # Console for debug(+400)
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality on B7 by default
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
WS2812_DRIVER = pwm
MIDI_ENABLE = no            # MIDI support (+2400 to 4200, depending on config)
UNICODE_ENABLE = yes         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
ENCODER_ENABLE = yes				# Allows the use of an encoder
OLED_DRIVER_ENABLE = yes