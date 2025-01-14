#include "PreCompile.h"
#include "Monster.h"
#include "Player.h"

AMonster::AMonster()
{
	
}

AMonster::~AMonster()
{
}

std::shared_ptr<class USpriteRenderer> AMonster::GetRenderer()
{
	return Renderer;
}


void AMonster::BeginPlay()
{
	AActor::BeginPlay();
	Player = dynamic_cast<APlayer*>(GetWorld()->GetMainPawn());
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	MonsterDirection();
}

void AMonster::MonsterDirection()
{
	PlayerPos = Player->GetActorLocation();
	PlayerDir = PlayerPos - GetActorLocation();

	//UEngineDebug::OutPutString(MousePos.ToString());

	Distance = PlayerDir.Length();

	if (DetectionRange >= Distance && 63.0f <= Distance)
	{
		Move = true;

		FSM.ChangeState(EStateType::WALK);

		PlayerDir.Normalize();

		float AngleDeg = FVector::GetVectorAngleDeg({ 1, 0 }, PlayerDir);

		FVector PlayerCross = FVector::Cross({ 1, 0 }, PlayerDir);

		if (0.0f > PlayerCross.Z)
		{
			AngleDeg = 360.0f - AngleDeg;
		}

		if (22.5f > AngleDeg)
		{
			Dir = '6';
		}
		else if (67.5f > AngleDeg)
		{
			Dir = '9';
		}
		else if (112.5f > AngleDeg)
		{
			Dir = '8';
		}
		else if (157.5f > AngleDeg)
		{
			Dir = '7';
		}
		else if (202.5f > AngleDeg)
		{
			Dir = '4';
		}
		else if (247.5f > AngleDeg)
		{
			Dir = '1';
		}
		else if (292.5f > AngleDeg)
		{
			Dir = '2';
		}
		else if (337.5f > AngleDeg)
		{
			Dir = '3';
		}
		else
		{
			Dir = '6';
		}
	}
	else
	{
		if (true == Move)
		{
			FSM.ChangeState(EStateType::IDLE);
			Move = false;
		}
	}
}

void AMonster::MonsterMove(float _DeltaTime)
{
	if (true == Move)
	{
		if (64.0f >= Distance)
		{
			Move = false;
			FSM.ChangeState(EStateType::ATTACK);
		}

		Distance -= (PlayerDir * Speed * _DeltaTime).Length();
		AddRelativeLocation(PlayerDir * Speed * _DeltaTime);
		//UEngineDebug::OutPutString(std::to_string(Distance));
	}
}

void AMonster::MonsterAttack()
{

}

