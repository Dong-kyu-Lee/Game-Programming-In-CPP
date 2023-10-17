#include "Game.h"

const int thickness = 15;
const int paddleH = 100;

Game::Game()
{
	mIsRunning = true;
	mWindow = nullptr;
	mRenderer = nullptr;
	mPaddlePos = { 20, 768 / 2 };
	mBallPos = { 1024 / 2, 768 / 2 };
	mTicksCount = 0;
}

// �Լ� �ʱ�ȭ�� �����ϸ� true, �׷��� ������ false
bool Game::Initialize()
{
	// sdlResult�� 0�� �ƴϸ� SDL ���̺귯�� �ʱ�ȭ ����
	int sdlResult = SDL_Init(SDL_INIT_AUDIO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming In C++ (Chapter 1)", // ������ ����
		100,	// �������� ���� ��� x��ǥ
		100,	// �������� ���� ��� y��ǥ
		1024,	// ������ �ʺ�
		768,	// ������ ����
		0);		// �÷��� (0�� ��� �÷��׵� �������� ������ �ǹ�)
	
	// �÷��� ����
	// SDL_WINDOW_FULLSCREEN : ��ü ȭ�� ���
	// SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_CreateWindow�� ���޹��� �ʺ�, ���̴� �����ϰ� ���� ��ž�� �ػ󵵷� ��üȭ�� ����
	// SDL_WINDOW_OPENGL : OpenGL �׷��Ƚ� ���̺귯���� ���� ���� �߰�
	// SDL_WINDOW_RESIZABLE : ������ â ũ�� ���� ����

	if (!mWindow)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, // �������� ���� ������ ������
		-1,			// SDL�� ��ī�� �����϶�� �ǹ�. ������ ����ϴ� �����찡 �������� �� �ǹ�����. �Ϲ������� -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // ����ȭ�� ������ ��� ����(���� ��ī�� ����ϴ���) | VSYNC�� ���� ����
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
	SDL_DestroyWindow(mWindow); // SDL_Window ��ü ����
	SDL_DestroyRenderer(mRenderer); // SDL_Renderer ��ü ����
	SDL_Quit(); // SDL ����
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput(); // Ű �Է� ���� input
		UpdateGame(); // ���� ���� ������Ʈ
		GenerateOutput(); // ������Ʈ �� ���¸� ���
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

	// ���� Ű���� Ű���� ���¸� ��Ÿ���� ����
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// ESC ������ ���� ����
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame() 
{
	// ������ ������ ���ķ� 16ms�� ���� ������ ���
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// delta time�� ���� ������ tick���� ���� ������ tick���� ����.
	// ���� �� ������ ��ȯ�Ѵ�.
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// ���� �������� ���� tick �� ����
	mTicksCount = SDL_GetTicks();

	// delta time�� �ִ� 0.05�ʱ����� ���� ��
	if (deltaTime > 0.05f) deltaTime = 0.05f;
}

void Game::GenerateOutput() 
{
	// �������� ���� ����
	SDL_SetRenderDrawColor(
		mRenderer, 0, 0, 255, 255 // R G B A
	);
	SDL_RenderClear(mRenderer); // ������ �������� �ĸ� ���۸� Ŭ������

#pragma region Wall Rendering
	// ���� �� �������ϱ�
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // ��, �� ����
	
	// SDL_Rect ����ü�� ���� ����� x,y��ǥ, �ʺ�, ���̸� �Է¹޴´�.
	SDL_Rect wall{ 0,0,1024,thickness };
	SDL_RenderFillRect(mRenderer, &wall); // ���� ��

	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall); // �Ʒ��� ��

	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 768;
	SDL_RenderFillRect(mRenderer, &wall); // ������ ��
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

	SDL_RenderPresent(mRenderer); // ���� ���ۿ� �ĸ� ���� ��ȯ
}