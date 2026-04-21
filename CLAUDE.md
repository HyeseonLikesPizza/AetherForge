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
main   ← 항상 빌드 가능 + PIE 동작. 마일스톤에만 merge, 태그 찍음
└── dev   ← 통합 브랜치. 모든 feature의 베이스이자 merge 대상
    ├── feature/*  ← 새 기능
    ├── fix/*      ← 버그 수정
    ├── chore/*    ← 빌드/설정/gitignore 등
    └── wip/*      ← 실험 (merge 안 할 수도 있음)
```

### 절대 규칙 (어기면 히스토리 꼬임)

1. **모든 작업 브랜치는 `dev`에서 분기한다.** feature → feature 분기/merge 금지.
2. **`main`에 직접 커밋 금지.** dev → main merge만 허용.
3. **feature → dev merge는 `--no-ff` 필수.** fast-forward는 feature 경계 유실.
4. **공유 브랜치(dev/main)에 rebase/force push 금지.** 로컬 feature만 rebase 허용.
5. **한 브랜치 = 한 목적.** 기능 + 버그 + 리팩토링 섞지 않는다.

### 표준 플로우

**새 작업 시작:**
```bash
git checkout dev && git pull
git checkout -b feature/<목적>
```

**feature → dev merge (빌드 + PIE 확인 후):**
```bash
git checkout dev
git merge --no-ff feature/<목적>
git branch -d feature/<목적>
git push origin --delete feature/<목적>
```

**dev → main merge (플레이 가능한 마일스톤):**
```bash
git checkout main
git merge --no-ff dev
git tag v0.X-phaseN
git push origin main --tags
```

**feature 작업 중 dev가 앞서 나갔을 때:**
- 내 로컬 feature만 사용 중 → `git rebase dev` (히스토리 일직선)
- 이미 push되어 공유 중 → `git merge dev` (rebase는 히스토리 재작성이라 금지)

### 커밋 컨벤션
- `feat:` 새 기능/클래스 추가
- `fix:` 버그 수정
- `chore:` 빌드 설정, gitignore 등 코드 외 변경
- `refactor:` 기능 변경 없이 코드 정리
- `docs:` 문서만

### 브랜치 네이밍
- 소문자 + 하이픈 (`feature/gas-attributes`, `fix/asc-nullptr`)
- `refactoring/` 쓰지 않음 → `feature/` 또는 `fix/`에 흡수

### 판단 기준: 브랜치 조작 전 체크
- 사용자가 "feature A를 feature B에 merge" 같은 요청을 하면 → **먼저 왜 그러는지 확인하고 dev 경유 권장**
- `main`에 뭔가 누락돼 보여도 임의로 merge하지 않음 → 사용자 확인
- stash/untracked 파일이 있는데 checkout이 막히면 → `-f`는 사용자 승인 후에만

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
