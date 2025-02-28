#pragma once
#include <iostream>
#include <io.h>

#include "EnginePath.h"

// 파일과 관련된 모든 기능은 여기에서 사용합니다.
// FIle 랩핑
// 코딩 애초에 잘못사용하기도 힘들게 짜는것이 베스트 입니다.
// 삭제
// 이동


const int MAXPATH = 256;

class UEngineFile : public UEnginePath
{
	// 하드코딩 
public:
	ENGINEAPI UEngineFile();
	// 생성체인
	ENGINEAPI UEngineFile(const std::string& _Path);
	ENGINEAPI UEngineFile(std::string_view _Path);
	ENGINEAPI UEngineFile(std::filesystem::path _Path);
	ENGINEAPI UEngineFile(const UEnginePath& _Path);
	ENGINEAPI ~UEngineFile();

	// Write
	ENGINEAPI void Write(class UEngineSerializer& _Ser);
	ENGINEAPI void Read(class UEngineSerializer& _Ser);

	ENGINEAPI void Write(const void* _Ptr, size_t _Size);
	ENGINEAPI void Read(void* _Ptr, size_t _Size);

	ENGINEAPI void FileOpen(const char* _Mode);
	void Close();

	int GetFileSize();

	ENGINEAPI std::string GetAllFileText();

	// 기능 클래스 랩핑
private:
	// 상수
	// _MAX_DIR 윈도우에 의존적인 프로그램
	FILE* File = nullptr;
};

