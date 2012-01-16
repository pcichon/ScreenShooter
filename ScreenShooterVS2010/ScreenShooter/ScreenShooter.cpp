#include <string>
#include<windows.h>
#include<winuser.h>

#include "ScreenShooter.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

extern "C"
{

FREObject getScreenShot(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
	{
		HDC hdcScr, hdcMem;
		HBITMAP hbmScr;
		RECT rc;

		HWND desktopWnd = GetDesktopWindow();
		GetWindowRect(desktopWnd, &rc);

		int iXRes,
			iYRes;

		iXRes = rc.right - rc.left;
		iYRes = rc.bottom - rc.top;

		hdcScr = GetDC(desktopWnd);
		hdcMem = CreateCompatibleDC(hdcScr);
		hbmScr = CreateCompatibleBitmap(hdcScr, iXRes, iYRes);

		if(hbmScr == NULL) return 0;
		SelectObject(hdcMem, hbmScr);
		BitBlt(hdcMem, 0, 0, iXRes, iYRes, hdcScr, rc.left, rc.top, SRCCOPY);

		MemoryStream^ stream = gcnew MemoryStream();

		Bitmap^ bitmap = Image::FromHbitmap((IntPtr)hbmScr);

		bitmap->Save(stream, ImageFormat::Png);

		array<Byte>^ raw = stream->ToArray();

		uint8_t* output = new uint8_t[iXRes * iYRes * 4];

		int outputSize = (int) stream->Length;

		Marshal::Copy(raw, 0, (IntPtr) output, outputSize);

		FREObject objectByteArray = argv[0];
		FREByteArray byteArray;

		FREObject length;
		
		FRENewObjectFromUint32(outputSize, &length);

		FRESetObjectProperty(objectByteArray, (const uint8_t*) "length", length, NULL);

		FREAcquireByteArray(objectByteArray, &byteArray);

		memcpy(byteArray.bytes, output, outputSize);

		FREReleaseByteArray(objectByteArray);

		stream->Close();
		
		ReleaseDC(0, hdcScr);
		ReleaseDC(0, hdcMem);
		delete output, stream, bitmap;

		return NULL;
	}


	void contextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctions, const FRENamedFunction** functions)
	{
		*numFunctions = 1;

		FRENamedFunction* func = (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*numFunctions));

		func[0].name = (const uint8_t*) "getScreenShot";
		func[0].functionData = NULL;
		func[0].function = &getScreenShot;

		*functions = func;
	}

	void contextFinalizer(FREContext ctx)
	{
		return;
	}

	void initializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer)
	{
		*ctxInitializer = &contextInitializer;
		*ctxFinalizer = &contextFinalizer;
	}

	void finalizer(void* extData)
	{
		return;
	}
}
