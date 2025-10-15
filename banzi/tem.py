# -------------------------------------------------
# Pico Internal-Temperature Monitor (English Ver.)
# -------------------------------------------------
# Hardware: any Raspberry Pi Pico / Pico W
# Wiring:   none – just the on-board LED
# Author:   you

from machine import ADC, Pin
from utime import sleep

# ---------- user-config ----------
READ_INTERVAL_S   = 2.0          # sampling period
LONG_BLINK_S      = 0.8          # length of “long” blink (tens)
SHORT_BLINK_S     = 0.2          # length of “short” blink (units)
GAP_S             = 0.2          # gap between blinks
PAUSE_BETWEEN_DIGITS_S = 1.0     # gap between tens and units

WAVEFORM_WIDTH    = 40           # ASCII plot width
TEMP_RANGE_MIN    = 20.0         # bottom of plot (°C)
TEMP_RANGE_MAX    = 40.0         # top of plot (°C)
# ---------------------------------

# ADC channel 4 is the internal temperature sensor
adc_temp = ADC(4)

# On-board LED (Pico W: "LED", vanilla Pico: 25)
led = Pin("LED", Pin.OUT)

# convert raw 16-bit reading to voltage
_ADC_TO_V = 3.3 / 65535

# datasheet formula constants
_V_TO_TEMP_OFFSET = 0.706
_V_TO_TEMP_SLOPE  = 0.001721      # 1.721 mV / °C
_BASE_TEMP        = 27.0          # °C


def read_temp_celsius():
    """Return current die temperature in °C."""
    raw_v = adc_temp.read_u16() * _ADC_TO_V
    temp_c = _BASE_TEMP - (raw_v - _V_TO_TEMP_OFFSET) / _V_TO_TEMP_SLOPE
    return temp_c


def report_by_led(temp_int):
    """Blink out the integer temperature: tens = long, units = short."""
    tens = temp_int // 10
    units = temp_int % 10
    print(f"LED: {tens} long blink(s) + {units} short blink(s)")

    # ----- tens -----
    for _ in range(tens):
        led.on()
        sleep(LONG_BLINK_S)
        led.off()
        sleep(GAP_S)

    sleep(PAUSE_BETWEEN_DIGITS_S)

    # ----- units -----
    for _ in range(units):
        led.on()
        sleep(SHORT_BLINK_S)
        led.off()
        sleep(GAP_S)


def plot_ascii(temp_c):
    """Print a tiny bar-graph to the serial console."""
    # clamp inside chosen range
    t = max(TEMP_RANGE_MIN, min(TEMP_RANGE_MAX, temp_c))
    ratio = (t - TEMP_RANGE_MIN) / (TEMP_RANGE_MAX - TEMP_RANGE_MIN)
    bar_len = int(ratio * WAVEFORM_WIDTH)

    bar   = '#' * bar_len
    space = ' ' * (WAVEFORM_WIDTH - bar_len)

    # left-hand scale
    left_label = f"{TEMP_RANGE_MIN:2.0f}C"
    right_label = f"{TEMP_RANGE_MAX:2.0f}C"

    print(f"{left_label} |{bar}{space}| {temp_c:5.2f}C  {right_label}")


# -------------------- main loop --------------------
def main():
    print("Pico temperature monitor started (Ctrl-C to stop)\n")
    try:
        while True:
            temp = read_temp_celsius()

            # 1. visual waveform
            plot_ascii(temp)

            # 2. LED morse-style readout
            report_by_led(round(temp))

            sleep(READ_INTERVAL_S)

    except KeyboardInterrupt:
        led.off()
        print("\nUser interrupted LED off, script exit.")


# run only if this file is executed (not imported)
if __name__ == "__main__":
    main()