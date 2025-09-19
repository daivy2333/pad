import re

def calc(expr: str) -> float:

    tokens = re.findall(r'\d+\.\d+|[+\-*/()]', expr.replace(' ', ''))
    tokrns = [t for t in tokens if t]

    def parse_atom():
        nonlocal pos

        tok = tokens[pos]

        if tok == '(':
            pos += 1
            val = parse_expr()
            assert tokens[pos] == ')','缺少'
            pos += 1
            return val

        if tok in '+-' and (pos == 0 or tokens[pos - 1] in '+-*/('):

            pos += 1
            return -parse_atom() if tok == '-' else parse_atom()

        pos += 1
        return float(tok)
    
    def parse_mul_div():
        nonlocal pos

        left = parse_atom()

        while pos < len(tokens) and tokens[pos] in '*/':
            op = tokens[pos]

            pos += 1
            right = parse_atom()

            left = left * right if op == '*' else left / right

        return left

    def parse_expr():

        nonlocal pos

        left = parse_mul_div()

        while pos < len(tokens) and tokens[pos] in '+-':
            op = tokens[pos]

            pos += 1

            right = parse_mul_div()

            left = left + right if op == '+' else left - right

        return left

    pos = 0

    result = parse_expr()

    assert pos == len(tokens)

    return result

if __name__ == '__main__':
    s = input()
    try:
        print(calc(s))
    except Exception as e:
        print(e)