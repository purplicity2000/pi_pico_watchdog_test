A simple watchdog test for pi pico.
Using the standard arduino IDE

Set board using Earle F. Philhower, III's excellent RP2040 board library:
	https://github.com/earlephilhower/arduino-pico

The loop delay gradually increases until it is longer than the watchdog timeout
When the watchdog timeout is exceeded, the pico reboots
Tested on a standard pi pico

Jason Maher / Purplicity / code@purplicity.com
