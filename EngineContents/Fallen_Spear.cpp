#include "PreCompile.h"
#include "Fallen_Spear.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AFallen_Spear::AFallen_Spear()
{
	MonsterTypeValue = EMonsterType::Fallen_Spear;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Fallen_SpearRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Fallen_SpearRenderer->CreateAnimation("Attack_2", "Fallen Ones with Spear_Attack.png", 0, 12, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_1", "Fallen Ones with Spear_Attack.png", 13, 25, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_4", "Fallen Ones with Spear_Attack.png", 26, 38, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_7", "Fallen Ones with Spear_Attack.png", 39, 51, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_8", "Fallen Ones with Spear_Attack.png", 52, 64, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_9", "Fallen Ones with Spear_Attack.png", 65, 77, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_6", "Fallen Ones with Spear_Attack.png", 78, 90, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Attack_3", "Fallen Ones with Spear_Attack.png", 91, 103, 0.1f, false);

	Fallen_SpearRenderer->SetAnimationEvent("Attack_2", 12, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_1", 25, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_4", 38, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_7", 51, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_8", 64, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_9", 77, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_6", 90, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Attack_3", 103, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SpearRenderer->CreateAnimation("Die_2", "Fallen Ones with Spear_Die.png", 0, 17, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_1", "Fallen Ones with Spear_Die.png", 18, 35, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_4", "Fallen Ones with Spear_Die.png", 36, 53, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_7", "Fallen Ones with Spear_Die.png", 54, 71, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_8", "Fallen Ones with Spear_Die.png", 72, 89, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_9", "Fallen Ones with Spear_Die.png", 90, 107, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_6", "Fallen Ones with Spear_Die.png", 108, 125, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Die_3", "Fallen Ones with Spear_Die.png", 126, 143, 0.1f, false);

	Fallen_SpearRenderer->CreateAnimation("Hit_2", "Fallen Ones with Spear_Hit.png", 0, 10, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_1", "Fallen Ones with Spear_Hit.png", 11, 21, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_4", "Fallen Ones with Spear_Hit.png", 22, 32, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_7", "Fallen Ones with Spear_Hit.png", 33, 43, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_8", "Fallen Ones with Spear_Hit.png", 44, 54, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_9", "Fallen Ones with Spear_Hit.png", 55, 65, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_6", "Fallen Ones with Spear_Hit.png", 66, 76, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Hit_3", "Fallen Ones with Spear_Hit.png", 77, 87, 0.1f, false);

	Fallen_SpearRenderer->SetAnimationEvent("Hit_2", 10, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_1", 21, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_4", 32, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_7", 43, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_8", 54, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_9", 65, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_6", 76, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Hit_3", 87, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SpearRenderer->CreateAnimation("Idle_2", "Fallen Ones with Spear_Idle.png", 0, 10, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_1", "Fallen Ones with Spear_Idle.png", 11, 21, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_4", "Fallen Ones with Spear_Idle.png", 22, 32, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_7", "Fallen Ones with Spear_Idle.png", 33, 43, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_8", "Fallen Ones with Spear_Idle.png", 44, 54, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_9", "Fallen Ones with Spear_Idle.png", 55, 65, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_6", "Fallen Ones with Spear_Idle.png", 66, 76, 0.1f);
	Fallen_SpearRenderer->CreateAnimation("Idle_3", "Fallen Ones with Spear_Idle.png", 77, 87, 0.1f);

	Fallen_SpearRenderer->CreateAnimation("Special_2", "Fallen Ones with Spear_Special.png", 0, 12, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_1", "Fallen Ones with Spear_Special.png", 13, 25, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_4", "Fallen Ones with Spear_Special.png", 26, 38, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_7", "Fallen Ones with Spear_Special.png", 39, 51, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_8", "Fallen Ones with Spear_Special.png", 52, 64, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_9", "Fallen Ones with Spear_Special.png", 65, 77, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_6", "Fallen Ones with Spear_Special.png", 78, 90, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Special_3", "Fallen Ones with Spear_Special.png", 91, 103, 0.1f, false);

	Fallen_SpearRenderer->SetAnimationEvent("Special_2", 12, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_2");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_1", 25, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_1");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_4", 38, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_4");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_7", 51, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_7");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_8", 64, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_8");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_9", 77, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_9");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_6", 90, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_6");
		});
	Fallen_SpearRenderer->SetAnimationEvent("Special_3", 103, [this]()
		{
			Fallen_SpearRenderer->ChangeAnimation("Idle_3");
		});

	Fallen_SpearRenderer->CreateAnimation("Walk_2", "Fallen Ones with Spear_Walk.png", 0, 10, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_1", "Fallen Ones with Spear_Walk.png", 11, 21, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_4", "Fallen Ones with Spear_Walk.png", 22, 32, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_7", "Fallen Ones with Spear_Walk.png", 33, 43, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_8", "Fallen Ones with Spear_Walk.png", 44, 54, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_9", "Fallen Ones with Spear_Walk.png", 55, 65, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_6", "Fallen Ones with Spear_Walk.png", 66, 76, 0.1f, false);
	Fallen_SpearRenderer->CreateAnimation("Walk_3", "Fallen Ones with Spear_Walk.png", 77, 87, 0.1f, false);


	Fallen_SpearRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Fallen_SpearRenderer->SetupAttachment(RootComponent);

	Fallen_SpearRenderer->ChangeAnimation("Special_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AFallen_Spear::~AFallen_Spear()
{
}

void AFallen_Spear::BeginPlay()
{
	AActor::BeginPlay();
}

void AFallen_Spear::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}