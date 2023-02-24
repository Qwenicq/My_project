/*++

Copyright (c) 2022 <company name>

Module Name:

    Ê÷.c

Abstract:

    Resource DLL for Ê÷ (Ê÷).

Author:

    <user> (<email-name>) Mmmm DD, 2022

Revision History:

--*/

#pragma comment(lib, "clusapi.lib")
#pragma comment(lib, "resutils.lib")

#define UNICODE 1

#pragma warning( disable : 4115 )  // named type definition in parentheses
#pragma warning( disable : 4201 )  // nonstandard extension used : nameless struct/union
#pragma warning( disable : 4214 )  // nonstandard extension used : bit field types other than int

#include <windows.h>

#pragma warning( default : 4214 )  // nonstandard extension used : bit field types other than int
#pragma warning( default : 4201 )  // nonstandard extension used : nameless struct/union
#pragma warning( default : 4115 )  // named type definition in parentheses

#include <clusapi.h>
#include <resapi.h>
#include <stdio.h>

//
// Type and constant definitions.
//

#define MY_RESNAME  L"Ê÷"

#define DBG_PRINT printf

typedef struct _MY_RESOURCE {
    RESID                   ResId; // for validation
    HKEY                    ParametersKey;
    RESOURCE_HANDLE         ResourceHandle;
    LPWSTR                  ResourceName;
    CLUS_WORKER             OnlineThread;
    CLUSTER_RESOURCE_STATE  State;
} MY_RESOURCE, *PMY_RESOURCE;


//
// Global data.
//

// Event Logging routine.

PLOG_EVENT_ROUTINE g_LogEvent = NULL;

// Resource Status routine for pending Online and Offline calls.

PSET_RESOURCE_STATUS_ROUTINE g_SetResourceStatus = NULL;

// Forward reference to our RESAPI function table.

extern CLRES_FUNCTION_TABLE g_MyFunctionTable;

//
// Ê÷ resource read-write private properties.
//
RESUTIL_PROPERTY_ITEM
MyResourcePrivateProperties[] = {
    { 0 }
};


//
// Function prototypes.
//

DWORD
WINAPI
Startup(
    IN LPCWSTR ResourceType,
    IN DWORD MinVersionSupported,
    IN DWORD MaxVersionSupported,
    IN PSET_RESOURCE_STATUS_ROUTINE SetResourceStatus,
    IN PLOG_EVENT_ROUTINE LogEvent,
    OUT PCLRES_FUNCTION_TABLE *FunctionTable
    );

RESID
WINAPI
MyOpen(
    IN LPCWSTR ResourceName,
    IN HKEY ResourceKey,
    IN RESOURCE_HANDLE ResourceHandle
    );

VOID
WINAPI
MyClose(
    IN RESID ResourceId
    );

DWORD
WINAPI
MyOnline(
    IN RESID ResourceId,
    IN OUT PHANDLE EventHandle
    );

DWORD
WINAPI
MyOnlineThread(
    PCLUS_WORKER WorkerPtr,
    IN PMY_RESOURCE ResourceEntry
    );

DWORD
WINAPI
MyOffline(
    IN RESID ResourceId
    );

VOID
WINAPI
MyTerminate(
    IN RESID ResourceId
    );

DWORD
MyDoTerminate(
    IN PMY_RESOURCE ResourceEntry
    );

BOOL
WINAPI
MyLooksAlive(
    IN RESID ResourceId
    );

BOOL
WINAPI
MyIsAlive(
    IN RESID ResourceId
    );

BOOL
MyCheckIsAlive(
    IN PMY_RESOURCE ResourceEntry
    );

DWORD
WINAPI
MyResourceControl(
    IN RESID ResourceId,
    IN DWORD ControlCode,
    IN PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned
    );


BOOLEAN
WINAPI
DllMain(
    IN HINSTANCE    DllHandle,
    IN DWORD        Reason,
    IN LPVOID       Reserved
    )

