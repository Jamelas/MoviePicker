#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

void loadFile();
void menu();
void viewList();
void addMovie();
void deleteMovie();
void chooseRandomMovie();

std::vector<std::string> movieList; // To store the movie names
std::fstream movieListFile; // Input file stream
std::string fileName, line; // To store each line read from the file

int main() {
    loadFile();
    std::cout << "Welcome to MoviePicker." << std::endl;
    std::cout << "Keep track of movies that you want to watch." << std::endl;
    menu();

    return 0; // Return 0 to indicate successful execution
}


void loadFile() {
    fileName = "MovieList.txt";
    movieListFile.open(fileName.c_str(), std::fstream::in);

    // Check if the file was opened successfully
    if (!movieListFile.is_open()) {
        std::cout << "Failed to open " << fileName << "." << std::endl;
        std::cout << "Do you want to create a new file?" << std::endl;
        int count = 0;
        char decision;
        while (count < 5) {
            std::cout << "Enter 'y' to create a new file."<< std::endl;
            std::cout << "Enter 'q' to quit the program."<< std::endl;
            std::cin >> decision;
            switch (decision) {
                case 'y':
                    movieListFile.open(fileName.c_str(), std::fstream::out);
                    count = 5;
                    break;
                case 'q':
                    std::cout << "Shutting down program" << std::endl;
                    exit(0);
                default:
                    count++;
                    if (count == 5) {
                        std::cout << "Shutting down program due to too many incorrect inputs." << std::endl;
                        exit(0);
                    }
            }
        }
    }

    while (std::getline(movieListFile, line)) {
        // Save each line (movie name) in the vector
        movieList.push_back(line);
    }
    movieListFile.close(); // Close the file
}

void menu() {
    std::cout << std::endl;
    std::cout << "Choose an option from the menu by entering the corresponding number:" << std::endl;
    std::cout << "1. View list of movies." << std::endl;
    std::cout << "2. Add a new movie." << std::endl;
    std::cout << "3. Delete an existing movie." << std::endl;
    std::cout << "4. Choose a random movie." << std::endl;
    std::cout << "5. Quit the program." << std::endl;

    int decision;
    std::cin >> decision;

    switch (decision) {
        case 1:
            viewList();
            break;
        case 2:
            addMovie();
            break;
        case 3:
            deleteMovie();
            break;
        case 4:
            chooseRandomMovie();
            break;
        case 5:
            std::cout << "The program will now shut down." << std::endl;
            exit(0);
        default:
            std::cout << "Please enter a number from 1 - 5.";
            std::cout << std::endl;
    }
    menu();
}


void viewList() {
    std::cout << "Movies saved from the file:" << std::endl;
    for (const std::string& movie : movieList) {
        std::cout << "- " << movie << std::endl;
    }
}


void addMovie() {
    std::string newMovie;
    std::cout << "Enter the name of the new movie: ";
    std::cin.ignore(); // Ignore any previous newline character
    std::getline(std::cin, newMovie);

    // Add the new movie to the vector and update the file
    movieList.push_back(newMovie);
    movieListFile.open(fileName.c_str(), std::fstream::out | std::fstream::app);
    movieListFile << newMovie << "\n";
    movieListFile.close();

    std::cout << "Movie '" << newMovie << "' added successfully!" << std::endl;
}


void deleteMovie() {
    if (movieList.empty()) {
        std::cout << "The movie list is empty." << std::endl;
        return;
    }

    std::cout << "Enter the name of the movie you want to delete: ";
    std::string movieToDelete;
    std::cin.ignore(); // Ignore any previous newline character
    std::getline(std::cin, movieToDelete);

    // Use a std::vector<std::string>::iterator
    auto it = std::find(movieList.begin(), movieList.end(), movieToDelete);
    if (it != movieList.end()) {
        movieList.erase(it);

        // Update the file with the modified list
        movieListFile.open(fileName.c_str(), std::fstream::out | std::fstream::trunc);
        for (const std::string& movie : movieList) {
            movieListFile << movie << "\n";
        }
        movieListFile.close();

        std::cout << "Movie '" << movieToDelete << "' deleted successfully!" << std::endl;
    } else {
        std::cout << "Movie '" << movieToDelete << "' not found in the list." << std::endl;
    }
}



void chooseRandomMovie() {
    if (movieList.empty()) {
        std::cout << "The movie list is empty." << std::endl;
        return;
    }

    // Generate a random index within the range of the movie list
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomIndex = std::rand() % movieList.size();

    std::cout << "Randomly selected movie: " << movieList[randomIndex] << std::endl;
}
