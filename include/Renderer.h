/**
 * @file Renderer.h
 * 
 * @author Armagidon
 * @brief Rendering system for the OS. 
 * Holds all instances of scene object and index pointer to a current set scene.
 * Handles setup of a scene, disposal of scene and its components.
 * Renders components based on their update property
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "utils.h"
#include "scene.h"
#include "Arduino_ST7789_Fast.h"
#define DISPLAY_SIZE 240

void drawLine(int x, int y, int length, uint8_t thickness, bool vertical, uint16_t color);
void rendererSetup(Arduino_ST7789* d);
void render();
void setScene(uint8_t sceneIndex);
void add_scene(Scene scene);
Component* findComponentById(uint8_t id);
uint8_t find_scene_index_by_id(const char* id);
void printText(Arduino_ST7789* renderer, uint8_t x, uint8_t y, uint8_t size, uint16_t fg, uint16_t bg, const char* text);
Scene* get_current_scene();