/*++

Routine Description:

    Main DLL entry point.

Arguments:

    DllHandle - DLL instance handle.

    Reason - Reason for being called.

    Reserved - Reserved argument.

Return Value:

    TRUE - Success.

    FALSE - Failure.

--*/

{
    switch( Reason ) {

    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls( DllHandle );
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return(TRUE);

} // DllMain



DWORD
WINAPI
Startup(
    IN LPCWSTR ResourceType,
    IN DWORD MinVersionSupported,
    IN DWORD MaxVersionSupported,
    IN PSET_RESOURCE_STATUS_ROUTINE SetResourceStatus,
    IN PLOG_EVENT_ROUTINE LogEvent,
    OUT PCLRES_FUNCTION_TABLE *FunctionTable
    )

/*++

Routine Description:

    Startup the resource DLL. This routine verifies that at least one
    currently supported version of the resource DLL is between
    MinVersionSupported and MaxVersionSupported. If not, then the resource
    DLL should return ERROR_REVISION_MISMATCH.

    If more than one version of the resource DLL interface is supported by
    the resource DLL, then the highest version (up to MaxVersionSupported)
    should be returned as the resource DLL's interface. If the returned
    version is not within range, then startup fails.

    The ResourceType is passed in so that if the resource DLL supports more
    than one ResourceType, it can pass back the correct function table
    associated with the ResourceType.

Arguments:

    ResourceType - The type of resource requesting a function table.

    MinVersionSupported - The minimum resource DLL interface version 
        supported by the cluster software.

    MaxVersionSupported - The maximum resource DLL interface version
        supported by the cluster software.

    SetResourceStatus - Pointer to a routine that the resource DLL should 
        call to update the state of a resource after the Online or Offline 
        routine returns a status of ERROR_IO_PENDING.

    LogEvent - Pointer to a routine that handles the reporting of events 
        from the resource DLL. 

    FunctionTable - Returns a pointer to the function table defined for the
        version of the resource DLL interface returned by the resource DLL.

Return Value:

    ERROR_SUCCESS - The operation was successful.

    ERROR_MOD_NOT_FOUND - The resource type is unknown by this DLL.

    ERROR_REVISION_MISMATCH - The version of the cluster service doesn't
        match the versrion of the DLL.

    Win32 error code - The operation failed.

--*/

{
    if ( (MinVersionSupported > CLRES_VERSION_V1_00) ||
         (MaxVersionSupported < CLRES_VERSION_V1_00) ) {
        return(ERROR_REVISION_MISMATCH);
    }

    if ( lstrcmpiW( ResourceType, MY_RESNAME ) != 0 ) {
        return(ERROR_MOD_NOT_FOUND);
    }

    if ( !g_LogEvent ) {
        g_LogEvent = LogEvent;
        g_SetResourceStatus = SetResourceStatus;
    }

    *FunctionTable = &g_MyFunctionTable;

    return(ERROR_SUCCESS);

} // Startup


RESID
WINAPI
MyOpen(
    IN LPCWSTR ResourceName,
    IN HKEY ResourceKey,
    IN RESOURCE_HANDLE ResourceHandle
    )

/*++

Routine Description:

    Open routine for Ê÷ resources.

    Open the specified resource (create an instance of the resource). 
    Allocate all structures necessary to bring the specified resource 
    online.

Arguments:

    ResourceName - Supplies the name of the resource to open.

    ResourceKey - Supplies handle to the resource's cluster configuration 
        database key.

    ResourceHandle - A handle that is passed back to the resource monitor 
        when the SetResourceStatus or LogEvent method is called. See the 
        description of the SetResourceStatus and LogEvent methods on the
        MyStatup routine. This handle should never be closed or used
        for any purpose other than passing it as an argument back to the
        Resource Monitor in the SetResourceStatus or LogEvent callback.

Return Value:

    RESID of created resource.

    NULL on failure.

--*/

{
    DWORD               status;
    DWORD               disposition;
    RESID               resid = 0;
    HKEY                parametersKey = NULL;
    PMY_RESOURCE resourceEntry = NULL;

    //
    // Open the Parameters registry key for this resource.
    //

    status = ClusterRegCreateKey( ResourceKey,
                                  L"Parameters",
                                  0,
                                  KEY_ALL_ACCESS,
                                  NULL,
                                  &parametersKey,
                                  &disposition );

    if ( status != ERROR_SUCCESS ) {
        (g_LogEvent)(
            ResourceHandle,
            LOG_ERROR,
            L"Unable to open Parameters key. Error: %1!u!.\n",
            status );
        goto exit;
    }

    //
    // Allocate a resource entry.
    //

    resourceEntry = (PMY_RESOURCE) LocalAlloc( LMEM_FIXED, sizeof(MY_RESOURCE) );

    if ( resourceEntry == NULL ) {
        status = GetLastError();
        (g_LogEvent)(
            ResourceHandle,
            LOG_ERROR,
            L"Unable to allocate resource entry structure. Error: %1!u!.\n",
            status );
        goto exit;
    }

    //
    // Initialize the resource entry..
    //

    ZeroMemory( resourceEntry, sizeof(MY_RESOURCE) );

    resourceEntry->ResId = (RESID)resourceEntry; // for validation
    resourceEntry->ResourceHandle = ResourceHandle;
    resourceEntry->ParametersKey = parametersKey;
    resourceEntry->State = ClusterResourceOffline;

    //
    // Save the name of the resource.
    //
    resourceEntry->ResourceName = LocalAlloc( LMEM_FIXED, (lstrlenW( ResourceName ) + 1) * sizeof(WCHAR) );
    if ( resourceEntry->ResourceName == NULL ) {
        goto exit;
    }
    lstrcpyW( resourceEntry->ResourceName, ResourceName );

    //
    // Startup for the resource.
    //
    // TODO: Add your resource startup code here.


    resid = (RESID)resourceEntry;

exit:

    if ( resid == 0 ) {
        if ( parametersKey != NULL ) {
            ClusterRegCloseKey( parametersKey );
        }
        if ( resourceEntry != NULL ) {
            LocalFree( resourceEntry->ResourceName );
            LocalFree( resourceEntry );
        }
    }

    if ( status != ERROR_SUCCESS ) {
        SetLastError( status );
    }

    return(resid);

} // MyOpen



VOID
WINAPI
MyClose(
    IN RESID ResourceId
    )

/*++

Routine Description:

    Close routine for Ê÷ resources.

    Close the specified resource and deallocate all structures, etc.,
    allocated in the Open call. If the resource is not in the offline state,
    then the resource should be taken offline (by calling Terminate) before
    the close operation is performed.

Arguments:

    ResourceId - Supplies the RESID of the resource to close.

Return Value:

    None.

--*/

{
    PMY_RESOURCE resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT( "My: Close request for a nonexistent resource id %u\n",
                   ResourceId );
        return;
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Close resource sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return;
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"Close request.\n" );
#endif

    //
    // Close the Parameters key.
    //

    if ( resourceEntry->ParametersKey ) {
        ClusterRegCloseKey( resourceEntry->ParametersKey );
    }

    //
    // Deallocate the resource entry.
    //

    // ADDPARAM: Add new parameters here.

    LocalFree( resourceEntry->ResourceName );
    LocalFree( resourceEntry );

} // MyClose



