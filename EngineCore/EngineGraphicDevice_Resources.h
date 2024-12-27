#pragma once

// Ό³Έν :
class EngineGraphicDevice_Resources
{
public:
	// constrcuter destructer
	EngineGraphicDevice_Resources();
	~EngineGraphicDevice_Resources();

	// delete Function
	EngineGraphicDevice_Resources(const EngineGraphicDevice_Resources& _Other) = delete;
	EngineGraphicDevice_Resources(EngineGraphicDevice_Resources&& _Other) noexcept = delete;
	EngineGraphicDevice_Resources& operator=(const EngineGraphicDevice_Resources& _Other) = delete;
	EngineGraphicDevice_Resources& operator=(EngineGraphicDevice_Resources&& _Other) noexcept = delete;

protected:

private:

};

