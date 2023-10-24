#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>

class Game
{
public:
	Game();
	// ���� �ʱ�ȭ
	bool Initialize();
	// ������ ������ ������ ���� ������ ����
	void RunLoop();
	// ���� ����
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	SDL_Texture* GetTexture(std::string& fileName);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

private:
	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnLoadData();

	// SDL�� ������ ������
	SDL_Window* mWindow;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool mIsRunning;
	// �׷������� ������ �׸� �� ���� ��ü
	SDL_Renderer* mRenderer;
	// delta time�� ����� �� ����� ���� �������� Tick��
	Uint32 mTicksCount;
	// Ȱ��ȭ�� ����
	std::vector<class Actor*> mActors;
	// ��� ���� ����
	std::vector<class Actor*> mPendingActors;
	// ������ ����(Update) ���θ� ��Ÿ���� ����
	bool mUpdatingActors;
	// ���� �̸�(Key)�� �ؽ���(Value) ���� ������ ��
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	// �׸� Sprite�� ������ ����
	std::vector<class SpriteComponent*> mSprites;
};