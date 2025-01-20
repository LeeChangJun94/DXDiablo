#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>


// 설명 :
class ARandomTileMapTest : public AGameMode
{
public:
	
	class BSPNode
	{
	public:

		BSPNode();
		BSPNode(int _X, int _Y, int _Width, int _Height, int _MinRoomSize);
		~BSPNode();

		bool IsLeaf() const
		{
			return (!Left && !Right);
		}

		bool Split();

		void CreateRoom();
		void DeleteBSPTree(BSPNode* Node);

		BSPNode* Left;
		BSPNode* Right;

		int X;
		int Y;
		int Width;
		int Height;

		int MinRoomSize = 4;

		int RoomX = -1;
		int RoomY = -1;
		int RoomW = 0;
		int RoomH = 0;

	private:
		UEngineRandom Random;

	};

	class DungeonGenerator
	{
	public:

		DungeonGenerator();
		DungeonGenerator(int _Width, int _Height, int _MinRoom, int _Splits);
		~DungeonGenerator();

		void Generator();
		void PrintMap(class UTileMapRenderer* _TileMapRenderer);

		void BspPartition();
		void CreateRooms()
		{
			for (auto leaf : LeafNodes)
			{
				leaf->CreateRoom();
			}
		}

		void ConnectRooms();
		void CreateCorridor(std::pair<int, int> cA, std::pair<int, int> cB);
		void FillMapData();
		void Dig(int x, int y);
		
		// 방의 중앙 좌표를 구한다
		std::pair<int, int> GetRoomCenter(BSPNode* node);
		
		// 5) 맵 연결성 검사
		void EnsureConnectivity();
		



	private:
		UEngineRandom Random;

		int MapWidth;
		int MapHeight;
		int MinRoomSize;
		int MaxSplits;

		// 2D 맵: 1이면 벽, 0이면 바닥
		std::vector<std::vector<int>> MapData;

		// BSP 루트 노드
		BSPNode* Root;

		// leaf 노드 목록
		std::vector<BSPNode*> LeafNodes; // 별도의 관리를 위해 포인터 저장
	};

	// constrcuter destructer
	ARandomTileMapTest();
	~ARandomTileMapTest();

	// delete Function
	ARandomTileMapTest(const ARandomTileMapTest& _Other) = delete;
	ARandomTileMapTest(ARandomTileMapTest&& _Other) noexcept = delete;
	ARandomTileMapTest& operator=(const ARandomTileMapTest& _Other) = delete;
	ARandomTileMapTest& operator=(ARandomTileMapTest&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	UEngineRandom Random;

protected:
	void LevelChangeStart() override;

private:
	
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};


