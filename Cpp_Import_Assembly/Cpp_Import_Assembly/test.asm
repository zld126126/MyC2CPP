;���Ժ���   ���������  
;.386
.model flat, c
;public test_

.code

test_ proc

;��ʼ��ջָ֡��
    push ebp
    mov ebp,esp
;���ز���ֵ
    mov eax,[ebp+8]
    mov ecx,[ebp+12]
    mov edx,[ebp+16]

;���
    add eax,ecx
    add eax,edx

;�ָ���������ջָ֡��

    pop ebp
    ret


test_ endp
end