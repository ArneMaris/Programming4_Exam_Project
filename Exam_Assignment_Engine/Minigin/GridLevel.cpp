#include "MiniginPCH.h"
#include "GridLevel.h"
#include "ResourceManager.h"




dae::GridLevel::GridLevel(const std::wstring & levelFilePath)
{
	std::wstring fullPath = { ResourceManager::GetInstance().GetResourcesPath() + levelFilePath };

	{
		Logger::GetInstance().LogError(L"Level file could not be loaded, check filePath and try again! no Level loaded now!");
		return;
	}

}

dae::GridLevel::~GridLevel()
{
}
