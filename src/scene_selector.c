#include <stddef.h>
#include "../include/scene.h"
#include "scene_selector.h"
#include "test_scene.h"
#include "../include/game.h"

void SelectScene(Game *game, GameScene *scene, SceneType type)
{
    if (scene != NULL)
    {
        if (!scene->loaded)
        {
            TraceLog(LOG_DEBUG, "Unloading Scene %d", type);
            if (scene->unloadScene != NULL)
            {
                scene->unloadScene(game);
            }

            TraceLog(LOG_DEBUG, "Scene Unloaded%d", type);
            switch (type)
            {

            default:
                scene->initScene = InitTestScene;
                scene->updateScene = UpdateTestScene;
                scene->drawScene = DrawTestScene;
                scene->unloadScene = UnloadTestScene;
                scene->state = TEST_SCENE;
                break;
            }

            scene->loaded = true;
            TraceLog(LOG_DEBUG, "Loading Scene %d", type);
            if (scene->initScene != NULL)
            {
                scene->initScene(game);
            }
            TraceLog(LOG_DEBUG, "Scene Loaded%d", type);
        }
    }
}
