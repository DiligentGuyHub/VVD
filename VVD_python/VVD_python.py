def Max(first, second, diff, eq):
	if first > second:
		result = first 
		print (diff)
		print (result)
	elif second > first:
		result = second 
		print (diff)
		print (result)
	else:
		print (eq)
		return 0
	return 1

def main():
	first = 58 + -13
	second = 32
	str1 = "Max number is: "
	str2 = "Numbers are equal!"
	result = Max(first,second,str1,str2) + Max(first,second,str1,str2)
	print (result)
	return 1

main()
