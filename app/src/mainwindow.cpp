#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_model = new QStandardItemModel(this);
    ui->list_songs->setModel(m_model);


    if (argc == 2)
        m_dirname = QString::fromStdString(argv[1]);
    else
        m_dirname = ".";

    ui->action_recursion->setText("Enable recursion");

    QDir dir = openDir(m_dirname);
    if (dir.exists() && dir.isReadable())
        setDir(dir);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDir(QDir dir) {
    dir.makeAbsolute();
    m_dirname = dir.path();
    ui->label_dirname->setText(m_dirname);

    processDir(dir);
}

QDir MainWindow::openDir(QString dirname) {
    QDir dir(dirname);

    if (!dir.exists() || !dir.isReadable()) {
        QMessageBox::critical(this, "Directory does not exist", "Directory does not exist!\
                              \nPlease, select another directory.");
    }

    return dir;
}

void MainWindow::processDir(QDir dir) {
    m_songs.clear();
    m_vector.clear();
    m_model->clear();

    ui->edit_filename->setText(QString());
    ui->edit_title->setText(QString());
    ui->edit_artist->setText(QString());
    ui->edit_album->setText(QString());
    ui->edit_comment->setText(QString());
    ui->edit_genre->setText(QString());
    ui->edit_track->setText(QString());
    ui->edit_year->setText(QString());

    if (m_recursion) {
        processRecursion(dir, {});
        printMap();
    }
    else {
        readDir(dir, {});
        printMap();
    }
}

void MainWindow::processRecursion(QDir dir, const QString& name_prefix) {
    QList<QFileInfo> dirs = dir.entryInfoList(QDir::AllDirs | QDir::Hidden);

    readDir(dir, name_prefix);

    for (const QFileInfo& entry : dirs) {
        if (entry.fileName() != ".." && entry.fileName() != ".") {
            QDir entry_dir = openDir(entry.absoluteFilePath());

            QString full_name = name_prefix.isEmpty() ? entry.fileName() : name_prefix + "/" + entry.fileName();
            processRecursion(entry_dir, full_name);
            readDir(entry_dir, full_name);
        }
    }
}

void MainWindow::readDir(QDir dir, const QString& name_prefix) {
    dir.setNameFilters(QStringList() << "*.mp3" << "*.ogg" << "*.wav" << "*.flac");
    QList<QFileInfo> files = dir.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::Hidden);

    std::map<QString, Song> songs = m_songs;
    for (const QFileInfo& file : files) {
        Song song;

        if (!file.isReadable()) {
            makeUnreadableFile(songs, file, name_prefix);
            continue;
        }

        TagLib::FileRef tag(file.absoluteFilePath().toStdString().c_str());
        song.filename = name_prefix.isEmpty() ? file.fileName() : name_prefix + "/" + file.fileName();
        fillSong(song, tag);

        songs[song.filename] = song;
    }

    m_songs = songs;
}

void MainWindow::printMap() {
    for (const auto& [key, val] : m_songs) {
        QStandardItem *item = new QStandardItem(key);
        item->setEditable(false);
        m_model->appendRow(item);
    }
}

void MainWindow::printVector() {
    for (const auto& song : m_vector) {
        QStandardItem *item = new QStandardItem(song.filename);
        item->setEditable(false);
        m_model->appendRow(item);
    }
}

void MainWindow::makeUnreadableFile(std::map<QString, Song>& songs, const QFileInfo& file, const QString& name_prefix) {
    Song song;

    if (name_prefix.isEmpty())
        song.filename = file.fileName();
    else
        song.filename = name_prefix + "/" + file.fileName();

    song.title = "Not readable";
    song.artist = "Not readable";
    song.album = "Not readable";
    song.genre = "Not readable";
    song.comment = "Not readable";

    songs[song.filename] = song;
}

void MainWindow::editTags(std::string path, const QString& filename) {
    TagLib::FileRef tag(path.c_str());

    if (!tag.isNull()) {
        if (ui->edit_year->text().size() > 0 &&
            !ui->edit_year->text().toUInt() &&
            ui->edit_year->text() != "0") {
            QMessageBox::warning(this, "", "\nYear must contain only digits");
            return;
        }
        if (ui->edit_track->text().size() > 0 &&
            !ui->edit_track->text().toUInt() &&
            ui->edit_track->text() != "0") {
            QMessageBox::warning(this, "", "\nTrack must contain only digits");
            return;
        }
    }

    tag.tag()->setTitle(ui->edit_title->text().toStdString());
    tag.tag()->setArtist(ui->edit_artist->text().toStdString());
    tag.tag()->setAlbum(ui->edit_album->text().toStdString());
    tag.tag()->setGenre(ui->edit_genre->text().toStdString());
    tag.tag()->setYear(ui->edit_year->text().toUInt());
    tag.tag()->setTrack(ui->edit_track->text().toUInt());
    tag.tag()->setComment(ui->edit_comment->text().toStdString());
    tag.save();

    fillSong(m_songs[filename], tag);

    m_vector.clear();
    QMessageBox::information(this, "", "Tag saved!");
}

void MainWindow::fillSong(Song& song, TagLib::FileRef tag) {
    song.title = QString::fromStdString(tag.tag()->title().toCString());
    song.artist = QString::fromStdString(tag.tag()->artist().toCString());
    song.album = QString::fromStdString(tag.tag()->album().toCString());
    song.genre = QString::fromStdString(tag.tag()->genre().toCString());
    song.track = tag.tag()->track();
    song.year = tag.tag()->year();
}
