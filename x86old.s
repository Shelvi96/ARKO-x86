	section .data
		segment .bss
		section .text
		
		global rotbmp24
	rotbmp24:
	    push ebp
	    mov ebp, esp
		push ebx
		push esi
		push edi
		
		; [ebp+8]	- kolorki
		; [ebp+12] - szerokosc obrazka

		mov eax, [ebp+12]	; przygotowanie do
		mov edx, [ebp+12]	; 	mnożenia
		mul edx

		mov edi, eax		; liczba wszystkich pikseli
		mov ecx, 0x0 		; licznik petli i indeksow
		
	; Odbicie względem przekątnej y = -x
	dec ecx
	petla1:
		inc ecx
		cmp ecx, edi	; petla po wszystkich pikselach
		jz petla2
	   
	    ; obliczamy wspolrzedne kolorku
	    mov eax, ecx		; numer
	    mov ebx, [ebp+12]	; szerokosc
	    div ebx			; numer komorki / szerokosc obrazka
	    				; (x,y) = (edx, eax)

	    cmp edx, eax	; if x >= y
	    ja petla1		; pomijamy

	    				; wsp. x w edx
	    mov esi, eax    ; wsp. y

	    mov eax, edx
	    mul ebx

	    add eax, esi 	; w eax mamy teraz nowy indeks
	    mov ebx, ecx	; w ebx stary indeks

	    mov esi, [ebp+8]
	    ;add eax, [ebp+8]
	    ;add ebx, [ebp+8]
	    ;mov eax, [esi+eax]
	    ;mov ebx, [esi+ebx]
	    ;xchg eax, ebx

	    jmp petla1

	petla2:
		
	end:
		pop edi
		pop esi
	  	pop ebx
		mov esp, ebp
	    pop ebp
		ret
