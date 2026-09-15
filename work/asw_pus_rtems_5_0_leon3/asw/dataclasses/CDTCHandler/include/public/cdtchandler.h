#ifndef FCDTCHandlerH
#define FCDTCHandlerH

#include "../../../../../llsw/config/include/public/config.h"
#include "../../../../../llsw/config/include/public/basic_types.h"
//#include "../../../../../llsw/rtems_osswr/include/public/basic_types.h"
#include "../../../../../service_libraries/ccsds_pus/include/public/ccsds_pus.h"
#include "../../../../../llsw/tmtc_dyn_mem/include/public/tmtc_dyn_mem.h"
#include "../../../../../service_libraries/pus_services/pus_tc_handler/include/public/pus_tc_handler.h"

#include "../../../CDTCMemDescriptor/include/public/cdtcmemdescriptor_iface_v1.h"
#include "../../../CDTCAcceptReport/include/public/cdtcacceptreport_iface_v1.h"
#include "../../../CDTCExecCtrl/include/public/cdtcexecctrl_iface_v1.h"

class CDTCHandler {

	friend class CDEvAction;


protected:

	tc_handler_t mTCHandler;

public:

	//!Constructor
	CDTCHandler();

	//!Build From Descriptor
	void BuildFromDescriptor(CDTCMemDescriptor &descriptor);

	//!Do TC Acceptation
	CDTCAcceptReport DoAcceptation();

	//!Mng TC Rejection
	void MngTCRejection(CDTCAcceptReport & acceptReport);

	//!Mng TC Accetation
	void MngTCAcceptation();

	//!Set Execution Control 
	CDTCExecCtrl GetExecCtrl();

	//!Exec the prio telecommands
	void ExecPrioTC();

	//!Exec the reboot telecommands
	void ExecRebootTC();

	//!Exec the reboot telecommands
	void ExecHK_FDIRTC();

	//!Exec the reboot telecommands
	void ExecBKGTC();


};

#endif
