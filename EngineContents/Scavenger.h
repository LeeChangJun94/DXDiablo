#pragma once
#include "Monster.h"


// Ό³Έν :
class AScavenger : public AMonster
{
public:
	// constrcuter destructer
	AScavenger();
	~AScavenger();

	// delete Function
	AScavenger(const AScavenger& _Other) = delete;
	AScavenger(AScavenger&& _Other) noexcept = delete;
	AScavenger& operator=(const AScavenger& _Other) = delete;
	AScavenger& operator=(AScavenger&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

