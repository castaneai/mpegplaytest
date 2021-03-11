#include <stdio.h>
#include <dshow.h>
#include <comutil.h>

int main(int argc, const char** argv)
{
	IGraphBuilder* pGraphBuilder;
	IMediaControl* pMediaControl;

	CoInitialize(NULL);

	CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC,
		IID_IGraphBuilder,
		(LPVOID*)&pGraphBuilder);

	pGraphBuilder->QueryInterface(IID_IMediaControl,
		(LPVOID*)&pMediaControl);

	if (argc < 2) {
		printf("Usage: ./mpegplaytest <file>\n");
		return 2;
	}
	BSTR file = _com_util::ConvertStringToBSTR(argv[1]);
	pMediaControl->RenderFile(file);

	pMediaControl->Run();

	MessageBoxA(NULL, "Block Execution", "Block", MB_OK);

	pMediaControl->Release();
	pGraphBuilder->Release();

	CoUninitialize();

	return 0;
}