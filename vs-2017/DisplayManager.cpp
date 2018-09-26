//
//DisplayManager.cpp
//

#include "DisplayManager.h"
#include "LogManager.h"
#include "Vector.h"
#include "Color.h"
#include "utility.h"


// Compute character height, based on window size and font.
float df::charHeight(void) {
	return df::DisplayManager::getInstance().getVerticalPixels() / df::DisplayManager::getInstance().getVertical();
}

// Compute character width, based on window size and font.
float df::charWidth(void) {
	return df::DisplayManager::getInstance().getHorizontalPixels() / df::DisplayManager::getInstance().getHorizontal();
}

// Convert ASCII spaces (x,y) to window pixels (x,y).
df::Vector df::spacesToPixels(df::Vector spaces) {
	df::Vector vect;
	vect.setXY(spaces.getX()*df::charWidth(), spaces.getY()*df::charHeight());
	return vect;
}

// Convert window pixels (x,y) to ASCII spaces (x,y).
df::Vector df::pixelsToSpaces(df::Vector pixels) {
	df::Vector vect;
	vect.setXY(pixels.getX()/df::charWidth(),pixels.getY()/df::charHeight());
	return vect;
}

df::DisplayManager::DisplayManager() {
	setType("DisplayManager");
	m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	m_p_rectangle = new sf::RectangleShape();
	m_p_text = new sf::Text("", m_font);
}

df::DisplayManager::DisplayManager(DisplayManager const&) {}

void df::DisplayManager::operator=(DisplayManager const&) {}

// Get the one and only instance of the DisplayManager.
df::DisplayManager &df::DisplayManager::getInstance() {
	static DisplayManager displayManager;
	return displayManager;
}

