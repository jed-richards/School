n = int(input())

nums = []
for i in range(0,n):
    nums.append(int(input()))

parityArr = []
evens = []
odds = []

for num in nums:
    if num%2 == 0:
        parityArr.append(0)
        evens.append(num)
    else:
        parityArr.append(1)
        odds.append(num)

evens.sort()
odds.sort(reverse=True)

evenIndex = 0
oddIndex = 0

for i in range(0, len(parityArr)):
    if parityArr[i] == 0:
        #parityArr[i] = evens[evenIndex]
        print(evens[evenIndex])
        evenIndex += 1
    else:
        #parityArr[i] = odds[oddIndex]
        print(odds[oddIndex])
        oddIndex += 1



