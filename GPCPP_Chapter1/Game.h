#pragma once
#include <SDL.h>

// x, y 좌표를 가지고 있는 구조체
struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	// 게임 초기화
	bool Initialize();
	// 게임이 끝나기 전까지 게임 루프를 실행
	void RunLoop();
	// 게임 종료
	void Shutdown();

private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	int mPaddleDir;
	Vector2 mBallVel;
	Vector2 mPaddlePos;
	Vector2 mBallPos;

	// SDL이 생성한 윈도우
	SDL_Window* mWindow;
	// 게임이 계속 실행돼야 하는지를 판단
	bool mIsRunning;
	// 그래픽으로 뭔가를 그릴 때 쓰는 객체
	SDL_Renderer* mRenderer;
	// delta time을 계산할 때 사용할 이전 프레임의 Tick값
	Uint32 mTicksCount;
};