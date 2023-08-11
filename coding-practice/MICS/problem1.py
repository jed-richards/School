master_dict = {}

def f(n):
    if n in master_dict:
        return master_dict[n]

    elif n < -20:
        master_dict[n] = (f(n+15) + f(n+10) - f(n+5)) 
        return master_dict[n]

    elif n <= -10 and -20 <= n:
        master_dict[n] = n*3
        return master_dict[n]

    elif n > -10:
        master_dict[n] = (f(n-7) - f(n-2))
        return master_dict[n]


n = int(input())

inputs = []
for i in range(n):
    inputs.append(int(input()))

count = 1
for i in inputs:
    v = f(i)
    print(f'Case {count}: F({i}) = {v}')
    count+=1

