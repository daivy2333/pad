from machine import Pin
from utime import sleep

# ---------- Morse Code Section ----------
MORSE_CODE = {
    'A': '.-', 'B': '-...', 'C': '-.-.', 'D': '-..',
    'E': '.', 'F': '..-.', 'G': '--.', 'H': '....',
    'I': '..', 'J': '.---', 'K': '-.-', 'L': '.-..',
    'M': '--', 'N': '-.', 'O': '---', 'P': '.--.',
    'Q': '--.-', 'R': '.-.', 'S': '...', 'T': '-',
    'U': '..-', 'V': '...-', 'W': '.--', 'X': '-..-',
    'Y': '-.--', 'Z': '--..',
    '0': '-----', '1': '.----', '2': '..---', '3': '...--',
    '4': '....-', '5': '.....', '6': '-....', '7': '--...',
    '8': '---..', '9': '----.', ' ': '/'
}

led = Pin("LED", Pin.OUT)
DOT_TIME = 0.2
DASH_TIME = DOT_TIME * 3
LETTER_SPACE = DOT_TIME * 3
WORD_SPACE = DOT_TIME * 7

def blink_dot():
    led.on(); sleep(DOT_TIME)
    led.off(); sleep(DOT_TIME)

def blink_dash():
    led.on(); sleep(DASH_TIME)
    led.off(); sleep(DOT_TIME)

def text_to_morse(text):
    result = []
    for ch in text.upper():
        result.append(MORSE_CODE.get(ch, ''))
    return result

def blink_morse(text):
    morse_list = text_to_morse(text)
    print("Morse:", ' '.join(morse_list))
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

# ---------- Expert System Section ----------
class Rule:
    def __init__(self, antecedents, consequent):
        self.antecedents = antecedents
        self.consequent = consequent

def initialize_knowledge_base():
    id_map = {
        1: "has hair", 2: "gives milk", 3: "has feathers",
        4: "can fly", 5: "lays eggs", 6: "eats meat",
        7: "has canine teeth", 8: "has claws", 9: "eyes face forward",
        10: "has hooves", 11: "ruminant", 12: "yellow brown",
        13: "has spots", 14: "has black stripes", 15: "long neck",
        16: "long legs", 17: "cannot fly", 18: "can swim",
        19: "black and white", 20: "good flyer",
        21: "mammal", 22: "bird", 23: "carnivore", 24: "ungulate",
        25: "leopard", 26: "tiger", 27: "giraffe", 28: "zebra",
        29: "ostrich", 30: "penguin", 31: "albatross"
    }

    rules = [
        Rule([1], 21),
        Rule([2], 21),
        Rule([3], 22),
        Rule([4, 5], 22),
        Rule([6], 23),
        Rule([7, 8, 9], 23),
        Rule([21, 10], 24),
        Rule([21, 11], 24),
        Rule([21, 23, 12, 13], 25),
        Rule([21, 23, 12, 14], 26),
        Rule([24, 15, 16, 13], 27),
        Rule([24, 14], 28),
        Rule([22, 15, 16, 17, 19], 29),
        Rule([22, 18, 19, 17], 30),
        Rule([22, 20], 31)
    ]
    return id_map, rules

def get_user_facts(id_map):
    print("************************************************")
    print("Enter numbers for known facts (1-20):")
    for i in range(1, 21):
        print(f"{i}: {id_map[i]:<15}", end="\t")
        if i % 4 == 0:
            print()
    print("\nEnter 0 to finish.")
    facts = set()
    while True:
        try:
            n = int(input("Enter: "))
            if n == 0:
                break
            if 1 <= n <= 20:
                if n not in facts:
                    facts.add(n)
                    print(f"Added: {id_map[n]}")
                else:
                    print("Already added.")
            else:
                print("Invalid number.")
        except:
            print("Invalid input.")
    return facts

def run_inference(rules, initial_facts):
    facts = set(initial_facts)
    log = []
    changed = True
    while changed:
        changed = False
        for rule in rules:
            if rule.consequent in facts:
                continue
            if all(ant in facts for ant in rule.antecedents):
                facts.add(rule.consequent)
                changed = True
                log.append(f"IF {', '.join(map(str, rule.antecedents))} THEN {rule.consequent}")
    return facts, log

def display_results(initial_facts, final_facts, log, id_map):
    print("\nInitial facts:")
    print(", ".join(id_map[i] for i in initial_facts))

    print("\nInference log:")
    for entry in log:
        print(entry)

    result = None
    for i in range(25, 32):
        if i in final_facts:
            result = id_map[i]
            break

    print("\nFinal result:")
    if result:
        print(result)
        print("Outputting Morse code...")
        blink_morse(result)
    else:
        print("No animal identified.")

# ---------- Main ----------
if __name__ == "__main__":
    id_map, rules = initialize_knowledge_base()
    user_facts = get_user_facts(id_map)
    if not user_facts:
        print("No input facts, exiting.")
    else:
        final_facts, log = run_inference(rules, user_facts)
        display_results(user_facts, final_facts, log, id_map)


# 可以测试的 1 6 12 13 0 是金钱豹
