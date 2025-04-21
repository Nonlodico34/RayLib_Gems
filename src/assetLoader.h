#pragma once
#include "imports.h"

using namespace std;

class AssetLoader
{
public:
    AssetLoader();
    void loadTextures();
    void loadSounds();
    Texture2D *getTexture(string name);
    void playSound(string name);
    void playSoundPro(string name, float pitch, float volume);

private:
    unordered_map<string, Texture2D> texturesMap;
    unordered_map<string, Sound> soundsMap;
};

AssetLoader::AssetLoader()
{
}

void AssetLoader::loadTextures()
{
    texturesMap["ruby"] = LoadTexture("assets/ruby.png");
    texturesMap["amber"] = LoadTexture("assets/amber.png");
    texturesMap["topaz"] = LoadTexture("assets/topaz.png");
    texturesMap["emerald"] = LoadTexture("assets/emerald.png");
    texturesMap["jade"] = LoadTexture("assets/jade.png");
    texturesMap["sapphire"] = LoadTexture("assets/sapphire.png");
    texturesMap["diamond"] = LoadTexture("assets/diamond.png");
    texturesMap["amethyst"] = LoadTexture("assets/amethyst.png");
    texturesMap["rose_quartz"] = LoadTexture("assets/rose_quartz.png");
}

void AssetLoader::loadSounds()
{
    InitAudioDevice();
    soundsMap["gem_sound_1"] = LoadSound("assets/audio/gem_sound_1.mp3");
    soundsMap["gem_sound_2"] = LoadSound("assets/audio/gem_sound_2.mp3");
    soundsMap["gem_sound_3"] = LoadSound("assets/audio/gem_sound_3.mp3");
    soundsMap["gem_sound_4"] = LoadSound("assets/audio/gem_sound_4.mp3");
    soundsMap["gem_sound_5"] = LoadSound("assets/audio/gem_sound_5.mp3");
}

Texture2D *AssetLoader::getTexture(string name)
{
    return &texturesMap[name];
}

void AssetLoader::playSound(string name)
{
    if (soundsMap.find(name) != soundsMap.end())
    {
        PlaySound(soundsMap[name]);
    }
}

void AssetLoader::playSoundPro(string name, float pitch, float volume)
{
    if (soundsMap.find(name) != soundsMap.end())
    {
        Sound sound = soundsMap[name];
        SetSoundPitch(sound, pitch);
        SetSoundVolume(sound, volume);
        PlaySound(sound);
    }
}