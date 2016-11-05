#ifndef __mc13224v_traits_h

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.
#define __mc13224v_traits_h

#include <system/config.h>
#include <system/types.h>

// Mediators - Machine - Machine

__BEGIN_SYS

class Machine_Common;

template <> struct Traits<Machine_Common>: public Traits<void>
{
};

template <> struct Traits<Machine>: public Traits<Machine_Common>
{
	static const unsigned int MAX_CPUS = 1;
	static const unsigned int CPUS = 1;

	static const unsigned int CLOCK = 24000000;

	static const unsigned int STACK_SIZE = 1024;
	static const unsigned int HEAP_SIZE = 3072;
	static const unsigned int APPLICATION_STACK_SIZE = 1024;
	static const unsigned int APPLICATION_HEAP_SIZE = 3072;

	static const unsigned int SYSTEM_HEAP_SIZE = 2*HEAP_SIZE;
	static const bool SMP = false;
	static const unsigned int MAX_THREADS = 7;
	

	static const unsigned int PRIORITY_HEAP_BASE_ADDR = 0;
	static const unsigned int PRIORITY_HEAP_SIZE = 4;
	static const unsigned int PRIORITY_HEAP_TOP_ADDR = PRIORITY_HEAP_BASE_ADDR + PRIORITY_HEAP_SIZE - 1;

	static const bool flash_erase_checking = true;
};

template <> struct Traits<Battery>: public Traits<Machine_Common>
{
    static const bool enabled = true;
    static const bool buck_enabled = false;
    static const unsigned int buck_voltage_threshold = 2500; // in mV
    static const unsigned int frequency = 1; // in Hz
};

template <> struct Traits<Timer_0>: public Traits<Machine_Common>
{
    static const int FREQUENCY = 10; // default system timer, in Hz
};

template <> struct Traits<Timer_1>: public Traits<Machine_Common>
{
	static const int FREQUENCY = 10;
};

template <> struct Traits<Timer_2>: public Traits<Machine_Common>
{
	static const int FREQUENCY = 10;
};

template <> struct Traits<Timer_3>: public Traits<Machine_Common>
{
	static const int FREQUENCY = 10;
};

template <> struct Traits<RTC>: public Traits<Machine_Common>
{
	static const unsigned int EPOCH_DAYS = 1;
};

template <> struct Traits<Display>: public Traits<Machine_Common>
{
	static const bool on_serial = true;
};

template <> struct Traits<NIC>: public Traits<void>
{
    // static const bool enabled = true;
  static const bool enabled = false;
  static const bool promiscuous = false;

    typedef LIST<> NICS;
    static const unsigned int UNITS = NICS::Length;


    // typedef LIST<Radio> NICS;

    // static const unsigned int UNITS = NICS::Count<Radio>::Result;
};

template <> struct Traits<ADC>: public Traits<void>
{
    enum Power_Modes
    {
        FULL        = 0,
        LIGHT       = 1,
        STANDBY     = 2,
        OFF         = 3
    };
};

template <> struct Traits<Temperature_Sensor>: public Traits<void>
{
    typedef LIST<ERTJ1VG103FA> SENSORS;

    enum {
        KELVIN = 0,
        CELCIUS
    };
    static const int UNITS = CELCIUS;
};

__END_SYS

#endif

