#include "cocoa_helper.h"

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>

void* createMetalLayer(void* nsWindow) {
    NSWindow* window = (__bridge NSWindow*)nsWindow;
    NSView* contentView = [window contentView];

    CAMetalLayer* metalLayer = [CAMetalLayer layer];
    metalLayer.frame = contentView.bounds;
    metalLayer.opaque = YES;
    [contentView setLayer:metalLayer];
    [contentView setWantsLayer:YES];

    return (__bridge void*)metalLayer;
}

void updateMetalLayerFrame(void* metalLayer, int width, int height) {
    CAMetalLayer* layer = (__bridge CAMetalLayer*)metalLayer;
    layer.frame = CGRectMake(0, 0, width, height);
}
#endif