DWORD
WINAPI
MyOnline(
    IN RESID ResourceId,
    IN OUT PHANDLE EventHandle
    )

/*++

Routine Description:

    Online routine for Ê÷ resources.

    Bring the specified resource online (available for use). The resource
    DLL should attempt to arbitrate for the resource if it is present on a
    shared medium, like a shared SCSI bus.

Arguments:

    ResourceId - Supplies the resource id for the resource to be brought 
        online (available for use).

    EventHandle - Returns a signalable handle that is signaled when the 
        resource DLL detects a failure on the resource. This argument is 
        NULL on input, and the resource DLL returns NULL if asynchronous 
        notification of failures is not supported, otherwise this must be 
        the address of a handle that is signaled on resource failures.

Return Value:

    ERROR_SUCCESS - The operation was successful, and the resource is now 
        online.

    ERROR_RESOURCE_NOT_FOUND - RESID is not valid.

    ERROR_RESOURCE_NOT_AVAILABLE - If the resource was arbitrated with some 
        other systems and one of the other systems won the arbitration.

    ERROR_IO_PENDING - The request is pending, a thread has been activated 
        to process the online request. The thread that is processing the 
        online request will periodically report status by calling the 
        SetResourceStatus callback method, until the resource is placed into 
        the ClusterResourceOnline state (or the resource monitor decides to 
        timeout the online request and Terminate the resource. This pending 
        timeout value is settable and has a default value of 3 minutes.).

    Win32 error code - The operation failed.

--*/

