#include "fpu.h"

//enables the floating point unit
void Fpu_enable(void)
{
    //enable CP10 and CP11 full access
    SCB->CPACR |= (1U << 20);
    SCB->CPACR |= (1U << 21);
    SCB->CPACR |= (1U << 22);
    SCB->CPACR |= (1U << 23);
}