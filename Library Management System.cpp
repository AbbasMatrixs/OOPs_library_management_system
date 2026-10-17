#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Entity {
protected:                                //Abstraction
    int id;
    string name;
public:
    Entity(int id, string name) : id(id), name(name){
	}
    int getId() const {                   //Encapsulation
	return id; 
	}
    string getName() const { 
	return name; 
	}
    virtual void display() const = 0; // polymorphism
    virtual ~Entity(){
	}
};
class Book : public Entity {                // Inheritance
    string author;
    bool isBorrowed;
public:
    Book(int id, string title, string author): Entity(id, title), author(author), isBorrowed(false) {
	}
    void borrowBook() {
		isBorrowed = true; 
	}
    void returnBook() {
		isBorrowed = false; 
	}
    bool getIsBorrowed() const {
	return isBorrowed; 
	}
    void display() const override {
        cout << "ID: " << id << ", Title: " << name << ", Author: " << author
             << ", Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "ID: " << book.id << ", Title: " << book.name << ", Author: " << book.author
           << ", Status: " << (book.isBorrowed ? "Borrowed" : "Available");
        return os;
    }
};
class Library{
    vector<Book> books;
    bool isDuplicateId(int id) const {
        for (const auto& book : books) {
            if (book.getId() == id)
                return true;
        }
        return false;
    }

public:
    Library() {
        books.push_back(Book(1, "1984", "George Orwell"));
        books.push_back(Book(2, "To Kill a Mockingbird", "Harper Lee"));
        books.push_back(Book(3, "The Great Gatsby", "F. Scott Fitzgerald"));
    }

    void addBook(int id, const string& title, const string& author) {
        if (isDuplicateId(id)) {
            cout << "Error: A book with this ID already exists.\n";
            return;
        }
        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }
        for (const auto& book : books)
            book.display();
    }

    void searchBookByTitle(const string& title) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.getName() == title) {
                cout << book << endl;
                found = true;
            }
        }
        if (!found)
            cout << "Book not found!\n";
    }

    void borrowBook(int id) {
        for (auto& book : books) {
            if (book.getId() == id) {
                if (!book.getIsBorrowed()) {
                    book.borrowBook();
                    cout << "Book borrowed successfully!\n";
                } else {
                    cout << "Book is already borrowed!\n";
                }
                return;
            }
        }
        cout << "Book ID not found!\n";
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.getId() == id) {
                if (book.getIsBorrowed()) {
                    book.returnBook();
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book was not borrowed!\n";
                }
                return;
            }
        }
        cout << "Book ID not found!\n";
    }
};

int main() {
    Library library;
    int choice;
    do {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Display all books\n";
        cout << "2. Search book by title\n";
        cout << "3. Borrow a book\n";
        cout << "4. Return a book\n";
        cout << "5. Add a new book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            library.displayBooks();
            break;
        case 2: {
            cin.ignore();
            string title;
            cout << "Enter book title: ";
            getline(cin, title);
            library.searchBookByTitle(title);
            break;
        }
        case 3: {
            int id;
            cout << "Enter book ID to borrow: ";
            cin >> id;
            library.borrowBook(id);
            break;
        }
        case 4: {
            int id;
            cout << "Enter book ID to return: ";
            cin >> id;
            library.returnBook(id);
            break;
        }
        case 5: {
            int id;
            string title, author;
            cout << "Enter book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter book title: ";
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(id, title, author);
            break;
        }
        case 6:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 6);
    return 0;
}