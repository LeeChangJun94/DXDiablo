#pragma once
#include "Monster.h"

// Ό³Έν :
class ASkeleton_Bow : public AMonster
{
public:
	// constrcuter destructer
	ASkeleton_Bow();
	~ASkeleton_Bow();

	// delete Function
	ASkeleton_Bow(const ASkeleton_Bow& _Other) = delete;
	ASkeleton_Bow(ASkeleton_Bow&& _Other) noexcept = delete;
	ASkeleton_Bow& operator=(const ASkeleton_Bow& _Other) = delete;
	ASkeleton_Bow& operator=(ASkeleton_Bow&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Skeleton_BowRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

