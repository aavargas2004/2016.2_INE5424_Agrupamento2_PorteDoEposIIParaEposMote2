// EPOS-- ARM7 CPU Mediator Initialization

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <cpu.h>
#include <mmu.h>
#include <tsc.h>

__BEGIN_SYS

void CPU::init()
{
    db<Init, CPU>(TRC) << "CPU::init()\n";

	MMU::init();

	return;
}

__END_SYS
