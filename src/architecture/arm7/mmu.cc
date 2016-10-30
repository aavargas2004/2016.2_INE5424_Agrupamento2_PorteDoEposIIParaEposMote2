// EPOS-- ARM7 MMU Mediator Implementation

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <mmu.h>
#include <machine.h>
#include <system/traits.h>

__BEGIN_SYS

// Class attributes
MMU::List MMU::_free;

MMU::Phy_Addr MMU::alloc(unsigned int bytes) {
    Phy_Addr phy(false);
    if(bytes) {
        List::Element * e = _free.search_decrementing(bytes);
        if(e)
			//phy = e->object() + e->size();
            phy = (unsigned int)e->object() + (unsigned int)e->size();
        else
            db<MMU>(WRN) << "MMU::alloc() failed!\n";
    }
    db<MMU>(TRC) << "MMU::alloc(bytes=" << bytes << ") => "
                      << (void *)phy << "\n";
    return phy;
}

void MMU::free(Phy_Addr addr, int n) {
    db<MMU>(TRC) << "MMU::free(addr=" << (void *)addr
                      << ",n=" << n << ")\n";

	if(addr % 4 != 0){
		db<MMU>(ERR) << "Unaligned address to be freed!\n";
		Machine::panic();
	}

    if(addr && n) {
       	List::Element * e = new (addr) List::Element(addr, n);
        List::Element * m1, * m2;
        _free.insert_merging(e, &m1, &m2);
    }
}
__END_SYS
