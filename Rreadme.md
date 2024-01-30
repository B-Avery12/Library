# Command Line Library
## How to run:
    1 - In the directory with the Makefile run "make compile"
    2 - Run "library.exe"
    3 - Follow prompts for interacting with the library

## Notes:
    * The libray will start with 3 Books: Book 1, Book 2, Book3. The content for each books comes from the correspondig txt file.
    * Three example files of book contents have been included for testing.
    * This program is build on SQLITE, and uses the file LibrarySote.db as the representation for the database. If the file is deleted a new one will be created once the program starts, however, it won't have any of the data persisted.

## Additional book content:
    If additional book content is needed, create a new file. When asked for the path to the book, input the relative path from the directory containg the exe.