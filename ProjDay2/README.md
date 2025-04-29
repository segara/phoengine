# Phoengine ProjDay2 프로젝트 문서

## 1. 프로젝트 개요

Phoengine ProjDay2는 크로스 플랫폼(Windows 및 macOS) 게임 엔진의 기초 구조를 구현한 프로젝트입니다. 이 프로젝트는 플랫폼별 창 관리 시스템을 제공하며, Windows에서는 Win32 API와 OpenGL을, macOS에서는 Cocoa와 Metal을 사용합니다.

## 2. 프로젝트 구조

```
ProjDay2/
├── CMakeLists.txt           # 프로젝트 빌드 설정
├── Dependency.cmake         # 외부 라이브러리 의존성 관리
└── src/
    ├── Game.cpp             # Windows용 게임 구현
    ├── Game.h               # 게임 클래스 선언
    ├── Game.mm              # macOS용 게임 구현
    ├── main.cpp             # Windows용 진입점
    ├── main.mm              # macOS용 진입점
    ├── Metal_osx/           # macOS 플랫폼 구현
    │   ├── include/
    │   │   └── Window/
    │   │       └── OWindow.h  # macOS 창 클래스 선언
    │   └── source/
    │       └── Window/
    │           └── OWindow.mm # macOS 창 클래스 구현
    └── Opengl_win/          # Windows 플랫폼 구현
        ├── include/
        │   └── Window/
        │       └── OWindow.h  # Windows 창 클래스 선언
        └── source/
            └── Window/
                └── OWindow.cpp # Windows 창 클래스 구현
```

## 3. 주요 클래스 및 구성 요소

### 3.1 Game 클래스

게임 애플리케이션의 핵심 클래스로, 게임 루프와 창 관리를 담당합니다.

```cpp
class Game {
public:
    Game();
    ~Game();
    void run();
    void quit();
private:
    bool m_isRunning = true;
    std::unique_ptr<OWindow> m_display;
};
```

#### 주요 메서드:

- **Game()**: 생성자. 창 객체를 초기화합니다.
- **~Game()**: 소멸자.
- **run()**: 메인 게임 루프를 실행합니다.
- **quit()**: 게임을 종료합니다.

### 3.2 OWindow 클래스

플랫폼별 창 관리를 담당하는 클래스입니다.

```cpp
class OWindow {
public:
    OWindow();
    ~OWindow();
private:
    void* m_handle = nullptr;
};
```

#### 플랫폼별 구현:

- **Windows (OWindow.cpp)**: Win32 API를 사용하여 창을 생성하고 관리합니다.
- **macOS (OWindow.mm)**: Cocoa 프레임워크를 사용하여 창을 생성하고 관리합니다.

## 4. 플랫폼별 구현 세부 사항

### 4.1 Windows 구현

#### 창 관리
- Win32 API를 사용하여 창을 생성합니다.
- `WndProc` 함수에서 창 메시지를 처리합니다.
- `WM_DESTROY`, `WM_CLOSE` 메시지를 통해 창 종료를 관리합니다.

#### 게임 루프
- `PeekMessageA`로 윈도우 메시지를 처리합니다.
- `Sleep(1)`로 CPU 사용량을 제한합니다.

```cpp
void Game::run() {
    while(m_isRunning) {
        MSG msg = {};
        if(PeekMessageA(&msg, NULL, NULL, NULL, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                m_isRunning = false;
                continue;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(1);
    }
}
```

### 4.2 macOS 구현

#### 창 관리
- Cocoa 프레임워크를 사용하여 NSWindow 객체를 생성합니다.
- `WindowDelegate`를 통해 창 이벤트를 처리합니다.
- `windowWillClose:` 메서드로 창 종료를 감지합니다.

#### 애플리케이션 설정
- NSApplication을 초기화하고 AppDelegate를 설정합니다.
- `applicationWillTerminate:` 메서드로 애플리케이션 종료를 처리합니다.

#### 게임 루프
- `nextEventMatchingMask:` 메서드로 이벤트를 처리합니다.
- `std::this_thread::sleep_for`로 CPU 사용량을 제한합니다.

```cpp
void Game::run() {
    while(m_isRunning) {
        NSEvent *event;
        while (event = [NSApp nextEventMatchingMask:NSEventMaskAny
                            untilDate: [NSDate distantPast]
                            inMode:NSDefaultRunLoopMode
                            dequeue:YES]) {
            [NSApp sendEvent:event];
            [NSApp updateWindows];
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
```

## 5. 빌드 시스템

프로젝트는 CMake를 사용하여 빌드됩니다. 플랫폼별 설정을 다음과 같이 관리합니다:

### 5.1 CMakeLists.txt

- 플랫폼 감지를 통한 조건부 빌드 설정:
  ```cmake
  IF (WIN32)
      # Windows 설정
  ELSEIF(APPLE)
      # macOS 설정
  ENDIF()
  ```

