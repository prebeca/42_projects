section.text
global	ft_strcmp

ft_strcmp:
			xor rcx,rcx
compare:
			mov al, [rdi + rcx]
			sub al, [rsi + rcx]
			jnz done_compare
			cmp byte [rdi + rcx],0
			je done
			inc rcx
			jmp compare
done_compare:
			jns done
			sub rax,256
done:
			ret