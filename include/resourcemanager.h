#pragma once
#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define MAX_FILENAME_LENGTH 256
#define MAX_RESOURCES 100

// Enumeration for resource types
typedef enum
{
    RESOURCE_TYPE_TEXTURE = 0,
    RESOURCE_TYPE_SOUND = 1,
    // Add more resource types as needed
    RESOURCE_TYPE_COUNT
} ResourceType;

// Structure to represent a resource
typedef struct
{
    char filename[MAX_FILENAME_LENGTH]; // File path
    ResourceType type;
    union
    {
        Texture2D texture;
        Sound sound;
        // Add other data types you want to store here
    } data;       // Union to store resource data
    int refCount; // Reference count
} Resource;

// Structure for the resource manager
typedef struct
{
    Resource resources[MAX_RESOURCES];
    int numLoadedResources;
} ResourceManager;

// Function to load a generic resource
void LoadResource(ResourceManager *manager, const char *filename, ResourceType type)
{
    // Check if resource manager is full
    if (manager->numLoadedResources >= MAX_RESOURCES)
    {
        printf("Error: Resource manager is full.\n");
        return;
    }

    // Initialize a new resource
    Resource *resource = &manager->resources[manager->numLoadedResources];
    strcpy(resource->filename, filename);
    resource->type = type;

    // Load the resource based on type
    switch (type)
    {
    case RESOURCE_TYPE_TEXTURE:
        resource->data.texture = LoadTexture(filename);
        break;
    case RESOURCE_TYPE_SOUND:
        resource->data.sound = LoadSound(filename);
        break;
        // Add more cases as needed
    }

    // Increment the number of loaded resources
    manager->numLoadedResources++;
}

// Function to unload all loaded resources
void UnloadAllResources(ResourceManager *manager)
{
    for (int i = 0; i < manager->numLoadedResources; ++i)
    {
        switch (manager->resources[i].type)
        {
        case RESOURCE_TYPE_TEXTURE:
            UnloadTexture(manager->resources[i].data.texture);
            break;
        case RESOURCE_TYPE_SOUND:
            UnloadSound(manager->resources[i].data.sound);
            break;
            // Add more cases as needed
        }
    }
    manager->numLoadedResources = 0;
}

// Function to get a generic resource
void *GetResource(ResourceManager *manager, const char *filename)
{
    for (int i = 0; i < manager->numLoadedResources; ++i)
    {
        if (strcmp(manager->resources[i].filename, filename) == 0)
        {
            manager->resources[i].refCount++; // Increment reference count
            return &manager->resources[i].data;
        }
    }
    return NULL; // Resource not found
}

// Function to release a generic resource
void ReleaseResource(ResourceManager *manager, const char *filename)
{
    for (int i = 0; i < manager->numLoadedResources; ++i)
    {
        if (strcmp(manager->resources[i].filename, filename) == 0)
        {
            manager->resources[i].refCount--; // Decrement reference count
            if (manager->resources[i].refCount == 0)
            {
                // If reference count is zero, unload the resource
                switch (manager->resources[i].type)
                {
                case RESOURCE_TYPE_TEXTURE:
                    UnloadTexture(manager->resources[i].data.texture);
                    break;
                case RESOURCE_TYPE_SOUND:
                    UnloadSound(manager->resources[i].data.sound);
                    break;
                    // Add more cases as needed
                }
            }
            return;
        }
    }
}
