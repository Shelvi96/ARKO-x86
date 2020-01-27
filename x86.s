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
	lea eax, [eax*4]		; total number of bmp pixels

	mov ecx, eax			; counter
	mov edi, input			; current pixel
	
lp1:
	; checking if should be swapped
	mov eax, [cox]
	mov ebx, [coy]
	cmp eax, ebx
	jae nxt					; if x >= y skip

	; counting new position
	mov eax, [cox]
	mov ebx, width
	mul ebx
	mov ebx, [coy]
	add eax, ebx			; eax : x*witdh+y

	; counting new index
	mov ebx, 4
	mul ebx					
	mov esi, eax			; esi has dest coords

	; swapping old index with new one
	mov eax, esi
	mov esi, edi
	mov edi, eax

	; checking if end of a row
	mov eax, [cox]
	mov ebx, width
	sub ebx, 1
	cmp eax, ebx
	jne incrow

	; this is the end of the row -> moving to next column
	mov dword[cox], 0
	mov ebx, dword[coy]
	inc ebx
	mov dword[coy], ebx
	jmp nxt

	; its not the end of the row -> moving to next row
incrow:
	mov ebx, dword[cox]
	inc ebx
	mov dword[cox], ebx

	; move to next pixel (edi), decrease counter
nxt:
	add edi, 4
	sub ecx, 4
    jnz lp1
	
end:
	pop edi
	pop esi
  	pop ebx
	mov esp, ebp
    pop ebp
	ret
