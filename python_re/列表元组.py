def part1():
	# 初始化列表，这是一个以元组为元素的列表
    data = [('李芳', 86, 80), ('张艳', 74, 75)]
	# 添加元素
    data.append(('王志', 87, 95))
	
    new_data = [(name, round(0.4 * usual + 0.6 * final, 1))
    		for name, usual, final in data]
    print('新列表', new_data)
    data = [item for item in data if item[0] != '李芳']

    print('删除后列表', data)

if __name__ == '__main__':
    part1()