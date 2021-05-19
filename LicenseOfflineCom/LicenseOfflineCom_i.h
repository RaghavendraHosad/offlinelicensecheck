

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 08:44:07 2038
 */
/* Compiler settings for LicenseOfflineCom.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __LicenseOfflineCom_i_h__
#define __LicenseOfflineCom_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IOfflineLicenseValidityChecker_FWD_DEFINED__
#define __IOfflineLicenseValidityChecker_FWD_DEFINED__
typedef interface IOfflineLicenseValidityChecker IOfflineLicenseValidityChecker;

#endif 	/* __IOfflineLicenseValidityChecker_FWD_DEFINED__ */


#ifndef __OfflineLicenseValidityChecker_FWD_DEFINED__
#define __OfflineLicenseValidityChecker_FWD_DEFINED__

#ifdef __cplusplus
typedef class OfflineLicenseValidityChecker OfflineLicenseValidityChecker;
#else
typedef struct OfflineLicenseValidityChecker OfflineLicenseValidityChecker;
#endif /* __cplusplus */

#endif 	/* __OfflineLicenseValidityChecker_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IOfflineLicenseValidityChecker_INTERFACE_DEFINED__
#define __IOfflineLicenseValidityChecker_INTERFACE_DEFINED__

/* interface IOfflineLicenseValidityChecker */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IOfflineLicenseValidityChecker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e674de2f-ffb6-41f5-8eef-bf625f3011e7")
    IOfflineLicenseValidityChecker : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CheckSWValidity( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IOfflineLicenseValidityCheckerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IOfflineLicenseValidityChecker * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IOfflineLicenseValidityChecker * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IOfflineLicenseValidityChecker * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IOfflineLicenseValidityChecker * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IOfflineLicenseValidityChecker * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IOfflineLicenseValidityChecker * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IOfflineLicenseValidityChecker * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CheckSWValidity )( 
            IOfflineLicenseValidityChecker * This);
        
        END_INTERFACE
    } IOfflineLicenseValidityCheckerVtbl;

    interface IOfflineLicenseValidityChecker
    {
        CONST_VTBL struct IOfflineLicenseValidityCheckerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOfflineLicenseValidityChecker_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IOfflineLicenseValidityChecker_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IOfflineLicenseValidityChecker_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IOfflineLicenseValidityChecker_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IOfflineLicenseValidityChecker_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IOfflineLicenseValidityChecker_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IOfflineLicenseValidityChecker_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IOfflineLicenseValidityChecker_CheckSWValidity(This)	\
    ( (This)->lpVtbl -> CheckSWValidity(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IOfflineLicenseValidityChecker_INTERFACE_DEFINED__ */



#ifndef __LicenseOfflineComLib_LIBRARY_DEFINED__
#define __LicenseOfflineComLib_LIBRARY_DEFINED__

/* library LicenseOfflineComLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_LicenseOfflineComLib;

EXTERN_C const CLSID CLSID_OfflineLicenseValidityChecker;

#ifdef __cplusplus

class DECLSPEC_UUID("f7af9d31-717b-404b-ae60-49f485c43da0")
OfflineLicenseValidityChecker;
#endif
#endif /* __LicenseOfflineComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


