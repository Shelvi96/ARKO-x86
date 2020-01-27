section .data
cox dd 0
coy dd 0

segment .bss

section .text		
global rotbmp24
rotbmp24:
    push ebp
    mov ebp, esp
	push ebx
	push esi
	push edi
	
	%define input [ebp+8]	; bmp
	%define width [ebp+12]	; bmp width/height

	mov eax, width
	imul eax, width
	lea eax, [eax*2+eax]		; total number of bmp pixels

	mov ecx, eax			; counter
	mov esi, input			; target pixal
	mov edi, input			; source pixel
	
lp1:
	; checking if should be swapped
	mov eax, dword[cox]
	mov ebx, dword[coy]
	cmp eax, ebx
	jae swapped					; if x >= y skip

	; counting new position
	mov eax, width
	mov ebx, dword[cox]
	mul ebx
	mov ebx, dword[coy]
	add eax, ebx			; eax : x*witdh+y

	; counting new index
	mov ebx, 3
	mul ebx					
	add esi, eax			; esi has dest index
							; edi has source index

	;xchg edi, esi
	mov al, byte[esi]
	mov ah, byte[edi]
	mov byte[esi], ah
	mov byte[edi], al
	
	mov al, byte[esi+1]
	mov ah, byte[edi+1]
	mov byte[esi+1], ah
	mov byte[edi+1], al
	
	mov al, byte[esi+2]
	mov ah, byte[edi+2]
	mov byte[esi+2], ah
	mov byte[edi+2], al

	;mov byte[edi+1], 0
	;mov byte[edi+2], 0

swapped:
	; checking if end of a row
	mov ebx, dword[cox]
	mov eax, width
	sub eax, 1
	cmp eax, ebx
	jne incrow

	; this is the end of the row -> moving to next row
	mov dword[cox], 0
	mov ebx, dword[coy]
	inc ebx
	mov dword[coy], ebx
	jmp nxt

	; its not the end of the row -> moving to next column
incrow:
	;mov ebx, dword[cox]
	inc ebx
	mov [cox], ebx

	; reset esi (target), increase edi(source), decrease counter
nxt:
	mov esi, input
	add edi, 3
	sub ecx, 3
    jnz lp1
	
end:
	pop edi
	pop esi
  	pop ebx
	mov esp, ebp
    pop ebp
	ret
