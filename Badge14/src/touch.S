#include <xc.h>

   /* define which section (for example "text")
     * does this portion of code resides in. Typically,
     * all your code will reside in .text section as
     * shown below.
    */
   .text

   /* This is important for an assembly programmer. This
     * directive tells the assembler that don't optimize
     * the order of the instructions as well as don't insert
     * 'nop' instructions after jumps and branches.
    */
   .set noreorder

#ifdef QUICKREF
  .extern ANSELA           /* 0xBF886000 */
  .extern ANSELACLR        /* 0xBF886004 */
  .extern ANSELASET        /* 0xBF886008 */
  .extern ANSELAINV        /* 0xBF88600C */
  .extern TRISA            /* 0xBF886010 */
  .extern TRISACLR         /* 0xBF886014 */
  .extern TRISASET         /* 0xBF886018 */
  .extern TRISAINV         /* 0xBF88601C */
  .extern PORTA            /* 0xBF886020 */
  .extern PORTACLR         /* 0xBF886024 */
  .extern PORTASET         /* 0xBF886028 */
  .extern PORTAINV         /* 0xBF88602C */
  .extern LATA             /* 0xBF886030 */
  .extern LATACLR          /* 0xBF886034 */
  .extern LATASET          /* 0xBF886038 */
  .extern LATAINV          /* 0xBF88603C */
  .extern ODCA             /* 0xBF886040 */
  .extern ODCACLR          /* 0xBF886044 */
  .extern ODCASET          /* 0xBF886048 */
  .extern ODCAINV          /* 0xBF88604C */
  .extern CNPUA            /* 0xBF886050 */
  .extern CNPUACLR         /* 0xBF886054 */
  .extern CNPUASET         /* 0xBF886058 */
  .extern CNPUAINV         /* 0xBF88605C */
  .extern CNPDA            /* 0xBF886060 */
  .extern CNPDACLR         /* 0xBF886064 */
  .extern CNPDASET         /* 0xBF886068 */
  .extern CNPDAINV         /* 0xBF88606C */
  .extern CNCONA           /* 0xBF886070 */
  .extern CNCONACLR        /* 0xBF886074 */
  .extern CNCONASET        /* 0xBF886078 */
  .extern CNCONAINV        /* 0xBF88607C */
  .extern CNENA            /* 0xBF886080 */
  .extern CNENACLR         /* 0xBF886084 */
  .extern CNENASET         /* 0xBF886088 */
  .extern CNENAINV         /* 0xBF88608C */
  .extern CNSTATA          /* 0xBF886090 */
  .extern CNSTATACLR       /* 0xBF886094 */
  .extern CNSTATASET       /* 0xBF886098 */
  .extern CNSTATAINV       /* 0xBF88609C */
# /opt/microchip/xc32/v1.20/pic32mx/include/proc/p32mx250f128d.h
#endif

/*
   Upper left touch sensor
*/
.global getTouchUL
.ent getTouchUL
getTouchUL:
   /* function prologue - save registers used in this function 
     * on stack and adjust stack-pointer
     */
   addiu   sp, sp, -40
   sw      s0,  0(sp)
   sw      s1,  4(sp)
   sw      s2,  8(sp)
   sw      s3, 12(sp)
   sw      s4, 16(sp)
   sw      s5, 20(sp)
   sw      s6, 24(sp)
   sw      s7, 28(sp)
   sw      t0, 32(sp)
   sw      t1, 36(sp)


#define TOUCH_UL (1 << 5)

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   /* config as output */
   la      t0, TRISCCLR
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   /* clear latch bit */
   la      t0, LATCCLR
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   /* config as input */
   la      t0, TRISCSET
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   /* pull up on */
   la      t0, CNPUCSET
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   la      a0, PORTC

   lw      s0, 0(a0)
   lw      s1, 0(a0)
   lw      s2, 0(a0)
   lw      s3, 0(a0)
   lw      s4, 0(a0)
   lw      s5, 0(a0)
   lw      s6, 0(a0)
   lw      s7, 0(a0)

   srl     s0, s0, 5
   srl     s1, s1, 5
   srl     s2, s2, 5
   srl     s3, s3, 5
   srl     s4, s4, 5
   srl     s5, s5, 5
   srl     s6, s6, 5
   srl     s7, s7, 5

   andi    s0, s0, 1
   andi    s1, s1, 1
   andi    s2, s2, 1
   andi    s3, s3, 1
   andi    s4, s4, 1
   andi    s5, s5, 1
   andi    s6, s6, 1
   andi    s7, s7, 1

   add     s0, s1, s0
   add     s0, s2, s0
   add     s0, s3, s0
   add     s0, s4, s0
   add     s0, s5, s0
   add     s0, s6, s0
   add     s0, s7, s0

   la      t0, G_lower_slider_left
   sb      s0, 0(t0)

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_UL
   sw      t1, 0(t0)

   /* function epilogue - restore registers used in this function
     * from stack and adjust stack-pointer
     */
   lw      s0,  0(sp)
   lw      s1,  4(sp)
   lw      s2,  8(sp)
   lw      s3, 12(sp)
   lw      s4, 16(sp)
   lw      s5, 20(sp)
   lw      s6, 24(sp)
   lw      s7, 28(sp)
   lw      t0, 32(sp)
   lw      t1, 36(sp)
   addiu   sp, sp, 40

   /* return to caller */
   jr      ra
   nop
