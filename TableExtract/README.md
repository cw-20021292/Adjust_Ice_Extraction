# 얼음 추출 제어 개선 방안
## ICON-ICE-2KG 얼음 균등 배출 제어 시스템

---

## 1. 문제 정의

### 1.1 현상
- 얼음정수기에서 얼음을 자주 추출할 때 **얼음이 탱크 앞쪽으로 쏠리는 현상** 발생
- 앞쪽 얼음 더미 + 스크류 토출분이 중첩되어 **단계별(1~4단) 토출량 편차** 증가
- 특히 소량(1~2단) 반복 추출 시 오버/언더 발생 빈도 높음

### 1.2 목표
- **구조 변경 없이** 제어 로직만으로 해결
- 모터/도어/타이머 로직 조정
- 1~4단 단계별 일괄적이고 안정적인 얼음 추출량 확보

---

## 2. 제안 솔루션 개요

### 2.1 핵심 전략
1. **균등화 동작 (Equalization Drive)**: 추출 후 탱크 내 얼음 재배치
2. **적응형 토출량 제어 (Adaptive Dispensing)**: 앞쏠림 지수 기반 회전수 보정
3. **선택적 고급 제어**: 모터 전류/홀센서 활용 (하드웨어 가용 시)

### 2.2 제어 흐름도
```
[사용자 1~4단 선택]
    ↓
[F_front 업데이트 (쏠림 상태 반영)]
    ↓
[보정된 회전수 계산]
    ↓
[스크류 구동 → 얼음 토출]
    ↓
[균등화 동작 수행]
    ↓
[F_front 감소 처리]
```

---

## 3. 상세 구현 방안

### 3.1 균등화 동작 (Equalization Drive)

#### 3.1.1 목적
- 토출구 앞에 쌓인 얼음 더미를 무너뜨려 경사 완화
- 탱크 내부 얼음을 평평하게 재배치

#### 3.1.2 동작 시퀀스
```c
void Ice_Equalize_AfterDispense(void)
{
    // 1) 역방향 짧게 (되감기)
    Motor_SetDir(REVERSE);
    Motor_Run_ms(REV_TIME_MS);   // 권장: 150~400ms

    // 2) 저속 정방향 균등화 (토출구 닫힌 상태)
    Close_Ice_Door();            // 또는 Half_Open
    Motor_SetDir(FORWARD);
    Motor_SetSpeed(LOW_SPEED);   // 정격의 30~40%
    Motor_Run_ms(EQ_TIME_MS);    // 권장: 300~600ms
    Stop_Motor();
}
```

#### 3.1.3 파라미터 튜닝
| 파라미터 | 권장 범위 | 설명 |
|---------|----------|------|
| REV_TIME_MS | 150~400ms | 역방향 구동 시간 (너무 길면 소음 증가) |
| EQ_TIME_MS | 300~600ms | 저속 균등화 시간 (기구 특성에 따라 조정) |
| LOW_SPEED | 정격의 30~40% | 균등화 시 모터 속도 |

---

### 3.2 앞쏠림 지수 (F_front) 기반 적응형 제어

#### 3.2.1 F_front 정의
- **범위**: 0.0 ~ 1.0
- **의미**:
  - 0.0 = 얼음이 탱크 내 균일하게 분포
  - 1.0 = 얼음이 앞쪽으로 최대한 쏠린 상태

#### 3.2.2 F_front 업데이트 로직 (수정된 버전)

**? 잘못된 이전 모델:**
```c
// 3,4단에서 F_front 감소 - 논리적 오류!
case ICE_LEVEL_3: F_front -= 0.05f; break;
case ICE_LEVEL_4: F_front -= 0.08f; break;
```

**? 올바른 모델:**

**추출 동작 시 (모든 단계에서 F_front 증가)**
```c
void Update_FrontIndex_OnDispense(IceLevel level)
{
    // 모든 추출은 앞으로 쏠림을 증가시킴
    switch(level){
        case ICE_LEVEL_1: F_front += 0.10f; break;
        case ICE_LEVEL_2: F_front += 0.12f; break;
        case ICE_LEVEL_3: F_front += 0.15f; break;
        case ICE_LEVEL_4: F_front += 0.18f; break;
    }

    // 상한 제한
    if(F_front > 1.0f) F_front = 1.0f;
}
```

**평탄화 동작 시 (F_front 감소)**
```c
void Update_FrontIndex_OnEqualize(void)
{
    // 평탄화/교반 동작 1회 수행 시
    F_front -= 0.20f;   // 효과에 따라 튜닝
    if(F_front < 0.0f) F_front = 0.0f;
}
```

