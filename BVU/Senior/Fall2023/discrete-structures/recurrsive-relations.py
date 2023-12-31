from timeit import default_timer

vals = {}

def r_store(n: int):
    if n == 1:
        return 0
    if n in vals:
        return vals[n]
    else:
        vals[n] = r_store(n-1) + 3
        return vals[n]

def r_no_store(n: int):
    if n == 1:
        return 0
    else:
        return r_no_store(n-1) + 3

if __name__ == '__main__':
    t1 = default_timer()
    print(r_store(5))
    t2 = default_timer()
    store_time = t2 - t1
    
    t1 = default_timer()
    print(r_no_store(5))
    t2 = default_timer()
    no_store_time = t2 - t1

    print(store_time)
    print(no_store_time)
