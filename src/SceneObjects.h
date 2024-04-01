#pragma once
#include "glut.h"
#include <corecrt_math.h>
#include <string>

//macros for simplicity
#define TREE_BARK_HEIGHT 0.05
#define TREE_BARK_WIDTH 0.005
#define STAR_LINE_DELTA 0.004
#define HOUSE_WIDTH 0.025
#define HOUSE_HEIGHT 0.04
#define HOUSE_WINDOW_LENGTH 0.006
#define HOUSE_WINDOW_HEIGHT 0.0275
#define HOUSE_DOOR_WIDTH 0.01
#define HOUSE_DOOR_HEIGHT 0.0175

/// <summary>
///Darws a night sky star at the (x,y) posisiton
/// </summary>
/// <param name="x">x part of point</param>
/// <param name="y">y part of point</param>
void DrawStar(float x, float y);

/// <summary>
///Darws a circle as (x,y) posisiton as center of circle with given radius
/// use glcolor** to set circle color before calling this function
/// </summary>
/// <param name="center_x">the cnter point's x</param>
/// <param name="center_y">the cnter point's y</param>
/// <param name="radius">circle radius</param>
void DrawCircle(float center_x, float center_y, float radius);

/// <summary>
/// Draws tree at the given position as bottom left base point
/// </summary>
/// <param name="base_x">the bottom left corner's x</param>
/// <param name="base_y">the bottom left corner's y</param>
void DrawTree(float base_x, float base_y);

/// <summary>
/// Draws text wit theh given params
/// </summary>
/// <param name="text"> the text to be written</param>
/// <param name="txt_len">length of text</param>
/// <param name="font">GL font to use</param>
/// <param name="x_pos">the start x pos</param>
/// <param name="y_pos">the start y pos</param>
void DrawText(const char* text, int txt_len, void* font, GLfloat x_pos, GLfloat y_pos);

/// <summary>
/// Draws a house with a tree near it at the given point being the bottom left corner
/// </summary>
/// <param name="base_x">bottoms left corner's x value</param>
/// <param name="base_y">bottoms left corner's y value</param>
void DrawHouse(float base_x, float base_y);

class MyBasicButton
{


public:
	/// <summary>
	///Draw call for each time redraw is called
	/// </summary>
	void Draw();

	/// <summary>
	/// set the background color of the button in vec3 floats
	/// </summary>
	/// <param name="red">float red value</param>
	/// <param name="green">float green value</param>
	/// <param name="blue">float blue value</param>
	void SetColor(float red, float green, float blue);

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="pos_t1x">Bottom rect bottom left corner points x</param>
	/// <param name="pos_t1y">Bottom rect bottom left corner points y</param>
	/// <param name="pos_t2x">Bottom rect top right corner points x</param>
	/// <param name="pos_t2y">Bottom rect top right corner points x</param>
	/// <param name="color_red">button color red component float_vec3 format</param>
	/// <param name="color_green">button color green component float_vec3 format</param>
	/// <param name="color_blue">button color blue component float_vec3 format</param>
	/// <param name="onClick_Callback">onclick callback function</param>
	/// <param name="text">text opn button</param>
	MyBasicButton(float pos_t1x, float po1s_t1y, float pos_t2x, float pos_t2y, float color_red, float color_green, float color_blue, void(*onClick_Callback)(), std::string text);

	/// <summary>
	/// Deconstructor
	/// </summary>
	~MyBasicButton();

	/// <summary>
	/// checks if button is in given coordiantes and clicks the functiomn if it does exist
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void CheckClick(float x, float y);

private:
	float pos_t1x;
	float pos_t1y;
	float pos_t2x;
	float pos_t2y;

	float color_red;
	float color_green;
	float color_blue;
	void(*ClickedCallback)();
	std::string text;
};