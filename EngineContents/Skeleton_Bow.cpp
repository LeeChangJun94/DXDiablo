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
	MonsterTypeValue = EMonsterType::SKELETON_BOW;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	Renderer->CreateAnimation("Attack_2", "Skeleton with Bow_Attack.png", 0, 15, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_1", "Skeleton with Bow_Attack.png", 16, 31, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_4", "Skeleton with Bow_Attack.png", 32, 47, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_7", "Skeleton with Bow_Attack.png", 48, 63, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_8", "Skeleton with Bow_Attack.png", 64, 79, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_9", "Skeleton with Bow_Attack.png", 80, 95, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_6", "Skeleton with Bow_Attack.png", 96, 111, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_3", "Skeleton with Bow_Attack.png", 112, 127, 1.0f / 16, false);

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

	Renderer->CreateAnimation("Die_2", "Skeleton with Bow_Die.png", 0, 15, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_1", "Skeleton with Bow_Die.png", 16, 31, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_4", "Skeleton with Bow_Die.png", 32, 47, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_7", "Skeleton with Bow_Die.png", 48, 63, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_8", "Skeleton with Bow_Die.png", 64, 79, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_9", "Skeleton with Bow_Die.png", 80, 95, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_6", "Skeleton with Bow_Die.png", 96, 111, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_3", "Skeleton with Bow_Die.png", 112, 127, 1.0f / 16, false);

	Renderer->CreateAnimation("Hit_2", "Skeleton with Bow_Hit.png", 0, 4, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_1", "Skeleton with Bow_Hit.png", 5, 9, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_4", "Skeleton with Bow_Hit.png", 10, 14, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_7", "Skeleton with Bow_Hit.png", 15, 19, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_8", "Skeleton with Bow_Hit.png", 20, 24, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_9", "Skeleton with Bow_Hit.png", 25, 29, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_6", "Skeleton with Bow_Hit.png", 30, 34, 1.0f / 5, false);
	Renderer->CreateAnimation("Hit_3", "Skeleton with Bow_Hit.png", 35, 39, 1.0f / 5, false);

	Renderer->SetAnimationEvent("Hit_2", 4, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 9, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 14, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 19, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 24, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 29, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 34, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 39, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Skeleton with Bow_Idle.png", 0, 8, 1.0f / 9);
	Renderer->CreateAnimation("Idle_1", "Skeleton with Bow_Idle.png", 9, 17, 1.0f / 9);
	Renderer->CreateAnimation("Idle_4", "Skeleton with Bow_Idle.png", 18, 26, 1.0f / 9);
	Renderer->CreateAnimation("Idle_7", "Skeleton with Bow_Idle.png", 27, 35, 1.0f / 9);
	Renderer->CreateAnimation("Idle_8", "Skeleton with Bow_Idle.png", 36, 44, 1.0f / 9);
	Renderer->CreateAnimation("Idle_9", "Skeleton with Bow_Idle.png", 45, 53, 1.0f / 9);
	Renderer->CreateAnimation("Idle_6", "Skeleton with Bow_Idle.png", 54, 62, 1.0f / 9);
	Renderer->CreateAnimation("Idle_3", "Skeleton with Bow_Idle.png", 63, 71, 1.0f / 9);

	Renderer->CreateAnimation("Special_2", "Skeleton with Bow_Special.png", 0, 15, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_1", "Skeleton with Bow_Special.png", 16, 31, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_4", "Skeleton with Bow_Special.png", 32, 47, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_7", "Skeleton with Bow_Special.png", 48, 63, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_8", "Skeleton with Bow_Special.png", 64, 79, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_9", "Skeleton with Bow_Special.png", 80, 95, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_6", "Skeleton with Bow_Special.png", 96, 111, 1.0f / 16, false);
	Renderer->CreateAnimation("Special_3", "Skeleton with Bow_Special.png", 112, 127, 1.0f / 16, false);

	Renderer->SetAnimationEvent("Special_2", 15, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 31, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 63, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 79, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 111, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 127, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Skeleton with Bow_Walk.png", 0, 7, 1.0f / 8);
	Renderer->CreateAnimation("Walk_1", "Skeleton with Bow_Walk.png", 8, 15, 1.0f / 8);
	Renderer->CreateAnimation("Walk_4", "Skeleton with Bow_Walk.png", 16, 23, 1.0f / 8);
	Renderer->CreateAnimation("Walk_7", "Skeleton with Bow_Walk.png", 24, 31, 1.0f / 8);
	Renderer->CreateAnimation("Walk_8", "Skeleton with Bow_Walk.png", 32, 39, 1.0f / 8);
	Renderer->CreateAnimation("Walk_9", "Skeleton with Bow_Walk.png", 40, 47, 1.0f / 8);
	Renderer->CreateAnimation("Walk_6", "Skeleton with Bow_Walk.png", 48, 55, 1.0f / 8);
	Renderer->CreateAnimation("Walk_3", "Skeleton with Bow_Walk.png", 56, 63, 1.0f / 8);

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

