#include <Helpers/ResourcesSerializer.hpp>
#include <Services/Sound.hpp>
#include <include/config.hpp>
#include <magic_enum.hpp>
#include <memory>
#include <pch/qt.multimedia.hh>
#include <pch/std.algorithm.hh>
#include <pch/std.io.hh>

CONNECT_NAMESPACE_BEGIN
CONNECT_OPT_1_NAMESPACE_BEGIN
void SoundEvent::playAudio(const QString audioUrl) {
	auto audioOutput = std::make_shared<QAudioOutput>(nullptr);
	audioOutput->setVolume(static_cast<float>(volume));
	auto mediaPlayer = std::make_shared<QMediaPlayer>(nullptr);
	mediaPlayer->setAudioOutput(audioOutput.get());

	QObject::connect(mediaPlayer.get(), &QMediaPlayer::mediaStatusChanged,
					 [audioUrl](const QMediaPlayer::MediaStatus status) {
						 qDebug() << "Media Status Changed for" << audioUrl << ":"
								  << magic_enum::enum_name(status);
					 });

	QObject::connect(mediaPlayer.get(), &QMediaPlayer::errorOccurred,
					 [audioUrl](const QMediaPlayer::Error error, const QString& errorString) {
						 qDebug() << "Error Occurred for" << audioUrl << ":" << error
								  << errorString;
					 });

	mediaPlayer->setSource(audioUrl);
	mediaPlayer->play();

	audioOutputs.emplace(audioUrl, audioOutput);
	mediaPlayers.emplace(audioUrl, mediaPlayer);
}

void SoundEvent::stopAudio(const QString audioUrl) {
	if (auto itPlayer = mediaPlayers.find(audioUrl); itPlayer not_eq mediaPlayers.end()) {
		itPlayer->second->stop();
		mediaPlayers.erase(itPlayer);
	}

	if (auto itAudio = audioOutputs.find(audioUrl); itAudio not_eq audioOutputs.end()) {
		audioOutputs.erase(itAudio);
	}
}

SoundEvent::~SoundEvent() {
	// Ensure to stop and clean up all audio on destruction
	for (auto& pair : mediaPlayers) {
		pair.second->stop();
	}
	mediaPlayers.clear();
	audioOutputs.clear();
}
void SoundEvent::beep() noexcept { QApplication::beep(); }

QString SoundEvent::generateAudioPath() const {
	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	// @note: see the similiar part at `Blocks.cpp` for reason not to write `.size() - 1`.
	std::uniform_int_distribution<size_t> dis(0, audioSource.size() - 1);
	return audioSource.at(dis(gen));
}
absl::Status SoundEvent::initializeAudioData() {
	auto audioSourceOpt =
		ResourcesSerializer.deserialise(std::filesystem::current_path() / "resources.json");
	if (not audioSourceOpt)
		return absl::UnavailableError("Acquiring audio resources failed");
	auto it = audioSourceOpt.value().find("audios");
	if (it == audioSourceOpt.value().cend())
		return absl::UnavailableError("Acquiring audio resources failed");
	audioSource = std::move(
		it->second | std::views::transform([&](auto&& str) { return "qrc:/audios/" + str; }) |
		std::ranges::to<decltype(audioSource)>());
	return absl::OkStatus();
}
CONNECT_OPT_1_NAMESPACE_END
CONNECT_OPT_2_NAMESPACE_BEGIN
#pragma region folded
absl::Status SoundEvent::initializeAudioData(const std::string_view audioPath) {
	audioSourcePath = audioPath;
	audioSource.clear();
	try {
		if (this->audioSourcePath.empty() or not exists(this->audioSourcePath))
			return absl::NotFoundError("File not found or not exists.");
		for (const auto& entry : std::filesystem::recursive_directory_iterator(audioSourcePath)) {
			if (is_directory(entry)) {
				audioSource.insert_or_assign(entry.path().string(), AudioFolder{});
				qDebug() << "folder: " << entry.path().string();
			} else if (is_regular_file(entry)) {
				if (audioSource.contains(entry.path().parent_path().string()))
					audioSource.at(entry.path().parent_path().string())
						.emplace_back(entry.path().filename().string());
				else
					audioSource.insert_or_assign(entry.path().parent_path().string(),
												 AudioFolder{entry.path().filename().string()});
				qDebug() << "audio file: " << entry.path().filename();
			}
		}
		return absl::OkStatus();
	} catch (std::exception& e) {
		return absl::UnknownError(e.what());
	} catch (std::error_code& e) {
		return absl::InternalError(e.message());
	} catch (...) {
		return absl::UnknownError("Unknown exception occurred.");
	}
}
#pragma endregion
CONNECT_OPT_2_NAMESPACE_END
CONNECT_NAMESPACE_END