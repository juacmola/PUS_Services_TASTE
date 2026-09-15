#ifndef REQUEST_SIZE_H
#define REQUEST_SIZE_H

#include <stdint.h>

#include "dataview-uniq.h"

// struct used to calculate buffer size for drivers
struct GenericLinuxAllParametersStub
{
    union
    {
        // input ports

        // output ports

        uint8_t dummy_union_field[1];
    } all_types;
};

// GENERIC_PARTITION_BUFFER_SIZE should be even number
#define GENERIC_PARTITION_BUFFER_SIZE (((sizeof(struct GenericLinuxAllParametersStub) + 1) / 2) * 2)


#define BKGTCEXEC_SBKGTC_REQUEST_SIZE (sizeof (asn1SccRawTC))

#define HKFDIRMNG_SHKFDIRTC_REQUEST_SIZE (sizeof (asn1SccRawTC))

#define HKFDIRMNG_TRIGGER_REQUEST_SIZE (1)

#define TCMANAGER_POLL_REQUEST_SIZE (1)

#define TCMANAGER_SEVACTION_REQUEST_SIZE (1)


#endif
