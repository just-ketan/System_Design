# ISP : Interface Seggregation Principle

so did we ever write an interface, only to write empty methods to make compiler happy ?

## Problem : A Fat Interface
suppose we are building a media player app that supports different types of media
```yaml
    - Audio Files {wav mp3}
    - Video files {mp4, avi}
```

lets look at a convenient design
```cpp
class MediaPlayer{
    public:
        virtual void playAudio(const string& audiofile) = 0;
        virtual void stopAudio() = 0;
        virtual void adjustAudioVolume(int volume) = 0;

        virtual void playVideo(const string& videfile) = 0;
        virtual void stopVideo() = 0;
        virtual void adjustVideoBrightness(int brightness) = 0;
        virtual void displaySubtitles(const string& subfile) = 0;

        virtual ~MediaPlayer() = default;
};
```

now if we want a class say `AudioOnlyPlayer` then we have to have empty declarations for all the unrelated methods mentioned in the interface contract as well. thus, applying `Interface Seggregation` makes things modular and seggregated

```cpp
// audio-only capabilities
class AudioPlayerControl {
    public:
        virtual void playAudio(const stirng& file) = 0;
        virtual void stopAudio() = 0;
        virtual void adjustVolume(int volume) = 0;
        virtual ~AudioPlayerControl() = default;
};

// video-only capabilities
class VideoPlayerControls{
    public:
        virtual void playVideo(const string& file) = 0;
        virtual void stopVideo() = 0;
        virtual void adjustVideoBrightness(int brightness) = 0;
        virtual void displaySubs(const string& subfile) = 0;
        virtual ~VidePlayerControl() = default;
};

// Audio-Only Player
class ModernAudioPlayer : AudioPlayerControl{
    public:
        void playAudio(const string& file) override {
            // play
        }
        void stopAudio() override {
            // stop;
        }
        void adjustVolume(int vol) override {
            // adjust volume
        }
};

//Video-Only (silent) player
class SilentMoviePlayer : VideoPlayerControls{
    public:
        void playVideo(const stirng& file) override {   /* play video */  }
        void stopVideo() override   {   /* stop video */  }
        void adjustVideBrightness(int brightness) override  {   /* adjust brightness */    }
        void displaySubs(const string& subfile) override {  /* display subs  */}
};

// if we need both
class ComprehensivePlayer : public AudioPlayerControls, public VideoPlayerControls {
    public:
        void playAudio(const string& audiofile) override {    /* play audio   */ }
        void stopAudio() override {    /* stop audio */  }
        void adjustAudioVolume(int volume) override {    /* adjust audio volume */  }
        void playVideo(const string& videfile) override {    /* play video  */ }
        void stopVideo() override {    /* play video  */ }
        void adjustVideoBrightness(int brightness) override {    /* adjust video brightness  */ }
        void displaySubtitles(const string& subfile) override {    /* display subtitles  */ }
};
```