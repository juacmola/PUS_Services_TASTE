#ifndef __GETSET_H__
#define __GETSET_H__

#include "dataview-uniq.h"

size_t GetStreamCurrentLength(BitStream *pBitStrm);
byte *GetBitstreamBuffer(BitStream *pBitStrm);
byte GetBufferByte(byte *p, size_t off);
void SetBufferByte(byte *p, size_t off, byte b);
void ResetStream(BitStream *pStrm);
BitStream *CreateStream(size_t bufferSize);
void DestroyStream(BitStream *pBitStrm);


/* OCTETSTRING */
long RawTC__GetLength(RawTC* root);

/* OCTETSTRING */
void RawTC__SetLength(RawTC* root, long value);

/* OCTETSTRING_bytes */
byte RawTC__iDx_Get(RawTC* root, int iDx);

/* OCTETSTRING_bytes */
void RawTC__iDx_Set(RawTC* root, int iDx, byte value);

/* OCTETSTRING_Pointer */
byte* RawTC__GetPointer(RawTC* root);

/* ENUMERATED */
int RxTC__Get(RxTC* root);

/* ENUMERATED */
void RxTC__Set(RxTC* root, int value);

/* ENUMERATED */
int FwdCommand__Get(FwdCommand* root);

/* ENUMERATED */
void FwdCommand__Set(FwdCommand* root, int value);

/* BOOLEAN */
flag GPendingEvAction__Get(GPendingEvAction* root);

/* BOOLEAN */
void GPendingEvAction__Set(GPendingEvAction* root, flag value);

/* BOOLEAN */
flag GToReboot__Get(GToReboot* root);

/* BOOLEAN */
void GToReboot__Set(GToReboot* root, flag value);

/* BOOLEAN */
flag GFwToHK_FDIR__Get(GFwToHK_FDIR* root);

/* BOOLEAN */
void GFwToHK_FDIR__Set(GFwToHK_FDIR* root, flag value);

/* BOOLEAN */
flag GFwToBKG__Get(GFwToBKG* root);

/* BOOLEAN */
void GFwToBKG__Set(GFwToBKG* root, flag value);

/* INTEGER */
asn1SccUint Telecommand__service_type_Get(Telecommand* root);

/* INTEGER */
void Telecommand__service_type_Set(Telecommand* root, asn1SccUint value);

/* INTEGER */
asn1SccUint Telecommand__subservice_type_Get(Telecommand* root);

/* INTEGER */
void Telecommand__subservice_type_Set(Telecommand* root, asn1SccUint value);

/* OCTETSTRING */
long Telecommand__param_GetLength(Telecommand* root);

/* OCTETSTRING */
void Telecommand__param_SetLength(Telecommand* root, long value);

/* OCTETSTRING_bytes */
byte Telecommand__param_iDx_Get(Telecommand* root, int iDx);

/* OCTETSTRING_bytes */
void Telecommand__param_iDx_Set(Telecommand* root, int iDx, byte value);

/* OCTETSTRING_Pointer */
byte* Telecommand__param_GetPointer(Telecommand* root);

/* REAL */
double Pr_time__Get(Pr_time* root);

/* REAL */
void Pr_time__Set(Pr_time* root, double value);

/* INTEGER */
asn1SccSint T_Int32__Get(T_Int32* root);

/* INTEGER */
void T_Int32__Set(T_Int32* root, asn1SccSint value);

/* INTEGER */
asn1SccUint T_UInt32__Get(T_UInt32* root);

/* INTEGER */
void T_UInt32__Set(T_UInt32* root, asn1SccUint value);

/* CHOICE selector */
int T_Runtime_Error__kind_Get(T_Runtime_Error* root);

/* CHOICE selector */
void T_Runtime_Error__kind_Set(T_Runtime_Error* root, int value);

/* INTEGER */
asn1SccUint T_Runtime_Error__noerror_Get(T_Runtime_Error* root);

/* INTEGER */
void T_Runtime_Error__noerror_Set(T_Runtime_Error* root, asn1SccUint value);

/* INTEGER */
asn1SccSint T_Runtime_Error__encodeerror_Get(T_Runtime_Error* root);

/* INTEGER */
void T_Runtime_Error__encodeerror_Set(T_Runtime_Error* root, asn1SccSint value);

/* INTEGER */
asn1SccSint T_Runtime_Error__decodeerror_Get(T_Runtime_Error* root);

/* INTEGER */
void T_Runtime_Error__decodeerror_Set(T_Runtime_Error* root, asn1SccSint value);

/* INTEGER */
asn1SccSint T_Int8__Get(T_Int8* root);

/* INTEGER */
void T_Int8__Set(T_Int8* root, asn1SccSint value);

/* INTEGER */
asn1SccUint T_UInt8__Get(T_UInt8* root);

/* INTEGER */
void T_UInt8__Set(T_UInt8* root, asn1SccUint value);

/* BOOLEAN */
flag T_Boolean__Get(T_Boolean* root);

/* BOOLEAN */
void T_Boolean__Set(T_Boolean* root, flag value);

/* INTEGER */
asn1SccUint PID_Range__Get(PID_Range* root);

