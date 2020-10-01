#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

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

    openDir(m_dirname);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_openDirectory_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, "Choose directory", m_dirname,
        QFileDialog::DontUseNativeDialog);

    openDir(directory);
}

void MainWindow::on_action_recursion_triggered()
{
    m_recursion = m_recursion ? false : true;
    openDir(m_dirname);
}

void MainWindow::on_button_save_clicked()
{
    QFileInfo file = QFileInfo(m_dirname + "/" + ui->edit_filename->text());
    std::string path = (m_dirname + "/" + ui->edit_filename->text()).toStdString();

    if (file.isDir()) {
        QMessageBox::critical(this, "File invalid", "Please select a file!");
        return ;
    }
    else if (file.isReadable() && file.isWritable()) {
        editTags(path);
    }
    else {
        QMessageBox::critical(this, "File invalid", "You lack permission to read/write this file.");
        return ;
    }
}

void MainWindow::on_list_songs_doubleClicked(const QModelIndex &index) {
    Song song = m_songs[m_model->itemFromIndex(index)->text()];
    ui->edit_filename->setText(song.filename);
    ui->edit_title->setText(song.title);
    ui->edit_artist->setText(song.artist);
    ui->edit_album->setText(song.album);
    ui->edit_comment->setText(song.comment);
    ui->edit_genre->setText(song.genre);
    ui->edit_track->setText(QString::number(song.track));
    ui->edit_year->setText(QString::number(song.year));
}

void MainWindow::openDir(QString dirname) {
    QDir dir(dirname);

    if (!dir.exists() || !dir.isReadable()) {
        QMessageBox::critical(this, "Directory does not exist", "Directory does not exist!\
                              \nPlease, select another directory.");
        return ;
    }

    dir.makeAbsolute();
    m_dirname = dir.path();
    ui->label_dirname->setText(m_dirname);

    processDir(dir);
}

void MainWindow::processDir(QDir dir) {
    m_model->clear();
    if (m_recursion) {

        //
    }
    else {
        readDir(dir, {});
        printDir();
    }
}

void MainWindow::readDir(QDir dir, const QString& name_prefix) {
    dir.setNameFilters(QStringList() << "*.mp3" << "*.ogg" << "*.wav" << "*.flac");
    QList<QFileInfo> files = dir.entryInfoList(QDir::Files | QDir::NoSymLinks | QDir::Hidden);

    std::map<QString, Song> songs;
    for (const QFileInfo& file : files) {
        Song song;

        if (!file.isReadable()) {
            makeUnreadableFile(songs, file, name_prefix);
            continue;
        }

        TagLib::FileRef tag(file.absoluteFilePath().toStdString().c_str());

        if (name_prefix.isEmpty())
            song.filename = file.fileName();
        else
            song.filename = name_prefix + file.fileName();
        song.title = QString::fromStdString(tag.tag()->title().toCString());
        song.artist = QString::fromStdString(tag.tag()->artist().toCString());
        song.album = QString::fromStdString(tag.tag()->album().toCString());
        song.genre = QString::fromStdString(tag.tag()->genre().toCString());
        song.track = tag.tag()->track();
        song.year = tag.tag()->year();

        songs[song.filename] = song;
    }

    m_songs = songs;
}

void MainWindow::printDir() {
    for (const auto& [key, val] : m_songs) {
        QStandardItem *item = new QStandardItem(key);
        item->setEditable(false);
        m_model->appendRow(item);
    }
}

void MainWindow::makeUnreadableFile(std::map<QString, Song>& songs, const QFileInfo& file, const QString& name_prefix) {
    Song song;

    if (name_prefix.isEmpty())
        song.filename = file.fileName();
    else
        song.filename = name_prefix + file.fileName();

    song.title = "Not readable";
    song.artist = "Not readable";
    song.album = "Not readable";
    song.genre = "Not readable";
    song.comment = "Not readable";

    songs[song.filename] = song;
}

void MainWindow::editTags(std::string path) {
    TagLib::FileRef tag(path.c_str());

    if (!tag.isNull()) {
        if (ui->edit_year->text().size() > 0 &&
            !ui->edit_year->text().toUInt()) {
            QMessageBox::warning(this, "", "\nYear must contain only digits");
            return;
        }
        if (ui->edit_track->text().size() > 0 &&
            !ui->edit_track->text().toUInt()) {
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
    QMessageBox::information(this, "", "Tag saved!");
}
