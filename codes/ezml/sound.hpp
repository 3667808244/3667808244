#pragma once

#include <chrono>
#include <cstddef>
#include <filesystem>
#include <memory>
#include <span>
#include <vector>

#include "ezml/audio.hpp"
#include "ezml/error.hpp"

namespace ezml::audio {
	class SoundBuffer {
			/* 表示一段已解码、常驻内存的音频数据
			 * 一个 SoundBuffer 可以被多个 Sound 共享
			 * */
		protected:
			SoundBuffer(AudioSpec spec, std::vector<std::byte> samples);

		public:
			SoundBuffer(const SoundBuffer &buffer) = delete;
			SoundBuffer operator=(const SoundBuffer &buffer) = delete;

			SoundBuffer(SoundBuffer &&buffer);
			SoundBuffer &operator=(SoundBuffer &&buffer);

			const AudioSpec &spec() const;

			// 每声道的采样帧数
			std::uint64_t frame_count() const;

			std::chrono::microseconds duration() const;

			// 交织的原始采样数据
			std::span<const std::byte> samples() const;

			// 转为共享所有权，便于由同一份数据派生多个 Sound
			// 只能对右值调用：调用后本对象被移空
			std::shared_ptr<const SoundBuffer> share() &&;

			static error::ValueResult<SoundBuffer> load_file(const std::filesystem::path &path);

			static error::ValueResult<SoundBuffer> load_memory(std::span<const std::byte> data);
	};

	class Sound : public SoundSource {
			/* 表示 SoundBuffer 的一次播放
			 * 同一份 SoundBuffer 可以同时派生出多个 Sound
			 * */
		protected:
			Sound(std::shared_ptr<const SoundBuffer> buffer);

		public:
			Sound(const Sound &sound) = delete;
			Sound operator=(const Sound &sound) = delete;

			Sound(Sound &&sound);
			Sound &operator=(Sound &&sound);

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

			static error::ValueResult<Sound> create(std::shared_ptr<const SoundBuffer> buffer);
	};
}  // namespace ezml::audio
