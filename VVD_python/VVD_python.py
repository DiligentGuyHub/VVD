from StandardLibrary import *

def Max(first, second):
	if first > second:
		return first
	elif second > first:
		return second
	return 1

def Min(first, second):
	if first < second:
		return first
	elif second > first:
		return second
	else:
		return 0
	return 1

def main():
	value = 20
	mess = "Conjuction of two numbers equals: "
	conj = Max(10,20) & Min(30,40)

	result = IntStr(conj)

	print (mess + result)
	return 1

main()