- 소스 파일 구성:
  ```cmake
  IF (WIN32)
      file(GLOB SOURCES "src/Opengl_win/source/Window/*.cpp" "src/main.cpp" "src/Game.cpp")
  ELSEIF(APPLE)
      file(GLOB SOURCES "src/Metal_osx/source/Window/*.mm" "src/main.mm" "src/Game.mm")
  ENDIF()
  ```

- 플랫폼별 포함 경로 설정:
  ```cmake
  IF (WIN32)
      target_include_directories(${PROJECT_NAME} PUBLIC "src/Opengl_win/include")
  ELSEIF(APPLE)
      target_include_directories(${PROJECT_NAME} PUBLIC "src/Metal_osx/include")
  ENDIF()
  ```

### 5.2 Dependency.cmake

외부 라이브러리 의존성을 관리합니다:

- Windows에서는 GLFW 의존성 추가:
  ```cmake
  IF (WIN32)
      # GLFW 설정
      ExternalProject_Add(
          dep_glfw
          GIT_REPOSITORY "https://github.com/glfw/glfw.git"
          GIT_TAG "3.3.2"
          # ...
      )
      set(DEP_LIST ${DEP_LIST} dep_glfw)
      set(DEP_LIBS ${DEP_LIBS} glfw3)
  ENDIF()
  ```

- macOS에서는 기본 프레임워크 사용:
  ```cmake
  # CMakeLists.txt에서 macOS 프레임워크 설정
  ELSEIF(APPLE)
      find_library(FOUNDATION_FRAMEWORK Foundation)
      find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
      find_library(APPKIT_FRAMEWORK AppKit)
      SET(XCODE_FRAMEWORK ${FOUNDATION_FRAMEWORK} ${CORE_FOUNDATION_FRAMEWORK} ${APPKIT_FRAMEWORK})
  ENDIF()
  ```

## 6. 구현 특징 및 제한 사항

### 6.1 크로스 플랫폼 지원
- 조건부 컴파일을 통해 Windows와 macOS를 지원합니다.
- 플랫폼별 코드가 별도 파일로 분리되어 있어 관리가 용이합니다.

### 6.2 현재 제한 사항
- 아직 실제 렌더링 코드가 구현되지 않았습니다.
- 입력 처리 시스템이 미흡합니다.
- 게임 루프가 최적화되지 않았습니다 (Sleep 사용).
- 플랫폼 추상화 레이어가 부족합니다.

### 6.3 게임 루프
- 단순한 메시지 처리 루프를 사용합니다.
- 고정 프레임 레이트나 델타 타임 기반 업데이트가 구현되지 않았습니다.

## 7. 개선 방향

### 7.1 아키텍처 개선
- 플랫폼 독립적인 인터페이스 도입:
  ```cpp
  class Window {
  public:
      virtual ~Window() = default;
      virtual void create(const char* title, int width, int height) = 0;
      virtual void update() = 0;
      virtual bool processEvents() = 0;
      
      static std::unique_ptr<Window> create();
  };
  ```

- 플랫폼별 구현 상속:
  ```cpp
  class WindowsWindow : public Window { /* ... */ };
  class MacOSWindow : public Window { /* ... */ };
  ```

### 7.2 게임 루프 개선
- 델타 타임 기반 업데이트 구현:
  ```cpp
  void Game::run() {
      auto lastTime = std::chrono::high_resolution_clock::now();
      
      while (m_isRunning) {
          auto currentTime = std::chrono::high_resolution_clock::now();
          float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
          lastTime = currentTime;
          
          processEvents();
          update(deltaTime);
          render();
      }
  }
  ```

### 7.3 렌더링 시스템
- 플랫폼 독립적인 렌더링 인터페이스 추가
- OpenGL과 Metal 추상화 계층 구현

### 7.4 입력 시스템
- 플랫폼 독립적인 입력 처리 시스템 구현
- 키보드, 마우스, 게임패드 지원

## 8. 사용 방법

### 8.1 필요 조건
- CMake 3.13 이상
- Windows: Visual Studio 2019 이상
- macOS: Xcode 11 이상
- Git (의존성 다운로드용)

### 8.2 빌드 방법

1. 저장소 클론:
   ```bash
   git clone <repository-url>
   cd ProjDay2
   ```

2. 빌드 디렉토리 생성:
   ```bash
   mkdir build
   cd build
   ```

3. CMake 구성:
   ```bash
   cmake ..
   ```

4. 빌드 실행:
   ```bash
   cmake --build .
   ```

5. 프로그램 실행:
   ```bash
   ./cmake_opengl_example    # 또는 빌드된 실행 파일 이름
   ```

## 9. 결론

Phoengine ProjDay2는 크로스 플랫폼 게임 엔진의 기초 구조를 제공합니다. 현재는 창 관리와 기본 게임 루프가 구현되어 있으며, 플랫폼별 코드가 분리되어 있어 확장이 용이합니다. 향후 렌더링 시스템, 입력 처리, 리소스 관리 등을 추가하여 완전한 게임 엔진으로 발전시킬 수 있습니다.