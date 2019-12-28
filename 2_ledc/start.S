.global _start

_start:
    /*设置处理器进入SVC模式 */
    mrs r0, cpsr            /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x13    /*设置为SVC模式 */
    msr cpsr, r0           /*写回去cpsr寄存器 */

    /*设置sp指针 */
    ldr sp, = 0x80200000

    /*跳转到main函数 */
    b main


loop:
    b loop