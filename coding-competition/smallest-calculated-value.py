def get_smallest(a, b, c):
    value_list = []

    value_list.append((a-b)-c)
    value_list.append((a-b)+c)
    value_list.append((a-b)*c)
    if (a-b)%c == 0:
        value_list.append(int((a-b)/c))
    #if isinstance((a-b)/c, int):
    #    value_list.append((a-b)/c)

    value_list.append(a+b-c)
    value_list.append(a+b+c)
    value_list.append((a+b)*c)
    if (a+b)%c == 0:
        value_list.append(int((a+b)/c))
    #if isinstance((a+b)/c, int):
    #    value_list.append((a+b)/c)

    value_list.append((a*b)-c)
    value_list.append((a*b)+c)
    value_list.append((a*b)*c)
    if (a*b)%c == 0:
        value_list.append(int((a*b)/c))
    #if isinstance((a*b)/c, int):
    #    value_list.append((a*b)/c)

    if (a%b) == 0:
    #if isinstance((a/b), int):
        value_list.append(int((a/b)-c))
        value_list.append(int((a/b)+c))
        value_list.append(int((a/b)*c))
        if (a/b)%c == 0:
            value_list.append(int((a/b)/c))
    #if isinstance((a/b)/c, int):
    #    value_list.append((a/b)/c)

    for i in range(0, len(value_list)):
        if value_list[i] > 0:
            smallest = value_list[i]
            break

    for val in value_list:
        if val < smallest and val >= 0:
            smallest = val

    return smallest



values = input().split(' ')

a = int(values[0])
b = int(values[1])
c = int(values[2])

print(get_smallest(a, b, c))

