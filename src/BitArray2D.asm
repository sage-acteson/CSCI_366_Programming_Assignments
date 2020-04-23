
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
        ; calculate index
        imul rdx, rsi       ; row_width * row (first part of offset)
        add rdx, rcx        ; (row_width * row) + column (second part of offset) - index
        ; calculate the byte_offset
        mov rsi, rdx        ; copy the index value
        sar rsi, 3          ; /8 for offset
        ; calculate the bit_offset
        mov rax, rsi        ; copy the byte_offset value
        sal rax, 3          ; byte_offset * 8
        sub rdx, rax        ; calculate bit_offset
        ; make mask
        mov rcx, 8          ; init to calculate shift for mask
        sub rcx, rdx        ; calculate shift for mask
        sub rcx, 1
        mov rdx, 1
        sal rdx, cl         ; shift the mask to its final form

        ; apply the mask
        ;mov rax, [rdi+rsi*8]; read from memory at the byte offset
        or [rdi+rsi], rdx       ; apply the mask

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
        ; calculate index
        imul rdx, rsi       ; row_width * row (first part of offset)
        add rdx, rcx        ; ^ + column (second part of offset)
        ; calculate byte offset
        mov rsi, rdx        ; copy index
        sar rsi, 3          ; /8 for offset
        ; calculate bit offset
        mov rax, rsi        ; copy byte offset
        sal rax, 3          ; *8
        sub rdx, rax        ; get bit offset
        ; make mask
        mov rcx, 8          ; init shift val for mask
        sub rcx, rdx        ; calc shift
        sub rcx, 1
        mov rdx, 1          ; init mask
        sal rdx, cl         ; shift mask to its final form
        ; apply mask
        and rdx, [rdi+rsi]  ; apply mask
        ; determine result
        cmp rdx, 0          ; if result is larger than 0
        setg al             ; set something
        movsx rax, al       ; move and sign extend for returning


        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
