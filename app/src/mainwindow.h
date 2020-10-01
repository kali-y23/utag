#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QString m_dirname;
    bool m_recursion = false;

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

private:
    void openDir(QString dirname);
    void processDir();

};
#endif // MAINWINDOW_H
