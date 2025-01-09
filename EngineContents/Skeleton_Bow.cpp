#include "PreCompile.h"
#include "Skeleton_Bow.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

ASkeleton_Bow::ASkeleton_Bow()
{
	MonsterTypeValue = EMonsterType::Skeleton_Bow;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Skeleton_BowRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Skeleton_BowRenderer->CreateAnimation("Attack_2", "Skeleton with Bow_Attack.png", 0, 15, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_1", "Skeleton with Bow_Attack.png", 16, 31, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_4", "Skeleton with Bow_Attack.png", 32, 47, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_7", "Skeleton with Bow_Attack.png", 48, 63, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_8", "Skeleton with Bow_Attack.png", 64, 79, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_9", "Skeleton with Bow_Attack.png", 80, 95, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_6", "Skeleton with Bow_Attack.png", 96, 111, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Attack_3", "Skeleton with Bow_Attack.png", 112, 127, 0.1f, false);

	Skeleton_BowRenderer->SetAnimationEvent("Attack_2", 15, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_1", 31, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_4", 47, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_7", 63, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_8", 79, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_9", 95, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_6", 111, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Attack_3", 127, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_BowRenderer->CreateAnimation("Die_2", "Skeleton with Bow_Die.png", 0, 15, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_1", "Skeleton with Bow_Die.png", 16, 31, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_4", "Skeleton with Bow_Die.png", 32, 47, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_7", "Skeleton with Bow_Die.png", 48, 63, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_8", "Skeleton with Bow_Die.png", 64, 79, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_9", "Skeleton with Bow_Die.png", 80, 95, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_6", "Skeleton with Bow_Die.png", 96, 111, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Die_3", "Skeleton with Bow_Die.png", 112, 127, 0.1f, false);

	Skeleton_BowRenderer->CreateAnimation("Hit_2", "Skeleton with Bow_Hit.png", 0, 4, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_1", "Skeleton with Bow_Hit.png", 5, 9, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_4", "Skeleton with Bow_Hit.png", 10, 14, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_7", "Skeleton with Bow_Hit.png", 15, 19, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_8", "Skeleton with Bow_Hit.png", 20, 24, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_9", "Skeleton with Bow_Hit.png", 25, 29, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_6", "Skeleton with Bow_Hit.png", 30, 34, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Hit_3", "Skeleton with Bow_Hit.png", 35, 39, 0.1f, false);

	Skeleton_BowRenderer->SetAnimationEvent("Hit_2", 4, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_1", 9, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_4", 14, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_7", 19, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_8", 24, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_9", 29, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_6", 34, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Hit_3", 39, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_BowRenderer->CreateAnimation("Idle_2", "Skeleton with Bow_Idle.png", 0, 8, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_1", "Skeleton with Bow_Idle.png", 9, 17, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_4", "Skeleton with Bow_Idle.png", 18, 26, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_7", "Skeleton with Bow_Idle.png", 27, 35, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_8", "Skeleton with Bow_Idle.png", 36, 44, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_9", "Skeleton with Bow_Idle.png", 45, 53, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_6", "Skeleton with Bow_Idle.png", 54, 62, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Idle_3", "Skeleton with Bow_Idle.png", 63, 71, 0.1f);

	Skeleton_BowRenderer->CreateAnimation("Special_2", "Skeleton with Bow_Special.png", 0, 15, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_1", "Skeleton with Bow_Special.png", 16, 31, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_4", "Skeleton with Bow_Special.png", 32, 47, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_7", "Skeleton with Bow_Special.png", 48, 63, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_8", "Skeleton with Bow_Special.png", 64, 79, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_9", "Skeleton with Bow_Special.png", 80, 95, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_6", "Skeleton with Bow_Special.png", 96, 111, 0.1f, false);
	Skeleton_BowRenderer->CreateAnimation("Special_3", "Skeleton with Bow_Special.png", 112, 127, 0.1f, false);

	Skeleton_BowRenderer->SetAnimationEvent("Special_2", 15, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_1", 31, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_4", 47, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_7", 63, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_8", 79, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_9", 95, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_6", 111, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_BowRenderer->SetAnimationEvent("Special_3", 127, [this]()
		{
			Skeleton_BowRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_BowRenderer->CreateAnimation("Walk_2", "Skeleton with Bow_Walk.png", 0, 8, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_1", "Skeleton with Bow_Walk.png", 9, 17, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_4", "Skeleton with Bow_Walk.png", 18, 26, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_7", "Skeleton with Bow_Walk.png", 27, 35, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_8", "Skeleton with Bow_Walk.png", 36, 44, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_9", "Skeleton with Bow_Walk.png", 45, 53, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_6", "Skeleton with Bow_Walk.png", 54, 62, 0.1f);
	Skeleton_BowRenderer->CreateAnimation("Walk_3", "Skeleton with Bow_Walk.png", 63, 71, 0.1f);

	Skeleton_BowRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Skeleton_BowRenderer->SetupAttachment(RootComponent);

	Skeleton_BowRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

ASkeleton_Bow::~ASkeleton_Bow()
{
}

void ASkeleton_Bow::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkeleton_Bow::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

