#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <any>

#include "../utils/sdl-wrapper.hpp"

namespace ast
{
	enum AudioTypes
    {
        MUSIC,
        CLIP,
        SPATIAL
    };

    struct AudioObject
    {
        int type;
        Mix_Music* music;
        Mix_Chunk* chunk;
    };

    class AudioSystem
    {
    private:
        std::map<std::string, AudioObject*> audio_bank;

        static AudioSystem* instance;
    public:
        static AudioSystem* GetInstance()
        {
            if (!instance)
                instance = new AudioSystem();

            return instance;
        }

        std::map<std::string, AudioObject*> GetAudioBank() {
            return audio_bank;
        }

        void Initialise();
        void addSound(std::string name, const std::string& filename, Uint16 audio_type);
        void Play(const std::string& sound_name, Uint16 loop_mode);
        void PauseAll();
        void FreeAudio();
    };
}