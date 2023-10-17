#pragma once
#include <SDL.h>

// x, y ��ǥ�� ������ �ִ� ����ü
struct Vector2
{
	float x;
	float y;
};

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

private:
	// ���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	int mPaddleDir;
	Vector2 mBallVel;
	Vector2 mPaddlePos;
	Vector2 mBallPos;

	// SDL�� ������ ������
	SDL_Window* mWindow;
	// ������ ��� ����ž� �ϴ����� �Ǵ�
	bool mIsRunning;
	// �׷������� ������ �׸� �� ���� ��ü
	SDL_Renderer* mRenderer;
	// delta time�� ����� �� ����� ���� �������� Tick��
	Uint32 mTicksCount;
};