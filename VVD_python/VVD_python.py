from StandardLibrary import *

def Power(base, value):
	if value == 1:
		return (base)
	else:
		return (base * Power(base,value - 1))
	return (0)

def main():
	num = 5
	val = 3
	result = IntStr(Power(num,val))

	quest = ",does it means that Python is cool?"
	answ = "-It seems like that!\n"
	print ("-How much is " + IntStr(num) + " to the " + IntStr(val) + "d power?")
	print ("-It would be " + IntStr(result))
	print ("-Oh" + quest)
	print (answ)
	return (1)

main()
