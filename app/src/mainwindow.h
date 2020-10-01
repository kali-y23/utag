#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QList>
#include <QStandardItemModel>

#include "tag.h"
#include "fileref.h"

#include <map>

#include "song.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QString m_dirname;
    QStandardItemModel *m_model;
    bool m_recursion = false;
    std::map<QString, Song> m_songs;

public:
    MainWindow(int argc, char *argv[], QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_byTitle_triggered();

    void on_action_byArtist_triggered();

    void on_action_byAlbum_triggered();

    void on_action_byGenre_triggered();

    void on_action_byComment_triggered();

    void on_action_byTrack_triggered();

    void on_action_byYear_triggered();

    void on_action_openDirectory_triggered();

    void on_action_recursion_triggered();

    void on_button_save_clicked();

    void on_list_songs_doubleClicked(const QModelIndex &index);

private:
    void openDir(QString dirname);
    void processDir(QDir dir);
    void readDir(QDir dir, const QString& name_prefix);
    void printDir();
    void makeUnreadableFile(std::map<QString, Song>& songs, const QFileInfo& file, const QString& name_prefix);
    void editTags(std::string path);

};
#endif // MAINWINDOW_H
