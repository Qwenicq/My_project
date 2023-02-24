/////////////////////////////////////////////////////////////////////////////
//
//	Copyright (c) 2022 <company name>
//
//	Module Name:
//		��Ex.cpp
//
//	Abstract:
//		Implementation of the CMyApp class and DLL initialization
//		routines.
//
//	Author:
//		<name> (<e-mail name>) Mmmm DD, 2022
//
//	Revision History:
//
//	Notes:
//		NOTE: You must use the MIDL compiler from NT 4.0,
//		version 3.00.44 or greater
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <initguid.h>
#include <CluAdmEx.h>
#include "��Ex.h"
#include "ExtObj.h"
#include "BasePage.h"
#include "RegExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

#pragma warning(disable : 4701) // local variable may be used without having been initialized
#include <atlimpl.cpp>
#pragma warning(default : 4701)

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_CoMyEx, CExtObject)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// Global Function Prototypes
/////////////////////////////////////////////////////////////////////////////

STDAPI DllCanUnloadNow(void);
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
STDAPI DllRegisterServer(void);
STDAPI DllUnregisterServer(void);
STDAPI DllRegisterCluAdminExtension(IN HCLUSTER hcluster);
STDAPI DllUnregisterCluAdminExtension(IN HCLUSTER hcluster);

/////////////////////////////////////////////////////////////////////////////
// class CMyApp
/////////////////////////////////////////////////////////////////////////////

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyApp object

CMyApp theApp;

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyApp::InitInstance
//
//	Routine Description:
//		Initialize this instance of the application.
//
//	Arguments:
//		None.
//
//	Return Value:
//		Any return codes from CWinApp::InitInstance().
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL CMyApp::InitInstance(void)
{
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();

}  //*** CMyApp::InitInstance()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	CMyApp::ExitInstance
//
//	Routine Description:
//		Deinitialize this instance of the application.
//
//	Arguments:
//		None.
//
//	Return Value:
//		Any return codes from CWinApp::ExitInstance().
//
//--
/////////////////////////////////////////////////////////////////////////////
int CMyApp::ExitInstance(void)
{
	_Module.Term();
	return CWinApp::ExitInstance();

}  //*** CMyApp::ExitInstance()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	FormatError
//
//	Routine Description:
//		Format an error.
//
//	Arguments:
//		rstrError	[OUT] String in which to return the error message.
//		dwError		[IN] Error code to format.
//
//	Return Value:
//		None.
//
//--
/////////////////////////////////////////////////////////////////////////////
void FormatError(CString & rstrError, DWORD dwError)
{
	DWORD		dwResult;
	TCHAR		szError[256];

	dwResult = ::FormatMessage(
					FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					dwError,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
					szError,
					sizeof(szError) / sizeof(TCHAR),
					0
					);
	if (dwResult == 0)
	{
		// Format the NT status code from CLUSAPI since some of these haven't
		// been integrated into the system yet.
		dwResult = ::FormatMessage(
						FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
						::GetModuleHandle(_T("CLUSAPI.DLL")),
						dwError,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
						szError,
						sizeof(szError) / sizeof(TCHAR),
						0
						);
		if (dwResult == 0)
		{
			// Format the NT status code from NTDLL since this hasn't been
			// integrated into the system yet.
			dwResult = ::FormatMessage(
							FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,
							::GetModuleHandle(_T("NTDLL.DLL")),
							dwError,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
							szError,
							sizeof(szError) / sizeof(TCHAR),
							0
							);
		}  // if:  error formatting status code from CLUSAPI
	}  // if:  error formatting status code from system

	if (dwResult != 0)
		rstrError = szError;
	else
	{
		dwResult = ::GetLastError();
		TRACE(_T("FormatError() - Error 0x%08.8x formatting string for error code 0x%08.8x\n"), dwResult, dwError);
		rstrError.Format(_T("Error 0x%08.8x"));
	}  // else:  error formatting the message

}  //*** FormatError()

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow() && _Module.GetLockCount()==0) ? S_OK : S_FALSE;

}  //*** DllCanUnloadNow()

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);

}  //*** DllGetClassObject()

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	HRESULT hRes = S_OK;
	// registers object, typelib and all interfaces in typelib
	hRes = _Module.RegisterServer(FALSE /*bRegTypeLib*/);
	return hRes;

}  //*** DllRegisterServer()

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HRESULT hRes = S_OK;
	_Module.UnregisterServer();
	return hRes;

}  //*** DllUnregisterServer()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	DllRegisterCluAdminExtension
//
//	Routine Description:
//		Register the extension with the cluster database.
//
//	Arguments:
//		hCluster		[IN] Handle to the cluster to modify.
//
//	Return Value:
//		S_OK			Extension registered successfully.
//		Win32 error code if another failure occurred.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterCluAdminExtension(IN HCLUSTER hCluster)
{
	HRESULT		hr;
	HRESULT		hrReturn = S_OK;
	LPCWSTR		pwszResTypes = g_wszResourceTypeNames;

	while (*pwszResTypes != L'\0')
	{
		wprintf(L"  %s\n", pwszResTypes);
		hr = RegisterCluAdminResourceTypeExtension(
					hCluster,
					pwszResTypes,
					&CLSID_CoMyEx
					);
		if (hr != S_OK)
			hrReturn = hr;
		pwszResTypes += lstrlenW(pwszResTypes) + 1;
	}  // while:  more resource types

	return hrReturn;

}  //*** DllRegisterCluAdminExtension()

/////////////////////////////////////////////////////////////////////////////
//++
//
//	DllUnregisterCluAdminExtension
//
//	Routine Description:
//		Unregister the extension with the cluster database.
//
//	Arguments:
//		hCluster		[IN] Handle to the cluster to modify.
//
//	Return Value:
//		S_OK			Extension unregistered successfully.
//		Win32 error code if another failure occurred.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllUnregisterCluAdminExtension(IN HCLUSTER hCluster)
{
	HRESULT		hr;
	HRESULT		hrReturn = S_OK;
	LPCWSTR		pwszResTypes = g_wszResourceTypeNames;

	while (*pwszResTypes != L'\0')
	{
		wprintf(L"  %s\n", pwszResTypes);
		hr = UnregisterCluAdminResourceTypeExtension(
					hCluster,
					pwszResTypes,
					&CLSID_CoMyEx
					);
		if (hr != S_OK)
			hrReturn = hr;
		pwszResTypes += lstrlenW(pwszResTypes) + 1;
	}  // while:  more resource types

	return hrReturn;

}  //*** DllUnregisterCluAdminExtension()
