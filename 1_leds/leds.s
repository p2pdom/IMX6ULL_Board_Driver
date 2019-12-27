.global _start
_start:
    /* 开启所有外设时钟*/
    ldr r0, = 0x020C4068
    ldr r1, = 0xFFFFFFFF
    str r1, [r0]

    ldr r0, = 0x020C406C
    str r1, [r0]

    ldr r0, = 0x020C4070
    str r1, [r0]

    ldr r0, = 0x020C4074
    str r1, [r0]

    ldr r0, = 0x020C4078
    str r1, [r0]

    ldr r0, = 0x020C407C
    str r1, [r0]

    ldr r0, = 0x020C4080
    str r1, [r0]

    /*设置GPIO1_3的复用 */
    ldr r0, = 0x020E0068
    ldr r1, = 0x5
    str r1, [r0]

    /*配置IO口电气属性 */
    ldr r0, = 0x020E02F4
    ldr r1, = 0x10B0
    str r1, [r0]

    /*设置GPIO */
    ldr r0, = 0x0209C004
    ldr r1, = 0x8
    str r1, [r0]

    /*将LED对应IO口置0——点亮 */
    ldr r0, = 0x0209C000
    ldr r1, = 0x0
    str r1, [r0]

loop:
    b loop



