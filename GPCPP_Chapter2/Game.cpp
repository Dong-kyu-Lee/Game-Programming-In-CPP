#include "Game.h"
#include "Actor.h"
#include "Skull.h"
#include "SDL_image.h"
#include "SpriteComponent.h"
#include <math.h>
#include <algorithm>

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

	if (IMG_Init(IMG_INIT_PNG) == 0) 
	{
		SDL_Log("Failed to create SDL image : %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::Shutdown()
{
	UnLoadData(); // Actor 객체 해제
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

	mSkull->PressKeyboard(state);
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

	// mActors의 모든 액터를 Update
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// 대기 벡터의 액터를 mActors로 이동
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}

	// 죽은 액터 해제
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
	// 렌더링할 색상 지정
	SDL_SetRenderDrawColor(
		mRenderer, 0, 0, 255, 255 // R G B A
	);
	SDL_RenderClear(mRenderer); // 지정한 색상으로 후면 버퍼를 클리어함

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer); // 전면 버퍼와 후면 버퍼 교환
}

void Game::AddActor(class Actor* actor)
{
	// 액터가 갱신 중이라면 대기 벡터에 추가
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
	// 플레이어 로드
	mSkull = new Skull(this);
	mSkull->SetPosition(Vector2(100.0f, 384.0f));
	mSkull->SetScale(1.5f);
	// 배경 액터 로드

}

void Game::UnLoadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destory textures
	for (auto x : mTextures)
	{
		SDL_DestroyTexture(x.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* text = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		text = iter->second;
	}
	else
	{
		// 파일로부터 로딩
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		// 텍스쳐 생성
		text = SDL_CreateTextureFromSurface(mRenderer, surf);
		// SDL_Surface를 해제
		SDL_FreeSurface(surf);
		if (!text)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		// 파일로부터 가져온 텍스쳐를 mTextures에 저장
		mTextures.emplace(fileName, text);
	}

	return text;
}

// 그릴 스프라이트를 Game 객체의 sprte 벡터에 추가
void Game::AddSprite(SpriteComponent* sprite)
{
	// 정렬된 벡터에서 삽입해야 될 위치를 찾는다.
	// (자신보다 그리기 순서값이 큰(나중에 그려질) 최초 요소)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
