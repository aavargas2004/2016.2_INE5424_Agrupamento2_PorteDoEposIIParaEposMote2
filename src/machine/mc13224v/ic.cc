// EPOS-- Machine IC Mediator Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <machine/mc13224v/ic.h>

#include <machine.h>
#include <system/memory_map.h>

__BEGIN_SYS

IC::Interrupt_Handler IC::vector[11];

void IC::int_handler() {
    CPU::Reg16 pending = CPU::in16(IO_Map<Machine>::ITC_NIPEND);
    
    db<IC> (TRC) << "IC::int_handler(" << (int)pending << ")\n";

    if((1 << IRQ_TIMER) & pending)
    {
        db<IC> (INF) << "Interrupt! IRQ_TIMER\n";
        vector[IRQ_TIMER]();
    } else if((1 << IRQ_UART1) & pending)
    {
        db<IC> (INF) << "Interrupt! IRQ_UART1\n";
        vector[IRQ_UART1]();
    } else if((1 << IRQ_UART2) & pending)
    {
        db<IC> (INF) << "Interrupt! IRQ_UART2\n";
        vector[IRQ_UART2]();
    } else if((1 << IRQ_MACA) & pending)
    {
        db<IC> (INF) << "Interrupt! IRQ_MACA\n";
        vector[IRQ_MACA]();
    } else
    {
        db<IC> (INF) << "Unexpected Interrupt! => " << (unsigned int)pending << "\n";
//        Machine::panic();
    }
}

__END_SYS
