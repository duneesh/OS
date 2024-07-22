#include <windows.h>
#include <stdio.h>

int main()
{
    HANDLE hMapFile;
    LPCTSTR pBuf;
    char buff[100];

    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        TEXT("Local\\MyFileMappingObject")
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter some data to write to shared memory\n");
    fgets(buff, sizeof(buff), stdin);

    CopyMemory((PVOID)pBuf, buff, (strlen(buff) * sizeof(char)));
    printf("You wrote: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

