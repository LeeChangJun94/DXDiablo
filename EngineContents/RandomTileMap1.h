#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>
#include <algorithm>

static const int DUNGEON_WIDTH = 40;
static const int DUNGEON_HEIGHT = 40;
static const int MIN_ROOM_SIZE1 = 5;
static const int MAX_ROOM_SIZE1 = 9;
static const int BORDER_SIZE = 1;
static const int FLOOR_THRESHOLD = 600;
static const int FILL_RECT_MIN_W = 5;
static const int FILL_RECT_MIN_H = 5;
static const int FILL_RECT_MAX_W = 12;
static const int FILL_RECT_MAX_H = 14;
static const int MAX_FILL_TRIES = 100;



// ���� :
class ARandomTileMapTest : public AGameMode
{
public:
	
	struct Point
	{
		int X;
		int Y;
	};

	// �簢 ���� ���ǿ� ����ü
	struct Rect
	{
		int X;      // �»�� X
		int Y;      // �»�� Y
		int Width;
		int Height;

		// �簢 ������ ��ȿ��(�ʹ� ���� ����)�� Ȯ��
		bool IsValid() const
		{
			return (Width >= MIN_ROOM_SIZE1 && Height >= MIN_ROOM_SIZE1);
		}
	};

	// ����(�մ� ��) ������ �ӽ� ������ ����ü
	struct HallwayInfo
	{
		Point From;
		Point To;
		int Size;
	};
	
	struct RoomData
	{
		Rect RoomRect;
		int RoomNum;
	};

	// ���� �迭(������)
	std::vector<std::vector<char>> DungeonMap;

	std::vector<RoomData> RoomList;

	// ���� ������ �����ϴ� ����
	std::vector<HallwayInfo> HallwayList;

	// �簢�� ���ο� ���� �׸��� �Լ�
	// �𼭸��� 'A', 'B', 'C', 'E' ������ ǥ��, ��('#'), �ٴ�('.')�� �׸���.
	void DrawRoom(const Rect& _Room);
	

	// �� �� ���̸� ������ ���� ���� (�ӽ�) ����
	void ConnectRooms(const Rect& _Origin, const Rect& _NewRoom);
	
    std::vector<Rect> Subdivide(const Rect& _Area, const Rect& _PlacedRoom);
    
	void CreateRoom(const Rect& _Area, Rect* _OriginatingRoom = nullptr, bool _IsFirstRoom = false, bool _ForceLargeSetPiece = false);
	
    void DrawHallways();
    
	void CleanupDungeon();
	
    // Flood Fill ���� �̿��� Ư�� ������ ������ �ѷ��ο��ִ��� ã��, ����(�ּ� 5��5, �ִ� 12��14)�� �����ϸ� �ٴ�('.')���� ä��
    bool FillVoidAreas();
    
	// ������ �����ϴ� ���� �Լ�
	bool GenerateDungeon();
	


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
	
	int RoomCount = 0;
	
protected:
	void LevelChangeStart() override;

private:
	
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};