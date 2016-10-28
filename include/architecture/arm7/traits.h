#ifndef __arm7_traits_h

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.
#define __arm7_traits_h

// Mediators - Architecture - ARM7
__BEGIN_SYS



template <> struct Traits<CPU>: public Traits<void>
{
    enum {LITTLE, BIG};
    static const unsigned int ENDIANESS         = LITTLE;
    static const unsigned int WORD_SIZE         = 32;
//    static const unsigned int CLOCK             = Traits<Build>::MODEL == Traits<Build>::LM3S811 ? 50000000 : Traits<Build>::MODEL == Traits<Build>::Zynq ? 666666687 : 32000000;
    static const bool unaligned_memory_access   = false;

};

template <> struct Traits<TSC>: public Traits<void>
{
};

//'COLORS' now is a member of 'EPOS::S::Traits<EPOS::S::MMU>'
template <> struct Traits<MMU>: public Traits<void>
{
    static const bool colorful = false;
    static const unsigned int COLORS = 1;
};

__END_SYS

#endif
