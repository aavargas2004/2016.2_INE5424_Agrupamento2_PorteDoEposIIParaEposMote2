// EPOS PLASMA NULL NIC Mediator Declarations

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#ifndef __mc13224v_nic_h
#define __mc13224v_nic_h

#include <system.h>
#include <nic.h>
#include <ethernet.h>
#include "machine.h"
#include <utility/malloc.h>

__BEGIN_SYS

class NIC: public Ethernet
{
    friend class Machine;

private:
    typedef Traits<NIC>::NICS NICS;
    typedef IF<NICS::Polymorphic, NIC_Base<Ethernet>, NICS::Get<0>::Result>::Result Device;
    static const unsigned int UNITS = NICS::Length;
  
public:
    typedef Data_Observer<Buffer, Protocol> Observer;
    typedef Data_Observed<Buffer, Protocol> Observed;

public:
    template<unsigned int UNIT = 0>
    NIC(unsigned int u = UNIT) { 
        // _dev = reinterpret_cast<Device *>(NICS::Get<UNIT>::Result::get(u));
     }

    ~NIC() {
        _dev = 0;
    }

    int send(const Address & dst, const Protocol & prot, 
	     const void * data, unsigned int size) {
        return 0;
    }

    // Adress<UNITS> ==> UNITS is not what was supposed to be
    int receive(Address * src, Protocol * prot,
		void * data, unsigned int size) {
        return 0;
    }

    void reset() {}
    
    void attach(Observer * obs, const Protocol & prot) {}
    void detach(Observer * obs, const Protocol & prot) {}

    unsigned int mtu() const { return (unsigned int)0; }

    const Address & address() {
        return _Addr;
    }

    const Statistics & statistics() {
	return _Stat;
    }
    void address(const Address & address) { _Addr = address; }

    int send(Buffer * buf) { return 0; }
    void free(Buffer * buf) { }


    // Buffer * alloc(const Address & dst, const Protocol & prot, unsigned int once, unsigned int always, unsigned int payload) { return 0; }
    Buffer * alloc(const Address & dst, const Protocol & prot, unsigned int once, unsigned int always, unsigned int payload) { 
    // return new (SYSTEM) Buffer(this, once + always + payload, once + always + payload); // the last parameter is passed to Phy_Frame as the length
        return 0;
    // return new (SYSTEM) Buffer(this, once + always + payload, once + always + payload); // the last parameter is passed to Phy_Frame as the length

        // Buffer * b;
        // return b;
        // return _dev->alloc(this, dst, prot, once, always, payload); 

    }

    static void init();

private:
    Address _Addr;
    Statistics _Stat;
    Device * _dev;

};

__END_SYS

#endif

