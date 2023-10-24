#pragma once
#include <SDL.h>
#include <vector>

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

private:
	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
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
};