// Open graphics window ready for text-based display.
// Return 0 if ok, else -1.
int df::DisplayManager::startUp() {

	//If window is already created, return
	if (m_p_window != NULL)
		return 0;

	m_p_window = new sf::RenderWindow(sf::VideoMode(m_window_horizontal_pixels, m_window_vertical_pixels), WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

	m_p_window->setMouseCursorVisible(false); //Hide cursor in window
	//m_p_window->setVerticalSyncEnabled(true); //Sync window to monitor refresh rate


	if (!m_font.loadFromFile(FONT_FILE_DEFAULT)) {
		LM.writeLog("Error! Unable to load font 'df-font.ttf'.");
		return -1;
	}
	else
		LM.writeLog("Loaded font");

	if (df::Manager::startUp() == 0) //Start Manager
		return 0;

	return -1;
}

// Close graphics window.
void df::DisplayManager::shutDown() {
	m_p_window->close(); //Close window
}

// Draw character at window location (x,y) with color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
	if (m_p_window == NULL)
		return -1;

	df::Vector view_pos = worldToView(world_pos); //change view based on world position

	//Convert spaces to pixels
	df::Vector pixel_pos = spacesToPixels(world_pos);

	//Draw background rectangle
	m_p_rectangle->setSize(sf::Vector2f(charWidth(), charHeight()));
	m_p_rectangle->setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	m_p_rectangle->setPosition(pixel_pos.getX() - charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
	//m_p_window->draw(*m_p_rectangle);

	//Create character text to draw
	m_p_text->setString(ch);
	m_p_text->setStyle(sf::Text::Bold); //Make bold cuz it looks fly

	//Scale to the right size
	if (charWidth() < charHeight()) {
		m_p_text->setCharacterSize(charWidth() * 2);
	}
	else {
		m_p_text->setCharacterSize(charHeight() * 2);
	}

	//Set SFML color based on Dragonfly color
	switch (color) {
	case df::YELLOW:
		m_p_text->setFillColor(sf::Color::Yellow);
		break;
	case df::RED:
		m_p_text->setFillColor(sf::Color::Red);
		break;
	case df::BLACK:
		m_p_text->setFillColor(sf::Color::Black);
		break;
	case df::GREEN:
		m_p_text->setFillColor(sf::Color::Green);
		break;
	case df::BLUE:
		m_p_text->setFillColor(sf::Color::Blue);
		break;
	case df::MAGENTA:
		m_p_text->setFillColor(sf::Color::Magenta);
		break;
	case df::CYAN:
		m_p_text->setFillColor(sf::Color::Cyan);
		break;
	case df::WHITE:
		m_p_text->setFillColor(sf::Color::White);
		break;
	case df::UNDEFINED_COLOR:
		break;
	}

	m_p_text->setPosition(pixel_pos.getX(), pixel_pos.getY());

	m_p_window->draw(*m_p_text);

	return 0;
}

// Draw character at window location (x,y) with custom color.
// Return 0 if ok, else -1.
int df::DisplayManager::drawCh(Vector world_pos, char ch, unsigned char r,
	unsigned char g, unsigned char b) const {

	if (m_p_window == NULL)
		return -1;

	df::Vector view_pos = worldToView(world_pos); //change view based on world position

	//Convert spaces to pixels
	df::Vector pixel_pos = df::spacesToPixels(world_pos);

	//Draw background rectangle
	m_p_rectangle->setSize(sf::Vector2f(charWidth(), charHeight()));
	m_p_rectangle->setFillColor(WINDOW_BACKGROUND_COLOR_DEFAULT);
	m_p_rectangle->setPosition(pixel_pos.getX() - df::charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
	m_p_window->draw(*m_p_rectangle);

	//Create character text to draw
	m_p_text->setString(ch);
	m_p_text->setStyle(sf::Text::Bold); //Make bold cuz it looks fly

	//Scale to the right size
	if (df::charWidth() < df::charHeight())
		m_p_text->setCharacterSize(df::charWidth() * 2);
	else
		m_p_text->setCharacterSize(df::charHeight() * 2);

	//Set SFML color based on Dragonfly color and RGB values
	m_p_text->setFillColor(sf::Color::Color(r, g, b, 255));

	m_p_text->setPosition(pixel_pos.getX(), pixel_pos.getY());

	m_p_window->draw(*m_p_text);

	return 0;
}

// Draw single sprite frame at window location (x,y) with color.
// If centered true, then center frame at (x,y).
// Return 0 if ok, else -1.
int df::DisplayManager::drawFrame(Vector world_pos, Frame frame, bool centered,
	Color color, char transparent) const {

	float x_offset, y_offset;

	if (frame.getString() == "") {
		LM.writeLog("Sprite missing frame");
		return -1;
	}

	//Centered? then offset x,y by 1/2
	if (centered) {
		x_offset = frame.getWidth() / 2;
		y_offset = frame.getHeight() / 2;
	}
	else {
		x_offset = 0;
		y_offset = 0;
	}

	//Frame data stored in string
	std::string str = frame.getString();

	//Draw row by row, character by character
	for (int y = 0; y < frame.getHeight(); y++)
		for (int x = 0; x < frame.getWidth(); x++) {
			if (transparent == NULL || str[y*frame.getWidth() + x] != transparent) {
				df::Vector temp_pos(world_pos.getX() - x_offset + x, world_pos.getY() - y_offset + y);
				drawCh(temp_pos, str[y*frame.getWidth() + x], color);
			}
		}

	return 0;
}

// Draw string at window location (x,y) with color.
// Justified left, center or right.
// Return 0 if ok, else -1.
int df::DisplayManager::drawString(Vector world_pos, std::string str, Justification just,
	Color color) const {

	//Get starting position
	df::Vector starting_pos = world_pos;
	switch (just) {
	case CENTER_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		starting_pos.setX(world_pos.getX() - str.size());
		break;
	case LEFT_JUSTIFIED:
	default:
		break;
	}

	for (int i = 0; i < str.size(); i++) {
		df::Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
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

	//make sure window is allocated
	if (m_p_window == NULL)
		return -1;

	//Display current window
	m_p_window->display();

	//Clear window to get ready for next draw
	m_p_window->clear(window_background_color);

	return 0;
}

// Return pointer to SFML drawing window.
sf::RenderWindow *df::DisplayManager::getWindow() const {
	return m_p_window;
}

//Set default background color.
void df::DisplayManager::setBackgroundColor(sf::Color new_color) {
	window_background_color = new_color;
}