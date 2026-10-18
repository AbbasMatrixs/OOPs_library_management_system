#include <iostream>
#include <vector>
#include <string>
using namespace std;
// Interface Segregation Principle : Don't force classes to implement methods they don't need.
class IDisplayable {
public:
    virtual void display() const = 0;
    virtual ~IDisplayable() {}
};
// Dependency Inversion Principle 
class ILibrary {
public:
    virtual void displayBooks() const = 0;
    virtual void addBook(int id, const string& title,
                         const string& author) = 0;
    virtual ~ILibrary() {}
};
// Open/Closed Principle , Liskov Substitution Principle(book & entity like cat & animal)
class Entity : public IDisplayable {
protected:
    int id;
    string name;
public:
    Entity(int id, string name)
        : id(id), name(name) {}
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    virtual ~Entity() {}
};
// Inheritance
class Book : public Entity {
    string author;
    bool isBorrowed;
public:
    Book(int id, string title, string author)
        : Entity(id, title),
          author(author),
          isBorrowed(false) {}
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
        cout << "ID: " << id
             << ", Title: " << name
             << ", Author: " << author
             << ", Status: "
             << (isBorrowed ? "Borrowed"
                            : "Available")
             << endl;
    }
    friend ostream& operator<<(ostream& os,
                               const Book& book) {
        os << "ID: " << book.id
           << ", Title: " << book.name
           << ", Author: " << book.author
           << ", Status: "
           << (book.isBorrowed
               ? "Borrowed"
               : "Available");
        return os;
    }
};
// Single Responsibility Principle (SRP) - Library manages book collection
class Library : public ILibrary {
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
        books.push_back(
            Book(1, "1984",
                 "George Orwell"));
        books.push_back(
            Book(2,
                 "To Kill a Mockingbird",
                 "Harper Lee"));
        books.push_back(
            Book(3,
                 "The Great Gatsby",
                 "F. Scott Fitzgerald"));
    }
    void addBook(int id,
                 const string& title,
                 const string& author) override {
        if (isDuplicateId(id)) {
            cout << "Error: A book with this ID already exists.\n";
            return;
        }

        books.push_back(
            Book(id, title, author));

        cout << "Book added successfully!\n";
    }
    void displayBooks() const override {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }
        for (const auto& book : books)
            book.display();
    }

    void searchBookByTitle(
        const string& title) const {

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
                }
                else {
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
                }
                else {
                    cout << "Book was not borrowed!\n";
                }

                return;
            }
        }

        cout << "Book ID not found!\n";
    }
};
// Main
int main() {
    ILibrary* library = new Library();
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
            library->displayBooks();
            break;
        case 2: {
            string title;
            cin.ignore();
            cout << "Enter book title: ";
            getline(cin, title);
            dynamic_cast<Library*>(library)
                ->searchBookByTitle(title);
            break;
        }
        case 3: {
            int id;

            cout << "Enter book ID to borrow: ";
            cin >> id;

            dynamic_cast<Library*>(library)
                ->borrowBook(id);
            break;
        }
        case 4: {
            int id;

            cout << "Enter book ID to return: ";
            cin >> id;

            dynamic_cast<Library*>(library)
                ->returnBook(id);
            break;
        }

        case 5: {
            int id;
            string title;
            string author;

            cout << "Enter book ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter book title: ";
            getline(cin, title);

            cout << "Enter book author: ";
            getline(cin, author);

            library->addBook(id,title,author);
            break;
        }

        case 6:
            cout << "Exiting the system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    delete library;
    return 0;
}


/*SRP is applied because Book, Library, and main each have a separate responsibility. 
OCP is applied because new entities can be added by extending Entity without modifying existing code.
LSP is applied because Book inherits from Entity and can be used wherever Entity is expected. 
ISP is applied through the small IDisplayable interface that only contains display functionality.
DIP is applied because the program uses the ILibrary abstraction instead of directly depending on the Library class.*/