**시간 경과에 따른 자연 감소 (선택사항)**
```c
void Update_FrontIndex_OnTime(void)
{
    // 얼음 제조/낙하로 자연 분산 (30초마다 호출 등)
    F_front -= 0.01f;
    if(F_front < 0.0f) F_front = 0.0f;
}
```

#### 3.2.3 적응형 토출량 계산
```c
// 기준 회전수 (또는 시간) 테이블
const float base_cnt[4] = { N1, N2, N3, N4 };

float Get_Adjusted_Count(IceLevel level)
{
    float K = 0.12f;  // 앞쏠림 보정 게인 (튜닝 대상)
    int idx = level - 1;

    // 앞에 쏠려있을수록 회전수를 줄여서 과분출 상쇄
    float factor = 1.0f - (K * F_front);

    // 과도한 보정 방지
    if(factor < 0.85f) factor = 0.85f;
    if(factor > 1.05f) factor = 1.05f;

    return base_cnt[idx] * factor;
}
```

#### 3.2.4 EEPROM 저장 (선택사항)
```c
// F_front 값을 EEPROM에 주기적으로 저장하여
// 전원 차단 후에도 상태 유지
void Save_FrontIndex_ToEEPROM(void)
{
    uint8_t f_front_u8 = (uint8_t)(F_front * 100.0f);
    gu8_eeprom_wbuf[ADDR_F_FRONT] = f_front_u8;
    // EEPROM write 수행
}

void Load_FrontIndex_FromEEPROM(void)
{
    uint8_t f_front_u8 = gu8_eeprom_rbuf[ADDR_F_FRONT];
    if(f_front_u8 <= 100) {
        F_front = (float)f_front_u8 / 100.0f;
    } else {
        F_front = 0.0f; // 유효하지 않은 값이면 초기화
    }
}
```

---

### 3.3 전체 제어 시퀀스

```c
void Ice_Dispense_Control(IceLevel level)
{
    // 1. 현재 쏠림 상태 업데이트 (추출 전)
    Update_FrontIndex_OnDispense(level);

    // 2. 보정된 회전수 계산
    float cnt = Get_Adjusted_Count(level);

    // 3. 스크류 구동하여 얼음 토출
    Open_Ice_Door();
    Motor_SetDir(FORWARD);
    Motor_SetSpeed(NORMAL_SPEED);
    Motor_Run_Count(cnt);  // 또는 Motor_Run_ms()
    Close_Ice_Door();

    // 4. 균등화 동작 수행
    Ice_Equalize_AfterDispense();

    // 5. 평탄화 효과 반영
    Update_FrontIndex_OnEqualize();

    // 6. EEPROM 저장 (선택사항)
    Save_FrontIndex_ToEEPROM();
}
```

---

## 4. 고급 제어 (하드웨어 지원 시)

### 4.1 모터 전류 기반 얼음 공급 상태 감지

#### 4.1.1 원리
- 얼음이 많을수록 → 스크류 부하 증가 → 전류 ↑
- 얼음이 적을수록 → 스크류 부하 감소 → 전류 ↓

#### 4.1.2 구현
```c
float Get_IceSupplyFactor(void)
{
    // 토출 시작 후 초기 300ms 평균 전류 측정
    float I = Measure_MotorCurrent_Initial();

    if(I > I_REF_HIGH) return 0.95f;  // 공급 풍부 → 5% 감소
    if(I < I_REF_LOW)  return 1.05f;  // 공급 부족 → 5% 증가
    return 1.0f;
}

// 최종 토출량 계산 (이중 보정)
float cnt = base_cnt[idx] * factor_front * factor_supply;
```

### 4.2 홀센서 기반 정밀 제어
- 회전수를 직접 카운트하여 더 정확한 토출량 제어
- 모터 슬립이나 부하 변동에 강인함

---

## 5. 구현 시 주의사항

### 5.1 파라미터 튜닝
| 파라미터 | 역할 | 튜닝 방법 |
|---------|------|----------|
| REV_TIME_MS | 역회전 시간 | 실제 촬영으로 앞쪽 더미 무너짐 확인 |
| EQ_TIME_MS | 평탄화 시간 | DPP/LPP 샘플로 탱크 내부 균일도 측정 |
| K (보정 게인) | 쏠림 보정 강도 | 1~4단 각 10~20회 반복 시 ±5~10% 이내 목표 |
| F_front 증감량 | 쏠림 추적 민감도 | 실사용 패턴 데이터 기반 최적화 |

