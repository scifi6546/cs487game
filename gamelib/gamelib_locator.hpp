#ifndef GAMELIB_LOCATOR_HPP
#define GAMELIB_LOCATOR_HPP

#include <gamelib_base.hpp>
#include <gamelib_context.hpp>
#include <gamelib_audio.hpp>

namespace GameLib {
    class Locator {
    public:
        static Context* getContext() {
            if (!context_)
                throw std::runtime_error("Context not provided");
            return context_;
        }
        static void provide(Context* context) { context_ = context; }


        static IAudio* getAudio() {
            if (audioService_)
                return audioService_;
            return &nullAudioService_;
        }
        static void provide(IAudio* audio) { audioService_ = audio; }
    private:
        static Context* context_;

        static IAudio* audioService_;
        static IAudio nullAudioService_;
    };
}

#endif