.end getTouchUL


/*
   Upper Right touch sensor
*/
.global getTouchUR
.ent getTouchUR
getTouchUR:
   /* function prologue - save registers used in this function 
     * on stack and adjust stack-pointer
     */
   addiu   sp, sp, -40
   sw      s0,  0(sp)
   sw      s1,  4(sp)
   sw      s2,  8(sp)
   sw      s3, 12(sp)
   sw      s4, 16(sp)
   sw      s5, 20(sp)
   sw      s6, 24(sp)
   sw      s7, 28(sp)
   sw      t0, 32(sp)
   sw      t1, 36(sp)

#define TOUCH_UR (1 << 4)

   la      a0, PORTC

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   /* config as output */
   la      t0, TRISCCLR
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   /* clear latch bit */
   la      t0, LATCCLR
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   /* config as input */
   la      t0, TRISCSET
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   /* pull up on */
   la      t0, CNPUCSET
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   lw      s0, 0(a0)
   lw      s1, 0(a0)
   lw      s2, 0(a0)
   lw      s3, 0(a0)
   lw      s4, 0(a0)
   lw      s5, 0(a0)
   lw      s6, 0(a0)
   lw      s7, 0(a0)

   srl     s0, s0, 4
   srl     s1, s1, 4
   srl     s2, s2, 4
   srl     s3, s3, 4
   srl     s4, s4, 4
   srl     s5, s5, 4
   srl     s6, s6, 4
   srl     s7, s7, 4

   andi    s0, s0, 1
   andi    s1, s1, 1
   andi    s2, s2, 1
   andi    s3, s3, 1
   andi    s4, s4, 1
   andi    s5, s5, 1
   andi    s6, s6, 1
   andi    s7, s7, 1

   add     s0, s1, s0
   add     s0, s2, s0
   add     s0, s3, s0
   add     s0, s4, s0
   add     s0, s5, s0
   add     s0, s6, s0
   add     s0, s7, s0

   la      t0, G_lower_slider_right
   sb      s0, 0(t0)

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_UR
   sw      t1, 0(t0)

   /* function epilogue - restore registers used in this function
     * from stack and adjust stack-pointer
     */
   lw      s0,  0(sp)
   lw      s1,  4(sp)
   lw      s2,  8(sp)
   lw      s3, 12(sp)
   lw      s4, 16(sp)
   lw      s5, 20(sp)
   lw      s6, 24(sp)
   lw      s7, 28(sp)
   lw      t0, 32(sp)
   lw      t1, 36(sp)
   addiu   sp, sp, 40

   /* return to caller */
   jr      ra
   nop
.end getTouchUR



/*
   Right Upper sensor (Port C3)
*/
.global getTouchRU
.ent getTouchRU
getTouchRU:
   /* function prologue - save registers used in this function 
     * on stack and adjust stack-pointer
     */
   addiu   sp, sp, -40
   sw      s0,  0(sp)
   sw      s1,  4(sp)
   sw      s2,  8(sp)
   sw      s3, 12(sp)
   sw      s4, 16(sp)
   sw      s5, 20(sp)
   sw      s6, 24(sp)
   sw      s7, 28(sp)
   sw      t0, 32(sp)
   sw      t1, 36(sp)

