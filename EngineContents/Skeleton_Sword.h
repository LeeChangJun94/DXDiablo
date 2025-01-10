#pragma once
#include "Monster.h"

// Ό³Έν :
class ASkeleton_Sword : public AMonster
{
public:
	// constrcuter destructer
	ASkeleton_Sword();
	~ASkeleton_Sword();

	// delete Function
	ASkeleton_Sword(const ASkeleton_Sword& _Other) = delete;
	ASkeleton_Sword(ASkeleton_Sword&& _Other) noexcept = delete;
	ASkeleton_Sword& operator=(const ASkeleton_Sword& _Other) = delete;
	ASkeleton_Sword& operator=(ASkeleton_Sword&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Skeleton_SwordRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

