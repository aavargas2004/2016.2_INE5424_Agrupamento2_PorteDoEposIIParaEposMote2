// EPOS-- Machine Mediator Initialization

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <machine/mc13224v/battery.h>
#include <machine/mc13224v/buck_regulator.h>
#include <system/kmalloc.h>

__BEGIN_SYS

void Battery::init()
{
    db<Init, Battery>(TRC) << "Battery::init()\n";

    system_battery = new(kmalloc(sizeof(Battery))) Battery();

    if (Traits<Battery>::buck_enabled)
    {
        Buck_Regulator::enable();
        system_battery->check_buck();
    }
}

__END_SYS
