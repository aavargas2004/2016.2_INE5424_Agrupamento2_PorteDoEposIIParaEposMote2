// EPOS Timer Mediator Common Package

#ifndef __timer_h
#define __timer_h

#include <tsc.h>
#include <rtc.h>
#include <ic.h>

__BEGIN_SYS

class Timer_Common
{
public:
    typedef TSC::Hertz Hertz;
    typedef int Tick;
//    typedef RTC::Microsecond Microsecond;
    typedef IC::Interrupt_Handler Handler;

//matching function for call to 'EPOS::S::Timer_3::Timer_3(const unsigned int&, void (&)())'
//  typedef TSC::Hertz Tick; //epos1
//    typedef void (Handler)();

protected:
    Timer_Common() {}
};

__END_SYS

#ifdef __TIMER_H
#include __TIMER_H
#endif

#endif
