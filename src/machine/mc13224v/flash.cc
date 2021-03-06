// EPOS-- Machine Flash Mediator Declarations

// This work is licensed under the EPOS Software License v1.0.
// A copy of this license is available at the EPOS system source tree root.
// A copy of this license is also available online at:
// http://epos.lisha.ufsc.br/EPOS+Software+License+v1.0
// Note that EPOS Software License applies to both source code and executables.

#include <machine.h>
#include <machine/mc13224v/flash.h>

__BEGIN_SYS

Flash::nvm_detect_func Flash::nvm_detect = reinterpret_cast<nvm_detect_func>(reinterpret_cast<void *>(NVM_DETECT_ADDR));

Flash::nvm_read_func Flash::nvm_read = reinterpret_cast<nvm_read_func>(reinterpret_cast<void *>(NVM_READ_ADDR));

Flash::nvm_setsvar_func Flash::nvm_setsvar = reinterpret_cast<nvm_setsvar_func>(reinterpret_cast<void *>(NVM_SETSVAR_ADDR));

Flash::nvm_erase_func Flash::nvm_erase = reinterpret_cast<nvm_erase_func>(reinterpret_cast<void *>(NVM_ERASE_ADDR));

Flash::crm_set_spif_voltage_level_func Flash::CRM_SetSPIFVoltageLevel = reinterpret_cast<crm_set_spif_voltage_level_func>(reinterpret_cast<void *>(CRM_SET_SPIF_VOLTAGE_LEVEL_ADDR));

__END_SYS

