#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Node structure for doubly linked list
struct Song {
    string title;
    Song* prev;
    Song* next;

    Song(const string& t) : title(t), prev(nullptr), next(nullptr) {}
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;
    int size;

    // Helper to find a song by title
    Song* findSong(const string& title) {
        Song* temp = head;
        while (temp) {
            if (temp->title == title) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

    ~Playlist() {
        clear();
    }

    // Add song to the playlist (no duplicates)
    void addSong(const string& title) {
        if (findSong(title)) {
            cout << "Song \"" << title << "\" already exists in the playlist.\n";
            return;
        }
        Song* newSong = new Song(title);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        ++size;
        cout << "Added: " << title << endl;
    }

    // Remove song from the playlist
    void removeSong(const string& title) {
        Song* temp = findSong(title);
        if (!temp) {
            cout << "Song not found!\n";
            return;
        }
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (temp == head) head = temp->next;
        if (temp == tail) tail = temp->prev;
        if (temp == current) current = temp->next ? temp->next : temp->prev;
        delete temp;
        --size;
        cout << "Removed: " << title << endl;
    }

    // Display playlist forward
    void displayForward() const {
        Song* temp = head;
        cout << "\nPlaylist (Forward):\n";
        if (!temp) {
            cout << "[Empty]\n";
            return;
        }
        while (temp) {
            if (temp == current) cout << ">> ";
            cout << temp->title;
            if (temp->next) cout << " -> ";
            temp = temp->next;
        }
        cout << "\n";
    }

    // Display playlist backward
    void displayBackward() const {
        Song* temp = tail;
        cout << "\nPlaylist (Backward):\n";
        if (!temp) {
            cout << "[Empty]\n";
            return;
        }
        while (temp) {
            if (temp == current) cout << ">> ";
            cout << temp->title;
            if (temp->prev) cout << " -> ";
            temp = temp->prev;
        }
        cout << "\n";
    }

    // Play next song
    void nextSong() {
        if (current && current->next) {
            current = current->next;
            cout << "Now playing: " << current->title << endl;
        } else if (current) {
            cout << "End of playlist!\n";
        } else {
            cout << "Playlist is empty.\n";
        }
    }

    // Play previous song
    void prevSong() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Now playing: " << current->title << endl;
        } else if (current) {
            cout << "Start of playlist!\n";
        } else {
            cout << "Playlist is empty.\n";
        }
    }

    // Show current song
    void showCurrent() const {
        if (current) {
            cout << "Current song: " << current->title << endl;
        } else {
            cout << "No song is currently selected.\n";
        }
    }

    // Jump to a specific song
    void jumpToSong(const string& title) {
        Song* temp = findSong(title);
        if (temp) {
            current = temp;
            cout << "Jumped to: " << current->title << endl;
        } else {
            cout << "Song not found!\n";
        }
    }

    // Shuffle play (randomly pick a song)
    void shufflePlay() {
        if (size == 0) {
            cout << "Playlist is empty.\n";
            return;
        }
        vector<Song*> songs;
        Song* temp = head;
        while (temp) {
            songs.push_back(temp);
            temp = temp->next;
        }
        srand(static_cast<unsigned int>(time(nullptr)));
        int idx = rand() % songs.size();
        current = songs[idx];
        cout << "Shuffled to: " << current->title << endl;
    }

    // Clear the playlist
    void clear() {
        Song* temp = head;
        while (temp) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = current = nullptr;
        size = 0;
    }

    // Show playlist size
    void showSize() const {
        cout << "Total songs: " << size << endl;
    }
};

int main() {
    Playlist myPlaylist;
    int choice;
    string songTitle;

    while (true) {
        cout << "\n=== Music Playlist Manager ===\n";
        cout << "1. Add Song\n";
        cout << "2. Remove Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Play Next Song\n";
        cout << "6. Play Previous Song\n";
        cout << "7. Show Current Song\n";
        cout << "8. Jump to Song\n";
        cout << "9. Shuffle Play\n";
        cout << "10. Show Playlist Size\n";
        cout << "11. Clear Playlist\n";
        cout << "12. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter song title: ";
                getline(cin, songTitle);
                myPlaylist.addSong(songTitle);
                break;
            case 2:
                cout << "Enter song title to remove: ";
                getline(cin, songTitle);
                myPlaylist.removeSong(songTitle);
                break;
            case 3:
                myPlaylist.displayForward();
                break;
            case 4:
                myPlaylist.displayBackward();
                break;
            case 5:
                myPlaylist.nextSong();
                break;
            case 6:
                myPlaylist.prevSong();
                break;
            case 7:
                myPlaylist.showCurrent();
                break;
            case 8:
                cout << "Enter song title to jump to: ";
                getline(cin, songTitle);
                myPlaylist.jumpToSong(songTitle);
                break;
            case 9:
                myPlaylist.shufflePlay();
                break;
            case 10:
                myPlaylist.showSize();
                break;
            case 11:
                myPlaylist.clear();
                cout << "Playlist cleared.\n";
                break;
            case 12:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