{
    PMY_RESOURCE resourceEntry = NULL;
    DWORD               status;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT( "Ê÷: Online request for a nonexistent resource id %u.\n",
                   ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Online service sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"Online request.\n" );
#endif

    resourceEntry->State = ClusterResourceOffline;
    ClusWorkerTerminate( &resourceEntry->OnlineThread );
    status = ClusWorkerCreate( &resourceEntry->OnlineThread,
                               (PWORKER_START_ROUTINE)MyOnlineThread,
                               resourceEntry );
    if ( status != ERROR_SUCCESS ) {
        resourceEntry->State = ClusterResourceFailed;
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Online: Unable to start thread, status %1!u!.\n",
            status
            );
    } else {
        status = ERROR_IO_PENDING;
    }

    return(status);

} // MyOnline



DWORD
WINAPI
MyOnlineThread(
    PCLUS_WORKER WorkerPtr,
    IN PMY_RESOURCE ResourceEntry
    )

/*++

Routine Description:

    Worker function which brings a resource from the resource table online.
    This function is executed in a separate thread.

Arguments:

    WorkerPtr - Supplies the worker structure

    ResourceEntry - A pointer to the MY_RESOURCE block for this resource.

Returns:

    ERROR_SUCCESS - The operation completed successfully.
    
    Win32 error code - The operation failed.

--*/

{
    RESOURCE_STATUS     resourceStatus;
    DWORD               status = ERROR_SUCCESS;

    ResUtilInitializeResourceStatus( &resourceStatus );

    resourceStatus.ResourceState = ClusterResourceFailed;
    resourceStatus.WaitHint = 0;
    resourceStatus.CheckPoint = 1;

    //
    // Bring the resource online.
    //
    // TODO: Add code to bring your resource online.

// exit:
    if ( status != ERROR_SUCCESS ) {
        (g_LogEvent)(
            ResourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Error %1!u! bringing resource online.\n",
            status );
    } else {
        resourceStatus.ResourceState = ClusterResourceOnline;
    }

    // _ASSERTE(g_SetResourceStatus != NULL);
    g_SetResourceStatus( ResourceEntry->ResourceHandle, &resourceStatus );
    ResourceEntry->State = resourceStatus.ResourceState;

    return(status);

} // MyOnlineThread



DWORD
WINAPI
MyOffline(
    IN RESID ResourceId
    )

/*++

Routine Description:

    Offline routine for Ê÷ resources.

    Take the specified resource offline gracefully (unavailable for use).  
    Wait for any cleanup operations to complete before returning.

Arguments:

    ResourceId - Supplies the resource id for the resource to be shutdown 
        gracefully.

Return Value:

    ERROR_SUCCESS - The request completed successfully and the resource is 
        offline.

    ERROR_RESOURCE_NOT_FOUND - RESID is not valid.

    ERROR_IO_PENDING - The request is still pending, a thread has been 
        activated to process the offline request. The thread that is 
        processing the offline will periodically report status by calling 
        the SetResourceStatus callback method, until the resource is placed 
        into the ClusterResourceOffline state (or the resource monitor decides 
        to timeout the offline request and Terminate the resource).
    
    Win32 error code - Will cause the resource monitor to log an event and 
        call the Terminate routine.

--*/

