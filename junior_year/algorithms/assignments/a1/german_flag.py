def GermanFlag(A):
    B = len(A)
    CharArray = ["B", "R", "Y"]
    i = 0
    for char1 in CharArray:
        for char2 in A:
            if char2 == char1:
                B[i] = char2
                i += 1

    return B


print(GermanFlag(["R", "B", "B", "Y", "R"]))
