#include "Game.h"
#include <math.h>

const int thickness = 15;
const int paddleH = 100;

Game::Game() : mTicksCount(0), mIsRunning(true), mWindow(nullptr), mRenderer(nullptr)
{

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

	SDL_RenderPresent(mRenderer); // ���� ���ۿ� �ĸ� ���� ��ȯ
}