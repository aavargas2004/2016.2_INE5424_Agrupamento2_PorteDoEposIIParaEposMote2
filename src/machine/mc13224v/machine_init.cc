// EPOS-- Machine Mediator Initialization

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <machine/mc13224v/machine.h>
#include <machine/mc13224v/battery.h>

__BEGIN_SYS

void Machine::init()
{
    db<Init, Machine>(TRC) << "Machine::init()\n";

    if (Traits<Machine>::flash_erase_checking)
        check_flash_erase();

    if (Traits<Battery>::enabled)
        Battery::init();

    if (Traits<NIC>::enabled)
	NIC::init();
}

__END_SYS

