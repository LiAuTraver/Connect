#include <Services/Animation.hpp>
#include <Services/Sound.hpp>
#include <Views/mainwindow.hpp>

//! note: if use Qt ui file (in Qt Designer) then we shall include this
// `ui_{classname}.h`
#include "ui_MainWindow.h"

Connect::MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  ui(new Ui::MainWindow),
	  menu(new Menu(this)),
	  game(nullptr),
	  leaderboard(nullptr),
	  about(nullptr)  //! note: Initialize to nullptr, create it only when needed
{
	this->ui->setupUi(this);
	this->setCentralWidget(menu);
	this->initializeConnections(kThis);
	if (auto res = this->soundEvent.initializeAudioData(); not res.ok()) {
		qDebug() << "Failed to initialize audio resources: " << res.message().data();
		LOG(ERROR) << "Failed to initialize audio resources: " << res.message().data();
	}
	this->soundEvent.playAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");
}
Connect::MainWindow::~MainWindow() {
	//! note: no need to delete custom widgets: they are deleted by their parent
	//! (parent-child relationship)
	delete ui;	//! note: needed, see note in `game.cpp`
}

void Connect::MainWindow::handleExitFromGame(const PastGameWidget::Option choice) {
	soundEvent.stopAudio(gameBGM);
	switch (choice) {
		case BackToMenu:
			if (not menu)
				this->menu = new Menu(this);
			// game = dynamic_cast<Game *>(this->takeCentralWidget());
			this->soundEvent.playAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");
			this->setCentralWidget(menu);
			break;
		case ReplayGame:
			// fixme: shall I manually call `delete` for old game instance?
			game = new Game(this);
			gameBGM = soundEvent.generateAudioPath();
			soundEvent.playAudio(gameBGM);
			this->setCentralWidget(game);
			break;
		case ToLeaderboard:
			if (not leaderboard)
				this->leaderboard = new Leaderboard(this);
			// game = dynamic_cast<Game *>(this->takeCentralWidget());
			this->setCentralWidget(leaderboard);
			break;
		default:
			qCritical("You should not be here.");
			LOG(ERROR) << "You should not be here.";
			break;
	}
}

void Connect::MainWindow::handleAddNewRecord(const qint64 score, const qint64 elapsedTime) {
	if (not leaderboard)
		this->leaderboard = new Leaderboard(this);
	this->initializeConnections(kLeaderboard);
	leaderboard->onGameWinChangeRecord(score, elapsedTime);
}
void Connect::MainWindow::handleStartFromMenu(const Page page) {
	switch (page) {
		case kGame:
			if (not game)
				this->game = new Game(this);
			this->initializeConnections(kGame);
			//! Qt Gui take the widget away I must take back
			menu = dynamic_cast<Menu *>(this->takeCentralWidget());
		this->soundEvent.stopAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");
			gameBGM = this->soundEvent.generateAudioPath();
			this->soundEvent.playAudio(gameBGM);
			this->setCentralWidget(game);
			break;
		case kAbout:
			if (not about)
				this->about = new About(this);
			menu = dynamic_cast<Menu *>(this->takeCentralWidget());
			connect(about, &About::onCloseButtonCicked, this,
					[this] { handlePageExitToMenu(kAbout); });
			connect(about, &About::onVolumnSliderchanged, this,
					[this](const int value) { handleVolumeChanged(value); });
		this->soundEvent.stopAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");

			this->soundEvent.playAudio("qrc:/audios/Crazy_Dave's_Greeting.mp3");
			this->setCentralWidget(about);
			break;
		case kLeaderboard:
			if (not leaderboard)
				this->leaderboard = new Leaderboard(this);
			this->initializeConnections(kLeaderboard);
			menu = dynamic_cast<Menu *>(this->takeCentralWidget());
		this->soundEvent.stopAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");

			this->soundEvent.playAudio("qrc:/audios/Zen_Garden_In-Game.mp3");
			this->setCentralWidget(leaderboard);
			break;
		default:
			qCritical("shouldn't be here.");
			break;
	}
}
void Connect::MainWindow::handlePageExitToMenu(const Page page) {
	switch (page) {
		case kAbout:
			// fixme: bug-prone: deleted pointer isn't null at most time
			if (not menu)
				this->menu = new Menu(this);
			about = dynamic_cast<About *>(this->takeCentralWidget());
			this->soundEvent.stopAudio("qrc:/audios/Crazy_Dave's_Greeting.mp3");
			this->setCentralWidget(menu);
			break;
		case kLeaderboard:
			if (not menu)
				this->menu = new Menu(this);
			leaderboard = dynamic_cast<Leaderboard *>(this->takeCentralWidget());
			this->soundEvent.stopAudio("qrc:/audios/Zen_Garden_In-Game.mp3");
			this->setCentralWidget(menu);
			break;
		case kThis:
			QApplication::quit();
			// std::unreachable();
		default:
			// `Game` has parameter, cannot do it at here.
			break;
	}
	this->soundEvent.playAudio("qrc:/audios/Crazy_Dave_In-Game.mp3");

}

void Connect::MainWindow::handleVolumeChanged(const int newVolume) {
	soundEvent.volume = newVolume;
	qDebug() << "Volume changed to " << soundEvent.volume;
}

void Connect::MainWindow::initializeConnections(const Page page) {
	switch (page) {
		case kThis:
			connect(this->ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
			[[fallthrough]];
		case kMenu:
			connect(menu, &Menu::onStartButtonClicked, this,
					[this] { handleStartFromMenu(kGame); });
			connect(menu, &Menu::onRecordButtonClicked, this,
					[this] { handleStartFromMenu(kLeaderboard); });
			connect(menu, &Menu::onAboutButtonClicked, this,
					[this] { handleStartFromMenu(kAbout); });
			break;
		case kGame:
			//! note: the signal's parameter types must match the slot's parameter types,
			//! otherwise the error meaasge would be extremely wired.
			connect(game, &Game::onGameWinCheckRecord, this, &MainWindow::handleAddNewRecord);
			// qDebug() << "Signal-slot connection result:" << res;  // Should output 'true'
			connect(game, &Game::RelayTo, this, &MainWindow::handleExitFromGame);
			break;
		case kLeaderboard:
			connect(leaderboard, &Leaderboard::onLeaderboradCloseButtonClicked, this,
					[this] { handlePageExitToMenu(kLeaderboard); });
			break;
		default:
			qCritical("You should not be here.");
			break;
	}
}
void Connect::StatusWidget::onButtonEliminate(QPushButton *button) const { Animation(button); }
