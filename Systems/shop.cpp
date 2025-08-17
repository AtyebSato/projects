#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{
    InitWindow(1280, 720, "shop system");
    SetTargetFPS(60);

    Rectangle panelBounds = {100, 100, 300, 200}; // Scroll panel on screen
    Rectangle content = {0, 0, 280, 400};         // Size of scrollable content
    Vector2 scroll = {0, 0};
    Rectangle view;  // This will store the visible panel area

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Start scroll panel
        GuiScrollPanel(panelBounds, "SHOP", content, &scroll, &view);

        // Start scissor mode so buttons don’t draw outside the panel
        BeginScissorMode(view.x, view.y, view.width, view.height);

        // Draw buttons inside scroll panel (offset by scroll)
        for (int i = 0; i < 10; i++)
        {
            Rectangle button = {
                panelBounds.x + 10 - scroll.x,
                panelBounds.y + 10 + i * 40 - scroll.y,
                260,
                30
            };

            if (GuiButton(button, TextFormat("Item %d", i + 1)))
            {
                TraceLog(LOG_INFO, "Clicked on item %d", i + 1);
            }
        }

        EndScissorMode();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
