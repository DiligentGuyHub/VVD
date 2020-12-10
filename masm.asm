.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib user32.lib
includelib "..\Debug\StandardLibrary.lib"

ExitProcess proto : DWORD
MessageBoxA proto	: DWORD, : DWORD, : DWORD, : DWORD
GetStdHandle proto : DWORD
WriteConsoleA proto : DWORD, : DWORD, : DWORD, : DWORD, : DWORD

extern StrLen : proc
extern StrInt : proc
extern IntStr : proc
extern PintStr : proc
extern SignInt : proc
extern Concat : proc
extern print_int : proc
extern print_pint : proc
extern print_bool : proc
extern print_str : proc
extern print_sign : proc

.stack 4096

.const
handleOutput	SDWORD	-11
INT1			SDWORD	0
INT2			SDWORD	1
INT3			SDWORD	58
INT4			SDWORD	-13
INT5			SDWORD	32
STR1			BYTE	"Максимальное число равно: ", 0
STR2			BYTE	"Числа равны!", 0
INT6			SDWORD	1

.data
consoleHandle	DWORD	0h
Max_result			BYTE	?, 0
main_first			SDWORD	0
main_second			DWORD	0
main_mess1			BYTE	?, 0
main_mess2			BYTE	?, 0
main_result			BYTE	0


.code
Max PROC	 Max_first : SDWORD,  Max_second : DWORD,  Max_diff : BYTE,  Max_eq : BYTE

	mov ebx, Max_first
.if ebx > Max_second 

	push dword ptr[Max_diff]
	call print_str

	mov bl, Max_result
	invoke WriteConsoleA, consoleHandle, ebx, sizeof Max_result, 0, 0

	mov ebx, Max_second 
.elseif ebx > Max_first 

	mov bl, Max_diff
	invoke WriteConsoleA, consoleHandle, ebx, sizeof Max_diff, 0, 0

	mov bl, Max_result
	invoke WriteConsoleA, consoleHandle, ebx, sizeof Max_result, 0, 0
.else 
	mov bl, Max_eq
	invoke WriteConsoleA, consoleHandle, ebx, sizeof Max_eq, 0, 0
.endif
	ret
Max ENDP

main PROC
	push offset STR2
	push offset STR1
	push INT3
	PUSH INT5
	call Max
	push 0
  	call ExitProcess
main ENDP
end main
