# Phoengine 프로젝트 문서

## 프로젝트 개요

Phoengine은 OpenGL을 기반으로 한 간단한 게임 엔진 프로젝트입니다. Windows 플랫폼에서 기본적인 창 관리와 게임 루프를 구현하고 있으며, CMake를 사용하여 빌드 시스템을 관리합니다.

## 프로젝트 구조

```
ProjDay1/
├── CMakeLists.txt        # 프로젝트 빌드 설정
├── Dependency.cmake      # 외부 의존성 관리
└── src/                  # 소스 코드
    ├── Game.cpp          # 게임 클래스 구현
    ├── Game.h            # 게임 클래스 선언
    ├── main.cpp          # 프로그램 진입점
    └── Opengl3d_win/     # 플랫폼 종속적인 코드
        ├── include/      # 헤더 파일
        │   └── Window/
        │       └── Window.h     # 창 관리 클래스 선언
        └── source/       # 소스 파일
            └── Window/
                └── Window.cpp   # 창 관리 클래스 구현
```

## 주요 클래스 및 기능

### Window 클래스

창 관리를 담당하는 클래스로, Windows API를 사용하여 창을 생성하고 관리합니다.

```cpp
class Window
{
public:
    Window();
    ~Window();
    void onDestroy();
    bool isClosed();
private:
    void* m_handle = nullptr;
};
```

#### 주요 메서드

- **Window()**: 창을 생성하고 초기화합니다.
- **~Window()**: 창을 파괴합니다.
- **onDestroy()**: 창이 파괴될 때 호출되는 메서드입니다.
- **isClosed()**: 창이 닫혔는지 여부를 반환합니다.

### Game 클래스

게임의 메인 로직과 루프를 관리하는 클래스입니다.

```cpp
class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void quit();
    bool m_isRunning = true;
    std::unique_ptr<Window> m_display;
};
```

#### 주요 메서드

- **Game()**: 게임 객체를 초기화하고 창을 생성합니다.
- **~Game()**: 게임 객체를 정리합니다.
- **run()**: 게임의 메인 루프를 실행합니다.
- **quit()**: 게임을 종료합니다.

## 빌드 시스템

프로젝트는 CMake를 사용하여 빌드됩니다. 주요 빌드 설정은 다음과 같습니다:

### CMakeLists.txt

프로젝트의 빌드 구성을 정의합니다:

- C++17 표준 사용
- 창 속성 설정 (이름, 너비, 높이)
- 소스 및 헤더 파일 명시적 추가
- 의존성 관리
- Visual Studio에서 시작 프로젝트 설정

### Dependency.cmake

외부 라이브러리 의존성을 관리합니다:

- GLFW 라이브러리: 창 관리 및 입력 처리를 위한 크로스 플랫폼 라이브러리
- 외부 라이브러리의 설치 디렉토리 설정
- 헤더 및 라이브러리 경로 구성

## 프로그램 흐름

1. **초기화**: main.cpp에서 Game 객체 생성
2. **창 생성**: Game 생성자에서 Window 객체 생성
3. **게임 루프**: Game::run() 메서드에서 메시지 처리 및 게임 로직 실행
4. **종료**: 창이 닫히거나 게임이 종료되면 프로그램 종료

## Windows API 사용

프로젝트는 Windows API를 사용하여 창을 관리합니다:

- **RegisterClassEx**: 창 클래스 등록
- **CreateWindowEx**: 창 생성
- **ShowWindow/UpdateWindow**: 창 표시 및 업데이트
- **PeekMessageA/TranslateMessage/DispatchMessage**: 윈도우 메시지 처리
- **WndProc**: 윈도우 프로시저 함수로 메시지 처리

## 개선 가능한 부분

1. **플랫폼 독립성**: 현재는 Windows에 종속적입니다. GLFW를 직접 사용하여 크로스 플랫폼 지원을 개선할 수 있습니다.
2. **그래픽스 렌더링**: OpenGL 초기화 및 렌더링 코드가 아직 구현되지 않았습니다.
3. **게임 로직**: 현재는 기본적인 창 관리와 메시지 루프만 있으며, 실제 게임 로직이 없습니다.
4. **이벤트 시스템**: 키보드, 마우스 등의 입력 이벤트 처리 시스템이 필요합니다.
5. **타이밍 관리**: Sleep(1) 대신 더 정밀한 프레임 레이트 제어가 필요합니다.

## 사용 방법

### 필요 조건

- CMake 3.13 이상
- C++17 지원 컴파일러
- Git (의존성 다운로드용)

### 빌드 방법

1. 저장소 클론:
   ```
   git clone <저장소 URL>
   cd ProjDay1
   ```

2. 빌드 디렉토리 생성 및 CMake 구성:
   ```
   mkdir build
   cd build
   cmake ..
   ```

3. 프로젝트 빌드:
   ```
   cmake --build .
   ```

4. 실행:
   ```
   ./phoengine
   ```

## 결론

Phoengine은 기본적인 창 관리와 게임 루프를 구현한 간단한 게임 엔진 프로젝트입니다. 현재는 최소한의 기능만 구현되어 있으며, 그래픽스 렌더링, 입력 처리, 게임 로직 등의 기능을 추가하여 발전시킬 수 있습니다.