#pragma once
#include <EngineCore/Pawn.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>

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
class APlayer : public APawn
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

	void PlayerMove(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> PlayerRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;

	//std::shared_ptr<class URenderer> Renderer;

	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;

	UEngineWinImage ColImage;

	FVector MousePos = { 0, 0, 0, 0 };
	FVector MouseDir = { 0, 0, 0, 0 };
	
	float AngleDeg = 0.0f;
	float Speed = 200.0f;
	float Distance = 0.0f;
	std::string Dir = "5";
	std::string State = "Idle_";
	std::string Pos = "Town_";
	std::string Equipment = "Sword & Shield_";

	bool Move = false;

	PlayerDirection8 PlayerDirection = PlayerDirection8::S;
};

