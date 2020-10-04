section.text
global	ft_strlen

ft_strlen:
			xor rcx,rcx	
compare:
			cmp byte [rdi + rcx],0
			je done
			inc rcx
			jmp compare
done:
			mov rax,rcx
			ret