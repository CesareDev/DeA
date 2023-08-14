#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <ShObjIdl_core.h>

int main() 
{
    std::string spritePath;
    std::string texturePath = "..\\..\\..\\res\\map\\tileset.png";

    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    HRESULT init = CoInitialize(nullptr);
    if (SUCCEEDED(init))
    {
        IFileDialog* file;
        if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&file))))
        {
            file->SetTitle(L"Select the sprite image");;
            
            COMDLG_FILTERSPEC rgSpec[] =
            {
                { L"PNG file", L"*.png;"},
            };

            file->SetFileTypes(1, rgSpec);

            file->Show(NULL);

            IShellItem* result = nullptr;
            HRESULT pick = file->GetResult(&result);
            if (SUCCEEDED(pick))
            {
                wchar_t* pathBuffer = nullptr;
                HRESULT end = result->GetDisplayName(SIGDN_FILESYSPATH, &pathBuffer);
                if (SUCCEEDED(end))
                {
                    unsigned int i = 0;
                    while (pathBuffer[i] != '\0')
                    {
                        spritePath.push_back(char(pathBuffer[i]));
                        ++i;
                    }

                    sf::Image customSprite;
                    sf::Image targetTexture;

                    if (targetTexture.loadFromFile(texturePath))
                    {
                        if (!customSprite.loadFromFile(spritePath))
                        {
                            std::cout << "Make sure the image is named \"sprite.png\" and is inside the folder \"custom-character\"" << std::endl;
                        }
                        else
                        {
                            targetTexture.copy(customSprite, 0, 464, {0, 24, 64, 64});

                            if (!targetTexture.saveToFile(texturePath))
                                std::cout << "Can't save the texture file" << std::endl;

                            std::string delPath = "del " + spritePath;
                            system(delPath.c_str());

                            std::cout << "Sprite load successfully!" << std::endl;
                        }
                    }
                }
                delete[] pathBuffer;
            }
            if (result)
                result->Release();
        }
        file->Release();
        CoUninitialize();
    }

	std::cout << "Press any key...";
	std::cin.get();
	return 0;
}