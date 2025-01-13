#pragma once
#include "Monster.h"

// Ό³Έν :
class AHidden : public AMonster
{
public:
	// constrcuter destructer
	AHidden();
	~AHidden();

	// delete Function
	AHidden(const AHidden& _Other) = delete;
	AHidden(AHidden&& _Other) noexcept = delete;
	AHidden& operator=(const AHidden& _Other) = delete;
	AHidden& operator=(AHidden&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

