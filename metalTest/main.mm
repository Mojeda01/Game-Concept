#import <Cocoa/Cocoa.h>
#import <QuartzCore/CAMetalLayer.h>
#import <Metal/Metal.h>
#import <iostream>
#import "movement.h"

struct Vertex {
    float position[2];
    float color[4];
};

class MetalRenderer {
public:
    MetalRenderer(id<MTLDevice> device, CAMetalLayer* metalLayer) {
        this->device = device;
        this->metalLayer = metalLayer;
        commandQueue = [device newCommandQueue];
        createPipeline();
        createVertexBuffer();
    }

    ~MetalRenderer() {
        [pipelineState release];
        [commandQueue release];
        [vertexBuffer release];
        [device release];
    }

    void createPipeline() {
        NSError* error = nil;

        // Load shaders
        NSString* source = @R"(
            #include <metal_stdlib>
            using namespace metal;

            struct VertexIn {
                float2 position [[attribute(0)]];
                float4 color [[attribute(1)]];
            };

            struct VertexOut {
                float4 position [[position]];
                float4 color;
            };

            vertex VertexOut vertex_main(VertexIn in [[stage_in]], constant float4x4& transform [[buffer(1)]]) {
                VertexOut out;
                out.position = transform * float4(in.position, 0.0, 1.0);
                out.color = in.color;
                return out;
            }

            fragment float4 fragment_main(VertexOut in [[stage_in]]) {
                return in.color;
            }
        )";

        id<MTLLibrary> library = [device newLibraryWithSource:source options:nil error:&error];
        if (error) {
            std::cerr << "Failed to create library: " << [[error localizedDescription] UTF8String] << std::endl;
            return;
        }

        id<MTLFunction> vertexFunction = [library newFunctionWithName:@"vertex_main"];
        id<MTLFunction> fragmentFunction = [library newFunctionWithName:@"fragment_main"];

        // Create vertex descriptor
        MTLVertexDescriptor* vertexDescriptor = [[MTLVertexDescriptor alloc] init];
        vertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
        vertexDescriptor.attributes[0].offset = offsetof(Vertex, position);
        vertexDescriptor.attributes[0].bufferIndex = 0;
        vertexDescriptor.attributes[1].format = MTLVertexFormatFloat4;
        vertexDescriptor.attributes[1].offset = offsetof(Vertex, color);
        vertexDescriptor.attributes[1].bufferIndex = 0;
        vertexDescriptor.layouts[0].stride = sizeof(Vertex);

        // Create pipeline state
        MTLRenderPipelineDescriptor* pipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
        pipelineDescriptor.vertexFunction = vertexFunction;
        pipelineDescriptor.fragmentFunction = fragmentFunction;
        pipelineDescriptor.vertexDescriptor = vertexDescriptor;
        pipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;

        pipelineState = [device newRenderPipelineStateWithDescriptor:pipelineDescriptor error:&error];
        if (error) {
            std::cerr << "Failed to create pipeline state: " << [[error localizedDescription] UTF8String] << std::endl;
        }

        [vertexFunction release];
        [fragmentFunction release];
        [pipelineDescriptor release];
        [library release];
        [vertexDescriptor release];
    }

    void createVertexBuffer() {
        // Define vertex data for a triangle
        Vertex vertices[] = {
            {{ 0.0f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}}, // Top vertex (red)
            {{-0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}}, // Bottom-left vertex (green)
            {{ 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}}  // Bottom-right vertex (blue)
        };

        // Create vertex buffer
        vertexBuffer = [device newBufferWithBytes:vertices
                                           length:sizeof(vertices)
                                          options:MTLResourceStorageModeShared];
    }

    void render(const float transform[16]) {
        @autoreleasepool {
            id<CAMetalDrawable> drawable = [metalLayer nextDrawable];
            if (!drawable) return;

            MTLRenderPassDescriptor* renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
            renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
            renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
            renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0); // Clear to black
            renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

            id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
            id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
            [renderEncoder setRenderPipelineState:pipelineState];

            // Set vertex buffer
            [renderEncoder setVertexBuffer:vertexBuffer offset:0 atIndex:0];

            // Set the transformation matrix
            [renderEncoder setVertexBytes:transform length:sizeof(transform) atIndex:1];

            // Draw call
            [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

            [renderEncoder endEncoding];
            [commandBuffer presentDrawable:drawable];
            [commandBuffer commit];
        }
    }

private:
    id<MTLDevice> device;
    id<MTLCommandQueue> commandQueue;
    id<MTLRenderPipelineState> pipelineState;
    id<MTLBuffer> vertexBuffer;
    CAMetalLayer* metalLayer;
};

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (strong) NSWindow *window;
@property (strong) NSView *contentView;
@property (strong) CAMetalLayer *metalLayer;
@property MetalRenderer *renderer; // Use a raw pointer instead of a property
@property MovementHandler *movementHandler; // Use a raw pointer instead of a property
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    NSRect frame = NSMakeRect(0, 0, 800, 600);
    self.window = [[NSWindow alloc] initWithContentRect:frame
                                               styleMask:(NSWindowStyleMaskTitled |
                                                          NSWindowStyleMaskClosable |
                                                          NSWindowStyleMaskResizable)
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];
    [self.window setTitle:@"Metal App"];
    [self.window makeKeyAndOrderFront:nil];

    self.contentView = [[NSView alloc] initWithFrame:frame];
    [self.window setContentView:self.contentView];

    self.metalLayer = [CAMetalLayer layer];
    self.metalLayer.device = MTLCreateSystemDefaultDevice();
    self.metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    self.metalLayer.framebufferOnly = YES;
    self.metalLayer.frame = self.contentView.layer.frame;
    [self.contentView setLayer:self.metalLayer];
    [self.contentView setWantsLayer:YES];

    self.renderer = new MetalRenderer(self.metalLayer.device, self.metalLayer);
    self.movementHandler = new MovementHandler();

    [NSTimer scheduledTimerWithTimeInterval:1.0/60.0
                                     target:self
                                   selector:@selector(renderLoop)
                                   userInfo:nil
                                    repeats:YES];
}

- (void)renderLoop {
    static float lastTime = 0.0f;
    float currentTime = CACurrentMediaTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    self.movementHandler->update(deltaTime);
    float transform[16];
    self.movementHandler->getTransformationMatrix(transform);
    self.renderer->render(transform);
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    delete self.renderer;
    delete self.movementHandler;
}

- (void)keyDown:(NSEvent *)event {
    switch ([event keyCode]) {
        case 0x0D: // W
            self.movementHandler->setMoveUp(true);
            break;
        case 0x01: // S
            self.movementHandler->setMoveDown(true);
            break;
        case 0x00: // A
            self.movementHandler->setMoveLeft(true);
            break;
        case 0x02: // D
            self.movementHandler->setMoveRight(true);
            break;
        default:
            break;
    }
}

- (void)keyUp:(NSEvent *)event {
    switch ([event keyCode]) {
        case 0x0D: // W
            self.movementHandler->setMoveUp(false);
            break;
        case 0x01: // S
            self.movementHandler->setMoveDown(false);
            break;
        case 0x00: // A
            self.movementHandler->setMoveLeft(false);
            break;
        case 0x02: // D
            self.movementHandler->setMoveRight(false);
            break;
        default:
            break;
    }
}

- (void)mouseDragged:(NSEvent *)event {
    self.movementHandler->rotate([event deltaX]);
}

@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSApplication *app = [NSApplication sharedApplication];
        AppDelegate *delegate = [[AppDelegate alloc] init];
        [app setDelegate:delegate];
        [app run];
    }
    return 0;
}