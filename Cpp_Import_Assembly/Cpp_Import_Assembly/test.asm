;测试函数   三个数相加  
;.386
.model flat, c
;public test_

.code

test_ proc

;初始化栈帧指针
    push ebp
    mov ebp,esp
;加载参数值
    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    mov edx,[ebp+16]

;求和
    add eax,ecx
    add eax,edx

;恢复父函数的栈帧指针

    pop ebp
    ret


test_ endp
end