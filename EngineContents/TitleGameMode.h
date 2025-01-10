#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATitleGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	std::shared_ptr<class APlayer> Player;
	std::shared_ptr<class AZombie> Zombie;
	std::shared_ptr<class ASkeleton_Sword> Skeleton_Sword;
	std::shared_ptr<class ASkeleton_Bow> Skeleton_Bow;
	std::shared_ptr<class ASkeleton_Axe> Skeleton_Axe;
	std::shared_ptr<class ASkeleton_King> Skeleton_King;
	std::shared_ptr<class AScavenger> Scavenger;
	std::shared_ptr<class AHidden> Hidden;
	std::shared_ptr<class AFallen_Sword> Fallen_Sword;
	std::shared_ptr<class AFallen_Spear> Fallen_Spear;
protected:
	void LevelChangeStart() override;
private:
};

