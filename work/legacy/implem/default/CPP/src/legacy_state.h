#pragma once

#include "dataview-uniq.h"
#include "../../../../../asw_pus_rtems_5_0_leon3/asw/dataclasses/CDTCHandler/include/public/cdtchandler_iface_v1.h"

// Owns a pool buffer locally. Only RawTC byte values cross TASTE interfaces.
class LegacyTCHandler : public CDTCHandler {
public:
    LegacyTCHandler() = default;
    LegacyTCHandler(const LegacyTCHandler &) = delete;
    LegacyTCHandler &operator=(const LegacyTCHandler &) = delete;
    ~LegacyTCHandler();
    void Reset();
    bool Load(const asn1SccRawTC &packet);
    bool ExtractEventAction();
    void CopyPacket(asn1SccRawTC &packet) const;
};

class legacy_state {
public:
    CDTCAcceptReport VAcceptReport;
    LegacyTCHandler VCurrentTC;
    CDTCExecCtrl VTCExecCtrl;
    bool has_accepted_tc = false;
    uint16_t sequence_count = 0;
};
