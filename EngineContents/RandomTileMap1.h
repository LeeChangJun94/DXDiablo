#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>
#include <algorithm>

static const int DUNGEON_WIDTH = 40;
static const int DUNGEON_HEIGHT = 40;
static const int MIN_ROOM_SIZE1 = 4;
static const int MAX_ROOM_SIZE1 = 9;
static const int BORDER_SIZE = 1;
static const int FLOOR_THRESHOLD = 700;
static const int FILL_RECT_MIN_W = 5;
static const int FILL_RECT_MIN_H = 5;
static const int FILL_RECT_MAX_W = 12;
static const int FILL_RECT_MAX_H = 14;
static const int MAX_FILL_TRIES = 100;


// ���� :
class ARandomTileMapTest : public AGameMode
{
public:
	
	struct Point {
		int x;
		int y;
	};

	// �簢 ���� ���ǿ� ����ü
	struct Rect {
		int x;      // �»�� X
		int y;      // �»�� Y
		int width;
		int height;

		// �簢 ������ ��ȿ��(�ʹ� ���� ����)�� Ȯ��
		bool isValid() const {
			return (width >= MIN_ROOM_SIZE1 && height >= MIN_ROOM_SIZE1);
		}
	};

	// ����(�մ� ��) ������ �ӽ� ������ ����ü
	struct HallwayInfo {
		Point from;
		Point to;
	};
	
	// ���� �迭(������)
	std::vector<std::vector<char>> dungeonMap;

	// ���� ������ �����ϴ� ����
	std::vector<HallwayInfo> hallwayList;

	// �簢�� ���ο� ���� �׸��� �Լ�
	// �𼭸��� 'A', 'B', 'C', 'E' ������ ǥ��, ��('#'), �ٴ�('.')�� �׸���.
	void drawRoom(const Rect& room);
	

	// �� �� ���̸� ������ ���� ���� (�ӽ�) ����
	void connectRooms(const Rect& origin, const Rect& newRoom);
	
    std::vector<Rect> subdivide(const Rect& area, const Rect& placedRoom);
    
	void createRoom(const Rect& area, Rect* originatingRoom = nullptr, bool isFirstRoom = false, bool forceLargeSetPiece = false);
	
    void drawHallways();
    
	void cleanupDungeon();
	
    // Flood Fill ���� �̿��� Ư�� ������ ������ �ѷ��ο��ִ��� ã��, ����(�ּ� 5��5, �ִ� 12��14)�� �����ϸ� �ٴ�('.')���� ä��
    bool fillVoidAreas();
    
	// ������ �����ϴ� ���� �Լ�
	bool generateDungeon();
	


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