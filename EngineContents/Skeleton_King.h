#pragma once
#include "Monster.h"

// Ό³Έν :
class ASkeleton_King : public AMonster
{
public:
	// constrcuter destructer
	ASkeleton_King();
	~ASkeleton_King();

	// delete Function
	ASkeleton_King(const ASkeleton_King& _Other) = delete;
	ASkeleton_King(ASkeleton_King&& _Other) noexcept = delete;
	ASkeleton_King& operator=(const ASkeleton_King& _Other) = delete;
	ASkeleton_King& operator=(ASkeleton_King&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

