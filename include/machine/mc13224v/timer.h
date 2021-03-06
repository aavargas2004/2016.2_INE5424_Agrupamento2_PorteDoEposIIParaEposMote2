// EPOS-- MC13224V Timer Mediator Declarations

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#ifndef __mc13224v_timer_h
#define __mc13224v_timer_h

#include <timer.h>
#include <ic.h>
#include <rtc.h>
#include <system/memory_map.h>

__BEGIN_SYS


class Timer: public Timer_Common
{
protected:
    static const unsigned int CLOCK = Traits<Machine>::CLOCK;
	unsigned int instance, offset;
	static Handler* handlers[4];
	
	
	typedef RTC::Microsecond Microsecond;
	typedef IO_Map<Machine> IO;
	typedef CPU::Reg16 Reg16;
	
	// Internal clock divisors
	enum {
		D64		= 0xE,
		D128	= 0xF
	};

	enum INSTANCE {
		TIMER0 = 0,
		TIMER1 = 1,
		TIMER2 = 2,
		TIMER3 = 3
	};

public:
    typedef unsigned short Count;

    Timer(Handler* handler, const INSTANCE instance){
		// 100ms as a default period
		Timer(10, handler, instance);
    }

    Timer(const Hertz& f, Handler* handler, const INSTANCE instance):
		instance(instance), offset(instance * 0x20) {

		ctrl(0x20); // untill CNTR reach COMP1
		sctrl(0x0); // reset SCTRL
		load(0x0); // reset LOAD

		frequency(f);

		csctrl(0x41);

		ctrl( (D128<<9) | ctrl() );
		cntr(0x0);
		ctrl( (0x1<<13) | ctrl() );

		handlers[instance] = handler;
		IC::int_vector(IC::IRQ_TIMER, handler_wrapper);
		enable();
    }

    Timer(const Hertz & f) {
    	db<Timer>(TRC) << "Timer(f=" << f << ")\n";
    	frequency(f);
    }

    Hertz frequency() const { 
		return CLOCK / (128 * comp1());
	}
    
    void frequency(const Hertz & f) {
		comp1(freq2count(f));
		cmpld1(freq2count(f));
    };

    void reset() {
		// and the TCF bit??
		cntr(0x0);
	}
    
    static void init(){
		IC::enable(IC::IRQ_TIMER);
	}

    void enable(){
		IC::enable(IC::IRQ_TIMER);
		enbl(enbl() | 0x1<<instance);
	}

    void disable(){
		IC::disable(IC::IRQ_TIMER);
		enbl(enbl() & ~(0x1<<instance));
	}

    Tick read() { 
		return cntr();
	}

protected:

	static void handler_wrapper();

    static Hertz count2freq(const Count & c) { 
		// Using 128 as divisor in TIMERN_CTRL
		return (CLOCK/128.0) / (double) c; 
	}
    
	static Count freq2count(const Hertz & f) {
		return (CLOCK/128.0) / (double) f; 
	}

	void ctrl(Reg16 value){ CPU::out16(IO::TIMER0_CTRL + offset, value); }
	Reg16 ctrl() const { return CPU::in16(IO::TIMER0_CTRL + offset); }

	void sctrl(Reg16 value){ CPU::out16(IO::TIMER0_SCTRL + offset, value); }
	Reg16 sctrl() const { return CPU::in16(IO::TIMER0_SCTRL + offset); }

	void comp1(Reg16 value){ CPU::out16(IO::TIMER0_COMP1 + offset, value); }
	Reg16 comp1() const { return CPU::in16(IO::TIMER0_COMP1 + offset); }

	void comp2(Reg16 value){ CPU::out16(IO::TIMER0_COMP2 + offset, value); }
	Reg16 comp2() const { return CPU::in16(IO::TIMER0_COMP2 + offset); }

	void capt(Reg16 value){ CPU::out16(IO::TIMER0_CAPT + offset, value); }
	Reg16 capt() const { return CPU::in16(IO::TIMER0_CAPT + offset); }

	void load(Reg16 value){ CPU::out16(IO::TIMER0_LOAD + offset, value); }
	Reg16 load() const { return CPU::in16(IO::TIMER0_LOAD + offset); }

	void hold(Reg16 value){ CPU::out16(IO::TIMER0_HOLD + offset, value); }
	Reg16 hold() const { return CPU::in16(IO::TIMER0_HOLD + offset); }

	void cntr(Reg16 value){ CPU::out16(IO::TIMER0_CNTR + offset, value); }
	Reg16 cntr() const { return CPU::in16(IO::TIMER0_CNTR + offset); }

	void cmpld1(Reg16 value){ CPU::out16(IO::TIMER0_CMPLD1 + offset, value); }
	Reg16 cmpld1() const { return CPU::in16(IO::TIMER0_CMPLD1 + offset); }

	void cmpld2(Reg16 value){ CPU::out16(IO::TIMER0_CMPLD2 + offset, value); }
	Reg16 cmpld2() const { return CPU::in16(IO::TIMER0_CMPLD2 + offset); }

	void csctrl(Reg16 value){ CPU::out16(IO::TIMER0_CSCTRL + offset, value); }
	Reg16 csctrl() const { return CPU::in16(IO::TIMER0_CSCTRL + offset); }

	void enbl(Reg16 value){ CPU::out16(IO::TIMER0_ENBL, value); }
	Reg16 enbl() const { return CPU::in16(IO::TIMER0_ENBL); }

};

class Timer_0: public Timer{
public:
	static const unsigned int FREQUENCY = Traits<Timer_0>::FREQUENCY;
	Timer_0(Handler *handler): 
		Timer(FREQUENCY, handler, TIMER0){}
	Timer_0(const Microsecond& quantum, Handler *handler):
		Timer(1000000/quantum, handler, TIMER0){}
};

class Timer_1: public Timer{
public:
	static const unsigned int FREQUENCY = Traits<Timer_1>::FREQUENCY;
	Timer_1(Handler *handler): 
		Timer(FREQUENCY, handler, TIMER1){}
	Timer_1(const Microsecond& quantum, Handler *handler):
		Timer(1000000/quantum, handler, TIMER1){}
};

class Timer_2: public Timer{
public:
	static const unsigned int FREQUENCY = Traits<Timer_2>::FREQUENCY;
	Timer_2(Handler *handler): 
		Timer(FREQUENCY, handler, TIMER2){}
	Timer_2(const Microsecond& quantum, Handler *handler):
		Timer(1000000/quantum, handler, TIMER2){}
};

//Obs: Timer_3 is being used by the TSC
//TODO: Timer_3 source should be the 32kHz crystal, so TSC would have a good resolution
class Timer_3: public Timer{
public:
	static const unsigned int FREQUENCY = Traits<Timer_3>::FREQUENCY;
	Timer_3(Handler *handler): 
		Timer(FREQUENCY, handler, TIMER3){}
	Timer_3(const Microsecond& quantum, Handler *handler):
		Timer(1000000/quantum, handler, TIMER3){}
};


__END_SYS

#endif

