section.text
global	ft_strdup

extern malloc

ft_strdup:
			xor rcx,rcx
get_len:
			cmp byte [rdi + rcx],0
			je strdup
			inc rcx
			jmp get_len
strdup:
			push rdi
			inc rcx
			mov rdi,rcx
			call malloc
			pop rdi
			cmp rax,0
			jz done
			xor rcx,rcx
copy:
			mov bl,byte [rdi + rcx]
			mov byte [rax + rcx],bl
			cmp byte [rdi + rcx],0
			je done
			inc rcx
			jmp copy
done:
			ret