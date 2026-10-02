#pragma once

#include <chrono>
#include <filesystem>

#include "ezml/audio.hpp"
#include "ezml/error.hpp"

namespace ezml::audio {
	class Music : public SoundSource {
			/* 表示以流式解码方式播放的音频，适合较长的背景音乐
			 * 同一时刻只持有一小段解码缓冲
			 * */
		protected:
			Music(const std::filesystem::path &path);

		public:
			Music(const Music &music) = delete;
			Music operator=(const Music &music) = delete;

			Music(Music &&music);
			Music &operator=(Music &&music);

			std::chrono::microseconds duration() const;

			// 打开(或切换)音频文件，会重置播放状态
			void open(const std::filesystem::path &path);

			// SoundSource 接口

			void play() override;
			void pause() override;
			void stop() override;

			void set_volume(float volume) override;
			float volume() const override;

			void set_pitch(float pitch) override;
			float pitch() const override;

			void set_pan(float pan) override;
			float pan() const override;

			void set_looping(bool looping) override;
			bool looping() const override;

			void set_playing_offset(std::chrono::microseconds offset) override;
			std::chrono::microseconds playing_offset() const override;

			PlaybackStatus status() const override;

			static error::ValueResult<Music> load_file(const std::filesystem::path &path);
	};
}  // namespace ezml::audio
