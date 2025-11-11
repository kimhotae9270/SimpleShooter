# 🎯 Simple Shooter (Unreal Engine 5 C++)

플레이어와 AI가 서로 총격전을 벌이는 언리얼 C++ 기반 서바이벌 슈팅 게임입니다.  
Behavior Tree와 Blackboard를 이용한 AI, 라인트레이스 총기 시스템, 체력/사망 판정,  
그리고 승패 화면/자동 재시작 기능을 포함합니다.

---

## ✨ 주요 기능

- **플레이어 캐릭터**: 이동·점프·조준·사격, 피격 시 체력 감소 및 사망 처리.  
- **총기 시스템**: 라인트레이스로 피격 판정, 머즐 플래시·발사음·피격 이펙트.  
- **AI 적 캐릭터**: Behavior Tree + Blackboard 조합으로 시야 기반 추적 및 자동 사격.  
- **게임 모드**: 모든 AI 사망 시 승리, 플레이어 사망 시 패배.  
- **UI/HUD**: 시작 시 HUD, 종료 시 승리/패배 위젯 및 타이머 기반 재시작.  
- **Blueprint 통합**:  
  - `BT_EnemyAI.uasset` — AI의 의사결정 플로우  
  - `BB_EnemyAI.uasset` — 타깃/위치 저장용 블랙보드  
  - `BP_ShooterAICharacter.uasset` — AI 캐릭터 블루프린트

---

## 🧩 클래스 구조 요약
```markdown
C++ Source/
├─ SimpleShooter.cpp                      # 메인 모듈 초기화 (IMPLEMENT_PRIMARY_GAME_MODULE)
├─ SimpleShooterGameModeBase.cpp          # 기본 게임 모드, PawnKilled 이벤트 처리 준비
│
├─ ShooterCharacter.cpp                   # 플레이어 캐릭터: 입력, 체력, 사격, 사망 처리
├─ Gun.cpp                                # 총기 액터: 라인트레이스, 데미지, 이펙트/사운드
│
├─ ShooterAIController.cpp                # AI 컨트롤러: BT 실행, 플레이어 추적
│  ├─ BTService_PlayerLocation.cpp        # 플레이어 위치 벡터 업데이트
│  ├─ BTService_PlayerLocationIfSeen.cpp  # 시야 확보 시 타깃 설정 / 미확보 시 클리어
│  ├─ BTTask_Shoot.cpp                    # Shoot() 실행 태스크
│  └─ BTTask_ClearBlackboardValue.cpp     # 블랙보드 키 클리어
│
├─ KillEmAllGameMode.cpp                  # 라운드 승/패 판정, 게임 종료 처리
├─ ShooterPlayerController.cpp            # HUD 표시, 승/패 위젯, 재시작 타이머
├─ MyPawn.cpp                             # 테스트용 기본 Pawn
└─ 기타: BehaviorTree / Blackboard / Blueprint 에셋 3종 포함
```

---

## 🎮 조작법 (기본 매핑)

| 동작 | 입력 |
|------|------|
| 전진/후진 | `MoveForward` 축 (W / S) |
| 좌우 이동 | `MoveRight` 축 (A / D) |
| 시점 회전 | `LookUp`, `LookRight` |
| 점프 | `Jump` 액션 |
| 사격 | `Shoot` 액션 |

> `AShooterCharacter::SetupPlayerInputComponent()` 내에 매핑 정의됨.  
> 사격 시 `Shoot()` → `AGun::PullTrigger()` 호출.

---

## 🧠 AI Behavior Tree 구조

| 구성요소 | 설명 |
|----------|------|
| **BT_EnemyAI.uasset** | 메인 트리: 서비스와 태스크로 AI 의사결정 구성 |
| **BB_EnemyAI.uasset** | 블랙보드 데이터: `PlayerLocation`, `StartLocation`, `TargetActor` 등 |
| **UBTService_PlayerLocation** | 플레이어의 위치를 지속적으로 추적 (Vector 타입 키) |
| **UBTService_PlayerLocationIfSeen** | 시야 내 플레이어를 TargetActor(Object)로 설정, 놓치면 클리어 |
| **UBTTask_Shoot** | 컨트롤 중인 Pawn의 `Shoot()` 호출 |
| **UBTTask_ClearBlackboardValue** | 특정 키 값 제거 |

> AI는 시야(LineOfSight)에 따라 TargetActor를 업데이트하며, 사정거리 내에서 Shoot 태스크를 수행합니다.

---

## ⚙️ 게임 로직 플로우

1. **게임 시작**  
   - `SimpleShooter` 모듈 초기화:contentReference[oaicite:2]{index=2}  
   - GameMode는 `ASimpleShooterGameModeBase` 또는 `AKillEmAllGameMode`로 설정됨.  

2. **전투**  
   - 플레이어/AI는 각각 총을 발사하며 라인트레이스로 데미지 계산.  
   - `UGameplayStatics::ApplyPointDamage()` 호출 후 `TakeDamage()` 오버라이드에서 체력 감소.  

3. **사망 판정**  
   - 체력이 0 이하 → `GameMode->PawnKilled()` 호출:contentReference[oaicite:3]{index=3}  
   - 플레이어 사망 → 패배 / 모든 AI 사망 → 승리.  

4. **UI 표시 및 재시작**  

   - `ShooterPlayerController`가 승패 위젯 표시.  
   - 일정 시간 후 `RestartLevel()` 호출로 재시작.

---

## 🏗️ 빌드 및 실행
<p align="center">
  <img src="https://github.com/user-attachments/assets/4104f6d4-6f65-4f48-a9b8-956033c8da17" alt="myrecord_small" width="600"/>
</p>

