// EPOS-- Machine Buck Regulator Mediator Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <machine/mc13224v/battery.h>
#include <machine/mc13224v/buck_regulator.h>
#include <machine/mc13224v/adc.h>

__BEGIN_SYS

Battery * Battery::system_battery;

__END_SYS

__USING_SYS

Battery::Battery()
 : _adc()
{
    db<Battery>(TRC) << "Battery::Battery()\n";
}

const unsigned short Battery::get()
{
    db<Battery>(TRC) << "Battery::get()\n";

    return _adc.get();
}

const unsigned short Battery::sample()
{
    db<Battery>(TRC) << "Battery::sample()\n";

    return read_to_voltage(get());
}

const unsigned short Battery::charge()
{
    db<Battery>(TRC) << "Battery::charge()\n";

    return read_to_charge(get());
}

Battery & Battery::sys_batt()
{
    db<Battery>(TRC) << "Battery::sys_batt()\n";

    return *system_battery;
}
const unsigned short Battery::read_to_voltage(unsigned short value)
{
    db<Battery>(TRC) << "Battery::read_to_voltage(" << value << ")\n";

    if(value <= 0u) return 0;

    return (battery_reference * adc_max) / value;
}

const unsigned short Battery::read_to_charge(unsigned short value)
{
    db<Battery>(TRC) << "Battery::read_to_charge(" << value << ")\n";

    //"Dummy" linear model
    return 100 - (100 * (value - ADC_3p3v) / (ADC_1p8v - ADC_3p3v));
}

void Battery::check_buck()
{
    db<Battery>(TRC) << "Battery::check_buck()\n";

    check_buck(get());
}

/* A future implementation should use ADCs threshold feature to avoid pooling of the battery voltage */
void Battery::check_buck(unsigned short read)
{
    db<Battery>(TRC) << "Battery::check_buck(" << read << ")\n";

    if((read > buck_disable_adc_threshold) && (!Buck_Regulator::is_in_bypass()))
    {
        Buck_Regulator::enter_bypass();
    }
    else if((read < buck_enable_adc_threshold) && (Buck_Regulator::is_in_bypass()))
    {
        Buck_Regulator::leave_bypass();
    }
}

const void Battery::battery_over_threshold_set(unsigned short value)
{
    db<Battery>(TRC) << "Battery::battery_over_threshold_set(" << value << ")\n";

    // TODO: set 0x0200 in ?
}

const void Battery::battery_over_threshold_enable()
{
    db<Battery>(TRC) << "Battery::battery_over_threshold_enable()\n";

    // TODO: set 0x0200 in ?
}

const void Battery::battery_over_threshold_disable()
{
    db<Battery>(TRC) << "Battery::battery_over_threshold_disable()\n";

    // TODO: clear 0x0200 in ?
}

const void Battery::battery_under_threshold_set(unsigned short value)
{
    db<Battery>(TRC) << "Battery::battery_under_threshold_set(" << value << ")\n";

    // TODO: clear 0x0200 in ?
}

const void Battery::battery_under_threshold_enable()
{
    db<Battery>(TRC) << "Battery::battery_under_threshold_enable()\n";

    // TODO: set 0x0100 in ?
}

const void Battery::battery_under_threshold_disable()
{
    db<Battery>(TRC) << "Battery::battery_under_threshold_disable()\n";

    // TODO: clear 0x0100 in ?
}
