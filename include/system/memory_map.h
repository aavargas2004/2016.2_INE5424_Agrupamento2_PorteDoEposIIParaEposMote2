// EPOS Memory Map

#ifndef __memory_map_h
#define __memory_map_h

#include <system/config.h>

__BEGIN_SYS

//fazendo template de memory map que é especializado no memory map da machine mc13224v
template <class Machine>
struct Memory_Map {};

__END_SYS

#include __HEADER_MACH(memory_map)

#endif
