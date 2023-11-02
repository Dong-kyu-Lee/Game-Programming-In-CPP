#include "Game.h"
#include <math.h>

const int thickness = 15;
const int paddleH = 100;

Game::Game() : mPaddleDir(0), mTicksCount(0), mIsRunning(true), mWindow(nullptr), mRenderer(nullptr)
{

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

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

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

	// 패들의 움직임 입력
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame() 
{
	// 마지막 프레임 이후로 16ms가 지날 때까지 대기
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// delta time은 현재 프레임 tick값과 이전 프레임 tick값의 차다.
	// 차를 초 단위로 변환한다.
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// 다음 프레임을 위해 tick 값 갱신
	mTicksCount = SDL_GetTicks();

	// delta time을 최대 0.05초까지만 갖게 함
	if (deltaTime > 0.05f) deltaTime = 0.05f;

	// 패들의 움직임
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		// 패들의 경계값 확인
		if (mPaddlePos.y < (paddleH / 2 + thickness))
		{
			mPaddlePos.y = (paddleH / 2 + thickness);
		}
		else if (mPaddlePos.y > (768 - paddleH / 2 - thickness))
		{
			mPaddlePos.y = (768 - paddleH / 2 - thickness);
		}
	}

	// 공의 움직임
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		diff < paddleH / 2 &&
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		mBallVel.x < 0.0f
		)
	{
		mBallVel.x *= -1.0f;
	}
	// 공이 빠져나갔을 때(게임 오버일 때)
	if (mBallPos.x <= 0.0f)
	{
		mIsRunning = false;
	}
	// 공이 오른쪽 벽에 부딛혔을 때
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	// 공이 위쪽 벽에 부딛혔을 때
	else if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1.0f;
	}
	// 공이 아래쪽 벽에 부딛혔을 때
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1.0f;
	}
}

void Game::GenerateOutput() 
{
	// 렌더링할 색상 지정
	SDL_SetRenderDrawColor(
		mRenderer, 0, 0, 255, 255 // R G B A
	);
	SDL_RenderClear(mRenderer); // 지정한 색상으로 후면 버퍼를 클리어함

#pragma region Wall Rendering
	// 벽과 퐁 렌더링하기
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // 벽, 퐁 색상
	
	// SDL_Rect 구조체는 왼쪽 상단의 x,y좌표, 너비, 높이를 입력받는다.
	SDL_Rect wall{ 0,0,1024,thickness };
	SDL_RenderFillRect(mRenderer, &wall); // 위쪽 벽

	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall); // 아래쪽 벽

	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 768;
	SDL_RenderFillRect(mRenderer, &wall); // 오른쪽 벽
#pragma endregion

	SDL_Rect ball
	{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddle
	{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_RenderPresent(mRenderer); // 전면 버퍼와 후면 버퍼 교환
}