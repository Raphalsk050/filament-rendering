#pragma once

#ifdef __APPLE__
void* createMetalLayer(void* nsWindow);
void updateMetalLayerFrame(void* metalLayer, int width, int height);
#endif
