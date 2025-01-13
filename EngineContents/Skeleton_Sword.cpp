#include "PreCompile.h"
#include "Skeleton_Sword.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

ASkeleton_Sword::ASkeleton_Sword()
{
	MonsterTypeValue = EMonsterType::Skeleton_Sword;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Renderer->CreateAnimation("Attack_2", "Skeleton with Sword & Shield_Attack.png", 0, 11, 0.05f, false);
	Renderer->CreateAnimation("Attack_1", "Skeleton with Sword & Shield_Attack.png", 12, 23, 0.05f, false);
	Renderer->CreateAnimation("Attack_4", "Skeleton with Sword & Shield_Attack.png", 24, 35, 0.05f, false);
	Renderer->CreateAnimation("Attack_7", "Skeleton with Sword & Shield_Attack.png", 36, 47, 0.05f, false);
	Renderer->CreateAnimation("Attack_8", "Skeleton with Sword & Shield_Attack.png", 48, 59, 0.05f, false);
	Renderer->CreateAnimation("Attack_9", "Skeleton with Sword & Shield_Attack.png", 60, 71, 0.05f, false);
	Renderer->CreateAnimation("Attack_6", "Skeleton with Sword & Shield_Attack.png", 72, 83, 0.05f, false);
	Renderer->CreateAnimation("Attack_3", "Skeleton with Sword & Shield_Attack.png", 84, 95, 0.05f, false);

	Renderer->SetAnimationEvent("Attack_2", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 71, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 83, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Skeleton with Sword & Shield_Die.png", 0, 14, 0.1f, false);
	Renderer->CreateAnimation("Die_1", "Skeleton with Sword & Shield_Die.png", 15, 29, 0.1f, false);
	Renderer->CreateAnimation("Die_4", "Skeleton with Sword & Shield_Die.png", 30, 44, 0.1f, false);
	Renderer->CreateAnimation("Die_7", "Skeleton with Sword & Shield_Die.png", 45, 59, 0.1f, false);
	Renderer->CreateAnimation("Die_8", "Skeleton with Sword & Shield_Die.png", 60, 74, 0.1f, false);
	Renderer->CreateAnimation("Die_9", "Skeleton with Sword & Shield_Die.png", 75, 89, 0.1f, false);
	Renderer->CreateAnimation("Die_6", "Skeleton with Sword & Shield_Die.png", 90, 104, 0.1f, false);
	Renderer->CreateAnimation("Die_3", "Skeleton with Sword & Shield_Die.png", 105, 119, 0.1f, false);

	Renderer->CreateAnimation("Hit_2", "Skeleton with Sword & Shield_Hit.png", 0, 6, 0.1f, false);
	Renderer->CreateAnimation("Hit_1", "Skeleton with Sword & Shield_Hit.png", 7, 13, 0.1f, false);
	Renderer->CreateAnimation("Hit_4", "Skeleton with Sword & Shield_Hit.png", 14, 20, 0.1f, false);
	Renderer->CreateAnimation("Hit_7", "Skeleton with Sword & Shield_Hit.png", 21, 27, 0.1f, false);
	Renderer->CreateAnimation("Hit_8", "Skeleton with Sword & Shield_Hit.png", 28, 34, 0.1f, false);
	Renderer->CreateAnimation("Hit_9", "Skeleton with Sword & Shield_Hit.png", 35, 41, 0.1f, false);
	Renderer->CreateAnimation("Hit_6", "Skeleton with Sword & Shield_Hit.png", 42, 48, 0.1f, false);
	Renderer->CreateAnimation("Hit_3", "Skeleton with Sword & Shield_Hit.png", 49, 55, 0.1f, false);

	Renderer->SetAnimationEvent("Hit_2", 6, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 13, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 20, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 27, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 34, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 41, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 48, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 55, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Skeleton with Sword & Shield_Idle.png", 0, 12, 0.1f);
	Renderer->CreateAnimation("Idle_1", "Skeleton with Sword & Shield_Idle.png", 13, 25, 0.1f);
	Renderer->CreateAnimation("Idle_4", "Skeleton with Sword & Shield_Idle.png", 26, 38, 0.1f);
	Renderer->CreateAnimation("Idle_7", "Skeleton with Sword & Shield_Idle.png", 39, 51, 0.1f);
	Renderer->CreateAnimation("Idle_8", "Skeleton with Sword & Shield_Idle.png", 52, 64, 0.1f);
	Renderer->CreateAnimation("Idle_9", "Skeleton with Sword & Shield_Idle.png", 65, 77, 0.1f);
	Renderer->CreateAnimation("Idle_6", "Skeleton with Sword & Shield_Idle.png", 78, 90, 0.1f);
	Renderer->CreateAnimation("Idle_3", "Skeleton with Sword & Shield_Idle.png", 91, 103, 0.1f);

	Renderer->CreateAnimation("Walk_2", "Skeleton with Sword & Shield_Walk.png", 0, 7, 0.1f);
	Renderer->CreateAnimation("Walk_1", "Skeleton with Sword & Shield_Walk.png", 8, 15, 0.1f);
	Renderer->CreateAnimation("Walk_4", "Skeleton with Sword & Shield_Walk.png", 16, 23, 0.1f);
	Renderer->CreateAnimation("Walk_7", "Skeleton with Sword & Shield_Walk.png", 24, 31, 0.1f);
	Renderer->CreateAnimation("Walk_8", "Skeleton with Sword & Shield_Walk.png", 32, 39, 0.1f);
	Renderer->CreateAnimation("Walk_9", "Skeleton with Sword & Shield_Walk.png", 40, 47, 0.1f);
	Renderer->CreateAnimation("Walk_6", "Skeleton with Sword & Shield_Walk.png", 48, 55, 0.1f);
	Renderer->CreateAnimation("Walk_3", "Skeleton with Sword & Shield_Walk.png", 56, 63, 0.1f);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

ASkeleton_Sword::~ASkeleton_Sword()
{
}

void ASkeleton_Sword::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkeleton_Sword::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

