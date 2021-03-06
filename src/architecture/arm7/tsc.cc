// EPOS-- ARM7_TSC Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <architecture/arm7/tsc.h>
#include <machine/mc13224v/config.h>
//TODO: how to avoid breaking the Arch <=> Mach isolation?
#include <timer.h>


__BEGIN_SYS

volatile unsigned long TSC::_ts = 0;


TSC::Time_Stamp TSC::time_stamp() {
    static TSC_Timer _timer(RESOLUTION, tsc_timer_handler);
    return _timer.read() | _ts << (sizeof(CPU::Reg16) * 8);
}

void TSC::tsc_timer_handler() {
    _ts++;
}

__END_SYS
