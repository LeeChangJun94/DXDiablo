#pragma once
#include <EngineCore/Actor.h>

enum class PlayerDirection8
{
	N,
	NE,
	E,
	SE,
	S,
	SW,
	W,
	NW
};



// Ό³Έν :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return PlayerRenderer;
	}

	void Direction();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	FVector MousePos = { 0, 0 };

	PlayerDirection8 PlayerDirection = PlayerDirection8::S;
};

