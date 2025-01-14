#include "PreCompile.h"
#include "RandomTileMap.h"
#include "Zombie.h"
#include "Hidden.h"
#include <EngineBase/EngineRandom.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TileMapRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EnginePlatform/EngineInput.h>


enum class EEditMode
{
	TileMap,
	Object,
};

enum class ESpawnList
{
	Zombie,
	Hidden,
};

class UTileMapWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;
	int ObjectItem = -1;
	UTileMapRenderer* TileMapRenderer = nullptr;
	UEngineRandom Random;
	EEditMode Mode = EEditMode::TileMap;

	//std::list<std::shared_ptr<AMonster>> AllMonsterList;

	int TileCountX = 30;
	int TileCountY = 30;
	int SelectTileIndex = 0;

	void TileMapMode()
	{
		{
			UEngineSprite* Sprite = TileMapRenderer->GetSprite();

			for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
			{
				UEngineTexture* Texture = Sprite->GetTexture(i);
				FSpriteData Data = Sprite->GetSpriteData(i);

				//SRV입니다
				ImTextureID SRV = reinterpret_cast<ImTextureID>(Texture->GetSRV());

				std::string Text = std::to_string(i);

				if (i != 0)
				{
					if (0 != (i % 10))
					{
						ImGui::SameLine();
					}
				}


				ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
				ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };

				if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
				{
					SelectTileIndex = static_cast<int>(i);
				}
				// 엔터를 치지 않는개념.
			}

			ImGui::InputInt("TileMapX", &TileCountX);
			ImGui::InputInt("TileMapY", &TileCountY);

			if (ImGui::Button("TileMap Create"))
			{
				for (int y = 0; y < TileCountY; y++)
				{
					for (int x = 0; x < TileCountX; x++)
					{
						TileMapRenderer->SetTile(x, y, SelectTileIndex);
					}
				}
			}

			if (ImGui::Button("RandomMap Create"))
			{
				std::vector<std::vector<ETileType>> Map(HEIGHT, std::vector<ETileType>(WIDTH));
				GenerateDungeon(Map);

				for (int y = 0; y < HEIGHT; ++y)
				{
					for (int x = 0; x < WIDTH; ++x)
					{
						if (0 == static_cast<int>(Map[y][x]))
						{
							continue;
						}
					
						TileMapRenderer->SetTile(x, y, 0);
					}
				}
			}

			if (true == UEngineInput::IsPress(VK_LBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

				TileMapRenderer->SetTile(ScreenPos, SelectTileIndex);
			}

			if (true == UEngineInput::IsPress(VK_RBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

				TileMapRenderer->RemoveTile(ScreenPos);
			}
		}
	}

	void ObjectMode()
	{
		{
			std::vector<const char*> Arr;
			Arr.push_back("Monster");
			Arr.push_back("Monster2");


			ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

			// GetMainWindow()->IsScreenOut();


			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
				std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
				FVector Pos = Camera->ScreenMousePosToWorldPos();
				Pos.Z = 0.0f;

				std::shared_ptr<AMonster> NewMonster;

				switch (SelectMonster)
				{
				case ESpawnList::Zombie:
					NewMonster = GetWorld()->SpawnActor<AZombie>("Zombie");
					break;
				case ESpawnList::Hidden:
					NewMonster = GetWorld()->SpawnActor<AHidden>("Hidden");
					break;
				default:
					break;
				}

				NewMonster->SetActorLocation(Pos);
				//AllMonsterList.push_back(NewMonster);

			}
		}

		{
			if (ImGui::Button("EditObjectDelete"))
			{
				std::list<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMonster>();
				for (std::shared_ptr<AMonster> Monster : AllMonsterList)
				{
					Monster->Destroy();
				}

			}
		}

		{
			std::vector<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorArrayByClass<AMonster>();
			std::vector<std::string> ArrString;
			for (std::shared_ptr<class AActor> Actor : AllMonsterList)
			{
				ArrString.push_back(Actor->GetName());
			}

			std::vector<const char*> Arr;
			for (size_t i = 0; i < ArrString.size(); i++)
			{
				Arr.push_back(ArrString[i].c_str());
			}


			if (0 < Arr.size())
			{
				ImGui::ListBox("AllActorList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

				// AllMonsterList[SelectItem]->Destroy();

				if (ObjectItem != -1)
				{
					// AllMonsterList[ObjectItem]->
				}

				if (true == ImGui::Button("Delete"))
				{
					AllMonsterList[ObjectItem]->Destroy();
					ObjectItem = -1;
				}

			}
		}

	}

	void SaveAndLoad()
	{
		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrDefExt = "MapData";
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				std::list<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMonster>();

				UEngineSerializer Ser;

				Ser << static_cast<int>(AllMonsterList.size());

				for (std::shared_ptr<AMonster> Actor : AllMonsterList)
				{

					Ser << static_cast<int>(Actor->MonsterTypeValue);
					// 여기 저장된다는 이야기
					Actor->Serialize(Ser);
				}

				TileMapRenderer->Serialize(Ser);

				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);

				NewFile.FileOpen("wb");
				NewFile.Write(Ser);
			}
		}

		if (true == ImGui::Button("Load"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
				UEngineSerializer Ser;

				NewFile.FileOpen("rb");
				NewFile.Read(Ser);


				int MonsterCount = 0;

				Ser >> MonsterCount;

				for (size_t i = 0; i < MonsterCount; i++)
				{
					int MonsterTypeValue = 0;
					Ser >> MonsterTypeValue;

					EMonsterType MonsterType = static_cast<EMonsterType>(MonsterTypeValue);

					std::shared_ptr<AMonster> NewMon = nullptr;

					switch (MonsterType)
					{
					case ZOMBIE:
						NewMon = GetWorld()->SpawnActor<AZombie>();
						break;
					case HIDDEN:
						NewMon = GetWorld()->SpawnActor<AHidden>();
						break;
					default:
						break;
					}

					NewMon->DeSerialize(Ser);
				}

				TileMapRenderer->DeSerialize(Ser);
			}
		}
	}

	void OnGUI() override
	{

		if (Mode == EEditMode::Object)
		{
			if (ImGui::Button("ObjectMode"))
			{
				Mode = EEditMode::TileMap;
			}
		}
		else
		{
			if (ImGui::Button("TileMapMode"))
			{
				Mode = EEditMode::Object;
			}
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		switch (Mode)
		{
		case EEditMode::TileMap:
			TileMapMode();
			break;
		case EEditMode::Object:
			ObjectMode();
			break;
		default:
			break;
		}

		SaveAndLoad();
	}
};