/* INTEGER */
void PID_Range__Set(PID_Range* root, asn1SccUint value);

/* ENUMERATED */
int PID__Get(PID* root);

/* ENUMERATED */
void PID__Set(PID* root, int value);

/* Helper functions for NATIVE encodings */

void SetDataFor_RawTC(void *dest, void *src);
byte* MovePtrBySizeOf_RawTC(byte *pData);
byte* CreateInstanceOf_RawTC(void);
void DestroyInstanceOf_RawTC(byte *pData);

void SetDataFor_RxTC(void *dest, void *src);
byte* MovePtrBySizeOf_RxTC(byte *pData);
byte* CreateInstanceOf_RxTC(void);
void DestroyInstanceOf_RxTC(byte *pData);

void SetDataFor_FwdCommand(void *dest, void *src);
byte* MovePtrBySizeOf_FwdCommand(byte *pData);
byte* CreateInstanceOf_FwdCommand(void);
void DestroyInstanceOf_FwdCommand(byte *pData);

void SetDataFor_GPendingEvAction(void *dest, void *src);
byte* MovePtrBySizeOf_GPendingEvAction(byte *pData);
byte* CreateInstanceOf_GPendingEvAction(void);
void DestroyInstanceOf_GPendingEvAction(byte *pData);

void SetDataFor_GToReboot(void *dest, void *src);
byte* MovePtrBySizeOf_GToReboot(byte *pData);
byte* CreateInstanceOf_GToReboot(void);
void DestroyInstanceOf_GToReboot(byte *pData);

void SetDataFor_GFwToHK_FDIR(void *dest, void *src);
byte* MovePtrBySizeOf_GFwToHK_FDIR(byte *pData);
byte* CreateInstanceOf_GFwToHK_FDIR(void);
void DestroyInstanceOf_GFwToHK_FDIR(byte *pData);

void SetDataFor_GFwToBKG(void *dest, void *src);
byte* MovePtrBySizeOf_GFwToBKG(byte *pData);
byte* CreateInstanceOf_GFwToBKG(void);
void DestroyInstanceOf_GFwToBKG(byte *pData);

void SetDataFor_Telecommand(void *dest, void *src);
byte* MovePtrBySizeOf_Telecommand(byte *pData);
byte* CreateInstanceOf_Telecommand(void);
void DestroyInstanceOf_Telecommand(byte *pData);

void SetDataFor_Pr_time(void *dest, void *src);
byte* MovePtrBySizeOf_Pr_time(byte *pData);
byte* CreateInstanceOf_Pr_time(void);
void DestroyInstanceOf_Pr_time(byte *pData);

void SetDataFor_T_Int32(void *dest, void *src);
byte* MovePtrBySizeOf_T_Int32(byte *pData);
byte* CreateInstanceOf_T_Int32(void);
void DestroyInstanceOf_T_Int32(byte *pData);

void SetDataFor_T_UInt32(void *dest, void *src);
byte* MovePtrBySizeOf_T_UInt32(byte *pData);
byte* CreateInstanceOf_T_UInt32(void);
void DestroyInstanceOf_T_UInt32(byte *pData);

void SetDataFor_T_Runtime_Error(void *dest, void *src);
byte* MovePtrBySizeOf_T_Runtime_Error(byte *pData);
byte* CreateInstanceOf_T_Runtime_Error(void);
void DestroyInstanceOf_T_Runtime_Error(byte *pData);

void SetDataFor_T_Int8(void *dest, void *src);
byte* MovePtrBySizeOf_T_Int8(byte *pData);
byte* CreateInstanceOf_T_Int8(void);
void DestroyInstanceOf_T_Int8(byte *pData);

void SetDataFor_T_UInt8(void *dest, void *src);
byte* MovePtrBySizeOf_T_UInt8(byte *pData);
byte* CreateInstanceOf_T_UInt8(void);
void DestroyInstanceOf_T_UInt8(byte *pData);

void SetDataFor_T_Boolean(void *dest, void *src);
byte* MovePtrBySizeOf_T_Boolean(byte *pData);
byte* CreateInstanceOf_T_Boolean(void);
void DestroyInstanceOf_T_Boolean(byte *pData);

void SetDataFor_T_Null_Record(void *dest, void *src);
byte* MovePtrBySizeOf_T_Null_Record(byte *pData);
byte* CreateInstanceOf_T_Null_Record(void);
void DestroyInstanceOf_T_Null_Record(byte *pData);

void SetDataFor_PID_Range(void *dest, void *src);
byte* MovePtrBySizeOf_PID_Range(byte *pData);
byte* CreateInstanceOf_PID_Range(void);
void DestroyInstanceOf_PID_Range(byte *pData);

void SetDataFor_PID(void *dest, void *src);
byte* MovePtrBySizeOf_PID(byte *pData);
byte* CreateInstanceOf_PID(void);
void DestroyInstanceOf_PID(byte *pData);

void SetDataFor_int(void *dest, void *src);
byte* MovePtrBySizeOf_int(byte *pData);
byte* CreateInstanceOf_int(void);
void DestroyInstanceOf_int(byte *pData);


#endif
