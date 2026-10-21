# Smart Home Controller (ATmega128)

[![CI](https://github.com/mostafa115/Smart_Home_Project/actions/workflows/ci.yml/badge.svg)](https://github.com/mostafa115/Smart_Home_Project/actions/workflows/ci.yml)

Bare-metal C firmware for an ATmega128 smart-home prototype. It runs a keypad door lock whose password lives in an external I2C EEPROM, a servo-driven door, stepper-motor blinds, a temperature-controlled fan, a light sensor and a serial remote control. Every driver is written against the AVR registers directly, with no Arduino or vendor libraries.

## Features

- **Door lock.** On first boot the admin sets a numeric password on the 4x4 keypad. The password is stored in an external EEPROM over TWI (I2C). Pressing `*` asks for the password, and a correct entry opens the door with a servo on Timer1 PWM, then closes it again. Pressing `#` changes the password after the current one is confirmed.
- **Temperature.** An LM35 on ADC channel 0 is shown on two multiplexed 7-segment digits. Above 40 °C the fan starts and a warning LED turns on.
- **Fan and exhaust.** One DC motor is switched through two relays: forward runs the fan, reverse runs the exhaust.
- **Blinds.** A stepper motor opens and closes the blinds. The firmware tracks the blinds state so a repeated command does not over-rotate them.
- **Lighting.** An LDR on ADC channel 1 turns the light on when it gets dark.
- **Serial remote.** UART at 9600 baud accepts single-character commands and echoes each byte back.

| Command | Action |
|---|---|
| `0` | Start the fan |
| `1` | Start the exhaust fan |
| `2` | Stop the motor |
| `3` | Turn the light on |
| `4` | Open the blinds |
| `5` | Close the blinds |

## Architecture

```
firmware/
├── APP/    main.c: door-lock state machine and the Timer0 task loop
├── HAL/    CLCD, KPD (keypad), SSD (7-segment), DC_MOTOR, STEPPER_MOTOR, EEPROM
├── MCAL/   DIO, PORT, ADC, GIE, TIMER0, TIMER1, UART, TWI
└── LIB/    STD_TYPES.h, BIT_MATH.h
```

Most drivers follow the same file split: `*_interface.h` is the public API, `*_config.h` holds pin and mode choices, `*_private.h` and `*_register.h` stay internal, and `*_program.c` is the implementation. The application only includes interface headers, so it never touches a register directly.

The main loop handles the slow, blocking work: LCD prompts, password entry and motor moves. A Timer0 compare-match interrupt drives a small time-sliced loop. On each tick it services one job, such as reading a sensor, polling the switches and keypad, or refreshing one 7-segment digit, and it sets flags that the main loop acts on.

## Hardware

| Part | Connection |
|---|---|
| MCU | ATmega128 at 16 MHz |
| 16x2 character LCD | data on PORTE, control on PORTC |
| 4x4 keypad | PORTA |
| External EEPROM | TWI, device address `0xA0` |
| Servo (door) | Timer1 PWM output |
| Stepper motor (blinds) | ULN-series driver on PORTC pins 4 to 7 |
| DC motor (fan and exhaust) | two relays on PORTB pins 2 and 3 |
| LM35 temperature sensor | ADC0 |
| LDR | ADC1 |
| Two 7-segment digits | PORTF, PORTD and PORTB, multiplexed |

## Build

The Docker image contains the AVR toolchain and a host compiler, so the build does not depend on the local machine.

```sh
docker build -t smart-home-avr .
docker run --rm -v "$PWD:/src" smart-home-avr make all test
```

This produces `build/smart_home.hex`, prints the flash and RAM usage, and runs the unit tests. With `avr-gcc`, `avr-libc` and `make` installed locally, `make` and `make test` do the same.

The CI workflow runs the same container on every push and uploads the `.hex` file as a build artifact.

## Tests

The tests in `tests/` compile the real HAL drivers with the host `gcc` and link them against a fake DIO layer in `tests/fake_dio.c`. The fake records every pin write and lets each test decide what an input pin reads, so driver logic can be checked without hardware.

| Driver | What the tests check |
|---|---|
| 7-segment | every digit 0 to 9 lights the right segments, against a truth table written separately from the driver; only segment pins are written; enable drives the pin LOW and disable drives it HIGH |
| Keypad | all 16 keys map to the configured values through a simulated key matrix; the driver waits for the key to be released; every column is idle again afterwards; no key pressed returns `0xFF` |
| DC motor | forward, reverse and stop set the right relays; replaying every pin write shows the two relays are never on together while switching direction |
| BIT_MATH | set, clear, toggle and get |

Each test was checked by breaking the driver on purpose, for example by swapping the order of the two relay writes, and confirming that the test fails.

## Known limitations

- The password is stored as a 16-bit number, so values above 65535 overflow.
- After three wrong passwords the LCD shows a lock-out message, but further attempts are not blocked.
- The build reports two compiler warnings, one in the ADC driver and one in the LCD driver.

## History and credits

The firmware was written between December 2023 and January 2024. In 2026 the sources were reorganised by layer, and the Makefile, Docker image, CI workflow and unit tests were added. The firmware logic did not change. The only source edit was fixing the case of two include names so the code also builds on Linux.

Source files keep their original author headers. The Timer1 driver in `firmware/MCAL/TIMER1` is by Ahmed Saeed, and the EEPROM driver header names Hamo as its author.
