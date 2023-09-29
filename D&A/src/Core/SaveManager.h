#pragma once

class SaveManager
{
public:

	SaveManager();
	~SaveManager();

	void Save();
	void LoadSave(unsigned int saveIndex);
	void DeleteSave(unsigned int saveIndex);

	void SaveOptions();
	void LoadOptions();

	void LoadConfig();

	std::string GetInfo(unsigned int saveIndex);
	inline int GetSaveIndex() { return m_SaveIndex; }
	void ResetVariables();

private:

	int m_SaveIndex = 0;
};