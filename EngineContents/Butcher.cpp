#include "PreCompile.h"
#include "Butcher.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AButcher::AButcher()
{
	MonsterTypeValue = EMonsterType::Butcher;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	//ButcherRenderer = CreateDefaultSubObject<USpriteRenderer>();

	////ZombieRenderer->SetAutoScale(true);
	////ZombieRenderer->SetAutoScaleRatio(1.0f);

	//ButcherRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);

	//ButcherRenderer->CreateAnimation("Attack_2", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_1", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_4", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_7", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_8", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_9", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_6", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Attack_3", "Scavenger_Attack.png", 0, 11, 0.1f, false);

	//ButcherRenderer->SetAnimationEvent("Attack_2", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_2");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_1", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_1");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_4", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_4");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_7", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_7");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_8", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_8");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_9", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_9");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_6", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_6");
	//	});
	//ButcherRenderer->SetAnimationEvent("Attack_3", , [this]()
	//	{
	//		ButcherRenderer->ChangeAnimation("Idle_3");
	//	});

	//ButcherRenderer->CreateAnimation("Die_2", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_1", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_4", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_7", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_8", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_9", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_6", "Scavenger_Die.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Die_3", "Scavenger_Die.png", 0, 11, 0.1f, false);

	//ButcherRenderer->CreateAnimation("Hit_2", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_1", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_4", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_7", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_8", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_9", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_6", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Hit_3", "Scavenger_Hit.png", 0, 11, 0.1f, false);

	//ButcherRenderer->CreateAnimation("Idle_2", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_1", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_4", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_7", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_8", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_9", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_6", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Idle_3", "Scavenger_Idle.png", 0, 11, 0.1f, false);

	//ButcherRenderer->CreateAnimation("Special_2", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_1", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_4", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_7", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_8", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_9", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_6", "Scavenger_Special.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Special_3", "Scavenger_Special.png", 0, 11, 0.1f, false);

	//ButcherRenderer->CreateAnimation("Walk_2", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_1", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_4", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_7", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_8", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_9", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_6", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	//ButcherRenderer->CreateAnimation("Walk_3", "Scavenger_Walk.png", 0, 11, 0.1f, false);


	//ButcherRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	//ButcherRenderer->SetupAttachment(RootComponent);

	//ButcherRenderer->ChangeAnimation("Idle_2");

	//Collision = CreateDefaultSubObject<UCollision>();
	//Collision->SetupAttachment(RootComponent);
	//Collision->SetCollisionProfileName("Monster");
	//Collision->SetScale3D({ 50.0f, 50.0f });
}

AButcher::~AButcher()
{
}

void AButcher::BeginPlay()
{
	AActor::BeginPlay();
}

void AButcher::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

