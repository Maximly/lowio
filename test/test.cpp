#include "windows.h"
#include "stdio.h"

int
main()
{
 HANDLE hDrv = CreateFile("\\\\.\\lowio.vxd",
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL, OPEN_EXISTING,
    FILE_FLAG_DELETE_ON_CLOSE, NULL);
 char p[10];
 gets(p);
 CloseHandle(hDrv);
 return 0;
}