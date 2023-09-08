#pragma once

class SaveManager
{
public:

	SaveManager();
	~SaveManager();

	void Save();
	void LoadSave(unsigned int saveIndex);
	void DeleteSave(unsigned int saveIndex);

	void SaveConfig();
	void LoadConfig();

	std::string GetInfo(unsigned int saveIndex);

private:

	void ResetVariables();

	int m_SaveIndex = 0;
};