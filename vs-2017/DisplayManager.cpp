//
//DisplayManager.cpp
//

#include "DisplayManager.h";

df::DisplayManager::DisplayManager() {
	setType("DisplayManager");
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT; 
}

// Get the one and only instance of the DisplayManager.
df::DisplayManager &df::DisplayManager::getInstance() {
	static DisplayManager instance;
	return instance;
}

// Open graphics window ready for text-based display.
// Return 0 if ok, else -1.
int df::DisplayManager::startUp() {

	if (m_p_window != NULL)
		return 0;

	m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels),WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

	m_p_window->setVerticalSyncEnabled(true);
	m_p_window->setMouseCursorVisible(false);

	if (!m_p_window || !m_font.loadFromFile(FONT_FILE_DEFAULT))
		return -1;

	Manager::startUp();
}

// Close graphics window.
void df::DisplayManager::shutDown() {
	if (m_p_window != NULL)
		delete m_p_window;
}


// Draw character at window location (x,y) with color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(df::Vector world_pos, char ch, df::Color color) const {

	// Make sure window is allocated .
	if (m_p_window == NULL)
		return -1;

	//Convert spaces (x,y) to pixels (x,y)
	df::Vector pixelPos = spacesToPixels(world_pos);

	//Draw background rectangle since test is "see through" in SFML
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixelPos.getX() - charWidth() / 10, pixelPos.getY() + charHeight() / 5);
	m_p_window->draw(rectangle);

	//Create character text to draw
	static sf::Text text("", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	//Scale to right size
	if (charWidth() < charHeight())
		text.setCharacterSize(charWidth() * 2);
	else
		text.setCharacterSize(charHeight() * 2);

	//Set SFML color based on Dragonfly color
	switch (color)
	{
	case df::UNDEFINED_COLOR:
		break;
	case df::BLACK:
		text.setColor(sf::Color::Black);
		break;
	case df::RED:
		text.setColor(sf::Color::Red);
		break;
	case df::GREEN:
		text.setColor(sf::Color::Green);
		break;
	case df::YELLOW:
		text.setColor(sf::Color::Yellow);
		break;
	case df::BLUE:
		text.setColor(sf::Color::Blue);
		break;
	case df::MAGENTA:
		text.setColor(sf::Color::Magenta);
		break;
	case df::CYAN:
		text.setColor(sf::Color::Cyan);
		break;
	case df::WHITE:
		text.setColor(sf::Color::White);
		break;
	case df::CUSTOM:
		break;
	default:
		break;
	}

	//Set position in window (in pixels)
	text.setPosition(pixelPos.getX(), pixelPos.getY());

	//Draw chracter
	m_p_window->draw(text);

	return 0;
}

// Draw character at window location (x,y) with custom color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(df::Vector world_pos, char ch, unsigned char r, unsigned char g, unsigned char b) const {

	// Make sure window is allocated .
	if (m_p_window == NULL)
		return -1;

	//Convert spaces (x,y) to pixels (x,y)
	df::Vector pixelPos = df::spacesToPixels(world_pos);

	//Draw background rectangle since test is "see through" in SFML
	static sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
	rectangle.setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	rectangle.setPosition(pixelPos.getX() - charWidth() / 10, pixelPos.getY() + charHeight() / 5);
	m_p_window->draw(rectangle);

	//Create character text to draw
	static sf::Text text("", m_font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	//Scale to right size
	if (charWidth() < charHeight())
		text.setCharacterSize(charWidth() * 2);
	else
		text.setCharacterSize(charHeight() * 2);

	//Set color based on rbg values
	text.setColor(sf::Color::Color(r, g, b, 255));

	//Set position in window (in pixels)
	text.setPosition(pixelPos.getX(), pixelPos.getY());

	//Draw chracter
	m_p_window->draw(text);

	return 0;
}


// Draw single sprite frame at window location (x,y) with color.
// If centered true, then center frame at (x,y).
// Return 0 if ok, else -1.
int df::DisplayManager::drawFrame(df::Vector world_pos, df::Frame frame, bool centered, df::Color color) const {

	//Error chack empty string
	if (frame.getString() == "")
		return -1;

	int xOffset = 0;
	int yOffset = 0;

	if (centered)
	{
		xOffset = frame.getWidth() / 2;
		yOffset = frame.getHeight() / 2;
	}

	//Frame data stored in string
	std::string str = frame.getString();

	//Draw row by row, character by character
	for (int y = 0; y < frame.getHeight(); y++) {
		for (int x = 0; x < frame.getWidth(); x++) {
			df::Vector tempPos(world_pos.getX() - xOffset + x,world_pos.getY() - yOffset + y);
			drawCh(tempPos, str[y * frame.getWidth() + x], color);
		}
	}

	return 0;
}

// Draw string at window location (x,y) with color.
// Justified left, center or right.
// Return 0 if ok, else -1.
int df::DisplayManager::drawString(df::Vector world_pos, std::string str, df::Justification just, df::Color color) const {

	//Get starting position
	df::Vector  startingPos = world_pos;
	switch (just)
	{
	case df::LEFT_JUSTIFIED:
		break;
	case df::CENTER_JUSTIFIED:
		startingPos.setX(world_pos.getX() - str.size() / 2);
		break;
	case df::RIGHT_JUSTIFIED:
		startingPos.setX(world_pos.getX() - str.size());
		break;
	default:
		break;
	}

	//Draw string character by character
	for (int i = 0; i < str.size(); i++) {
		df::Vector tempPos(startingPos.getX() + i, startingPos.getY());
		drawCh(tempPos, str[i], color);
	}

	return 0;
}

// Return window's horizontal maximum (in characters).
int df::DisplayManager::getHorizontal() const {
	return m_window_horizontal_chars;
}

// Return window's vertical maximum (in characters).
int df::DisplayManager::getVertical() const {
	return m_window_vertical_chars;
}

// Return window's horizontal maximum (in pixels).
int df::DisplayManager::getHorizontalPixels() const {
	return m_window_horizontal_pixels;
}

// Return window's vertical maximum (in pixels).
int df::DisplayManager::getVerticalPixels() const {
	return m_window_vertical_pixels;
}

// Render current window buffer.
// Return 0 if ok, else -1.
int df::DisplayManager::swapBuffers() {

	//Make sure window is allocated
	if (m_p_window == NULL)
		return -1;

	//Display current window
	m_p_window->display();

	//Clear window to get ready for next draw
	m_p_window->clear();

	return 0;
}

// Return pointer to SFML drawing window.
sf::RenderWindow * df::DisplayManager::getWindow() const
{
	return m_p_window;
}


//Compute character height
float df::charHeight() {
	df::DisplayManager &disMan = df::DisplayManager::getInstance();
	return (float)disMan.getVerticalPixels() / (float)disMan.getVertical();
}

//Compute character width
float df::charWidth() {
	df::DisplayManager &disMan = df::DisplayManager::getInstance();
	return (float)disMan.getHorizontalPixels() / (float)disMan.getHorizontal();
}

//Convert ASCII spaces (x,y) to window pixels (x,y)
df::Vector df::spacesToPixels(df::Vector spaces) {
	return df::Vector(spaces.getX() * df::charWidth(), spaces.getY() * df::charHeight());
}

//Convert window pixels (x,y) to ASCII spaces (x,y)
df::Vector df::pixelsToSpaces(df::Vector pixels) {
	return df::Vector(pixels.getX() / df::charWidth(), pixels.getY() / df::charHeight());
}