#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::on_action_openDirectory_triggered()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, "Choose directory", m_dirname,
        QFileDialog::DontUseNativeDialog);

    QDir dir = openDir(directory);
    if (dir.exists() && dir.isReadable())
        setDir(dir);
}

void MainWindow::on_action_recursion_triggered()
{
    m_recursion = m_recursion ? false : true;
    QString text = m_recursion ? "Disable recursion" : "Enable recursion";
    ui->action_recursion->setText(text);

    QDir dir = openDir(m_dirname);
    if (dir.exists() && dir.isReadable())
        processDir(dir);
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
        editTags(path, ui->edit_filename->text());
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