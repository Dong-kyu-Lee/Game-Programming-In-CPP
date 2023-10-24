#include "Game.h"
#include "Actor.h"
#include "SDL_image.h"
#include <math.h>

const int thickness = 15;
const int paddleH = 100;

Game::Game() 
: mTicksCount(0)
, mIsRunning(true)
, mWindow(nullptr)
, mRenderer(nullptr)
, mUpdatingActors(false)
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

	if (IMG_Init(IMG_INIT_PNG) == 0) 
	{
		SDL_Log("Failed to create SDL image : %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::Shutdown()
{
	UnLoadData(); // Actor ��ü ����
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

	// mActors�� ��� ���͸� Update
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// ��� ������ ���͸� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}

	// ���� ���� ����
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors)
	{
		delete actor;
	}
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

void Game::AddActor(class Actor* actor)
{
	// ���Ͱ� ���� ���̶�� ��� ���Ϳ� �߰�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(class Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::LoadData()
{

}

void Game::UnLoadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

SDL_Texture* Game::GetTexture(std::string& fileName)
{
	SDL_Texture* text = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		text = iter->second;
	}
	else
	{
		// ���Ϸκ��� �ε�
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		// �ؽ��� ����
		text = SDL_CreateTextureFromSurface(mRenderer, surf);
		// SDL_Surface�� ����
		SDL_FreeSurface(surf);
		if (!text)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		// ���Ϸκ��� ������ �ؽ��ĸ� mTextures�� ����
		mTextures.emplace(fileName, text);
	}

	return text;
}