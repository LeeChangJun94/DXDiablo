#include "PreCompile.h"
#include "RandomTileMap1.h"
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
#include "queue"


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

	int TileCountX = 40;
	int TileCountY = 40;
	int SelectTileIndex = 0;
	int MinRoomSize = 4;
	int MaxSplits = 8;

	void TileMapMode()
	{
		{
			UEngineSprite* Sprite = TileMapRenderer->GetSprite();

			for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
			{
				UEngineTexture* Texture = Sprite->GetTexture(i);
				FSpriteData Data = Sprite->GetSpriteData(i);

				//SRV�Դϴ�
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
				// ���͸� ġ�� �ʴ°���.
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
				ARandomTileMapTest::DungeonGenerator dungeon(TileCountX, TileCountY, MinRoomSize, MaxSplits);
				dungeon.Generator();
				dungeon.PrintMap(TileMapRenderer);
				/*std::vector<std::vector<ETileType>> Map(HEIGHT, std::vector<ETileType>(WIDTH));
				GenerateDungeon(Map);

				for (int y = 0; y < HEIGHT; ++y)
				{
					for (int x = 0; x < WIDTH; ++x)
					{
						if (0 == static_cast<int>(Map[y][x]))
						{
							continue;
						}
					
						TileMapRenderer->SetTile(x, y, 1);
					}
				}*/
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
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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
					// ���� ����ȴٴ� �̾߱�
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
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
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

ARandomTileMapTest::ARandomTileMapTest()
{
	// �������� ���ּž� �մϴ�.
	// �̰� UI�����Ұ��� 
	GetWorld()->CreateCollisionProfile("Monster");

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	TileMapRenderer->SetupAttachment(RootComponent);
	TileMapRenderer->SetTileSetting(ETileMapType::Iso, "Tile", { 128.0f, 63.0f }, { 128.0f, 192.0f }, { 0.0f, 0.0f });

	// CreateDefaultSubObject<>

	// ī�޶� �����Ÿ� �ڷ� ���� 
	// ī�޶� ��ġ������ ������ ����� �Ұ��̴�.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

}

ARandomTileMapTest::~ARandomTileMapTest()
{
}

void ARandomTileMapTest::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);
}



void ARandomTileMapTest::LevelChangeStart()
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


ARandomTileMapTest::BSPNode::BSPNode()
{
}

ARandomTileMapTest::BSPNode::BSPNode(int _X, int _Y, int _Width, int _Height, int _MinRoomSize)
	: X(_X), Y(_Y), Width(_Width), Height(_Height), MinRoomSize(_MinRoomSize)
{
}

ARandomTileMapTest::BSPNode::~BSPNode()
{
}

bool ARandomTileMapTest::BSPNode::Split()
{
	if (false == IsLeaf())
	{
		return false;
	}

	bool SplitVertically = (Random.RandomInt(0, 1) == 1);

	int MaxSplit = 0;

	if (true == SplitVertically)
	{
		MaxSplit = Width;
	}
	else
	{
		MaxSplit = Height;
	}
	
	// �ּ� �� ũ�⸦ �����Ͽ�, �� ������ ������ �� �ִ��� Ȯ��
	if (MaxSplit <= MinRoomSize * 2)
	{
		return false; // ���� �Ұ�
	}

	// ���� ��ġ�� �������� ����
	int SplitPos = Random.RandomInt(MinRoomSize, MaxSplit - MinRoomSize);

	if (SplitVertically)
	{
		// ���� ����
		Left = new BSPNode(X, Y, SplitPos, Height, MinRoomSize);
		Right = new BSPNode(X + SplitPos, Y, Width - SplitPos, Height, MinRoomSize);
	}
	else {
		// ���� ����
		Left = new BSPNode(X, Y, Width, SplitPos, MinRoomSize);
		Right = new BSPNode(X, Y + SplitPos, Width, Height - SplitPos, MinRoomSize);
	}

	return true;
}

void ARandomTileMapTest::BSPNode::CreateRoom()
{
	if (false == IsLeaf())
	{
		return; // leaf ��尡 �ƴϸ� �� ���� �Ұ�
	}

	// ���� �ȿ� ���� ���� ���� ������ ���ٸ� ��ŵ
	// (�� �ּ� ũ�� + �����ڸ� margin ���)
	int Margin = 1;
	int RoomMaxW = Width - 2 * Margin;
	int RoomMaxH = Height - 2 * Margin;
	if (RoomMaxW < MinRoomSize || RoomMaxH < MinRoomSize)
	{
		return;
	}

	// �� ũ�� ���� ����
	int W = Random.RandomInt(MinRoomSize, RoomMaxW);
	int H = Random.RandomInt(MinRoomSize, RoomMaxH);

	// �� ��ġ�� ���� ���ο��� ���� ��ġ
	int RX = X + Random.RandomInt(Margin, Width - W - Margin);
	int RY = Y + Random.RandomInt(Margin, Height - H - Margin);

	RoomX = RX;
	RoomY = RY;
	RoomW = W;
	RoomH = H;
}

void ARandomTileMapTest::BSPNode::DeleteBSPTree(BSPNode* Node)
{
	if (!Node)
	{
		return;
	}
	DeleteBSPTree(Node->Left);
	DeleteBSPTree(Node->Right);

	delete Node;
}




ARandomTileMapTest::DungeonGenerator::DungeonGenerator()
{
}

ARandomTileMapTest::DungeonGenerator::DungeonGenerator(int _Width, int _Height, int _MinRoom, int _Splits)
	: MapWidth(_Width), MapHeight(_Height), MinRoomSize(_MinRoom), MaxSplits(_Splits)
{
	// �� 2D �迭 �ʱ�ȭ(��=1)
	MapData.resize(MapHeight, std::vector<int>(MapWidth, 1));
	// ��Ʈ ��� ����
	Root = new BSPNode(0, 0, MapWidth, MapHeight, MinRoomSize);
}

ARandomTileMapTest::DungeonGenerator::~DungeonGenerator()
{
}

void ARandomTileMapTest::DungeonGenerator::Generator()
{
	BspPartition();
	CreateRooms();
	ConnectRooms();
	FillMapData();
	//EnsureConnectivity();
}

void ARandomTileMapTest::DungeonGenerator::PrintMap(UTileMapRenderer* _TileMapRenderer)
{
	for (int y = 0; y < MapHeight; ++y)
	{
		for (int x = 0; x < MapWidth; ++x)
		{
			if (MapData[y][x] == 0)
			{
				_TileMapRenderer->SetTile(x, y, 0);
			}
			else
			{
				_TileMapRenderer->SetTile(x, y, 1);
			}
		}
	}
}

void ARandomTileMapTest::DungeonGenerator::BspPartition()
{
	std::vector<BSPNode*> Nodes;
	Nodes.push_back(Root);

	for (int i = 0; i < MaxSplits; ++i)
	{
		bool DidSplit = false;
		std::vector<BSPNode*> NewNodes;
		for (auto Node : Nodes)
		{
			if (Node->IsLeaf() && Node->Split())
			{
				// ���� ���� -> �ڽ� ��� 2��
				NewNodes.push_back(Node->Left);
				NewNodes.push_back(Node->Right);
				DidSplit = true;
			}
			else
			{
				NewNodes.push_back(Node);
			}
		}

		Nodes = NewNodes;
		// �̹� �������� ������ ���� �Ͼ�� �ʾҴٸ� ����
		if (false == DidSplit)
		{
			break;
		}
	}

	// leaf ��常 ����
	LeafNodes.clear();
	for (auto n : Nodes) {
		if (n->IsLeaf()) {
			LeafNodes.push_back(n);
		}
	}

}

void ARandomTileMapTest::DungeonGenerator::ConnectRooms()
{
	// BFS�� ť�� ���� Ʈ���� ��ȸ�ϸ鼭, 
	// parent->left, parent->right ��尡 ���� �� �� ����
	std::queue<BSPNode*> q;
	q.push(Root);

	while (!q.empty())
	{
		BSPNode* Node = q.front();
		q.pop();

		BSPNode* Left = Node->Left;
		BSPNode* Right = Node->Right;
		if (Left && Right) {
			// �� �ڽ� ��尡 ���� ���� ������ �ִٸ� ���� ����
			auto CenterA = GetRoomCenter(Left);
			auto CenterB = GetRoomCenter(Right);

			if (CenterA.first >= 0 && CenterB.first >= 0) {
				CreateCorridor(CenterA, CenterB);
			}

			q.push(Left);
			q.push(Right);
		}
	}
}

void ARandomTileMapTest::DungeonGenerator::CreateCorridor(std::pair<int, int> cA, std::pair<int, int> cB)
{
	int x1 = cA.first;
	int y1 = cA.second;
	int x2 = cB.first;
	int y2 = cB.second;

	// ���η� ���� �İ�, ���η� �Ǵ� (����)
	if (x2 < x1) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	// ���� ����
	for (int x = x1; x <= x2; x++)
	{
		Dig(x, y1);
	}

	// ���� ����
	if (y2 < y1)
	{
		std::swap(y1, y2);
	}
	for (int y = y1; y <= y2; y++)
	{
		Dig(x2, y);
	}
}

void ARandomTileMapTest::DungeonGenerator::FillMapData()
{
	for (auto leaf : LeafNodes)
	{
		if (leaf->RoomX >= 0)
		{
			int rx = leaf->RoomX;
			int ry = leaf->RoomY;
			int rw = leaf->RoomW;
			int rh = leaf->RoomH;
			for (int y = ry; y < ry + rh; ++y)
			{
				for (int x = rx; x < rx + rw; ++x)
				{
					Dig(x, y);
				}
			}
		}
	}
}

void ARandomTileMapTest::DungeonGenerator::Dig(int _X, int _Y)
{
	if (_X >= 0 && _X < MapWidth && _Y >= 0 && _Y < MapHeight)
	{
		MapData[_Y][_X] = 0;
	}
}

std::pair<int, int> ARandomTileMapTest::DungeonGenerator::GetRoomCenter(BSPNode* _Node)
{
	if (_Node->RoomW > 0 && _Node->RoomH > 0)
	{
		int cx = _Node->RoomX + _Node->RoomW / 2;
		int cy = _Node->RoomY + _Node->RoomH / 2;
		return std::make_pair(cx, cy);
	}
	return std::make_pair(-1, -1);
}

void ARandomTileMapTest::DungeonGenerator::EnsureConnectivity()
{
	// ù ��°�� �߰ߵǴ� �ٴ�(0)�� ���������� BFS
	std::pair<int, int> start(-1, -1);
	for (int y = 0; y < MapHeight; ++y)
	{
		for (int x = 0; x < MapWidth; ++x)
		{
			if (MapData[y][x] == 0)
			{
				start = { x, y };
				break;
			}
		}
		if (start.first >= 0) break;
	}

	if (start.first < 0)
	{
		// �ٴ��� ���� ������ �׳� ����
		//std::cout << "[INFO] �ٴ��� �ϳ��� �����ϴ�.\n";
		return;
	}

	// BFS�� �湮
	std::vector<std::vector<bool>> visited(MapHeight, std::vector<bool>(MapWidth, false));
	std::queue<std::pair<int, int>> q;
	q.push(start);
	visited[start.second][start.first] = true;

	const std::vector<std::pair<int, int>> dirs = { {1,0},{-1,0},{0,1},{0,-1} };
	while (!q.empty())
	{
		auto [cx, cy] = q.front();
		q.pop();

		for (auto& d : dirs)
		{
			int nx = cx + d.first;
			int ny = cy + d.second;
			if (nx >= 0 && nx < MapWidth && ny >= 0 && ny < MapHeight)
			{
				if (!visited[ny][nx] && MapData[ny][nx] == 0)
				{
					visited[ny][nx] = true;
					q.push({ nx, ny });
				}
			}
		}
	}

	// ��� �ٴ� ��ǥ�� ã��, visited ���� ���� ���� �ִ��� Ȯ��
	std::vector<std::pair<int, int>> allFloor;
	for (int y = 0; y < MapHeight; ++y)
	{
		for (int x = 0; x < MapWidth; ++x)
		{
			if (MapData[y][x] == 0) {
				allFloor.push_back({ x, y });
			}
		}
	}

	std::vector<std::pair<int, int>> notConnected;
	for (auto& pos : allFloor) {
		if (!visited[pos.second][pos.first])
		{
			notConnected.push_back(pos);
		}
	}

	if (!notConnected.empty())
	{
		//std::cout << "[INFO] ������� ���� ������ �����մϴ�. (����: "	<< notConnected.size() << ")\n";
		// �ʿ� ��, �߰� ���� �����̳� �ٸ� ��ó�� ������ ���⿡ ���� ����

	}
	else
	{
		//std::cout << "[INFO] ��� �ٴ��� ����Ǿ� �ֽ��ϴ�.\n";
	}
}

