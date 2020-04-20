
        global  set_bit_elem
        global  get_bit_elem
        section .text

set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here
        imul rdx, rsi       ; row_width * row (first part of offset)
        add rcx, rdx        ; (row_width * row) + column (second part of offset) - in rcx because cl used to extend
        mov rax, 1          ; initialize the mask
        sal rax, cl         ; shift by offset to create the mask
        or [rdi], rax       ; apply the mask

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0
        imul rdx, rsi       ; row_width * row (first part of offset)
        add rcx, rdx        ; ^ + column (second part of offset) - in rcx because cl (for sign extension) is second part of rcx
        mov rax, 1          ; init mask
        sal rax, cl         ; shift to create mask
        and rax, [rdi]      ; apply mask
        cmp rax, 0          ; if larger than zero then bit is 1
        setg al             ; set flag
        movsx rax, al       ; move and sign extend flag into all of rax for returning

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
