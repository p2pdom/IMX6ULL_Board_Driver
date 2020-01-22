.global _start
.global _bss_start
.global _bss_end



_start:
    b Reset_Handler      /*复位中断     */
    b Undefined_Handler  /*未定义中断   */
    b SVC_Hnadler        /*SVC中断     */
    b PrefAbort_Handler  /*预取终止指令  */
    b DataAbort_Handler  /*数据终止指令  */
    nop                  /*未使用中断    */
    b IRQ_Handler        /*IRQ中断     */
    b FIQ_Handler        /*FIQ快速中断  */

/*复位中断服务函数*/
Reset_Handler:

    /*关闭cache和MMU */
    /*
     *  需要操作CP15协处理器寄存器：
     *      MCR<c> <coproc>, <opc1>, <Rt>, <CRn>, <CRm>{, <opc2>} -> ARM数据到CP15
     *      MRC<c> <coproc>, <opc1>, <Rt>, <CRn>, <CRm>{, <opc2>} -> CP15数据到ARM
     */
    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1<<0)   //关闭MMU
    bic r0, r0, #(1<<1)   //关闭对齐
    bic r0, r0, #(1<<2)   //关闭D_cache
    bic r0, r0, #(1<<11)  //关闭分支预测
    bic r0, r0, #(1<<12)  //关闭I_cache
    mcr p15, 0, r0, c1, c0, 0

    /*设置中断向量偏移 */
    ldr r0, =0x87800000
    dsb  //数据同步
    isb  //指令同步
    mcr p15, 0, r0, c12, c0, 0
    dsb  //数据同步
    isb  //指令同步 

    /*设置处理器9种模式的SP指针 */
    //设置User和Sys的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x1F    /*设置为User模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80200000 /*设置SP指针 */
    //设置FIQ的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x11    /*设置为FIQ模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80400000 /*设置SP指针 */
    //设置IRQ的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x12    /*设置为IRQ模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80600000 /*设置SP指针 */
    //设置SVC的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x13    /*设置为SVC模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80800000 /*设置SP指针 */
    //设置MON的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x16    /*设置为MON模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80A00000 /*设置SP指针 */
    //设置ABT的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x17    /*设置为ABT模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80C00000 /*设置SP指针 */
    //设置HYP的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x1A    /*设置为HYP模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80E00000 /*设置SP指针 */
    //设置UND的SP指针
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x1B    /*设置为UND模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    ldr sp, =0x80F00000 /*设置SP指针 */
    
    dsb  //数据同步
    isb  //指令同步

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

    /*跳转到main函数 */
    mrs r0, cpsr         /*读取cpsr进入r0 */
    bic r0, r0, #0x1F    /*讲r0低5位清零 */
    orr r0, r0, #0x13    /*设置为SVC模式 */
    msr cpsr, r0         /*写回去cpsr寄存器 */
    b main


/*未定义中断服务函数*/
Undefined_Handler:
    b Undefined_Handler

/*SVC中断服务函数*/
SVC_Hnadler:
    b SVC_Hnadler

/*预取终止指令服务函数*/
PrefAbort_Handler:
    b PrefAbort_Handler

/*数据终止指令服务函数*/
DataAbort_Handler:
    b DataAbort_Handler


/*IRQ中断服务函数*/
IRQ_Handler:
    b IRQ_Handler

/*FIQ快速中断服务函数*/
FIQ_Handler:
    b FIQ_Handler

loop:
    b loop
  
