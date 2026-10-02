#pragma once

#include <chrono>
#include <cstdint>

namespace ezml::audio {
	// 采样格式
	enum class SampleFormat {
		I16,  // 有符号16位整数
		I32,  // 有符号32位整数
		F32,  // 32位浮点
	};

	// 声道布局
	enum class ChannelLayout : std::uint8_t {
		Mono = 1,
		Stereo = 2,
	};

	// 描述一段音频数据的格式
	struct AudioSpec {
			std::uint32_t sample_rate;	// 采样率(Hz)
			ChannelLayout channels;		// 声道布局
			SampleFormat format;		// 采样格式
	};

	// 播放状态
	enum class PlaybackStatus {
		Stopped,
		Paused,
		Playing,
	};

	class SoundSource {
			/* 所有可播放音源的公共接口
			 * 纯接口：只规范接口，不提供任何默认实现
			 * */
		public:
			virtual ~SoundSource() = default;

			// 播放控制

			virtual void play() = 0;
			virtual void pause() = 0;
			virtual void stop() = 0;

			// 播放参数

			virtual void set_volume(float volume) = 0;	// [0, 100]
			virtual float volume() const = 0;

			virtual void set_pitch(float pitch) = 0;  // 1.0 为原速
			virtual float pitch() const = 0;

			virtual void set_pan(float pan) = 0;  // -1 为左，1 为右
			virtual float pan() const = 0;

			virtual void set_looping(bool looping) = 0;
			virtual bool looping() const = 0;

			virtual void set_playing_offset(std::chrono::microseconds offset) = 0;
			virtual std::chrono::microseconds playing_offset() const = 0;

			virtual PlaybackStatus status() const = 0;
	};

	// 全局混音设置，作用于所有音源

	void set_global_volume(float volume);  // [0, 100]
	float global_volume();

	void pause_all();
	void resume_all();
}  // namespace ezml::audio
