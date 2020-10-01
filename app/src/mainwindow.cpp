#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(int argc, char *argv[], QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

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
}

void MainWindow::processDir() {
    
}
