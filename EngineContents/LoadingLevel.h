#pragma once
#include <EngineCore/GameMode.h>
#include <atomic>
#include <EnginePlatform/EngineThread.h>

// Ό³Έν :
class ALoadingLevel : public AGameMode
{
public:
	// constrcuter destructer
	ALoadingLevel();
	~ALoadingLevel();

	// delete Function
	ALoadingLevel(const ALoadingLevel& _Other) = delete;
	ALoadingLevel(ALoadingLevel&& _Other) noexcept = delete;
	ALoadingLevel& operator=(const ALoadingLevel& _Other) = delete;
	ALoadingLevel& operator=(ALoadingLevel&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;

private:
	std::atomic<bool> LoadingEnd = false;

	UEngineThread Thread;

};

