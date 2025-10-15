from machine import Pin
from utime import sleep

# 定义摩斯码字典
MORSE_CODE = {
    'A': '.-',     'B': '-...',   'C': '-.-.',   'D': '-..',
    'E': '.',      'F': '..-.',   'G': '--.',    'H': '....',
    'I': '..',     'J': '.---',   'K': '-.-',    'L': '.-..',
    'M': '--',     'N': '-.',     'O': '---',    'P': '.--.',
    'Q': '--.-',   'R': '.-.',    'S': '...',    'T': '-',
    'U': '..-',    'V': '...-',   'W': '.--',    'X': '-..-',
    'Y': '-.--',   'Z': '--..',
    '0': '-----',  '1': '.----',  '2': '..---',  '3': '...--',
    '4': '....-',  '5': '.....',  '6': '-....',  '7': '--...',
    '8': '---..',  '9': '----.',
    ' ': '/',  # 单词之间的间隔
}

# LED 引脚
led = Pin("LED", Pin.OUT)

# 定义时间单位（可以调整闪烁速度）
DOT_TIME = 0.2   # “点”时间
DASH_TIME = DOT_TIME * 3  # “划”时间
LETTER_SPACE = DOT_TIME * 3
WORD_SPACE = DOT_TIME * 7

def blink_dot():
    led.on()
    sleep(DOT_TIME)
    led.off()
    sleep(DOT_TIME)

def blink_dash():
    led.on()
    sleep(DASH_TIME)
    led.off()
    sleep(DOT_TIME)

def text_to_morse(text):
    result = []
    for ch in text.upper():
        result.append(MORSE_CODE.get(ch, ''))
    return result

def blink_morse(text):
    morse_list = text_to_morse(text)
    print("the mos is", ' '.join(morse_list))
    for code in morse_list:
        if code == '/':
            sleep(WORD_SPACE)
        else:
            for symbol in code:
                if symbol == '.':
                    blink_dot()
                elif symbol == '-':
                    blink_dash()
            sleep(LETTER_SPACE)
a = 0
# 主程序
while True:

    try:
        a += 1
        blink_morse('i love you')
        print("finished")
        if a == 10:
            break
    except KeyboardInterrupt:
        led.off()
        print("\nmamba out")
        break
    