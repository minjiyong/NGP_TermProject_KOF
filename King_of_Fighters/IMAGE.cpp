#include "image.h"

IMAGE::IMAGE() {};
IMAGE::~IMAGE() {};

void IMAGE::SetImage(const wchar_t* filename, int left, int top, int right, int bottom) {
    // 1. 이미지가 이미 로드되어 있다면 해제 (재사용 시 안전장치)
    if (!_img.IsNull()) {
        _img.Destroy();
    }

    // 2. 로딩 시도 및 결과 확인
    HRESULT hResult = _img.Load(filename);

    // 3. 실패 시 경고창 띄우기 (디버깅용)
    if (FAILED(hResult)) {
        std::wstring errorMsg = L"이미지 로드 실패: ";
        errorMsg += filename;
        MessageBox(NULL, errorMsg.c_str(), L"오류", MB_OK | MB_ICONERROR);
        return; // 더 이상 진행하지 않고 종료
    }

    // 4. 성공했을 때만 정보 설정
    _width = _img.GetWidth();
    _height = _img.GetHeight();

    // 비트맵 핸들이 제대로 생성되었는지 이중 체크
    if ((HBITMAP)_img == NULL) {
        MessageBox(NULL, L"핸들값 NULL 오류", L"오류", MB_OK);
    }

    _left = left;
    _top = top;
    _right = right;
    _bottom = bottom;

    // WinMain 환경에서는 std::cout이 안 보일 수 있으니 OutputDebugString 권장
    OutputDebugString(L"이미지 로딩 성공\n");
}
void IMAGE::InitImage(const wchar_t* action, const int num) {
	//wchar_t fileName = L"Chin Gentsai_"+ std::to_wstring(num) + std::to_wstring(num) + L".png";
	//_img.Load(&fileName);
}