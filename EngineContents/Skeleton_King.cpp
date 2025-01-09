#include "PreCompile.h"
#include "Skeleton_King.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

ASkeleton_King::ASkeleton_King()
{
	MonsterTypeValue = EMonsterType::Skeleton_King;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Skeleton_KingRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Skeleton_KingRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->CreateAnimation("Attack_2", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_1", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_4", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_7", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_8", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_9", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_6", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Attack_3", "Scavenger_Attack.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->SetAnimationEvent("Attack_2", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_1", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_4", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_7", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_8", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_9", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_6", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_KingRenderer->SetAnimationEvent("Attack_3", , [this]()
		{
			Skeleton_KingRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_KingRenderer->CreateAnimation("Die_2", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_1", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_4", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_7", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_8", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_9", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_6", "Scavenger_Die.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Die_3", "Scavenger_Die.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->CreateAnimation("Hit_2", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_1", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_4", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_7", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_8", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_9", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_6", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Hit_3", "Scavenger_Hit.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->CreateAnimation("Idle_2", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_1", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_4", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_7", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_8", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_9", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_6", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Idle_3", "Scavenger_Idle.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->CreateAnimation("Special_2", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_1", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_4", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_7", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_8", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_9", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_6", "Scavenger_Special.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Special_3", "Scavenger_Special.png", 0, 11, 0.1f, false);

	Skeleton_KingRenderer->CreateAnimation("Walk_2", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_1", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_4", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_7", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_8", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_9", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_6", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	Skeleton_KingRenderer->CreateAnimation("Walk_3", "Scavenger_Walk.png", 0, 11, 0.1f, false);


	Skeleton_KingRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Skeleton_KingRenderer->SetupAttachment(RootComponent);

	Skeleton_KingRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

ASkeleton_King::~ASkeleton_King()
{
}

void ASkeleton_King::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkeleton_King::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

