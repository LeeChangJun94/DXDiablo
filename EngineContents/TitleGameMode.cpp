#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "Player.h"
#include "Zombie.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("WindowButton"))
		{
			std::shared_ptr<AZombie> NewZombie = GetWorld()->SpawnActor<AZombie>();
			NewZombie->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("test");

	}
};

ATitleGameMode::ATitleGameMode()
{

	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");

	GetWorld()->LinkCollisionProfile("Player", "Monster");

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	//Camera->GetCameraComponent()->SetZSort(0, true);

	{
		Player = GetWorld()->SpawnActor<APlayer>();
		Player->SetActorLocation({ 300.0f, 0.0f, 0.0f });
		//Player->GetRenderer()->SetSpriteData(4);
	}

	{
		Zombie = GetWorld()->SpawnActor<AZombie>();
	}


	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	//if (nullptr == Logo && true == Logo->IsDestroy())
	//{
	//	Logo = nullptr;
	//}
}

	void ATitleGameMode::LevelChangeStart()
	{
		UEngineGUI::AllWindowOff();

		{
			std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

			if (nullptr == Window)
			{
				Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
			}

			Window->SetActive(true);
		}

		{
			std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

			if (nullptr == Window)
			{
				Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
			}

			Window->SetActive(true);
		}
	}