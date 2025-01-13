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

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Renderer->CreateAnimation("Attack_2", "Fallen Ones with Spear_Attack.png", 0, 12, 0.05f, false);
	Renderer->CreateAnimation("Attack_1", "Fallen Ones with Spear_Attack.png", 13, 25, 0.05f, false);
	Renderer->CreateAnimation("Attack_4", "Fallen Ones with Spear_Attack.png", 26, 38, 0.05f, false);
	Renderer->CreateAnimation("Attack_7", "Fallen Ones with Spear_Attack.png", 39, 51, 0.05f, false);
	Renderer->CreateAnimation("Attack_8", "Fallen Ones with Spear_Attack.png", 52, 64, 0.05f, false);
	Renderer->CreateAnimation("Attack_9", "Fallen Ones with Spear_Attack.png", 65, 77, 0.05f, false);
	Renderer->CreateAnimation("Attack_6", "Fallen Ones with Spear_Attack.png", 78, 90, 0.05f, false);
	Renderer->CreateAnimation("Attack_3", "Fallen Ones with Spear_Attack.png", 91, 103, 0.05f, false);

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

	Renderer->CreateAnimation("Die_2", "Fallen Ones with Spear_Die.png", 0, 17, 0.1f, false);
	Renderer->CreateAnimation("Die_1", "Fallen Ones with Spear_Die.png", 18, 35, 0.1f, false);
	Renderer->CreateAnimation("Die_4", "Fallen Ones with Spear_Die.png", 36, 53, 0.1f, false);
	Renderer->CreateAnimation("Die_7", "Fallen Ones with Spear_Die.png", 54, 71, 0.1f, false);
	Renderer->CreateAnimation("Die_8", "Fallen Ones with Spear_Die.png", 72, 89, 0.1f, false);
	Renderer->CreateAnimation("Die_9", "Fallen Ones with Spear_Die.png", 90, 107, 0.1f, false);
	Renderer->CreateAnimation("Die_6", "Fallen Ones with Spear_Die.png", 108, 125, 0.1f, false);
	Renderer->CreateAnimation("Die_3", "Fallen Ones with Spear_Die.png", 126, 143, 0.1f, false);

	Renderer->CreateAnimation("Hit_2", "Fallen Ones with Spear_Hit.png", 0, 10, 0.1f, false);
	Renderer->CreateAnimation("Hit_1", "Fallen Ones with Spear_Hit.png", 11, 21, 0.1f, false);
	Renderer->CreateAnimation("Hit_4", "Fallen Ones with Spear_Hit.png", 22, 32, 0.1f, false);
	Renderer->CreateAnimation("Hit_7", "Fallen Ones with Spear_Hit.png", 33, 43, 0.1f, false);
	Renderer->CreateAnimation("Hit_8", "Fallen Ones with Spear_Hit.png", 44, 54, 0.1f, false);
	Renderer->CreateAnimation("Hit_9", "Fallen Ones with Spear_Hit.png", 55, 65, 0.1f, false);
	Renderer->CreateAnimation("Hit_6", "Fallen Ones with Spear_Hit.png", 66, 76, 0.1f, false);
	Renderer->CreateAnimation("Hit_3", "Fallen Ones with Spear_Hit.png", 77, 87, 0.1f, false);

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

	Renderer->CreateAnimation("Idle_2", "Fallen Ones with Spear_Idle.png", 0, 10, 0.1f);
	Renderer->CreateAnimation("Idle_1", "Fallen Ones with Spear_Idle.png", 11, 21, 0.1f);
	Renderer->CreateAnimation("Idle_4", "Fallen Ones with Spear_Idle.png", 22, 32, 0.1f);
	Renderer->CreateAnimation("Idle_7", "Fallen Ones with Spear_Idle.png", 33, 43, 0.1f);
	Renderer->CreateAnimation("Idle_8", "Fallen Ones with Spear_Idle.png", 44, 54, 0.1f);
	Renderer->CreateAnimation("Idle_9", "Fallen Ones with Spear_Idle.png", 55, 65, 0.1f);
	Renderer->CreateAnimation("Idle_6", "Fallen Ones with Spear_Idle.png", 66, 76, 0.1f);
	Renderer->CreateAnimation("Idle_3", "Fallen Ones with Spear_Idle.png", 77, 87, 0.1f);

	Renderer->CreateAnimation("Special_2", "Fallen Ones with Spear_Special.png", 0, 12, 0.1f, false);
	Renderer->CreateAnimation("Special_1", "Fallen Ones with Spear_Special.png", 13, 25, 0.1f, false);
	Renderer->CreateAnimation("Special_4", "Fallen Ones with Spear_Special.png", 26, 38, 0.1f, false);
	Renderer->CreateAnimation("Special_7", "Fallen Ones with Spear_Special.png", 39, 51, 0.1f, false);
	Renderer->CreateAnimation("Special_8", "Fallen Ones with Spear_Special.png", 52, 64, 0.1f, false);
	Renderer->CreateAnimation("Special_9", "Fallen Ones with Spear_Special.png", 65, 77, 0.1f, false);
	Renderer->CreateAnimation("Special_6", "Fallen Ones with Spear_Special.png", 78, 90, 0.1f, false);
	Renderer->CreateAnimation("Special_3", "Fallen Ones with Spear_Special.png", 91, 103, 0.1f, false);

	Renderer->SetAnimationEvent("Special_2", 12, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 25, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 38, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 51, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 64, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 77, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 90, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 103, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Fallen Ones with Spear_Walk.png", 0, 10, 0.1f, false);
	Renderer->CreateAnimation("Walk_1", "Fallen Ones with Spear_Walk.png", 11, 21, 0.1f, false);
	Renderer->CreateAnimation("Walk_4", "Fallen Ones with Spear_Walk.png", 22, 32, 0.1f, false);
	Renderer->CreateAnimation("Walk_7", "Fallen Ones with Spear_Walk.png", 33, 43, 0.1f, false);
	Renderer->CreateAnimation("Walk_8", "Fallen Ones with Spear_Walk.png", 44, 54, 0.1f, false);
	Renderer->CreateAnimation("Walk_9", "Fallen Ones with Spear_Walk.png", 55, 65, 0.1f, false);
	Renderer->CreateAnimation("Walk_6", "Fallen Ones with Spear_Walk.png", 66, 76, 0.1f, false);
	Renderer->CreateAnimation("Walk_3", "Fallen Ones with Spear_Walk.png", 77, 87, 0.1f, false);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Special_2");

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