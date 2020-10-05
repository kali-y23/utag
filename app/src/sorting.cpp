#include "mainwindow.h"
#include "./ui_mainwindow.h"

bool operator>(const std::string& a, const std::string& b) noexcept {
    const char *s1 = a.c_str();
    const char *s2 = b.c_str();

    while(*s1 && *s1 == *s2) {
        ++s1;
        ++s2;
    }

    int rc = std::toupper(*s1) - std::toupper(*s2);

    if (rc)
        return rc;

    return *s1 - *s2;
}

std::vector<Song> MainWindow::makeVector() {
    std::vector<Song> songs(m_songs.size());
    int i = 0;

    for (const auto& [key, val] : m_songs) {
        songs[i++] = val;
    }

    return songs;
}

void MainWindow::on_action_byTitle_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.title.toStdString() < b.title.toStdString();
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byArtist_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.artist.toStdString() < b.artist.toStdString();
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byAlbum_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.album.toStdString() < b.album.toStdString();
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byGenre_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.genre.toStdString() < b.genre.toStdString();
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byComment_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.comment.toStdString() < b.comment.toStdString();
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byTrack_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.track < b.track;
            });

    m_model->clear();

    printVector();
}

void MainWindow::on_action_byYear_triggered()
{
    if (m_vector.empty())
        m_vector = makeVector();

    std::sort(m_vector.begin(), m_vector.end(),
            [](Song a, Song b) {
                return a.year < b.year;
            });

    m_model->clear();

    printVector();
}
