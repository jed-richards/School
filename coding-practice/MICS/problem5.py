f = input()
st = input()

st.replace("F", f)

strs = st.split()

nums = []

for s in strs:
    if s == 'F':
        nums.append(int(f))
    else:
        nums.append(int(s))


TOTAL = sum(nums)

possible = {}

for x in range(0, TOTAL):
    possible[x] = False

possible[0] = True

for i in range(0, len(nums)):
    x = TOTAL
    while x >= 0:
        if possible.get(x) == True:
            possible[x + nums[i]] = True
        x -= 1

arr = []
for k in possible.keys():
    if possible.get(k) == False:
        arr.append(k)

arr.sort()

print(f'The number of amounts between 0 and {TOTAL} that cannot be made exactly is {len(arr)}.')
print('The amounts that cannot be made exactly are:')
for n in arr:
    print(n)
