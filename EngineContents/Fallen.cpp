#include "PreCompile.h"
#include "Fallen.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AFallen::AFallen()
{
	MonsterTypeValue = EMonsterType::Fallen;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	FallenRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	FallenRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);

	FallenRenderer->CreateAnimation("Attack_2", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_1", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_4", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_7", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_8", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_9", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_6", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Attack_3", "Scavenger_Attack.png", 0, 11, 0.1f, false);

	FallenRenderer->SetAnimationEvent("Attack_2", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_2");
		});
	FallenRenderer->SetAnimationEvent("Attack_1", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_1");
		});
	FallenRenderer->SetAnimationEvent("Attack_4", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_4");
		});
	FallenRenderer->SetAnimationEvent("Attack_7", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_7");
		});
	FallenRenderer->SetAnimationEvent("Attack_8", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_8");
		});
	FallenRenderer->SetAnimationEvent("Attack_9", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_9");
		});
	FallenRenderer->SetAnimationEvent("Attack_6", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_6");
		});
	FallenRenderer->SetAnimationEvent("Attack_3", , [this]()
		{
			FallenRenderer->ChangeAnimation("Idle_3");
		});

	FallenRenderer->CreateAnimation("Die_2", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_1", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_4", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_7", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_8", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_9", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_6", "Scavenger_Die.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Die_3", "Scavenger_Die.png", 0, 11, 0.1f, false);

	FallenRenderer->CreateAnimation("Hit_2", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_1", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_4", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_7", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_8", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_9", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_6", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Hit_3", "Scavenger_Hit.png", 0, 11, 0.1f, false);

	FallenRenderer->CreateAnimation("Idle_2", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_1", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_4", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_7", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_8", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_9", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_6", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Idle_3", "Scavenger_Idle.png", 0, 11, 0.1f, false);

	FallenRenderer->CreateAnimation("Special_2", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_1", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_4", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_7", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_8", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_9", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_6", "Scavenger_Special.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Special_3", "Scavenger_Special.png", 0, 11, 0.1f, false);

	FallenRenderer->CreateAnimation("Walk_2", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_1", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_4", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_7", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_8", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_9", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_6", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	FallenRenderer->CreateAnimation("Walk_3", "Scavenger_Walk.png", 0, 11, 0.1f, false);


	FallenRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	FallenRenderer->SetupAttachment(RootComponent);

	FallenRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AFallen::~AFallen()
{
}

void AFallen::BeginPlay()
{
	AActor::BeginPlay();
}

void AFallen::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}