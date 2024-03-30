option casemap:none
includelib kernel32.lib

extrn GetStdHandle: proc
extrn WriteFile: proc

.code

public _sum
public _sub
public _mult
public _print

_sum proc
	mov rax, rcx
	add rax, rdx
	ret
_sum endp

_sub proc
	mov rax, rcx
	sub rax, rdx
	ret
_sub endp

_mult proc
	mov rax, rcx
	imul rax, rdx
	ret
_mult endp

_print proc
	sub rsp, 40
	mov rdx, rcx
	mov rcx, -11
	call GetStdHandle
	mov rcx, rax
	mov rax, -1
	calcLen:
	inc rax
	cmp byte ptr [rdx][rax * 1], 0
	jne calcLen
	mov r8d, eax
	xor r9d, r9d
	mov qword ptr [rsp + 32], 0
	call WriteFile
	add rsp, 40
	ret
_print endp
end