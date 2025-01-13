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

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Renderer->CreateAnimation("Attack_2", "Skeleton King_Attack.png", 0, 15, 0.05f, false);
	Renderer->CreateAnimation("Attack_1", "Skeleton King_Attack.png", 16, 31, 0.05f, false);
	Renderer->CreateAnimation("Attack_4", "Skeleton King_Attack.png", 32, 47, 0.05f, false);
	Renderer->CreateAnimation("Attack_7", "Skeleton King_Attack.png", 48, 63, 0.05f, false);
	Renderer->CreateAnimation("Attack_8", "Skeleton King_Attack.png", 64, 79, 0.05f, false);
	Renderer->CreateAnimation("Attack_9", "Skeleton King_Attack.png", 80, 95, 0.05f, false);
	Renderer->CreateAnimation("Attack_6", "Skeleton King_Attack.png", 96, 111, 0.05f, false);
	Renderer->CreateAnimation("Attack_3", "Skeleton King_Attack.png", 112, 127, 0.05f, false);

	Renderer->SetAnimationEvent("Attack_2", 15, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 31, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 63, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 79, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 111, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 127, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Skeleton King_Die.png", 0, 15, 0.1f, false);
	Renderer->CreateAnimation("Die_1", "Skeleton King_Die.png", 16, 31, 0.1f, false);
	Renderer->CreateAnimation("Die_4", "Skeleton King_Die.png", 32, 47, 0.1f, false);
	Renderer->CreateAnimation("Die_7", "Skeleton King_Die.png", 48, 63, 0.1f, false);
	Renderer->CreateAnimation("Die_8", "Skeleton King_Die.png", 64, 79, 0.1f, false);
	Renderer->CreateAnimation("Die_9", "Skeleton King_Die.png", 80, 95, 0.1f, false);
	Renderer->CreateAnimation("Die_6", "Skeleton King_Die.png", 96, 111, 0.1f, false);
	Renderer->CreateAnimation("Die_3", "Skeleton King_Die.png", 112, 127, 0.1f, false);

	Renderer->CreateAnimation("Hit_2", "Skeleton King_Hit.png", 0, 5, 0.1f, false);
	Renderer->CreateAnimation("Hit_1", "Skeleton King_Hit.png", 6, 11, 0.1f, false);
	Renderer->CreateAnimation("Hit_4", "Skeleton King_Hit.png", 12, 17, 0.1f, false);
	Renderer->CreateAnimation("Hit_7", "Skeleton King_Hit.png", 18, 23, 0.1f, false);
	Renderer->CreateAnimation("Hit_8", "Skeleton King_Hit.png", 24, 29, 0.1f, false);
	Renderer->CreateAnimation("Hit_9", "Skeleton King_Hit.png", 30, 35, 0.1f, false);
	Renderer->CreateAnimation("Hit_6", "Skeleton King_Hit.png", 36, 41, 0.1f, false);
	Renderer->CreateAnimation("Hit_3", "Skeleton King_Hit.png", 42, 47, 0.1f, false);

	Renderer->SetAnimationEvent("Hit_2", 5, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 17, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 29, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 41, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Skeleton King_Idle.png", 0, 7, 0.1f);
	Renderer->CreateAnimation("Idle_1", "Skeleton King_Idle.png", 8, 15, 0.1f);
	Renderer->CreateAnimation("Idle_4", "Skeleton King_Idle.png", 16, 23, 0.1f);
	Renderer->CreateAnimation("Idle_7", "Skeleton King_Idle.png", 24, 31, 0.1f);
	Renderer->CreateAnimation("Idle_8", "Skeleton King_Idle.png", 32, 39, 0.1f);
	Renderer->CreateAnimation("Idle_9", "Skeleton King_Idle.png", 40, 47, 0.1f);
	Renderer->CreateAnimation("Idle_6", "Skeleton King_Idle.png", 48, 55, 0.1f);
	Renderer->CreateAnimation("Idle_3", "Skeleton King_Idle.png", 56, 63, 0.1f);

	Renderer->CreateAnimation("Special_2", "Skeleton King_Special.png", 0, 11, 0.1f, false);
	Renderer->CreateAnimation("Special_1", "Skeleton King_Special.png", 12, 23, 0.1f, false);
	Renderer->CreateAnimation("Special_4", "Skeleton King_Special.png", 24, 35, 0.1f, false);
	Renderer->CreateAnimation("Special_7", "Skeleton King_Special.png", 36, 47, 0.1f, false);
	Renderer->CreateAnimation("Special_8", "Skeleton King_Special.png", 48, 59, 0.1f, false);
	Renderer->CreateAnimation("Special_9", "Skeleton King_Special.png", 60, 71, 0.1f, false);
	Renderer->CreateAnimation("Special_6", "Skeleton King_Special.png", 72, 83, 0.1f, false);
	Renderer->CreateAnimation("Special_3", "Skeleton King_Special.png", 84, 95, 0.1f, false);

	Renderer->SetAnimationEvent("Special_2", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 71, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 83, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Skeleton King_Walk.png", 0, 8, 0.1f);
	Renderer->CreateAnimation("Walk_1", "Skeleton King_Walk.png", 9, 17, 0.1f);
	Renderer->CreateAnimation("Walk_4", "Skeleton King_Walk.png", 18, 26, 0.1f);
	Renderer->CreateAnimation("Walk_7", "Skeleton King_Walk.png", 27, 35, 0.1f);
	Renderer->CreateAnimation("Walk_8", "Skeleton King_Walk.png", 36, 44, 0.1f);
	Renderer->CreateAnimation("Walk_9", "Skeleton King_Walk.png", 45, 53, 0.1f);
	Renderer->CreateAnimation("Walk_6", "Skeleton King_Walk.png", 54, 62, 0.1f);
	Renderer->CreateAnimation("Walk_3", "Skeleton King_Walk.png", 63, 71, 0.1f);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Attack_2");

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

