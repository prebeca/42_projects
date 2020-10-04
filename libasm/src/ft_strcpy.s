section.text
global	ft_strcpy

ft_strcpy:
			xor rcx,rcx
compare:

			mov bl, byte [rsi + rcx]
			mov byte [rdi + rcx],bl
			cmp byte [rsi + rcx],0
			je done
			inc rcx
			jmp compare
done:
			mov rax,rdi
			ret