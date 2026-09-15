#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "dataview-uniq_getset.h"

#include "asn1crt_encoding.h"
size_t GetStreamCurrentLength(BitStream *pBitStrm) {
    return pBitStrm->currentByte + ((pBitStrm->currentBit+7)/8);
}

byte *GetBitstreamBuffer(BitStream *pBitStrm) {
    return pBitStrm->buf;
}

byte GetBufferByte(byte *p, size_t off) {
    assert(p);
    return p[off];
}

void SetBufferByte(byte *p, size_t off, byte b) {
    assert(p);
    p[off] = b;
}

void ResetStream(BitStream *pStrm) {
    assert(pStrm);
    assert(pStrm->count >= 0);
    pStrm->currentByte = 0;
    pStrm->currentBit = 0;
}

BitStream *CreateStream(size_t bufferSize) {
    BitStream *pBitStrm = malloc(sizeof(BitStream));
    assert(pBitStrm);
    unsigned char* buf = malloc(bufferSize);
    assert(buf);
    memset(buf, 0x0, bufferSize);
    BitStream_Init(pBitStrm, buf, bufferSize);
    return pBitStrm;
}

void DestroyStream(BitStream *pBitStrm) {
    assert(pBitStrm);
    assert(pBitStrm->buf);
    free(pBitStrm->buf);
    free(pBitStrm);
}


/* OCTETSTRING */
long RawTC__GetLength(RawTC* root)
{
    return (*root).nCount;
}

/* OCTETSTRING */
void RawTC__SetLength(RawTC* root, long value)
{
    (*root).nCount = value;
}

/* OCTETSTRING_bytes */
byte RawTC__iDx_Get(RawTC* root, int iDx)
{
    return (*root).arr[iDx];
}

/* OCTETSTRING_bytes */
void RawTC__iDx_Set(RawTC* root, int iDx, byte value)
{
    (*root).arr[iDx] = value;
}

/* OCTETSTRING_Pointer */
byte* RawTC__GetPointer(RawTC* root)
{
    return &(*root).arr[0];
}

/* ENUMERATED */
int RxTC__Get(RxTC* root)
{
    return (*root);
}

/* ENUMERATED */
void RxTC__Set(RxTC* root, int value)
{
    (*root) = value;
}

/* ENUMERATED */
int FwdCommand__Get(FwdCommand* root)
{
    return (*root);
}

/* ENUMERATED */
void FwdCommand__Set(FwdCommand* root, int value)
{
    (*root) = value;
}

/* BOOLEAN */
flag GPendingEvAction__Get(GPendingEvAction* root)
{
    return (*root);
}

/* BOOLEAN */
void GPendingEvAction__Set(GPendingEvAction* root, flag value)
{
    (*root) = value;
}

/* BOOLEAN */
flag GToReboot__Get(GToReboot* root)
{
    return (*root);
}

/* BOOLEAN */
void GToReboot__Set(GToReboot* root, flag value)
{
    (*root) = value;
}

/* BOOLEAN */
flag GFwToHK_FDIR__Get(GFwToHK_FDIR* root)
{
    return (*root);
}

/* BOOLEAN */
void GFwToHK_FDIR__Set(GFwToHK_FDIR* root, flag value)
{
    (*root) = value;
}

/* BOOLEAN */
flag GFwToBKG__Get(GFwToBKG* root)
{
    return (*root);
}

/* BOOLEAN */
void GFwToBKG__Set(GFwToBKG* root, flag value)
{
    (*root) = value;
}

/* INTEGER */
asn1SccUint Telecommand__service_type_Get(Telecommand* root)
{
    return (*root).service_type;
}

/* INTEGER */
void Telecommand__service_type_Set(Telecommand* root, asn1SccUint value)
{
    (*root).service_type = value;
}

/* INTEGER */
asn1SccUint Telecommand__subservice_type_Get(Telecommand* root)
{
    return (*root).subservice_type;
}

/* INTEGER */
void Telecommand__subservice_type_Set(Telecommand* root, asn1SccUint value)
{
    (*root).subservice_type = value;
}

/* OCTETSTRING */
long Telecommand__param_GetLength(Telecommand* root)
{
    return 3;
}

