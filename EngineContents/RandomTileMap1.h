#pragma once
#include <EngineCore/GameMode.h>

class BSPNode
{
public:
	int X;
	int Y;
	int Width;
	int Height;

	int MinRoomSize;

	BSPNode* Left;
	BSPNode* Right;

	int RoomX = -1;
	int RoomY = -1;
	int RoomW = 0;
	int RoomH = 0;


};




// Ό³Έν :
class ARandomTileMap1 : public AGameMode
{
public:
	
	// constrcuter destructer
	ARandomTileMap1();
	~ARandomTileMap1();

	// delete Function
	ARandomTileMap1(const ARandomTileMap1& _Other) = delete;
	ARandomTileMap1(ARandomTileMap1&& _Other) noexcept = delete;
	ARandomTileMap1& operator=(const ARandomTileMap1& _Other) = delete;
	ARandomTileMap1& operator=(ARandomTileMap1&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);


protected:
	void LevelChangeStart() override;

private:

	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};

