#include <stdbool.h>
#include "raylib.h"

#include "base.h"
#include "default_app.h"

int DefaultAppRun()
{

    /*
    LOG_ALL = 0,        // Display all logs
    LOG_TRACE,          // Trace logging, intended for internal use only
    LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,           // Info logging, used for program execution info
    LOG_WARNING,        // Warning logging, used on recoverable failures
    LOG_ERROR,          // Error logging, used on unrecoverable failures
    LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE
    **/
    SetTraceLogLevel(LOG_LEVEL_ENABLE);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();
    SetTargetFPS(TARGET_FPS);

    static GameScene scene = {0};

    // SceneType sceneType = START_SCENE;
    // SceneType sceneType = TEST_SCENE;
    SceneType sceneType = TEST_SCENE;
    Game game = NewGame();

    scene.loaded = false;

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        SelectScene(&game, &scene, sceneType);
        if (scene.updateScene != NULL)
        {
            scene.updateScene(&game, GetFrameTime());
        }

        BeginDrawing();
        if (scene.drawScene != NULL)
        {
            scene.drawScene(&game);
        }
        EndDrawing();
    }

    CloseAudioDevice(); // Close audio device connection

    CloseWindow();

    return 0;
}
