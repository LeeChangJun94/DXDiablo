#pragma once
#include "Monster.h"

// Ό³Έν :
class ASkeleton : public AMonster
{
public:
	// constrcuter destructer
	ASkeleton();
	~ASkeleton();

	// delete Function
	ASkeleton(const ASkeleton& _Other) = delete;
	ASkeleton(ASkeleton&& _Other) noexcept = delete;
	ASkeleton& operator=(const ASkeleton& _Other) = delete;
	ASkeleton& operator=(ASkeleton&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> SkeletonRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

