# utag

This project was done as a part of my ***ucode*** education programme.

UTag allows the user to read and write tags, such as *title*, *artist*, etc. of the audio files of various formats.

- **Build**

> You can build the project with CMake, using the CMakeLists.txt in the root directory.

- **Frameworks**

> Project depends on [TagLib](https://github.com/taglib/taglib) and Qt Widgets. Taglib is included into the project as a static library, Qt needs to be installed on your machine and linked dynamically.

- **Features**
    > - Supports mp3, ogg, wav and flac audio formats.
    > - User can select a directory from the GUI in order to display all songs from that directory. Select Finder->Open Directory from the menu.
    > - Supports recursive browsing of songs in all subdirectories of the chosen directory. Recursion needs to be enabled through Finder->Enable Recursion.
    > - Songs can be sorted by tag by ASCII table. Go to the View menu and choose the tag to sort by.
