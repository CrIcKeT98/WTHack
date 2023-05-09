public air_leading_hook

.code

air_leading_hook PROC
	movaps [rsp + 30h], xmm6
	mov byte ptr [rsp + 20h], 0h
	lea rdi, [rsp+30h]
	lea r8, [rsp+20h]
	mov rcx, rsi

	push rdx

	mov r8, [rcx]
	mov rdx, [rcx + 14h]
	add r8, rdx
	add r8, 94h
	mov rax, r8
	mov DWORD PTR [rax], 1h

	pop rdx

	jmp rdx
air_leading_hook ENDP

end