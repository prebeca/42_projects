section.text
global	ft_read

extern __errno_location

ft_read:
			xor rax,rax
			mov rax,0
			syscall
			cmp rax,0
			jl error
			ret
error:
			push rax
			call __errno_location
			pop rbx
			neg rbx
			mov [rax],rbx
			mov rax,-1
			ret