#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>

APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	// LogoRenderer->SetSprite("Player.png", 0);

	PlayerRenderer->CreateAnimation("Idle_S", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 0, 19, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_S");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_SW", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 20, 39, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_SW");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_W", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 40, 59, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_W");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_NW", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 60, 79, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_NW");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_N", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 80, 99, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_N");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_NE", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 100, 119, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_NE");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_E", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 120, 139, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_E");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_SE", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 140, 159, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_SE");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_S", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 0, 7, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_S");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_SW", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 8, 15, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_SW");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_W", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 16, 23, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_W");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_NW", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 24, 31, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_NW");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_N", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 32, 39, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_N");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_NE", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 40, 47, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_NE");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_E", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 48, 55, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_E");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_SE", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 56, 63, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_SE");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->ChangeAnimation("Idle_S");

	// 부모가 존재하지 않는 root는 Relative든 Local이던 
	// 결과는 같다. 
	// 부모의 크기에 내가 영향을 받을수 있기 대문에 함수가 나뉜것이다.
	// 부모가 없으면
	PlayerRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	PlayerRenderer->SetupAttachment(RootComponent);


	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//// 부모의 스케일이 나에게 영향을 주면서 나는 100이 아닐수가 있다
	//Child->SetRelativeLocation({100.0f, 0.0f, 0.0f});
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Direction();



	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	//if (UEngineInput::IsPress('Q'))
	//{
	//	AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	//}

	//if (UEngineInput::IsPress('E'))
	//{
	//	PlayerRenderer->ChangeAnimation("Move");
	//	// 단 1순간만 처리되는 걸로 
	//	// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	//}

	//if (UEngineInput::IsPress('R'))
	//{
	//	// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	//}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}

void APlayer::Direction()
{
	if (UEngineInput::IsDown('X'))
	{
		PlayerRenderer->ChangeAnimation("Move_S");
	}
	
	if (UEngineInput::IsUp('X'))
	{
		PlayerRenderer->ChangeAnimation("Idle_S");
	}

	if (UEngineInput::IsDown('Z'))
	{
		PlayerRenderer->ChangeAnimation("Move_SW");
	}
	
	if (UEngineInput::IsUp('Z'))
	{
		PlayerRenderer->ChangeAnimation("Idle_SW");
	}

	if (UEngineInput::IsDown('A'))
	{
		PlayerRenderer->ChangeAnimation("Move_W");
	}

	if (UEngineInput::IsUp('A'))
	{
		PlayerRenderer->ChangeAnimation("Idle_W");
	}

	if (UEngineInput::IsDown('Q'))
	{
		PlayerRenderer->ChangeAnimation("Move_NW");
	}

	if (UEngineInput::IsUp('Q'))
	{
		PlayerRenderer->ChangeAnimation("Idle_NW");
	}

	if (UEngineInput::IsDown('W'))
	{
		PlayerRenderer->ChangeAnimation("Move_N");
	}

	if (UEngineInput::IsUp('W'))
	{
		PlayerRenderer->ChangeAnimation("Idle_N");
	}

	if (UEngineInput::IsDown('E'))
	{
		PlayerRenderer->ChangeAnimation("Move_NE");
	}

	if (UEngineInput::IsUp('E'))
	{
		PlayerRenderer->ChangeAnimation("Idle_NE");
	}

	if (UEngineInput::IsDown('D'))
	{
		PlayerRenderer->ChangeAnimation("Move_E");
	}

	if (UEngineInput::IsUp('D'))
	{
		PlayerRenderer->ChangeAnimation("Idle_E");
	}

	if (UEngineInput::IsDown('C'))
	{
		PlayerRenderer->ChangeAnimation("Move_SE");
	}

	if (UEngineInput::IsUp('C'))
	{
		PlayerRenderer->ChangeAnimation("Idle_SE");
	}
}
