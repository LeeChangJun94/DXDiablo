#include "PreCompile.h"
#include "LoadingLevel.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EngineCore/EngineCore.h>
#include "TileMapEditor.h"
#include "RandomTileMap.h"
#include "TitleGameMode.h"
#include "TitleHUD.h"
#include "Player.h"

ALoadingLevel::ALoadingLevel()
{
}

ALoadingLevel::~ALoadingLevel()
{
}

void ALoadingLevel::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);


	if (true == LoadingEnd)
	{
		// 이미지를 변환 
		UEngineCore::CreateLevel<ATitleGameMode, APlayer, ATitleHUD>("Titlelevel");
		UEngineCore::CreateLevel<ATileMapEditor, APawn, AHUD>("TileMapEditor");
		UEngineCore::CreateLevel<ARandomTileMap, APawn, AHUD>("RandomTileMap");
		UEngineCore::OpenLevel("RandomTileMap");
	}

}

void ALoadingLevel::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	if (false == LoadingEnd)
	{


		Thread.Start("Loading", [this]()
			{

				// 쓰레드 모르잖아. 뚜드려 맞는다.
				{
					// 말도 안되는 겁니다.
					// 쓰레드가 살아있으려면 이 객체도 살아있어야 한다는 것을 기억핫세요.
					// UEngineThread Thread;

					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
						return;
					}
					Dir.Append("Image");
					// 로딩바 만들고 싶으면  100개면 10 10 10 10 10 10
					std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
					for (size_t i = 0; i < ImageFiles.size(); i++)
					{
						std::string FilePath = ImageFiles[i].GetPathToString();
						UEngineTexture::Load(FilePath);
					}
				}

				{
					UEngineDirectory Dir;
					if (false == Dir.MoveParentToDirectory("ContentsResources"))
					{
						MSGASSERT("리소스 폴더를 찾지 못했습니다.");
						return;
					}
					Dir.Append("Image\\Tile");

					UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
				}


				UEngineSprite::CreateSpriteToMeta("Warrior in Heavy Armor (Weaponless)_Idle_Town.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Heavy Armor (Weaponless)_Walk_Town.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Walk_Town.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Idle_Town.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Butcher_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Butcher_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Butcher_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Butcher_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Butcher_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Scavenger_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Scavenger_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Scavenger_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Scavenger_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Scavenger_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Scavenger_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Skeleton King_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton King_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton King_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton King_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton King_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton King_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Zombie_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Zombie_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Zombie_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Zombie_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Zombie_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Hidden_Attack.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Hidden_Die.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Hidden_Hit.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Hidden_Idle.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Hidden_Special.png", ".sdata");
				UEngineSprite::CreateSpriteToMeta("Hidden_Walk.png", ".sdata");

				UEngineSprite::CreateSpriteToMeta("Church Dungeon.png", ".sdata");


				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Test");
					Mat->SetVertexShader("DiabloShader.fx");
					Mat->SetPixelShader("DiabloShader.fx");
				}


				{
					std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("MyCollisionDebugMaterial1");
					Mat->SetVertexShader("EngineDebugCollisionShader.fx");
					Mat->SetPixelShader("EngineDebugCollisionShader.fx");
					// 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
					Mat->SetDepthStencilState("CollisionDebugDepth");
					Mat->SetRasterizerState("CollisionDebugRas");
				}

				//for (size_t i = 0; i < 100000; i++)
				//{
				//	UEngineDebug::OutPutString("Loading.....");
				//}

				this->LoadingEnd = true;
			});
	}
}