#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class ATileMapEditor : public AGameMode
{
public:
	// constrcuter destructer
	ATileMapEditor();
	~ATileMapEditor();

	// delete Function
	ATileMapEditor(const ATileMapEditor& _Other) = delete;
	ATileMapEditor(ATileMapEditor&& _Other) noexcept = delete;
	ATileMapEditor& operator=(const ATileMapEditor& _Other) = delete;
	ATileMapEditor& operator=(ATileMapEditor&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;

private:
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};