{
    PMY_RESOURCE resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT( "Ê÷: Offline request for a nonexistent resource id %u\n",
            ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Offline resource sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"Offline request.\n" );
#endif

    // TODO: Offline code

    // NOTE: Offline should try to shut the resource down gracefully, whereas
    // Terminate must shut the resource down immediately. If there are no
    // differences between a graceful shut down and an immediate shut down,
    // Terminate can be called for Offline, as it is below.  However, if there
    // are differences, replace the call to Terminate below with your graceful
    // shutdown code.

    //
    // Terminate the resource.
    //
    return MyDoTerminate( resourceEntry );

} // MyOffline



VOID
WINAPI
MyTerminate(
    IN RESID ResourceId
    )

/*++

Routine Description:

    Terminate routine for Ê÷ resources.

    Take the specified resource offline immediately (the resource is
    unavailable for use).

Arguments:

    ResourceId - Supplies the resource id for the resource to be brought 
        offline.

Return Value:

    None.

--*/

{
    PMY_RESOURCE resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT( "Ê÷: Terminate request for a nonexistent resource id %u\n",
            ResourceId );
        return;
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"Terminate resource sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return;
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"Terminate request.\n" );
#endif

    //
    // Terminate the resource.
    //
    MyDoTerminate( resourceEntry );
    resourceEntry->State = ClusterResourceOffline;

} // MyTerminate



DWORD
MyDoTerminate(
    IN PMY_RESOURCE ResourceEntry
    )

/*++

Routine Description:

    Do the actual Terminate work for Ê÷ resources.

Arguments:

    ResourceEntry - Supplies resource entry for resource to be terminated

Return Value:

    ERROR_SUCCESS - The request completed successfully and the resource is 
        offline.

    Win32 error code - Will cause the resource monitor to log an event and 
        call the Terminate routine.

--*/

{
    DWORD       status = ERROR_SUCCESS;

    //
    // Kill off any pending threads.
    //
    ClusWorkerTerminate( &ResourceEntry->OnlineThread );

    //
    // Terminate the resource.
    //
    // TODO: Add code to terminate your resource.
    if ( status == ERROR_SUCCESS ) {
        ResourceEntry->State = ClusterResourceOffline;
    }

    return(status);

} // MyDoTerminate



BOOL
WINAPI
MyLooksAlive(
    IN RESID ResourceId
    )

/*++

Routine Description:

    LooksAlive routine for Ê÷ resources.

    Perform a quick check to determine if the specified resource is probably
    online (available for use).  This call should not block for more than
    300 ms, preferably less than 50 ms.

Arguments:

    ResourceId - Supplies the resource id for the resource to polled.

Return Value:

    TRUE - The specified resource is probably online and available for use.

    FALSE - The specified resource is not functioning normally.

--*/

{
    PMY_RESOURCE  resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT("Ê÷: LooksAlive request for a nonexistent resource id %u\n",
            ResourceId );
        return(FALSE);
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"LooksAlive sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return(FALSE);
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"LooksAlive request.\n" );
#endif

    // TODO: LooksAlive code

    // NOTE: LooksAlive should be a quick check to see if the resource is
    // available or not, whereas IsAlive should be a thorough check.  If
    // there are no differences between a quick check and a thorough check,
    // IsAlive can be called for LooksAlive, as it is below.  However, if there
    // are differences, replace the call to IsAlive below with your quick
    // check code.

    //
    // Check to see if the resource is alive.
    //
    return(MyCheckIsAlive( resourceEntry ));

} // MyLooksAlive



BOOL
WINAPI
MyIsAlive(
    IN RESID ResourceId
    )

