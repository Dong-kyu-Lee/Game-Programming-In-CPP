#include "Game.h"

Game::Game()
{
	mIsRunning = true;
	mWindow = nullptr;
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

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow); // SDL_Window ��ü ����
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

void Game::UpdateGame() {}

void Game::GenerateOutput() {}