ARandomTileMap::ARandomTileMap()
{
	// 레벨마다 해주셔야 합니다.
	// 이걸 UI공유할건지 
	GetWorld()->CreateCollisionProfile("Monster");

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;


	//PivotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//PivotSpriteRenderer->SetupAttachment(RootComponent);
	//PivotSpriteRenderer->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	TileMapRenderer->SetupAttachment(RootComponent);
	TileMapRenderer->SetTileSetting(ETileMapType::Iso, "Tile", { 128.0f, 63.0f }, { 128.0f, 192.0f }, { 0.0f, 0.0f });

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			//Map[y][x] = static_cast<int>(ETileType::WALL);
		}
	}


	// CreateDefaultSubObject<>



	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

}

ARandomTileMap::~ARandomTileMap()
{
}

void ARandomTileMap::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);
}

//void ARandomTileMap::PrintMap(const std::vector<std::vector<ETileType>>& _Map)
//{
//	for (int y = 0; y < HEIGHT; ++y)
//	{
//		for (int x = 0; x < WIDTH; ++x)
//		{
//			if (0 == static_cast<int>(_Map[y][x]))
//			{
//				continue;
//			}
//
//			TileMapRenderer->SetTile(x, y, 0);
//		}
//	}
//}

//FRoom CreateRoom(int _X, int _Y)
//{
//	FRoom Room;
//	Room.X = _X;
//	Room.Y = _Y;
//	Room.Width = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
//	Room.Height = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE + 1) + MIN_ROOM_SIZE;
//	return Room;
//}

