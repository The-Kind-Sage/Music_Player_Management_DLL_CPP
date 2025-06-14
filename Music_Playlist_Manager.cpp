#include <iostream>
#include <string>

using namespace std;

// Node structure for doubly linked list
struct Song {
    string title;
    Song* prev;
    Song* next;

    Song(string t) : title(t), prev(nullptr), next(nullptr) {}
};

// Playlist class
class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Add song to the playlist
    void addSong(string title) {
        Song* newSong = new Song(title);
        if (!head) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Added: " << title << endl;
    }

    // Remove song from the playlist
    void removeSong(string title) {
        Song* temp = head;
        while (temp) {
            if (temp->title == title) {
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                if (temp == current) current = temp->next ? temp->next : temp->prev;
                delete temp;
                cout << "Removed: " << title << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found!\n";
    }

    // Display playlist forward
    void displayForward() {
        Song* temp = head;
        cout << "\nPlaylist (Forward):\n";
        while (temp) {
            cout << temp->title << " -> ";
            temp = temp->next;
        }
        cout << "END\n";
    }

    // Display playlist backward
    void displayBackward() {
        Song* temp = tail;
        cout << "\nPlaylist (Backward):\n";
        while (temp) {
            cout << temp->title << " -> ";
            temp = temp->prev;
        }
        cout << "START\n";
    }

    // Play next song
    void nextSong() {
        if (current && current->next) {
            current = current->next;
            cout << "Now playing: " << current->title << endl;
        } else {
            cout << "End of playlist!\n";
        }
    }

    // Play previous song
    void prevSong() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Now playing: " << current->title << endl;
        } else {
            cout << "Start of playlist!\n";
        }
    }
};

// Main function
int main() {
    Playlist myPlaylist;
    int choice;
    string songTitle;

    while (true) {
        cout << "\nMusic Playlist Manager\n";
        cout << "1. Add Song\n2. Remove Song\n3. Display Playlist Forward\n4. Display Playlist Backward\n";
        cout << "5. Play Next Song\n6. Play Previous Song\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
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
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}
