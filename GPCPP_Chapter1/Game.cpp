#include "Game.h"

Game::Game()
{
	mIsRunning = true;
	mWindow = nullptr;
	mRenderer = nullptr;
}

// 함수 초기화에 성공하면 true, 그렇지 않으면 false
bool Game::Initialize()
{
	// sdlResult가 0이 아니면 SDL 라이브러리 초기화 실패
	int sdlResult = SDL_Init(SDL_INIT_AUDIO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming In C++ (Chapter 1)", // 윈도우 제목
		100,	// 윈도우의 좌측 상단 x좌표
		100,	// 윈도우의 좌측 상단 y좌표
		1024,	// 윈도우 너비
		768,	// 윈도우 높이
		0);		// 플래그 (0은 어떠한 플래그도 설정되지 않음을 의미)
	
	// 플래그 예시
	// SDL_WINDOW_FULLSCREEN : 전체 화면 모드
	// SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_CreateWindow가 전달받은 너비, 높이는 무시하고 현재 데탑의 해상도로 전체화면 적용
	// SDL_WINDOW_OPENGL : OpenGL 그래픽스 라이브러리에 대한 지원 추가
	// SDL_WINDOW_RESIZABLE : 윈도우 창 크기 조절 가능

	if (!mWindow)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, // 렌더링을 위해 생성한 윈도우
		-1,			// SDL이 글카를 결정하라는 의미. 게임이 사용하는 윈도우가 여러개일 때 의미있음. 일반적으로 -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // 가속화된 렌더러 사용 여부(좋은 글카를 사용하는지) | VSYNC를 제공 여부
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer : %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow); // SDL_Window 객체 해제
	SDL_DestroyRenderer(mRenderer); // SDL_Renderer 객체 해제
	SDL_Quit(); // SDL 종료
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput(); // 키 입력 등의 input
		UpdateGame(); // 게임 상태 업데이트
		GenerateOutput(); // 업데이트 된 상태를 출력
	}
}

void Game::ProcessInput() 
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	// 현재 키보드 키들의 상태를 나타내는 변수
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// ESC 누르면 루프 종료
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame() {}

void Game::GenerateOutput() 
{
	// 렌더링할 색상 지정
	SDL_SetRenderDrawColor(
		mRenderer, 0, 0, 255, 255 // R G B A
	);
	SDL_RenderClear(mRenderer); // 지정한 색상으로 후면 버퍼를 클리어함
	SDL_RenderPresent(mRenderer); // 전면 버퍼와 후면 버퍼 교환
}