FRoomNode* SplitRoom(int _X, int _Y, int _Width, int _Height, int _MinRoomSize)
{
	UEngineRandom Random;

	if (_Width <= _MinRoomSize * 2 && _Height <= _MinRoomSize * 2)
	{
		FRoomNode* Node = new FRoomNode(_X, _Y, _Width, _Height);
		Node->Room = FRoom(_X + 1, _Y + 1, _Width - 2, _Height - 2);
		return Node;
	}

	bool SplitHorizontal = _Width > _Height;  // 수평 또는 수직 분할
	if (_Width > _Height && _Width / 2 >= _MinRoomSize)
	{
		SplitHorizontal = true;
	}
	if (_Height > _Width && _Width / 2 >= _MinRoomSize)
	{
		SplitHorizontal = false;
	}
		
	if (SplitHorizontal)
	{
		int SplitX = Random.RandomInt(0, _Width - _MinRoomSize * 2) + _MinRoomSize;
		FRoomNode* Left = SplitRoom(_X, _Y, SplitX, _Height, _MinRoomSize);
		FRoomNode* Right = SplitRoom(_X + SplitX, _Y, _Width - SplitX, _Height, _MinRoomSize);
		FRoomNode* Node = new FRoomNode(_X, _Y, _Width, _Height);
		Node->_Left = Left;
		Node->_Right = Right;
		return Node;
	}
	else
	{
		int SplitY = Random.RandomInt(0, _Height - _MinRoomSize * 2) + _MinRoomSize;
		FRoomNode* Left = SplitRoom(_X, _Y, _Width, SplitY, _MinRoomSize);
		FRoomNode* Right = SplitRoom(_X, _Y + SplitY, _Width, _Height - SplitY, _MinRoomSize);
		FRoomNode* Node = new FRoomNode(_X, _Y, _Width, _Height);
		Node->_Left = Left;
		Node->_Right = Right;
		return Node;
	}
}

void GenerateDungeon(std::vector<std::vector<ETileType>>& _Map)
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			_Map[y][x] = ETileType::EMPTY;
		}
	}

	std::vector<FRoom> Rooms;
	FRoomNode* Root = SplitRoom(0, 0, WIDTH, HEIGHT, MIN_ROOM_SIZE);

	Traverse(Root, Rooms);

	for (const FRoom& Room : Rooms)
	{
		for (int y = Room.Y; y < Room.Y + Room.Height; ++y)
		{
			for (int x = Room.X; x < Room.X + Room.Width; ++x)
			{
				if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
				{
					_Map[y][x] = ETileType::WALL;
				}
			}
		}
	}

	for (size_t i = 1; i < Rooms.size(); ++i)
	{
		const FRoom& Prev = Rooms[i - 1];
		const FRoom& Curr = Rooms[i];

		int StartX = (Prev.X + Prev.X + Prev.Width) / 2;
		int StartY = (Prev.Y + Prev.Y + Prev.Height) / 2;
		int EndX = (Curr.X + Curr.X + Curr.Width) / 2;
		int EndY = (Curr.Y + Curr.Y + Curr.Height) / 2;

		while (StartX != EndX)
		{
			_Map[StartY][StartX] = ETileType::WALL;
			StartX += (StartX < EndX) ? 1 : -1;
		}
		while (StartY != EndY)
		{
			_Map[StartY][StartX] = ETileType::WALL;
			StartY += (StartY < EndY) ? 1 : -1;
		}
	}

	DeleteBSPTree(Root);
}

void Traverse(FRoomNode* _Node, std::vector<FRoom>& _Rooms)
{
	if (_Node == nullptr)
	{
		return;
	}

	if (_Node->_Left == nullptr && _Node->_Right == nullptr)
	{
		_Rooms.push_back(_Node->Room);
		return;
	}

	Traverse(_Node->_Left, _Rooms);
	Traverse(_Node->_Right, _Rooms);
}

void DeleteBSPTree(FRoomNode* Node)
{
	if (!Node)
	{
		return;
	}
	DeleteBSPTree(Node->_Left);
	DeleteBSPTree(Node->_Right);

	delete Node;
}


void ARandomTileMap::LevelChangeStart()
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
		TileMapWindow = UEngineGUI::FindGUIWindow<UTileMapWindow>("TileMapWindow");

		if (nullptr == TileMapWindow)
		{
			TileMapWindow = UEngineGUI::CreateGUIWindow<UTileMapWindow>("TileMapWindow");
		}

		TileMapWindow->SetActive(true);
		TileMapWindow->TileMapRenderer = TileMapRenderer.get();
	}

}

