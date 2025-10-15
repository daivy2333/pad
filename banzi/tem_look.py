# ------------ thermal_breathe.py ------------
# Hot-breath LED: 27 °C dim → 30 °C bright
# Board-only, run on any Pico / Pico W
# Author: you

from machine import Pin, PWM, ADC
from utime import sleep_ms

# ---------- config ----------
LED_PIN      = "LED"          # Pico W
# LED_PIN   = 25              # vanilla Pico
PWM_FREQ     = 1_000          # 1 kHz

T_LOW  = 27.0                 # °C → 最暗
T_HIGH = 30.0                 # °C → 最亮
DIM    = 2_000                # 27 °C 对应 duty (≈3 %)
BRIGHT = 65_535               # 30 °C 对应 duty (100 %)

SMOOTH_MS = 50                # 刷新周期
# ----------------------------

adc_temp = ADC(4)
led = PWM(Pin(LED_PIN))
led.freq(PWM_FREQ)

# 温度转换常量（来自数据手册）
_ADC_TO_V = 3.3 / 65535
_OFFSET   = 0.706
_SLOPE    = 0.001721
_BASE     = 27.0

def read_temp():
    raw_v = adc_temp.read_u16() * _ADC_TO_V
    return _BASE - (raw_v - _OFFSET) / _SLOPE

def clamp(x, lo, hi):
    return max(lo, min(hi, x))

def temp_to_duty(temp):
    """线性映射温度 → duty"""
    if temp <= T_LOW:
        return DIM
    if temp >= T_HIGH:
        return BRIGHT
    ratio = (temp - T_LOW) / (T_HIGH - T_LOW)
    return int(DIM + ratio * (BRIGHT - DIM))

print("Thermal breathing LED started (Ctrl-C to stop)")
try:
    while True:
        temp = read_temp()
        duty = temp_to_duty(temp)
        led.duty_u16(duty)
        sleep_ms(SMOOTH_MS)

except KeyboardInterrupt:
    led.duty_u16(0)
    led.deinit()
    print("LED off – script exit")