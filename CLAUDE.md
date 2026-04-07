# AetherForge - Claude 프로젝트 가이드

## 프로젝트 개요
- **엔진**: Unreal Engine 5.7
- **장르**: 3인칭 RPG
- **핵심 시스템**: GAS, 인벤토리, 멀티플레이
- **현재 단계**: Phase 1 (핵심 아키텍처) 진행 중

---

## 파일 저장 규칙

| 파일 종류 | 저장 경로 |
|-----------|-----------|
| Claude가 생성하는 .md 문서 | `AetherForge/AetherForge/` |
| 작업일지 | `AetherForge/AetherForge/작업일지.md` |
| 구현 플랜 | `AetherForge/AetherForge/` |

- 작업일지는 매 세션 종료 시 업데이트
- `AetherForge/AetherForge/` 폴더는 `.gitignore`로 git에 올라가지 않음

---

## Git 브랜치 전략

```
main   ← 항상 빌드 가능 + PIE 동작하는 상태만
└── dev  ← 평소 작업 베이스
    ├── feature/*  ← 새 기능
    ├── fix/*      ← 버그 수정
    └── wip/*      ← 실험적 시도 (merge 안 할 수도 있음)
```

- `refactoring/` 브랜치는 사용하지 않음 → `feature/` 또는 `fix/`에 흡수
- feature 완료 시 `dev`로 merge, 플레이 가능한 마일스톤 도달 시에만 `main`으로 merge

### 커밋 컨벤션
- `feat`: 새 기능/클래스 추가
- `fix`: 버그 수정
- `chore`: 빌드 설정, gitignore 등 코드 외 변경
- `refactor`: 기능 변경 없이 코드 정리

---

## 소스 폴더 구조

```
Source/AetherForge/
  Public/
    Framework/     <- AFGameMode, AFGameState, AFGameInstance
    Player/        <- AFPlayerController, AFPlayerState
    Character/     <- AFCharacter
    GAS/
      Attributes/  <- AFAttributeSet
      Abilities/   <- AFGameplayAbility 서브클래스
      Effects/     <- AFGameplayEffect 서브클래스
    Inventory/     <- AFInventoryComponent, AFItemDefinition
    UI/
    Data/
    Interface/
  Private/
    (Public 미러)
```

### Include 경로 형식
```cpp
#include "AetherForge/Public/폴더명/파일명.h"
// 예: #include "AetherForge/Public/Player/AFPlayerState.h"
```

---

## 핵심 아키텍처 규칙

### ASC 위치: 반드시 PlayerState에
```cpp
// AFPlayerState에 배치 — Character에 두면 안 됨
UPROPERTY(VisibleAnywhere)
TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
```
**이유:** Character는 죽으면 파괴/재생성됨 → ASC를 Character에 두면 리스폰 시 어빌리티 상태, 쿨다운, 이펙트 전부 초기화됨

### GameMode: AGameMode 상속 (AGameModeBase 아님)
멀티플레이에 필요한 Match State, 재접속 처리, 리스폰 딜레이 등이 AGameMode에만 있음

### ASC 초기화: 반드시 2곳에서 호출
```cpp
// 서버: PossessedBy
// 클라이언트: OnRep_PlayerState
PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
```

---

## 자주 실수하는 것들

1. **ASC를 Character에 배치** → 반드시 PlayerState에
2. **Character의 `OnRep_PlayerState`에서 `InitAbilityActorInfo` 누락** → 서버는 동작, 클라이언트 깨짐
3. **`AFInventoryComponent`에 `SetIsReplicatedByDefault(true)` 누락** → 컴파일 에러 없이 복제 안 됨
4. **`.gitignore`에 `AetherForge/` 앞 슬래시 누락** → `Source/AetherForge/`까지 ignore됨. 반드시 `/AetherForge/`로 작성

---

## 구현 단계 (Phase)

- [x] Phase 0: 프로젝트 기초 설정 (플러그인, Build.cs, 폴더 구조)
- [ ] Phase 1: 핵심 아키텍처 (GameMode, PlayerState, Character 등) ← 현재
- [ ] Phase 2: GAS 통합 (AttributeSet, GameplayAbility, GameplayEffect)
- [ ] Phase 3: 3인칭 캐릭터 + Enhanced Input
- [ ] Phase 4: 인벤토리 시스템
- [ ] Phase 5: 멀티플레이 기초

자세한 내용: `AetherForge/AetherForge/RPG_프로젝트_시작_플랜.md`