/*++

Routine Description:

    IsAlive routine for Ê÷ resources.

    Perform a thorough check to determine if the specified resource is online
    (available for use). This call should not block for more than 400 ms,
    preferably less than 100 ms.

Arguments:

    ResourceId - Supplies the resource id for the resource to polled.

Return Value:

    TRUE - The specified resource is online and functioning normally.

    FALSE - The specified resource is not functioning normally.

--*/

{
    PMY_RESOURCE  resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT("Ê÷: IsAlive request for a nonexistent resource id %u\n",
            ResourceId );
        return(FALSE);
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"IsAlive sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return(FALSE);
    }

#ifdef LOG_VERBOSE
    (g_LogEvent)(
        resourceEntry->ResourceHandle,
        LOG_INFORMATION,
        L"IsAlive request.\n" );
#endif

    //
    // Check to see if the resource is alive.
    //
    return(MyCheckIsAlive( resourceEntry ));

} // MyIsAlive



BOOL
MyCheckIsAlive(
    IN PMY_RESOURCE ResourceEntry
    )

/*++

Routine Description:

    Check to see if the resource is alive for Ê÷ resources.

Arguments:

    ResourceEntry - Supplies the resource entry for the resource to polled.

Return Value:

    TRUE - The specified resource is online and functioning normally.

    FALSE - The specified resource is not functioning normally.

--*/

{
    //
    // Check to see if the resource is alive.
    //
    // TODO: Add code to determine if your resource is alive.

    return(TRUE);

} // MyCheckIsAlive



DWORD
WINAPI
MyResourceControl(
    IN RESID ResourceId,
    IN DWORD ControlCode,
    IN PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned
    )

/*++

Routine Description:

    ResourceControl routine for Ê÷ resources.

    Perform the control request specified by ControlCode on the specified
    resource.

Arguments:

    ResourceId - Supplies the resource id for the specific resource.

    ControlCode - Supplies the control code that defines the action
        to be performed.

    InBuffer - Supplies a pointer to a buffer containing input data.

    InBufferSize - Supplies the size, in bytes, of the data pointed
        to by InBuffer.

    OutBuffer - Supplies a pointer to the output buffer to be filled in.

    OutBufferSize - Supplies the size, in bytes, of the available space
        pointed to by OutBuffer.

    BytesReturned - Returns the number of bytes of OutBuffer actually
        filled in by the resource. If OutBuffer is too small, BytesReturned
        contains the total number of bytes for the operation to succeed.

Return Value:

    ERROR_SUCCESS - The function completed successfully.

    ERROR_RESOURCE_NOT_FOUND - RESID is not valid.

    ERROR_INVALID_FUNCTION - The requested control code is not supported.
        In some cases, this allows the cluster software to perform the work.

    Win32 error code - The function failed.

--*/

{
    DWORD               status;
    PMY_RESOURCE  resourceEntry;

    resourceEntry = (PMY_RESOURCE)ResourceId;

    if ( resourceEntry == NULL ) {
        DBG_PRINT("Ê÷: ResourceControl request for a nonexistent resource id %u\n",
            ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

    if ( resourceEntry->ResId != ResourceId ) {
        (g_LogEvent)(
            resourceEntry->ResourceHandle,
            LOG_ERROR,
            L"ResourceControl sanity check failed! ResourceId = %1!u!.\n",
            ResourceId );
        return(ERROR_RESOURCE_NOT_FOUND);
    }

    switch ( ControlCode ) {

        case CLUSCTL_RESOURCE_UNKNOWN:
            *BytesReturned = 0;
            status = ERROR_SUCCESS;
            break;

        default:
            status = ERROR_INVALID_FUNCTION;
            break;
    }

    return(status);

} // MyResourceControl


//***********************************************************
//
// Define Function Table
//
//***********************************************************

CLRES_V1_FUNCTION_TABLE( g_MyFunctionTable,     // Name
                         CLRES_VERSION_V1_00,         // Version
                         My,                    // Prefix
                         NULL,                        // Arbitrate
                         NULL,                        // Release
                         MyResourceControl,     // ResControl
                         NULL);                       // ResTypeControl
