# ------------ breathe_led.py -------------
# Board-only LED breath lamp (MicroPython)
# Author: you

from machine import Pin, PWM
from math import sin, pi
from utime import sleep_ms

# ---------- config ----------
LED_PIN      = "LED"      # Pico W
# LED_PIN   = 25          # vanilla Pico
BREATHE_HZ   = 0.8        # 0.5 ~ 2.0  Hz  越大越快
PWM_FREQ     = 1_000      # 1 kHz 足够，无噪音
STEPS        = 120        # 一个周期采样点，越大越平滑
# ----------------------------

# build lookup table (0-65535 for 16-bit PWM)
sin_table = [int((sin(2 * pi * i / STEPS) + 1) * 32767) for i in range(STEPS)]

led = PWM(Pin(LED_PIN))
led.freq(PWM_FREQ)

period_ms = int(1000 / BREATHE_HZ)

print("Breathing LED started  (Ctrl-C to stop)")
try:
    while True:
        for duty in sin_table:
            led.duty_u16(duty)
            sleep_ms(period_ms // STEPS)
except KeyboardInterrupt:
    led.duty_u16(0)
    led.deinit()
    print("LED off – script ended")