/* OCTETSTRING */
void Telecommand__param_SetLength(Telecommand* root, long value)
{
    fprintf(stderr, "WARNING: setting length of fixed-length sequence\n");
}

/* OCTETSTRING_bytes */
byte Telecommand__param_iDx_Get(Telecommand* root, int iDx)
{
    return (*root).param.arr[iDx];
}

/* OCTETSTRING_bytes */
void Telecommand__param_iDx_Set(Telecommand* root, int iDx, byte value)
{
    (*root).param.arr[iDx] = value;
}

/* OCTETSTRING_Pointer */
byte* Telecommand__param_GetPointer(Telecommand* root)
{
    return &(*root).param.arr[0];
}

/* REAL */
double Pr_time__Get(Pr_time* root)
{
    return (*root);
}

/* REAL */
void Pr_time__Set(Pr_time* root, double value)
{
    (*root) = value;
}

/* INTEGER */
asn1SccSint T_Int32__Get(T_Int32* root)
{
    return (*root);
}

/* INTEGER */
void T_Int32__Set(T_Int32* root, asn1SccSint value)
{
    (*root) = value;
}

/* INTEGER */
asn1SccUint T_UInt32__Get(T_UInt32* root)
{
    return (*root);
}

/* INTEGER */
void T_UInt32__Set(T_UInt32* root, asn1SccUint value)
{
    (*root) = value;
}

/* CHOICE selector */
int T_Runtime_Error__kind_Get(T_Runtime_Error* root)
{
    return (*root).kind;
}

/* CHOICE selector */
void T_Runtime_Error__kind_Set(T_Runtime_Error* root, int value)
{
    (*root).kind = value;
}

/* INTEGER */
asn1SccUint T_Runtime_Error__noerror_Get(T_Runtime_Error* root)
{
    return (*root).u.noerror;
}

/* INTEGER */
void T_Runtime_Error__noerror_Set(T_Runtime_Error* root, asn1SccUint value)
{
    (*root).u.noerror = value;
}

/* INTEGER */
asn1SccSint T_Runtime_Error__encodeerror_Get(T_Runtime_Error* root)
{
    return (*root).u.encodeerror;
}

/* INTEGER */
void T_Runtime_Error__encodeerror_Set(T_Runtime_Error* root, asn1SccSint value)
{
    (*root).u.encodeerror = value;
}

/* INTEGER */
asn1SccSint T_Runtime_Error__decodeerror_Get(T_Runtime_Error* root)
{
    return (*root).u.decodeerror;
}

/* INTEGER */
void T_Runtime_Error__decodeerror_Set(T_Runtime_Error* root, asn1SccSint value)
{
    (*root).u.decodeerror = value;
}

/* INTEGER */
asn1SccSint T_Int8__Get(T_Int8* root)
{
    return (*root);
}

/* INTEGER */
void T_Int8__Set(T_Int8* root, asn1SccSint value)
{
    (*root) = value;
}

/* INTEGER */
asn1SccUint T_UInt8__Get(T_UInt8* root)
{
    return (*root);
}

/* INTEGER */
void T_UInt8__Set(T_UInt8* root, asn1SccUint value)
{
    (*root) = value;
}

/* BOOLEAN */
flag T_Boolean__Get(T_Boolean* root)
{
    return (*root);
}

/* BOOLEAN */
void T_Boolean__Set(T_Boolean* root, flag value)
{
    (*root) = value;
}

/* INTEGER */
asn1SccUint PID_Range__Get(PID_Range* root)
{
    return (*root);
}

/* INTEGER */
void PID_Range__Set(PID_Range* root, asn1SccUint value)
{
    (*root) = value;
}

/* ENUMERATED */
int PID__Get(PID* root)
{
    return (*root);
}

/* ENUMERATED */
void PID__Set(PID* root, int value)
{
    (*root) = value;
}

/* Helper functions for NATIVE encodings */

void SetDataFor_RawTC(void *dest, void *src)
{
    memcpy(dest, src, sizeof(RawTC));
}

byte* MovePtrBySizeOf_RawTC(byte *pData)
{
    return pData + sizeof(RawTC);
}

