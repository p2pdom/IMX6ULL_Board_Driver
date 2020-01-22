.global _start
.global _bss_start


_start:
    /*设置处理器进入SVC模式 */
    mrs r0, cpsr            /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x13    /*设置为SVC模式 */
    msr cpsr, r0           /*写回去cpsr寄存器 */

    /*清除bss段  */
_bss_start:
    .word __bss_start

_bss_end:
    .word __bss_end

    ldr r0, _bss_start
    ldr r1, _bss_end
    mov r2, #0
bss_loop:
    stmia r0!, {r2}
    cmp r0, r1
    ble bss_loop


    /*设置sp指针 */
    ldr sp, = 0x80200000

    /*跳转到main函数 */
    b main


loop:
    b loop