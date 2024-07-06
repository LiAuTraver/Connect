#pragma once

#include <include/config.hpp>
#include <pch/qt.core.hh>
#include <pch/qt.multimedia.hh>
#include <pch/qt.widgets.hh>
CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
class SoundEvent {
public:
	// cannot make `const` elem at container.
	using AudioCollection = std::vector<QString>;
	using AudioCollectionOpt = std::optional<AudioCollection>;

public:
	SoundEvent() = default;
	~SoundEvent();
	void playAudio(QString);
	void stopAudio(QString);

public:
	static void beep() noexcept;
	_NODISCARD QString generateAudioPath() const;
	absl::Status initializeAudioData();
	AudioCollection audioSource{};
	std::unordered_map<QString,std::shared_ptr<QAudioOutput>> audioOutputs{};
	std::unordered_map<QString, std::shared_ptr<QMediaPlayer>> mediaPlayers{};
	int volume{50};
};
CONNECT_OPT_1_NAMESPACE_END

CONNECT_OPT_2_NAMESPACE_BEGIN
#pragma region folded
class SoundEvent {
public:
	// cannot make `const` elem at container.
	using AudioFolder = std::vector<std::string>;
	using AudioCollection = std::unordered_map<std::string, AudioFolder>;
	using AudioCollectionOpt = std::optional<AudioCollection>;

public:
	SoundEvent() = default;

public:
	static void beep() noexcept;
	_NODISCARD const char* generateAudioPath(std::string_view) const;
	absl::Status initializeAudioData(std::string_view = AUDIO_PATH);

public:
	static constinit const std::string_view AUDIO_PATH;

	AudioCollection audioSource{};
	std::filesystem::path audioSourcePath{};

private:
};
#pragma endregion
CONNECT_OPT_2_NAMESPACE_END
CONNECT_NAMESPACE_END
