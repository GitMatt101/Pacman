#pragma once
#include "shapes.hpp"

/**
* Creates a VAO for a shape.
* 
* @param shape - Shape to create a VAO for.
*/
void initShapeVAO(Shape* shape);

/**
* Updates a shape's VAO.
*
* @param shape - Shape to update.
*/
void updateShapeVAO(Shape* shape);

/**
* Creates a VAO and a VBO for text display.
* 
* @param textVAO - Pointer to the text VAO.
* @param textVBO - Pointer to the text VBO.
*/
void initTextVAO(GLuint* textVAO, GLuint* textVBO);