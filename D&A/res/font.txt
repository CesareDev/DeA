font use:

esempio charactersize = 30;

sf::Font font;
font.loadFromFile("res/DungeonFont.ttf");


((sf::Texture&)font.getTexture(charactersize)).setSmooth(false);
sf::Text t("Ciao a tutti", font, charactersize);
target.draw(t);