### 5.2 소음 및 내구성
- **역방향 구동**: 각도/시간을 과하게 잡지 않도록 (기어 충격)
- **저속 균등화**: 소음 테스트 필수 (야간 사용 고려)
- **반복 횟수**: 평탄화 동작이 너무 잦으면 부품 수명 저하

### 5.3 에러 핸들링
```c
// 모터 전류 이상 감지
if(Motor_Current > I_THRESHOLD_JAM) {
    Stop_Motor();
    Alarm_IceJam();  // 얼음 뭉침/걸림
}

// 얼음 부족 감지
if(Motor_Current < I_THRESHOLD_EMPTY && dispense_count > 3) {
    Warning_IceEmpty();  // 얼음 부족 경고
}
```

---

## 6. 테스트 시나리오

### 6.1 기본 기능 테스트
1. **1단 연속 추출 (20회)**
   - 목표: 각 회당 편차 ±10% 이내
   - 확인: F_front 증가 추이 및 보정 효과

2. **4단 연속 추출 (10회)**
   - 목표: 대용량 안정성 확인
   - 확인: 탱크 저수위 시 동작

3. **혼합 패턴 (1-2-3-4-1-2...)**
   - 목표: 실제 사용 패턴 모사
   - 확인: F_front 동적 변화 및 적응 성능

### 6.2 경계 조건 테스트
- 탱크 만량 상태에서 1단 추출
- 탱크 저수위 상태에서 4단 추출
- 전원 차단 후 F_front 복원 (EEPROM)

### 6.3 내구성 테스트
- 1000회 연속 추출 (소음, 발열, 부품 마모)
- 균등화 동작 10000회 (모터, 기어 수명)

---

## 7. 파일 구조 및 수정 대상

### 7.1 주요 수정 파일
```
Source/Ice_Mini/
├── ice_dispense_control.c     [신규] 메인 제어 로직
├── ice_equalize.c              [신규] 균등화 동작
├── valve_ice_screw.c           [수정] 스크류 모터 제어
├── M1_ice_dispense.c           [수정] 기존 토출 로직 통합
├── eeprom.c                    [수정] F_front 저장/로드
└── Global_Variable.h           [수정] F_front 변수 추가
```

### 7.2 전역 변수 추가
```c
// Global_Variable.h
static float F_front = 0.0f;           // 앞쏠림 지수 (0.0~1.0)

// 튜닝 파라미터
#define REV_TIME_MS          250       // 역회전 시간 (ms)
#define EQ_TIME_MS           500       // 균등화 시간 (ms)
#define LOW_SPEED            30        // 저속 균등화 속도 (%)
#define K_FRONT_GAIN         0.12f     // 앞쏠림 보정 게인

// F_front 증감량
#define F_INC_LEVEL1         0.10f
#define F_INC_LEVEL2         0.12f
#define F_INC_LEVEL3         0.15f
#define F_INC_LEVEL4         0.18f
#define F_DEC_EQUALIZE       0.20f
```

---

## 8. 향후 개선 방향

### 8.1 단기 (Phase 1)
- [ ] 기본 F_front 추적 및 보정 구현
- [ ] 균등화 동작 추가
- [ ] 1~4단 토출량 정확도 테스트

### 8.2 중기 (Phase 2)
- [ ] 모터 전류 센싱 통합
- [ ] 사용 패턴 학습 (1일 단위 통계)
- [ ] 시간대별 자동 평탄화 스케줄링

### 8.3 장기 (Phase 3)
- [ ] IoT 연동 (앱에서 토출량 통계 확인)
- [ ] AI 기반 사용 패턴 예측
- [ ] 자가 진단 기능 (얼음 뭉침, 부품 마모 예측)

---

## 9. 참고 자료

### 9.1 관련 문서
- `README.md`: 전체 프로젝트 개요
- `eeprom.c`: 데이터 저장 구조
- `M1_ice_dispense.c`: 기존 토출 로직

### 9.2 변수 명명 규칙 (본 프로젝트)
- `f_`: Flag 변수
- `gu8_`: Global Unsigned 8-bit
- `gu16_`: Global Unsigned 16-bit
- `F_`: 대문자 Flag (주요 상태)

### 9.3 연락처
- 작성자: [Cursor AI Assistant]
- 작성일: 2024-12-12
- 버전: v1.0

---

## 10. 라이센스 및 주의사항

- 본 문서는 ICON-ICE-2KG 제빙기 프로젝트 내부 자료임
- 외부 유출 금지
- 코드 수정 시 반드시 Korean (EUC-KR) 인코딩 사용
- 변경 사항은 주석에 날짜와 작성자 기록 필수

---

**END OF DOCUMENT**