byte* CreateInstanceOf_RawTC() {
    RawTC *p = (RawTC*)malloc(sizeof(RawTC));
    RawTC_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_RawTC(byte *pData) {
    free(pData);
}

void SetDataFor_RxTC(void *dest, void *src)
{
    memcpy(dest, src, sizeof(RxTC));
}

byte* MovePtrBySizeOf_RxTC(byte *pData)
{
    return pData + sizeof(RxTC);
}

byte* CreateInstanceOf_RxTC() {
    RxTC *p = (RxTC*)malloc(sizeof(RxTC));
    RxTC_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_RxTC(byte *pData) {
    free(pData);
}

void SetDataFor_FwdCommand(void *dest, void *src)
{
    memcpy(dest, src, sizeof(FwdCommand));
}

byte* MovePtrBySizeOf_FwdCommand(byte *pData)
{
    return pData + sizeof(FwdCommand);
}

byte* CreateInstanceOf_FwdCommand() {
    FwdCommand *p = (FwdCommand*)malloc(sizeof(FwdCommand));
    FwdCommand_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_FwdCommand(byte *pData) {
    free(pData);
}

void SetDataFor_GPendingEvAction(void *dest, void *src)
{
    memcpy(dest, src, sizeof(GPendingEvAction));
}

byte* MovePtrBySizeOf_GPendingEvAction(byte *pData)
{
    return pData + sizeof(GPendingEvAction);
}

byte* CreateInstanceOf_GPendingEvAction() {
    GPendingEvAction *p = (GPendingEvAction*)malloc(sizeof(GPendingEvAction));
    GPendingEvAction_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_GPendingEvAction(byte *pData) {
    free(pData);
}

void SetDataFor_GToReboot(void *dest, void *src)
{
    memcpy(dest, src, sizeof(GToReboot));
}

byte* MovePtrBySizeOf_GToReboot(byte *pData)
{
    return pData + sizeof(GToReboot);
}

byte* CreateInstanceOf_GToReboot() {
    GToReboot *p = (GToReboot*)malloc(sizeof(GToReboot));
    GToReboot_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_GToReboot(byte *pData) {
    free(pData);
}

void SetDataFor_GFwToHK_FDIR(void *dest, void *src)
{
    memcpy(dest, src, sizeof(GFwToHK_FDIR));
}

byte* MovePtrBySizeOf_GFwToHK_FDIR(byte *pData)
{
    return pData + sizeof(GFwToHK_FDIR);
}

byte* CreateInstanceOf_GFwToHK_FDIR() {
    GFwToHK_FDIR *p = (GFwToHK_FDIR*)malloc(sizeof(GFwToHK_FDIR));
    GFwToHK_FDIR_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_GFwToHK_FDIR(byte *pData) {
    free(pData);
}

void SetDataFor_GFwToBKG(void *dest, void *src)
{
    memcpy(dest, src, sizeof(GFwToBKG));
}

byte* MovePtrBySizeOf_GFwToBKG(byte *pData)
{
    return pData + sizeof(GFwToBKG);
}

byte* CreateInstanceOf_GFwToBKG() {
    GFwToBKG *p = (GFwToBKG*)malloc(sizeof(GFwToBKG));
    GFwToBKG_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_GFwToBKG(byte *pData) {
    free(pData);
}

void SetDataFor_Telecommand(void *dest, void *src)
{
    memcpy(dest, src, sizeof(Telecommand));
}

byte* MovePtrBySizeOf_Telecommand(byte *pData)
{
    return pData + sizeof(Telecommand);
}

byte* CreateInstanceOf_Telecommand() {
    Telecommand *p = (Telecommand*)malloc(sizeof(Telecommand));
    Telecommand_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_Telecommand(byte *pData) {
    free(pData);
}

void SetDataFor_Pr_time(void *dest, void *src)
{
    memcpy(dest, src, sizeof(Pr_time));
}

byte* MovePtrBySizeOf_Pr_time(byte *pData)
{
    return pData + sizeof(Pr_time);
}

byte* CreateInstanceOf_Pr_time() {
    Pr_time *p = (Pr_time*)malloc(sizeof(Pr_time));
    Pr_time_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_Pr_time(byte *pData) {
    free(pData);
}

void SetDataFor_T_Int32(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_Int32));
}

byte* MovePtrBySizeOf_T_Int32(byte *pData)
{
    return pData + sizeof(T_Int32);
}

byte* CreateInstanceOf_T_Int32() {
    T_Int32 *p = (T_Int32*)malloc(sizeof(T_Int32));
    T_Int32_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_Int32(byte *pData) {
    free(pData);
}

void SetDataFor_T_UInt32(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_UInt32));
}

byte* MovePtrBySizeOf_T_UInt32(byte *pData)
{
    return pData + sizeof(T_UInt32);
}

byte* CreateInstanceOf_T_UInt32() {
    T_UInt32 *p = (T_UInt32*)malloc(sizeof(T_UInt32));
    T_UInt32_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_UInt32(byte *pData) {
    free(pData);
}

void SetDataFor_T_Runtime_Error(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_Runtime_Error));
}

byte* MovePtrBySizeOf_T_Runtime_Error(byte *pData)
{
    return pData + sizeof(T_Runtime_Error);
}

byte* CreateInstanceOf_T_Runtime_Error() {
    T_Runtime_Error *p = (T_Runtime_Error*)malloc(sizeof(T_Runtime_Error));
    T_Runtime_Error_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_Runtime_Error(byte *pData) {
    free(pData);
}

void SetDataFor_T_Int8(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_Int8));
}

byte* MovePtrBySizeOf_T_Int8(byte *pData)
{
    return pData + sizeof(T_Int8);
}

byte* CreateInstanceOf_T_Int8() {
    T_Int8 *p = (T_Int8*)malloc(sizeof(T_Int8));
    T_Int8_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_Int8(byte *pData) {
    free(pData);
}

void SetDataFor_T_UInt8(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_UInt8));
}

byte* MovePtrBySizeOf_T_UInt8(byte *pData)
{
    return pData + sizeof(T_UInt8);
}

byte* CreateInstanceOf_T_UInt8() {
    T_UInt8 *p = (T_UInt8*)malloc(sizeof(T_UInt8));
    T_UInt8_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_UInt8(byte *pData) {
    free(pData);
}

void SetDataFor_T_Boolean(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_Boolean));
}

byte* MovePtrBySizeOf_T_Boolean(byte *pData)
{
    return pData + sizeof(T_Boolean);
}

byte* CreateInstanceOf_T_Boolean() {
    T_Boolean *p = (T_Boolean*)malloc(sizeof(T_Boolean));
    T_Boolean_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_Boolean(byte *pData) {
    free(pData);
}

void SetDataFor_T_Null_Record(void *dest, void *src)
{
    memcpy(dest, src, sizeof(T_Null_Record));
}

byte* MovePtrBySizeOf_T_Null_Record(byte *pData)
{
    return pData + sizeof(T_Null_Record);
}

byte* CreateInstanceOf_T_Null_Record() {
    T_Null_Record *p = (T_Null_Record*)malloc(sizeof(T_Null_Record));
    T_Null_Record_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_T_Null_Record(byte *pData) {
    free(pData);
}

void SetDataFor_PID_Range(void *dest, void *src)
{
    memcpy(dest, src, sizeof(PID_Range));
}

byte* MovePtrBySizeOf_PID_Range(byte *pData)
{
    return pData + sizeof(PID_Range);
}

byte* CreateInstanceOf_PID_Range() {
    PID_Range *p = (PID_Range*)malloc(sizeof(PID_Range));
    PID_Range_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_PID_Range(byte *pData) {
    free(pData);
}

void SetDataFor_PID(void *dest, void *src)
{
    memcpy(dest, src, sizeof(PID));
}

byte* MovePtrBySizeOf_PID(byte *pData)
{
    return pData + sizeof(PID);
}

byte* CreateInstanceOf_PID() {
    PID *p = (PID*)malloc(sizeof(PID));
    PID_Initialize(p);
    return (byte*)p;
}

void DestroyInstanceOf_PID(byte *pData) {
    free(pData);
}

void SetDataFor_int(void *dest, void *src)
{
    memcpy(dest, src, sizeof(int));
}

byte* MovePtrBySizeOf_int(byte *pData)
{
    return pData + sizeof(int);
}

byte* CreateInstanceOf_int() {
    int *p = (int*)malloc(sizeof(int));
    *p = 0;
    return (byte*)p;
}

void DestroyInstanceOf_int(byte *pData) {
    free(pData);
}

