//
// monitor our memory usage and die when passing threshold.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#if defined(WIN32) || defined(WIN64) || defined(_WIN32)
#include <ntstatus.h>

// We need to prevent winnt.h from defining the core STATUS codes,
// otherwise they will conflict with what we're getting from ntstatus.h
#define UMDF_USING_NTSTATUS 1
#define WIN32_NO_STATUS     1

#endif



// use the portability work of cUrl: faster than writing our own header files...
#include "curl_setup.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>


#if !defined(WIN32) && !defined(WIN64)

int main(void) {

    return EXIT_SUCCESS;
}

#else

#if !defined(UNICODE)
#error "Compile in UNICODE mode!"
#endif

#define PSAPI_VERSION 2

#include <math.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <tchar.h>
#include <strsafe.h>
#include <eh.h>
#include <stdarg.h>
#include <winternl.h>
#include <winnt.h>


#ifndef MAX
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#endif


#define ASSERT(check)           \
if (!(check))                   \
{                               \
    ErrorExit(TEXT(#check));    \
}

#define VERIFY(check)           \
if (!(check))                   \
{                               \
    ErrorExit(TEXT(#check));    \
}


#define BUFSIZE 4096

static float round_nice(float v)
{
    float lg = log10f(v / 10.0f);
    float d = roundf(lg);
    float pw = powf(10.0f, d);
    float vi = v / pw;
    vi = roundf(vi);
    vi *= pw;
    return vi;
}

// Format a readable error message, display a message box,
// and exit from the application.
static void ErrorExit(const wchar_t * lpszFunction)
{
    LPTSTR lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((STRSAFE_LPWSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s\n"),
        lpszFunction, dw, lpMsgBuf);
    OutputDebugStringW((LPCTSTR)lpDisplayBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    //ExitProcess(1); <-- do NOT call ExitProcess but exit() instead so that our atexit handler will be called!
    exit(1);
}

static void printError(const wchar_t * msg)
{
    DWORD eNum;
    WCHAR sysMsg[256];

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        sysMsg, 256, NULL);

    // Display the message
    WCHAR m[2000];
    wsprintf(m, TEXT("WARNING: %s failed with error %d (%s)\n"), msg, eNum, sysMsg);
    OutputDebugStringW(m);

    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}

static void debugPrint(const wchar_t* msg, ...)
{
    va_list argptr;
    va_start(argptr, msg);

    wchar_t buf[4000];
    _vsntprintf(buf, sizeof(buf) / sizeof(buf[0]), msg, argptr);
    va_end(argptr);

    OutputDebugStringW(buf);
    _tprintf(TEXT("%s"), buf);
}

static size_t available_memory_size = 0;

const int DIV = 1024;
const float MDIV = DIV * DIV;
const float GDIV = DIV * MDIV;

static void showMemoryConsumption()
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS_EX pmc = { sizeof(pmc), 0 };

    hProcess = GetCurrentProcess();

    if (GetProcessMemoryInfo(hProcess, (PPROCESS_MEMORY_COUNTERS)&pmc, sizeof(pmc)))
    {
        debugPrint(L"\tPageFaultCount:             %8zu\n", (SIZE_T)pmc.PageFaultCount);
        debugPrint(L"\tPeakWorkingSetSize:         %8zu\n", pmc.PeakWorkingSetSize);
        debugPrint(L"\tWorkingSetSize:             %8zu\n", pmc.WorkingSetSize);
        debugPrint(L"\tQuotaPeakPagedPoolUsage:    %8zu\n", pmc.QuotaPeakPagedPoolUsage);
        debugPrint(L"\tQuotaPagedPoolUsage:        %8zu\n", pmc.QuotaPagedPoolUsage);
        debugPrint(L"\tQuotaPeakNonPagedPoolUsage: %8zu\n", pmc.QuotaPeakNonPagedPoolUsage);
        debugPrint(L"\tQuotaPeakNonPagedPoolUsage: %8zu\n", pmc.QuotaNonPagedPoolUsage);
        debugPrint(L"\tPagefileUsage:              %8zu\n", pmc.PagefileUsage);
        debugPrint(L"\tPeakPagefileUsage:          %8zu\n", pmc.PeakPagefileUsage);
        debugPrint(L"\tPrivateUsage:               %8zu\n", pmc.PrivateUsage);
    }
    else
    {
        ErrorExit(L"GetProcessMemoryInfo");
    }

    MEMORYSTATUSEX statex = { sizeof(statex), 0 };

    if (GlobalMemoryStatusEx(&statex))
    {
        if (!available_memory_size)
        {
            available_memory_size = statex.ullAvailPhys;
        }

        debugPrint(L"There is  % 8d percent of memory in use.\n", (int)statex.dwMemoryLoad);
        debugPrint(L"There are %8.1f total MB of physical memory.\n", (SIZE_T)statex.ullTotalPhys / MDIV);
        debugPrint(L"There are %8.1f free  MB of physical memory.\n", (SIZE_T)statex.ullAvailPhys / MDIV);
        debugPrint(L"There are %8.1f total MB of paging file.\n", (SIZE_T)statex.ullTotalPageFile / MDIV);
        debugPrint(L"There are %8.1f free  MB of paging file.\n", (SIZE_T)statex.ullAvailPageFile / MDIV);
        debugPrint(L"There are %8.1f total GB of virtual memory.\n", statex.ullTotalVirtual / GDIV);
        debugPrint(L"There are %8.1f free  GB of virtual memory.\n", statex.ullAvailVirtual / GDIV);
        // Show the amount of extended memory available.
        debugPrint(L"There are %8.1f free  MB of extended memory.\n", (SIZE_T)statex.ullAvailExtendedVirtual / MDIV);
    }
    else
    {
        ErrorExit(L"GlobalMemoryStatusEx");
    }

    unsigned int heap_count = 1;
    HANDLE heap_list[256];
    DWORD rv = GetProcessHeaps(heap_count, heap_list);
    if (rv == 0)
    {
        ErrorExit(L"GetProcessHeaps(1)");
    }
    if (rv > heap_count)
    {
        rv = GetProcessHeaps(sizeof(heap_list) / sizeof(heap_list[0]), heap_list);
        if (rv == 0)
        {
            ErrorExit(L"GetProcessHeaps(N)");
        }
        heap_count = rv;
    }

    HEAP_SUMMARY total_summary = { sizeof(total_summary) };

    for (unsigned int i = 0; i < heap_count; i++)
    {
        HEAP_SUMMARY summary = { sizeof(summary) };
        BOOL err = HeapSummary(heap_list[i], 0, &summary);
        // fix for the Win32 API documentation: turns out that HeapSummary returns 1, with GetLastError() set to S_OK, when it successfully filled the summary info struct.
        if (err != S_OK && GetLastError() != S_OK)
        {
            ErrorExit(L"HeapSummary");
        }

        total_summary.cbAllocated += summary.cbAllocated;
        total_summary.cbCommitted += summary.cbCommitted;
        total_summary.cbMaxReserve += summary.cbMaxReserve;
        total_summary.cbReserved += summary.cbReserved;
    }

    // perform some heuristics on the memory consumption to decide when to abort:
    if (statex.dwMemoryLoad > 90)
    {
        debugPrint(L"Aborting @ 90%% memory loading threshold.\n");
        ExitProcess(0);
    }
    if (pmc.WorkingSetSize >= 0.75 * statex.ullTotalPageFile)
    {
        debugPrint(L"Aborting @ 75%% of total page file consumed threshold.\n");
        ExitProcess(0);
    }
    if (pmc.WorkingSetSize >= 0.75 * statex.ullTotalPhys)
    {
        debugPrint(L"Aborting @ 75%% of total physical memory consumed threshold.\n");
        ExitProcess(0);
    }
    //auto totmem = total_summary.cbAllocated + total_summary.cbCommitted + total_summary.cbReserved;
    auto totmem = MAX(total_summary.cbReserved, pmc.WorkingSetSize);
    if (totmem >= 0.75 * statex.ullTotalPhys)
    {
        debugPrint(L"Aborting @ 75%% of total physical memory consumed threshold.\n");
        ExitProcess(0);
    }
    if (pmc.WorkingSetSize >= 0.75 * statex.ullTotalVirtual)
    {
        debugPrint(L"Aborting @ 75%% of total virtual memory space consumed threshold.\n");
        ExitProcess(0);
    }

    // --------------------------------------

    typedef __kernel_entry NTSTATUS
        NTAPI
        NtQuerySystemInformation_t(
            IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
            OUT PVOID SystemInformation,
            IN ULONG SystemInformationLength,
            OUT PULONG ReturnLength OPTIONAL
        );

    uint64_t memory_pressure = 0;
    HINSTANCE h = LoadLibrary(TEXT("ntdll.dll"));
    if (h != NULL)
    {
        NtQuerySystemInformation_t* qsi_f = (NtQuerySystemInformation_t*)GetProcAddress(h, "NtQuerySystemInformation");
        if (NULL != qsi_f)
        {
            ULONG siLength = 0;
            SYSTEM_PROCESS_INFORMATION *proc_infos = NULL;
            ULONG info_size = 1024 * sizeof(proc_infos[0]);
            NTSTATUS st;
            
            do {
                proc_infos = (SYSTEM_PROCESS_INFORMATION *)realloc(proc_infos, info_size);
                ASSERT(proc_infos != NULL);
                st = (*qsi_f)(SystemProcessInformation, proc_infos, info_size, &siLength);
                if (st == S_OK) 
                    break;
                
                if (st != STATUS_BUFFER_TOO_SMALL && st != STATUS_INFO_LENGTH_MISMATCH) 
                {
                    debugPrint(L"NtQuerySystemInformation failed with status code 0x%08lx.\n", (unsigned long)st);
                    ExitProcess(0);
                }

                info_size *= 2;
            } while (info_size <= 1e7);

            if (st == S_OK)
            {
                SYSTEM_PROCESS_INFORMATION* proc_info = proc_infos;
                
                for (;;)
                {
                    memory_pressure += proc_info->WorkingSetSize;

#if 0  // this code causes some obscure errors and crashes as we attempt to get info from various system/kernel process handles   :-S

                    HANDLE hProcess2 = proc_info->UniqueProcessId;
                    PROCESS_MEMORY_COUNTERS_EX pmc2 = { sizeof(pmc2), 0 };

                    if (GetProcessMemoryInfo(hProcess2, (PPROCESS_MEMORY_COUNTERS)&pmc2, sizeof(pmc2)))
                    {
                        debugPrint(L"\t + PageFaultCount:             %8zu\n", (SIZE_T)pmc2.PageFaultCount);
                        debugPrint(L"\t + PeakWorkingSetSize:         %8zu\n", pmc2.PeakWorkingSetSize);
                        debugPrint(L"\t + WorkingSetSize:             %8zu\n", pmc2.WorkingSetSize);
                        debugPrint(L"\t + QuotaPeakPagedPoolUsage:    %8zu\n", pmc2.QuotaPeakPagedPoolUsage);
                        debugPrint(L"\t + QuotaPagedPoolUsage:        %8zu\n", pmc2.QuotaPagedPoolUsage);
                        debugPrint(L"\t + QuotaPeakNonPagedPoolUsage: %8zu\n", pmc2.QuotaPeakNonPagedPoolUsage);
                        debugPrint(L"\t + QuotaPeakNonPagedPoolUsage: %8zu\n", pmc2.QuotaNonPagedPoolUsage);
                        debugPrint(L"\t + PagefileUsage:              %8zu\n", pmc2.PagefileUsage);
                        debugPrint(L"\t + PeakPagefileUsage:          %8zu\n", pmc2.PeakPagefileUsage);
                        debugPrint(L"\t + PrivateUsage:               %8zu\n", pmc2.PrivateUsage);
                    }
                    else
                    {
                        debugPrint(L"\t + WorkingSetSize:             %8zu\n", proc_info->WorkingSetSize);
                    }
#endif

                    if (proc_info->NextEntryOffset == 0)
                        break;

                    proc_info = (SYSTEM_PROCESS_INFORMATION * ) (((uint8_t *)proc_info) + proc_info->NextEntryOffset);
                }

                uint64_t est_memory_pressure = statex.ullTotalPhys - statex.ullAvailPhys;
                debugPrint(L"--> Netto global system memory pressure: %8.1f MB\n", memory_pressure / MDIV);
                debugPrint(L"--> Bruto global system memory pressure: %8.1f MB\n", est_memory_pressure / MDIV);
            }
            else 
            {
                debugPrint(L"NtQuerySystemInformation required too much memory to our taste. Terminating the test app.\n");
                ExitProcess(0);
            }

            free(proc_infos);
        }

        FreeLibrary(h);
    }
}

static void growHeapAndWatch(int n)
{
    const size_t AV_MEM_1PCT = (size_t)(round_nice(available_memory_size / MDIV / 100) * MDIV);
    const size_t CHUNKSIZE = MAX((size_t) 25e6, AV_MEM_1PCT);
    void* p = malloc(CHUNKSIZE);
    ++n;
    debugPrint(L"+ chunk %d @ size: %.0f MB\n", n, CHUNKSIZE / MDIV);
    showMemoryConsumption();
    if (!p)
    {
        debugPrint(L"# chunk alloc FAILED\n", n);
        ExitProcess(1);
    }

    // do a bit more alloc + free:
    if (n % 10 == 3)
    {
        void* m = malloc(4 * CHUNKSIZE);
        if (!m)
        {
            debugPrint(L"# special chunk alloc FAILED\n", n);
            ExitProcess(1);
        }
        free(p);
        free(m);
        debugPrint(L"+ special block %d\n", n);
        showMemoryConsumption();
    }

    // recurse to grow
    growHeapAndWatch(n);
}

int _tmain(int argc, TCHAR* argv[])
{
    debugPrint(TEXT("start exec...\n"));

    // https://docs.microsoft.com/en-us/windows/win32/psapi/collecting-memory-usage-information-for-a-process
    // https://docs.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa965225(v=vs.85)
    //
    showMemoryConsumption();

    growHeapAndWatch(0);
}

#endif

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
