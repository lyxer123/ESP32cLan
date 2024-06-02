/* myErrno.h */
#ifndef MY_ERRNO_H
#define MY_ERRNO_H

#include <Arduino.h>
#include <errno.h>
#include "myInterpreter.h"

#ifndef BUILTIN_MINI_STDLIB

#ifdef __cplusplus
extern "C" {
#endif

    #ifdef EACCES
        extern int EACCESValue;
    #endif

    #ifdef EADDRINUSE
        extern int EADDRINUSEValue;
    #endif

    #ifdef EADDRNOTAVAIL
        extern int EADDRNOTAVAILValue;
    #endif

    #ifdef EAFNOSUPPORT
        extern int EAFNOSUPPORTValue;
    #endif

    #ifdef EAGAIN
        extern int EAGAINValue;
    #endif

    #ifdef EALREADY
        extern int EALREADYValue;
    #endif

    #ifdef EBADF
        extern int EBADFValue;
    #endif

    #ifdef EBADMSG
        extern int EBADMSGValue;
    #endif

    #ifdef EBUSY
        extern int EBUSYValue;
    #endif

    #ifdef ECANCELED
        extern int ECANCELEDValue;
    #endif

    #ifdef ECHILD
        extern int ECHILDValue;
    #endif

    #ifdef ECONNABORTED
        extern int ECONNABORTEDValue;
    #endif

    #ifdef ECONNREFUSED
        extern int ECONNREFUSEDValue;
    #endif

    #ifdef ECONNRESET
        extern int ECONNRESETValue;
    #endif

    #ifdef EDEADLK
        extern int EDEADLKValue;
    #endif

    #ifdef EDESTADDRREQ
        extern int EDESTADDRREQValue;
    #endif

    #ifdef EDOM
        extern int EDOMValue;
    #endif

    #ifdef EDQUOT
        extern int EDQUOTValue;
    #endif

    #ifdef EEXIST
        extern int EEXISTValue;
    #endif

    #ifdef EFAULT
        extern int EFAULTValue;
    #endif

    #ifdef EFBIG
        extern int EFBIGValue;
    #endif

    #ifdef EHOSTUNREACH
        extern int EHOSTUNREACHValue;
    #endif

    #ifdef EIDRM
        extern int EIDRMValue;
    #endif

    #ifdef EILSEQ
        extern int EILSEQValue;
    #endif

    #ifdef EINPROGRESS
        extern int EINPROGRESSValue;
    #endif

    #ifdef EINTR
        extern int EINTRValue;
    #endif

    #ifdef EINVAL
        extern int EINVALValue;
    #endif

    #ifdef EIO
        extern int EIOValue;
    #endif

    #ifdef EISCONN
        extern int EISCONNValue;
    #endif

    #ifdef EISDIR
        extern int EISDIRValue;
    #endif

    #ifdef ELOOP
        extern int ELOOPValue;
    #endif

    #ifdef EMFILE
        extern int EMFILEValue;
    #endif

    #ifdef EMLINK
        extern int EMLINKValue;
    #endif

    #ifdef EMSGSIZE
        extern int EMSGSIZEValue;
    #endif

    #ifdef EMULTIHOP
        extern int EMULTIHOPValue;
    #endif

    #ifdef ENAMETOOLONG
        extern int ENAMETOOLONGValue;
    #endif

    #ifdef ENETDOWN
        extern int ENETDOWNValue;
    #endif

    #ifdef ENETRESET
        extern int ENETRESETValue;
    #endif

    #ifdef ENETUNREACH
        extern int ENETUNREACHValue;
    #endif

    #ifdef ENFILE
        extern int ENFILEValue;
    #endif

    #ifdef ENOBUFS
        extern int ENOBUFSValue;
    #endif

    #ifdef ENODATA
        extern int ENODATAValue;
    #endif

    #ifdef ENODEV
        extern int ENODEVValue;
    #endif

    #ifdef ENOENT
        extern int ENOENTValue;
    #endif

    #ifdef ENOEXEC
        extern int ENOEXECValue;
    #endif

    #ifdef ENOLCK
        extern int ENOLCKValue;
    #endif

    #ifdef ENOLINK
        extern int ENOLINKValue;
    #endif

    #ifdef ENOMEM
        extern int ENOMEMValue;
    #endif

    #ifdef ENOMSG
        extern int ENOMSGValue;
    #endif

    #ifdef ENOPROTOOPT
        extern int ENOPROTOOPTValue;
    #endif

    #ifdef ENOSPC
        extern int ENOSPCValue;
    #endif

    #ifdef ENOSR
        extern int ENOSRValue;
    #endif

    #ifdef ENOSTR
        extern int ENOSTRValue;
    #endif

    #ifdef ENOSYS
        extern int ENOSYSValue;
    #endif

    #ifdef ENOTCONN
        extern int ENOTCONNValue;
    #endif

    #ifdef ENOTDIR
        extern int ENOTDIRValue;
    #endif

    #ifdef ENOTEMPTY
        extern int ENOTEMPTYValue;
    #endif

    #ifdef ENOTRECOVERABLE
        extern int ENOTRECOVERABLEValue;
    #endif

    #ifdef ENOTSOCK
        extern int ENOTSOCKValue;
    #endif

    #ifdef ENOTSUP
        extern int ENOTSUPValue;
    #endif

    #ifdef ENOTTY
        extern int ENOTTYValue;
    #endif

    #ifdef ENXIO
        extern int ENXIOValue;
    #endif

    #ifdef EOPNOTSUPP
        extern int EOPNOTSUPPValue;
    #endif

    #ifdef EOVERFLOW
        extern int EOVERFLOWValue;
    #endif

    #ifdef EOWNERDEAD
        extern int EOWNERDEADValue;
    #endif

    #ifdef EPERM
        extern int EPERMValue;
    #endif

    #ifdef EPIPE
        extern int EPIPEValue;
    #endif

    #ifdef EPROTO
        extern int EPROTOValue;
    #endif

    #ifdef EPROTONOSUPPORT
        extern int EPROTONOSUPPORTValue;
    #endif

    #ifdef EPROTOTYPE
        extern int EPROTOTYPEValue;
    #endif

    #ifdef ERANGE
        extern int ERANGEValue;
    #endif

    #ifdef EROFS
        extern int EROFSValue;
    #endif

    #ifdef ESPIPE
        extern int ESPIPEValue;
    #endif

    #ifdef ESRCH
        extern int ESRCHValue;
    #endif

    #ifdef ESTALE
        extern int ESTALEValue;
    #endif

    #ifdef ETIME
        extern int ETIMEValue;
    #endif

    #ifdef ETIMEDOUT
        extern int ETIMEDOUTValue;
    #endif

    #ifdef ETXTBSY
        extern int ETXTBSYValue;
    #endif

    #ifdef EWOULDBLOCK
        extern int EWOULDBLOCKValue;
    #endif

    #ifdef EXDEV
        extern int EXDEVValue;
    #endif

    void StdErrnoSetupFunc(void);

#ifdef __cplusplus
}
#endif

#endif /* !BUILTIN_MINI_STDLIB */

#endif /* MY_ERRNO_H */
