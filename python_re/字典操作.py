def part2():

    goods = {'tv':3400 , 'contitor':2300}

    goods['洗衣机'] = 1200

    max_good = max(goods, key = goods.get)

    avg = sum(goods.values()) / len(goods)

    print(f'{max_good},{goods[max_good]}')
    print(f'{avg:.2f}')

    goods['contitor'] = 2800

    goods.pop('tv', None)

    print(goods)

part2()