#pragma once

class SaveManager
{
public:

	SaveManager();
	~SaveManager();

	void Save();
	void LoadSave(unsigned int saveIndex);

private:

	int m_SaveIndex = 0;
};