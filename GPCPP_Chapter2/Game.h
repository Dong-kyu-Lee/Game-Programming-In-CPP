#pragma once
#include <SDL.h>
#include <vector>
#include <string>
#include <unordered_map>

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

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	SDL_Texture* GetTexture(const std::string& fileName);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

private:
	// 게임 루프를 위한 헬퍼 함수
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnLoadData();

	// SDL이 생성한 윈도우
	SDL_Window* mWindow;
	// 게임이 계속 실행돼야 하는지를 판단
	bool mIsRunning;
	// 그래픽으로 뭔가를 그릴 때 쓰는 객체
	SDL_Renderer* mRenderer;
	// delta time을 계산할 때 사용할 이전 프레임의 Tick값
	Uint32 mTicksCount;
	// 활성화된 액터
	std::vector<class Actor*> mActors;
	// 대기 중인 액터
	std::vector<class Actor*> mPendingActors;
	// 액터의 갱신(Update) 여부를 나타내는 변수
	bool mUpdatingActors;
	// 파일 이름(Key)과 텍스쳐(Value) 쌍을 저장한 맵
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	// 그릴 Sprite를 저장한 벡터
	std::vector<class SpriteComponent*> mSprites;

	// 플레이어 객체
	class Skull* mSkull;
};