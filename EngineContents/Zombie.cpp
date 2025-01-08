#include "PreCompile.h"
#include "Zombie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AZombie::AZombie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	ZombieRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	ZombieRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_1", "Zombie_Attack.png", 12, 23, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_4", "Zombie_Attack.png", 24, 35, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_7", "Zombie_Attack.png", 36, 47, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_8", "Zombie_Attack.png", 48, 59, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_9", "Zombie_Attack.png", 60, 71, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_6", "Zombie_Attack.png", 72, 83, 0.1f, false);
	ZombieRenderer->CreateAnimation("Attack_3", "Zombie_Attack.png", 84, 95, 0.1f, false);

	ZombieRenderer->SetAnimationEvent("Attack_2", 11, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_2");
		});
	ZombieRenderer->SetAnimationEvent("Attack_1", 23, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_1");
		});
	ZombieRenderer->SetAnimationEvent("Attack_4", 35, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_4");
		});
	ZombieRenderer->SetAnimationEvent("Attack_7", 47, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_7");
		});
	ZombieRenderer->SetAnimationEvent("Attack_8", 59, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_8");
		});
	ZombieRenderer->SetAnimationEvent("Attack_9", 71, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_9");
		});
	ZombieRenderer->SetAnimationEvent("Attack_6", 83, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_6");
		});
	ZombieRenderer->SetAnimationEvent("Attack_3", 95, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_3");
		});

	ZombieRenderer->CreateAnimation("Die_2", "Zombie_Die.png", 0, 15, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_1", "Zombie_Die.png", 16, 31, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_4", "Zombie_Die.png", 32, 47, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_7", "Zombie_Die.png", 48, 63, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_8", "Zombie_Die.png", 64, 79, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_9", "Zombie_Die.png", 80, 95, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_6", "Zombie_Die.png", 96, 111, 0.1f, false);
	ZombieRenderer->CreateAnimation("Die_3", "Zombie_Die.png", 112, 127, 0.1f, false);

	ZombieRenderer->CreateAnimation("Hit_2", "Zombie_Hit.png", 0, 5, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_1", "Zombie_Hit.png", 6, 11, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_4", "Zombie_Hit.png", 12, 17, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_7", "Zombie_Hit.png", 18, 23, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_8", "Zombie_Hit.png", 24, 29, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_9", "Zombie_Hit.png", 30, 35, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_6", "Zombie_Hit.png", 36, 41, 0.1f, false);
	ZombieRenderer->CreateAnimation("Hit_3", "Zombie_Hit.png", 42, 47, 0.1f, false);

	ZombieRenderer->SetAnimationEvent("Hit_2", 5, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_2");
		});
	ZombieRenderer->SetAnimationEvent("Hit_1", 11, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_1");
		});
	ZombieRenderer->SetAnimationEvent("Hit_4", 17, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_4");
		});
	ZombieRenderer->SetAnimationEvent("Hit_7", 23, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_7");
		});
	ZombieRenderer->SetAnimationEvent("Hit_8", 29, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_8");
		});
	ZombieRenderer->SetAnimationEvent("Hit_9", 35, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_9");
		});
	ZombieRenderer->SetAnimationEvent("Hit_6", 41, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_6");
		});
	ZombieRenderer->SetAnimationEvent("Hit_3", 47, [this]()
		{
			ZombieRenderer->ChangeAnimation("Idle_3");
		});

	ZombieRenderer->CreateAnimation("Idle_2", "Zombie_Idle.png", 0, 10, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_1", "Zombie_Idle.png", 11, 21, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_4", "Zombie_Idle.png", 22, 32, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_7", "Zombie_Idle.png", 33, 43, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_8", "Zombie_Idle.png", 44, 54, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_9", "Zombie_Idle.png", 55, 65, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_6", "Zombie_Idle.png", 66, 76, 0.1f);
	ZombieRenderer->CreateAnimation("Idle_3", "Zombie_Idle.png", 77, 87, 0.1f);

	ZombieRenderer->CreateAnimation("Walk_2", "Zombie_Walk.png", 0, 23, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_1", "Zombie_Walk.png", 24, 47, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_4", "Zombie_Walk.png", 48, 71, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_7", "Zombie_Walk.png", 72, 95, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_8", "Zombie_Walk.png", 96, 119, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_9", "Zombie_Walk.png", 120, 143, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_6", "Zombie_Walk.png", 144, 167, 0.1f);
	ZombieRenderer->CreateAnimation("Walk_3", "Zombie_Walk.png", 168, 191, 0.1f);


	ZombieRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	ZombieRenderer->SetupAttachment(RootComponent);

	ZombieRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
	
}

AZombie::~AZombie()
{
}

void AZombie::BeginPlay()
{
	AActor::BeginPlay();
}

void AZombie::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