//3rd bit in portC
#define TOUCH_RU (1 << 3)

   la      a0, PORTC

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   /* config as output */
   la      t0, TRISCCLR
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   /* clear latch bit */
   la      t0, LATCCLR
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   /* config as input */
   la      t0, TRISCSET
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   /* pull up on */
   la      t0, CNPUCSET
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   //read portc
   lw      s0, 0(a0)
   lw      s1, 0(a0)
   lw      s2, 0(a0)
   lw      s3, 0(a0)
   lw      s4, 0(a0)
   lw      s5, 0(a0)
   lw      s6, 0(a0)
   lw      s7, 0(a0)

   //shift down to get the bit we need 
   srl     s0, s0, 3
   srl     s1, s1, 3
   srl     s2, s2, 3
   srl     s3, s3, 3
   srl     s4, s4, 3
   srl     s5, s5, 3
   srl     s6, s6, 3
   srl     s7, s7, 3

   //store if lowest bit is on per sample
   andi    s0, s0, 1
   andi    s1, s1, 1
   andi    s2, s2, 1
   andi    s3, s3, 1
   andi    s4, s4, 1
   andi    s5, s5, 1
   andi    s6, s6, 1
   andi    s7, s7, 1

   //add up the samples
   add     s0, s1, s0
   add     s0, s2, s0
   add     s0, s3, s0
   add     s0, s4, s0
   add     s0, s5, s0
   add     s0, s6, s0
   add     s0, s7, s0

   //store in variable
   la      t0, G_side_slider_right
   sb      s0, 0(t0)

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_RU
   sw      t1, 0(t0)

   /* function epilogue - restore registers used in this function
     * from stack and adjust stack-pointer
     */
   lw      s0,  0(sp)
   lw      s1,  4(sp)
   lw      s2,  8(sp)
   lw      s3, 12(sp)
   lw      s4, 16(sp)
   lw      s5, 20(sp)
   lw      s6, 24(sp)
   lw      s7, 28(sp)
   lw      t0, 32(sp)
   lw      t1, 36(sp)
   addiu   sp, sp, 40

   /* return to caller */
   jr      ra
   nop
.end getTouchRU


/*
   Left Upper sensor (Port C2)
*/
.global getTouchRL
.ent getTouchRL
getTouchRL:
   /* function prologue - save registers used in this function
     * on stack and adjust stack-pointer
     */
   addiu   sp, sp, -40
   sw      s0,  0(sp)
   sw      s1,  4(sp)
   sw      s2,  8(sp)
   sw      s3, 12(sp)
   sw      s4, 16(sp)
   sw      s5, 20(sp)
   sw      s6, 24(sp)
   sw      s7, 28(sp)
   sw      t0, 32(sp)
   sw      t1, 36(sp)

//3rd bit in portC
#define TOUCH_RL (1 << 2)

   la      a0, PORTC

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   /* config as output */
   la      t0, TRISCCLR
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   /* clear latch bit */
   la      t0, LATCCLR
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   /* config as input */
   la      t0, TRISCSET
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   /* pull up on */
   la      t0, CNPUCSET
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   //read portc
   lw      s0, 0(a0)
   lw      s1, 0(a0)
   lw      s2, 0(a0)
   lw      s3, 0(a0)
   lw      s4, 0(a0)
   lw      s5, 0(a0)
   lw      s6, 0(a0)
   lw      s7, 0(a0)

   //shift down to get the bit we need
   srl     s0, s0, 2
   srl     s1, s1, 2
   srl     s2, s2, 2
   srl     s3, s3, 2
   srl     s4, s4, 2
   srl     s5, s5, 2
   srl     s6, s6, 2
   srl     s7, s7, 2

   //store if lowest bit is on per sample
   andi    s0, s0, 1
   andi    s1, s1, 1
   andi    s2, s2, 1
   andi    s3, s3, 1
   andi    s4, s4, 1
   andi    s5, s5, 1
   andi    s6, s6, 1
   andi    s7, s7, 1

   //add up the samples
   add     s0, s1, s0
   add     s0, s2, s0
   add     s0, s3, s0
   add     s0, s4, s0
   add     s0, s5, s0
   add     s0, s6, s0
   add     s0, s7, s0

   //store in variable
   la      t0, G_side_slider_left
   sb      s0, 0(t0)

   /* pull up off */
   la      t0, CNPUCCLR
   ori     t1, zero, TOUCH_RL
   sw      t1, 0(t0)

   /* function epilogue - restore registers used in this function
     * from stack and adjust stack-pointer
     */
   lw      s0,  0(sp)
   lw      s1,  4(sp)
   lw      s2,  8(sp)
   lw      s3, 12(sp)
   lw      s4, 16(sp)
   lw      s5, 20(sp)
   lw      s6, 24(sp)
   lw      s7, 28(sp)
   lw      t0, 32(sp)
   lw      t1, 36(sp)
   addiu   sp, sp, 40

   /* return to caller */
   jr      ra
   nop
.end getTouchRL