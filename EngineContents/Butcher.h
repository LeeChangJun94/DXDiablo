#pragma once
#include "Monster.h"

// Ό³Έν :
class AButcher : public AMonster
{
public:
	// constrcuter destructer
	AButcher();
	~AButcher();

	// delete Function
	AButcher(const AButcher& _Other) = delete;
	AButcher(AButcher&& _Other) noexcept = delete;
	AButcher& operator=(const AButcher& _Other) = delete;
	AButcher& operator=(AButcher&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

