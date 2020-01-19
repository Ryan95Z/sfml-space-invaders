#ifndef CORE_GUI_TEXT_HPP
#define CORE_GUI_TEXT_HPP

#include "Font.hpp"
#include "TextRenderer.hpp"

class Text
{
public:
	Text();
	Text(std::string text);
	Text(std::string text, glm::vec3 colour);
	~Text();

	void setScale(float scale);
	void setFont(Font *f);
	void setPosition(float x, float y);
	void setPosition(glm::fvec2 pos);
	void setString(std::string text);
	void setColour(glm::vec3 colour);
	void setProjection(glm::mat4 projection);

	void draw();
private:
	void setUp(std::string text, glm::vec3 colour);

	Font *font;
	TextDetails details;
};

#endif // !CORE_GUI_TEXT_HPP