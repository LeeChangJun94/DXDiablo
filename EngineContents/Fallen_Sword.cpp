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

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	/*Fallen One with Sword_Attack.png", 
		Fallen One with Sword_Die.png", ".s
		Fallen One with Sword_Hit.png", ".s
		Fallen One with Sword_Idle.png", ".
		Fallen One with Sword_Special.png",
		Fallen One with Sword_Walk.png", ".*/

	Renderer->CreateAnimation("Attack_2", "Fallen One with Sword_Attack.png", 0, 12, 0.05f, false);
	Renderer->CreateAnimation("Attack_1", "Fallen One with Sword_Attack.png", 13, 25, 0.05f, false);
	Renderer->CreateAnimation("Attack_4", "Fallen One with Sword_Attack.png", 26, 38, 0.05f, false);
	Renderer->CreateAnimation("Attack_7", "Fallen One with Sword_Attack.png", 39, 51, 0.05f, false);
	Renderer->CreateAnimation("Attack_8", "Fallen One with Sword_Attack.png", 52, 64, 0.05f, false);
	Renderer->CreateAnimation("Attack_9", "Fallen One with Sword_Attack.png", 65, 77, 0.05f, false);
	Renderer->CreateAnimation("Attack_6", "Fallen One with Sword_Attack.png", 78, 90, 0.05f, false);
	Renderer->CreateAnimation("Attack_3", "Fallen One with Sword_Attack.png", 91, 103, 0.05f, false);

	Renderer->SetAnimationEvent("Attack_2", 12, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 25, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 38, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 51, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 64, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 77, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 90, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 103, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Fallen One with Sword_Die.png", 0, 13, 0.1f, false);
	Renderer->CreateAnimation("Die_1", "Fallen One with Sword_Die.png", 14, 27, 0.1f, false);
	Renderer->CreateAnimation("Die_4", "Fallen One with Sword_Die.png", 28, 41, 0.1f, false);
	Renderer->CreateAnimation("Die_7", "Fallen One with Sword_Die.png", 42, 55, 0.1f, false);
	Renderer->CreateAnimation("Die_8", "Fallen One with Sword_Die.png", 56, 69, 0.1f, false);
	Renderer->CreateAnimation("Die_9", "Fallen One with Sword_Die.png", 70, 83, 0.1f, false);
	Renderer->CreateAnimation("Die_6", "Fallen One with Sword_Die.png", 84, 97, 0.1f, false);
	Renderer->CreateAnimation("Die_3", "Fallen One with Sword_Die.png", 98, 111, 0.1f, false);

	Renderer->CreateAnimation("Hit_2", "Fallen One with Sword_Hit.png", 0, 10, 0.1f, false);
	Renderer->CreateAnimation("Hit_1", "Fallen One with Sword_Hit.png", 11, 21, 0.1f, false);
	Renderer->CreateAnimation("Hit_4", "Fallen One with Sword_Hit.png", 22, 32, 0.1f, false);
	Renderer->CreateAnimation("Hit_7", "Fallen One with Sword_Hit.png", 33, 43, 0.1f, false);
	Renderer->CreateAnimation("Hit_8", "Fallen One with Sword_Hit.png", 44, 54, 0.1f, false);
	Renderer->CreateAnimation("Hit_9", "Fallen One with Sword_Hit.png", 55, 65, 0.1f, false);
	Renderer->CreateAnimation("Hit_6", "Fallen One with Sword_Hit.png", 66, 76, 0.1f, false);
	Renderer->CreateAnimation("Hit_3", "Fallen One with Sword_Hit.png", 77, 87, 0.1f, false);

	Renderer->SetAnimationEvent("Hit_2", 10, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 21, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 32, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 43, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 54, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 65, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 76, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 87, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Fallen One with Sword_Idle.png", 0, 11, 0.1f);
	Renderer->CreateAnimation("Idle_1", "Fallen One with Sword_Idle.png", 12, 23, 0.1f);
	Renderer->CreateAnimation("Idle_4", "Fallen One with Sword_Idle.png", 24, 35, 0.1f);
	Renderer->CreateAnimation("Idle_7", "Fallen One with Sword_Idle.png", 36, 47, 0.1f);
	Renderer->CreateAnimation("Idle_8", "Fallen One with Sword_Idle.png", 48, 59, 0.1f);
	Renderer->CreateAnimation("Idle_9", "Fallen One with Sword_Idle.png", 60, 71, 0.1f);
	Renderer->CreateAnimation("Idle_6", "Fallen One with Sword_Idle.png", 72, 83, 0.1f);
	Renderer->CreateAnimation("Idle_3", "Fallen One with Sword_Idle.png", 84, 95, 0.1f);

	Renderer->CreateAnimation("Special_2", "Fallen One with Sword_Special.png", 0, 14, 0.1f, false);
	Renderer->CreateAnimation("Special_1", "Fallen One with Sword_Special.png", 15, 29, 0.1f, false);
	Renderer->CreateAnimation("Special_4", "Fallen One with Sword_Special.png", 30, 44, 0.1f, false);
	Renderer->CreateAnimation("Special_7", "Fallen One with Sword_Special.png", 45, 59, 0.1f, false);
	Renderer->CreateAnimation("Special_8", "Fallen One with Sword_Special.png", 60, 74, 0.1f, false);
	Renderer->CreateAnimation("Special_9", "Fallen One with Sword_Special.png", 75, 89, 0.1f, false);
	Renderer->CreateAnimation("Special_6", "Fallen One with Sword_Special.png", 90, 104, 0.1f, false);
	Renderer->CreateAnimation("Special_3", "Fallen One with Sword_Special.png", 105, 119, 0.1f, false);

	Renderer->SetAnimationEvent("Special_2", 14, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 29, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 44, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 74, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 89, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 104, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 119, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Fallen One with Sword_Walk.png", 0, 11, 0.1f);
	Renderer->CreateAnimation("Walk_1", "Fallen One with Sword_Walk.png", 12, 23, 0.1f);
	Renderer->CreateAnimation("Walk_4", "Fallen One with Sword_Walk.png", 24, 35, 0.1f);
	Renderer->CreateAnimation("Walk_7", "Fallen One with Sword_Walk.png", 36, 47, 0.1f);
	Renderer->CreateAnimation("Walk_8", "Fallen One with Sword_Walk.png", 48, 59, 0.1f);
	Renderer->CreateAnimation("Walk_9", "Fallen One with Sword_Walk.png", 60, 71, 0.1f);
	Renderer->CreateAnimation("Walk_6", "Fallen One with Sword_Walk.png", 72, 83, 0.1f);
	Renderer->CreateAnimation("Walk_3", "Fallen One with Sword_Walk.png", 84, 95, 0.1f);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Special_2");

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