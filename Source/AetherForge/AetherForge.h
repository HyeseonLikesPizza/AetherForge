
#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAF, Log, All);

// 호출 위치
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

// 호출 위치가 포함된 로그
#define PRINTINFO() UE_LOG(LogAF, Warning, TEXT("%s"), *CALLINFO)

// 호출 위치가 포함된 포매팅
#define PRINTLOG(fmt, ...) \
UE_LOG(LogAF, Log, TEXT("%s : %s"), *CALLINFO, *FString::Printf(fmt, ##__VA_ARGS__))