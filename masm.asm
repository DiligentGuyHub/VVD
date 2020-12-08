.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib user32.lib
includelib "..\Debug\StandardLibrary.lib"

ExitProcess proto : DWORD
MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD
extern StrLen : proc
extern StrInt : proc
extern IntStr : proc
extern PintStr : proc
extern SignInt : proc
extern print_int : proc
extern print_pint : proc
extern print_bool : proc
extern print_str : proc
extern print_sign : proc

.stack 4096

.const
INT1			SDWORD	5
INT2			SDWORD	10
INT3			SDWORD	2
INT4			SDWORD	2
INT5			SDWORD	2

.data
main_x			SDWORD	0
main_y			BYTE	1

.code
some PROC b : byte
	mov bl, b
	ret
some ENDP

main PROC
 	mov al, main_y
	push ax
	call some


	push 0
	call ExitProcess
main ENDP
end main