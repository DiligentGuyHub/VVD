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

.stack 4096

.const
handleOutput	SDWORD	-11
INT1			SDWORD	1
INT2			SDWORD	2
INT3			SDWORD	3
INT4			SDWORD	1

.data
consoleHandle	DWORD	0h
main_a			SDWORD	0
main_b			SDWORD	0
main_c			SDWORD	0
main_d			SDWORD	0


.code
main PROC
	invoke GetStdHandle, handleOutput
	mov consoleHandle, eax
	push	INT1
	pop ebx
	mov	main_a, ebx

	push	INT2
	pop ebx
	mov	main_b, ebx

	push	INT3
	pop ebx
	mov	main_c, ebx

	push	main_a
	push	main_b
	pop ebx
	pop edx
	add edx, ebx
	push edx
	push	main_c
	pop ebx
	pop edx
	add edx, ebx
	push edx
	pop ebx
	mov	main_d, ebx

	push	main_d
	call print_int

	push 0
	call ExitProcess
main ENDP
end main