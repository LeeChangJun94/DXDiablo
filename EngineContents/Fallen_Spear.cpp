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
	MonsterTypeValue = EMonsterType::FALLEN_SPEAR;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	Renderer->CreateAnimation("Attack_2", "Fallen Ones with Spear_Attack.png", 0, 12, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_1", "Fallen Ones with Spear_Attack.png", 13, 25, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_4", "Fallen Ones with Spear_Attack.png", 26, 38, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_7", "Fallen Ones with Spear_Attack.png", 39, 51, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_8", "Fallen Ones with Spear_Attack.png", 52, 64, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_9", "Fallen Ones with Spear_Attack.png", 65, 77, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_6", "Fallen Ones with Spear_Attack.png", 78, 90, 1.0f / 13, false);
	Renderer->CreateAnimation("Attack_3", "Fallen Ones with Spear_Attack.png", 91, 103, 1.0f / 13, false);

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

	Renderer->CreateAnimation("Die_2", "Fallen Ones with Spear_Die.png", 0, 17, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_1", "Fallen Ones with Spear_Die.png", 18, 35, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_4", "Fallen Ones with Spear_Die.png", 36, 53, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_7", "Fallen Ones with Spear_Die.png", 54, 71, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_8", "Fallen Ones with Spear_Die.png", 72, 89, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_9", "Fallen Ones with Spear_Die.png", 90, 107, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_6", "Fallen Ones with Spear_Die.png", 108, 125, 1.0f / 18, false);
	Renderer->CreateAnimation("Die_3", "Fallen Ones with Spear_Die.png", 126, 143, 1.0f / 18, false);

	Renderer->CreateAnimation("Hit_2", "Fallen Ones with Spear_Hit.png", 0, 10, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_1", "Fallen Ones with Spear_Hit.png", 11, 21, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_4", "Fallen Ones with Spear_Hit.png", 22, 32, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_7", "Fallen Ones with Spear_Hit.png", 33, 43, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_8", "Fallen Ones with Spear_Hit.png", 44, 54, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_9", "Fallen Ones with Spear_Hit.png", 55, 65, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_6", "Fallen Ones with Spear_Hit.png", 66, 76, 1.0f / 11, false);
	Renderer->CreateAnimation("Hit_3", "Fallen Ones with Spear_Hit.png", 77, 87, 1.0f / 11, false);

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

	Renderer->CreateAnimation("Idle_2", "Fallen Ones with Spear_Idle.png", 0, 10, 1.0f / 11);
	Renderer->CreateAnimation("Idle_1", "Fallen Ones with Spear_Idle.png", 11, 21, 1.0f / 11);
	Renderer->CreateAnimation("Idle_4", "Fallen Ones with Spear_Idle.png", 22, 32, 1.0f / 11);
	Renderer->CreateAnimation("Idle_7", "Fallen Ones with Spear_Idle.png", 33, 43, 1.0f / 11);
	Renderer->CreateAnimation("Idle_8", "Fallen Ones with Spear_Idle.png", 44, 54, 1.0f / 11);
	Renderer->CreateAnimation("Idle_9", "Fallen Ones with Spear_Idle.png", 55, 65, 1.0f / 11);
	Renderer->CreateAnimation("Idle_6", "Fallen Ones with Spear_Idle.png", 66, 76, 1.0f / 11);
	Renderer->CreateAnimation("Idle_3", "Fallen Ones with Spear_Idle.png", 77, 87, 1.0f / 11);

	Renderer->CreateAnimation("Special_2", "Fallen Ones with Spear_Special.png", 0, 12, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_1", "Fallen Ones with Spear_Special.png", 13, 25, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_4", "Fallen Ones with Spear_Special.png", 26, 38, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_7", "Fallen Ones with Spear_Special.png", 39, 51, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_8", "Fallen Ones with Spear_Special.png", 52, 64, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_9", "Fallen Ones with Spear_Special.png", 65, 77, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_6", "Fallen Ones with Spear_Special.png", 78, 90, 1.0f / 13, false);
	Renderer->CreateAnimation("Special_3", "Fallen Ones with Spear_Special.png", 91, 103, 1.0f / 13, false);

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

	Renderer->CreateAnimation("Walk_2", "Fallen Ones with Spear_Walk.png", 0, 10, 1.0f / 11);
	Renderer->CreateAnimation("Walk_1", "Fallen Ones with Spear_Walk.png", 11, 21, 1.0f / 11);
	Renderer->CreateAnimation("Walk_4", "Fallen Ones with Spear_Walk.png", 22, 32, 1.0f / 11);
	Renderer->CreateAnimation("Walk_7", "Fallen Ones with Spear_Walk.png", 33, 43, 1.0f / 11);
	Renderer->CreateAnimation("Walk_8", "Fallen Ones with Spear_Walk.png", 44, 54, 1.0f / 11);
	Renderer->CreateAnimation("Walk_9", "Fallen Ones with Spear_Walk.png", 55, 65, 1.0f / 11);
	Renderer->CreateAnimation("Walk_6", "Fallen Ones with Spear_Walk.png", 66, 76, 1.0f / 11);
	Renderer->CreateAnimation("Walk_3", "Fallen Ones with Spear_Walk.png", 77, 87, 1.0f / 11);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Special_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

	FSM.CreateState(EStateType::IDLE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});

	FSM.CreateState(EStateType::ATTACK, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Attack_2");
		});

	FSM.CreateState(EStateType::DIE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Die_2");
		});

	FSM.CreateState(EStateType::WALK, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Walk_2");
		});

	FSM.CreateState(EStateType::SPECIAL, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Special_2");
		});

	FSM.CreateState(EStateType::HIT, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Hit_2");
		});
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