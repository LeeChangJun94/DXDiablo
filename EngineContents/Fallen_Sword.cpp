#include "PreCompile.h"
#include "Fallen_Sword.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AFallen_Sword::AFallen_Sword()
{
	MonsterTypeValue = EMonsterType::Fallen_Sword;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Fallen_SwordRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	/*Fallen One with Sword_Attack.png", 
		Fallen One with Sword_Die.png", ".s
		Fallen One with Sword_Hit.png", ".s
		Fallen One with Sword_Idle.png", ".
		Fallen One with Sword_Special.png",
		Fallen One with Sword_Walk.png", ".*/

	Fallen_SwordRenderer->CreateAnimation("Attack_2", "Fallen One with Sword_Attack.png", 0, 12, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_1", "Fallen One with Sword_Attack.png", 13, 25, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_4", "Fallen One with Sword_Attack.png", 26, 38, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_7", "Fallen One with Sword_Attack.png", 39, 51, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_8", "Fallen One with Sword_Attack.png", 52, 64, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_9", "Fallen One with Sword_Attack.png", 65, 77, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_6", "Fallen One with Sword_Attack.png", 78, 90, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Attack_3", "Fallen One with Sword_Attack.png", 91, 103, 0.1f, false);

	Fallen_SwordRenderer->SetAnimationEvent("Attack_2", 12, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_1", 25, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_4", 38, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_7", 51, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_8", 64, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_9", 77, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_6", 90, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Attack_3", 103, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SwordRenderer->CreateAnimation("Die_2", "Fallen One with Sword_Die.png", 0, 13, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_1", "Fallen One with Sword_Die.png", 14, 27, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_4", "Fallen One with Sword_Die.png", 28, 41, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_7", "Fallen One with Sword_Die.png", 42, 55, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_8", "Fallen One with Sword_Die.png", 56, 69, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_9", "Fallen One with Sword_Die.png", 70, 83, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_6", "Fallen One with Sword_Die.png", 84, 97, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Die_3", "Fallen One with Sword_Die.png", 98, 111, 0.1f, false);

	Fallen_SwordRenderer->CreateAnimation("Hit_2", "Fallen One with Sword_Hit.png", 0, 10, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_1", "Fallen One with Sword_Hit.png", 11, 21, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_4", "Fallen One with Sword_Hit.png", 22, 32, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_7", "Fallen One with Sword_Hit.png", 33, 43, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_8", "Fallen One with Sword_Hit.png", 44, 54, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_9", "Fallen One with Sword_Hit.png", 55, 65, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_6", "Fallen One with Sword_Hit.png", 66, 76, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Hit_3", "Fallen One with Sword_Hit.png", 77, 87, 0.1f, false);

	Fallen_SwordRenderer->SetAnimationEvent("Hit_2", 10, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_1", 21, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_4", 32, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_7", 43, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_8", 54, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_9", 65, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_6", 76, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Hit_3", 87, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SwordRenderer->CreateAnimation("Idle_2", "Fallen One with Sword_Idle.png", 0, 11, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_1", "Fallen One with Sword_Idle.png", 12, 23, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_4", "Fallen One with Sword_Idle.png", 24, 35, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_7", "Fallen One with Sword_Idle.png", 36, 47, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_8", "Fallen One with Sword_Idle.png", 48, 59, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_9", "Fallen One with Sword_Idle.png", 60, 71, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_6", "Fallen One with Sword_Idle.png", 72, 83, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Idle_3", "Fallen One with Sword_Idle.png", 84, 95, 0.1f);

	Fallen_SwordRenderer->CreateAnimation("Special_2", "Fallen One with Sword_Special.png", 0, 14, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_1", "Fallen One with Sword_Special.png", 15, 29, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_4", "Fallen One with Sword_Special.png", 30, 44, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_7", "Fallen One with Sword_Special.png", 45, 59, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_8", "Fallen One with Sword_Special.png", 60, 74, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_9", "Fallen One with Sword_Special.png", 75, 89, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_6", "Fallen One with Sword_Special.png", 90, 104, 0.1f, false);
	Fallen_SwordRenderer->CreateAnimation("Special_3", "Fallen One with Sword_Special.png", 105, 119, 0.1f, false);

	Fallen_SwordRenderer->SetAnimationEvent("Special_2", 14, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_1", 29, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_4", 44, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_7", 59, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_8", 74, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_9", 89, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_6", 104, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SwordRenderer->SetAnimationEvent("Special_3", 119, [this]()
		{
			Fallen_SwordRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SwordRenderer->CreateAnimation("Walk_2", "Fallen One with Sword_Walk.png", 0, 11, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_1", "Fallen One with Sword_Walk.png", 12, 23, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_4", "Fallen One with Sword_Walk.png", 24, 35, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_7", "Fallen One with Sword_Walk.png", 36, 47, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_8", "Fallen One with Sword_Walk.png", 48, 59, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_9", "Fallen One with Sword_Walk.png", 60, 71, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_6", "Fallen One with Sword_Walk.png", 72, 83, 0.1f);
	Fallen_SwordRenderer->CreateAnimation("Walk_3", "Fallen One with Sword_Walk.png", 84, 95, 0.1f);


	Fallen_SwordRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Fallen_SwordRenderer->SetupAttachment(RootComponent);

	Fallen_SwordRenderer->ChangeAnimation("Special_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AFallen_Sword::~AFallen_Sword()
{
}

void AFallen_Sword::BeginPlay()
{
	AActor::BeginPlay();
}

void AFallen_Sword::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}