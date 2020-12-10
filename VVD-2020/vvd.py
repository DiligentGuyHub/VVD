

def Max(first, second, diff, eq):
    result = 0
    if first > second:
        result = first
        print (diff + str(result))
    elif second > first:
        result = second
        print (diff + str(result))
    else:
        print (eq)
        return 0
    return 1

# main 

def main():
    first = 16 + 15
    second = 32
    mess1 = "Максимальное число равно: "
    mess2 = "Числа равны!"
    result = Max(first, second, mess1, mess2)
    return
