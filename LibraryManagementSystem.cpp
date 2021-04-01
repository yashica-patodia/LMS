#include<bits/stdc++.h>
#include <dirent.h>
#include <sys/types.h>
#define endl '\n'
#define all(v) (v).begin(), (v).end()
typedef long long int lli;
#define sz(x) (lli)(x).size()
using namespace std;



class Book
{
public:
   int index;//stores the position of the object in the index.txt
   string title;//title of book
   string author;//author of book
   string releaseDate;
   string language;
   string filename;//filename as present in the directory
   string filepath;//the location of the file
   string bookType;

   void print(Book book)
   {
      cout << "File Name:" << book.filename << endl;
      cout << "Title:" << book.title << endl;
      cout << "Author:" << book.author << endl;
      cout << endl;

   }
   void displayBook(Book bk, string nameFile)
   {
      ifstream book ;
      book.open(nameFile);
      if (!book.is_open())
      {
         cout << "Book not found" << endl;
         return  ;
      }
      cout << "Displaying the book" << endl;
      cout << endl;
      print(bk);
      cout << endl;
      bool flag = false;
      string str;
      int yp = 0;
      while (!book.eof())
      {
         if (flag)
         {
            for (int i = 0; i < 50; i++)
            {
               if (book.eof())
               {
                  cout << "End of file reached" << endl;
                  break;
               }
               getline(book, str);
               while (str.length() == 0)
               {
                  getline(book, str);
                  if (book.eof())
                  {
                     cout << "End of file reached" << endl;
                     yp = 1;
                     break;
                  }

               }
               if (yp)
               {
                  // cout << "Yahsica" << endl;
                  break;
               }
               cout << str << endl;
            }
            // cout << "Do you want to continue reading the book? (1 or 0)" << endl;
            // int choice;
            // cin >> choice;
            // if (choice == 0)
            break;

         }
         else
         {
            getline(book, str);
            if (str.find("***") != string::npos)
               flag = true;


         }

      }

   }






};
class Paragraph {
public:
   vector<string> sentences;
};
class Chapter {
public:
   string name;
   string numChapter;
   vector<Paragraph> paragraphs;
   vector<string>allCharacters;

   void nextp() {
      Paragraph *p = new Paragraph();
      paragraphs.push_back(*p);
   }

   void addlinetolastPara(string str) {
      if (paragraphs.size() == 0) {
         Paragraph *p = new Paragraph();
         paragraphs.push_back(*p);
      }
      paragraphs.back().sentences.push_back(str);
   }
   void addCharacter(string str)
   {

      allCharacters.push_back(str);

   }

   void printchapter() {
      for (int i = 0; i < sz(paragraphs); i++) {
         for (int j = 0; j < sz(paragraphs[i].sentences); j++) {
            cout << paragraphs[i].sentences[j] << '\n';
         }
      }
   }
};

struct CompFreq {
   bool operator()(pair<long long int, Chapter> const& p1, pair<long long int, Chapter> const& p2) {
      return p1.first > p2.first;
   }
};

struct CompFreqPara {
   bool operator()(pair<long long int, Paragraph> const& p1, pair<int, Paragraph> const& p2) {
      return p1.first > p2.first;
   }
};
class Novel : public Book
{
public:
   int numOfChapters;
   vector<Chapter>allChapters;
   Novel(string filename, string directoryPath)
   {
      loadChapters(filename, directoryPath);
   }
   long long int countFrequency(string str, string pattern)//searches if a pattern is present in a string or not
   {
      // cout << "search  " << str << endl;
      int patternLength = pattern.length();
      int strLength = str.length();
      if (str.length() == 0 || patternLength == 0)
         return 0;

      lli res = 0;
      for (int i = 0; i <= strLength - patternLength; i++)
      {
         int j;
         for (j = 0; j < patternLength; j++)
         {
            if (str[i + j] != pattern[j])
               break;

         }
         if (j == patternLength)
            res++;
      }
      return res;

   }
   void loadChapters(string nameFile, string directoryPath)
   {
      ifstream book ;
      book.open(nameFile);
      if (!book.is_open())
      {
         cout << "Book not found" << endl;
         return  ;
      }

      string str;
      Chapter *chapter = new Chapter();
      allChapters.push_back(*chapter);
      bool book_start = false;
      while (getline(book, str))
      {
         if ((str.find("***") != string::npos))
            book_start = true;
         if (book_start)
         {
            string::size_type i = str.find("CHAPTER ");
            if (i == string::npos)
            {


               if (!str.empty())
               {
                  allChapters.back().addlinetolastPara(str);

               }
               else
               {
                  allChapters.back().nextp();

               }
            }
            else
            {

               free(chapter);
               chapter = new Chapter();
               str.erase(i, 8);
               string str2 = "";
               int k = 0;
               for (k = 0; k < sz(str); k++) {
                  if (str[k] != '.') str2 += str[k];
                  else break;
               }
               chapter->numChapter = str2;
               str2 = "";
               for (int j = k + 1; j < sz(str); j++) {
                  if (str[j] != '.') str2 += str[j];
                  else break;
               }
               chapter->name = str2;
               allChapters.push_back(*chapter);
               //chapter->chapterName = sentence;
            }
         }
      }
      book.close();
      return ;

   }

   void search_novel()
   {
      string search;
      cout << "Enter the word which you want to  search: " << endl;
      cin >> search;
      int numK;
      cout << "Enter the number of amount of top searches: " << endl;
      cin >> numK;
      cout << "Searching Novel... " << endl;
      cout << "You want top " << numK << " occurrences of the word in chapters or paragraphs:Enter  (chapter or paragraph) accordingly " << endl;
      string choice;

      cin >> choice;
      //transform(all(choice), choice.begin(), ::tolower);

      if (choice == "chapter")
      {
         priority_queue<pair<lli, Chapter>, vector<pair<lli, Chapter>>, CompFreq> q;
         for (int i = 0; i < sz(allChapters); i++)
         {
            long long int count_of_word = 0;
            for (int j = 0; j < sz(allChapters[i].paragraphs); j++)
            {
               for (int k = 0; k < sz(allChapters[i].paragraphs[j].sentences); k++)
               {
                  count_of_word += countFrequency(allChapters[i].paragraphs[j].sentences[k], search);
               }
            }


            if (q.empty())
               q.push(pair<lli, Chapter> (count_of_word, allChapters[i]));
            else
            {
               if (q.top().first <= count_of_word)
               {
                  q.push(pair<lli, Chapter> (count_of_word, allChapters[i]));
                  if (sz(q) > numK)
                     q.pop();
               }
            }
         }
         //int n = int(q.size());
         cout << "Printing the top k in ascending order" << endl;
         lli n = sz(q);
         bool end = false;
         for (int i = 0; i < n; i++)
         {
            cout << "\nThe chapter with " << n - i << " th most occurrence of " << search << " ... \n" << endl;
            cout << "\nCount of " << search << " is " << q.top().first << "\n" << endl;
            cout << "Number: " << q.top().second.numChapter << " ,Name: " << q.top().second.name << endl;
            cout << "-------------------------------------------------------------------------------" << endl;



            q.pop();
         }
      }


      else if (choice == "paragraph") {
         priority_queue<pair<lli, Paragraph>, vector<pair<lli, Paragraph>>, CompFreqPara> q;
         for (int i = 0; i < sz(allChapters); i++)
         {
            for (int j = 0; j < sz(allChapters[i].paragraphs); j++)
            {
               long long int count_of_word = 0;
               for (int k = 0; k < sz(allChapters[i].paragraphs[j].sentences); k++)
               {
                  count_of_word += countFrequency(allChapters[i].paragraphs[j].sentences[k], search);
               }

               if (q.empty())
                  q.push(pair<lli, Paragraph> (count_of_word, allChapters[i].paragraphs[j]));
               else
               {
                  if (q.top().first <= count_of_word)
                  {
                     q.push(pair<lli, Paragraph> (count_of_word, allChapters[i].paragraphs[j]));
                     if (sz(q) > numK)
                        q.pop();
                  }
               }

            }
         }
         lli n = sz(q);
         for (int i = 0; i < n; i++)
         {
            cout << "\nThe paragraph with " << n - i  << " most occurrence of " << search << "... \n" << endl;
            cout << "\nCount of " << search << " is " << q.top().first << "\n" << endl;
            for (int j = 0; j < sz(q.top().second.sentences); j++)
            {
               cout << q.top().second.sentences[j] << '\n';
            }

            q.pop();
         }


      }

   }
};

class Play : public Book
{
public:
   int numOfScenes;
   vector<Chapter>allChapters;

   Play(string filename, string directoryPath)
   {
      loadChapters(filename, directoryPath);
   }
   long long int countFrequency(string str, string pattern)//searches if a pattern is present in a string or not
   {
      // cout << "search  " << str << endl;
      int patternLength = pattern.length();
      int strLength = str.length();
      if (str.length() == 0 || patternLength == 0)
         return 0;
      lli res = 0;
      for (int i = 0; i <= strLength - patternLength; i++)
      {
         int j;
         for (j = 0; j < patternLength; j++)
         {
            if (str[i + j] != pattern[j])
               break;

         }
         if (j == patternLength)
            res++;
      }
      return res;

   }
   bool checkCharacter(char ch)
   {
      if (ch >= 'a' && ch <= 'z')
         return true;
      if (ch >= 'A' && ch <= 'Z')
         return true;
      return false;
   }
   bool checkUpperCase(string checkstr)
   {
      if (checkstr.size() == 0)
         return false;
      lli len = sz(checkstr);
      for (lli i = 0; i < len; i++)
      {
         char ch1 = checkstr[i];
         if (checkCharacter(ch1))
         {
            if (ch1 >= 'a' && ch1 <= 'z')
               return false;
         }
      }
      if (checkstr[len - 1] == '.')
         return true;
      else
         return false;



   }
   void loadChapters(string nameFile, string directoryPath)
   {
      ifstream book ;
      book.open(nameFile);
      if (!book.is_open())
      {
         cout << "Book not found" << endl;
         return  ;
      }

      string str;
      Chapter *chapter = new Chapter();
      allChapters.push_back(*chapter);
      bool book_start = false;
      while (getline(book, str))
      {
         if ((str.find("***") != string::npos))
            book_start = true;
         if (book_start)
         {
            string::size_type i = str.find("SCENE ");
            if (i == string::npos)
            {


               if (!str.empty())
               {
                  allChapters.back().addlinetolastPara(str);
                  if (checkUpperCase(str))
                     allChapters.back().addCharacter(str);


               }
               else
               {
                  allChapters.back().nextp();


               }
            }
            else
            {

               free(chapter);
               chapter = new Chapter();
               allChapters.push_back(*chapter);
               //chapter->chapterName = sentence;
            }
         }
      }
      book.close();
      return ;
   }

   void search_play()
   {



      set<string>allC;
      for (int i = 0; i < sz(allChapters); i++)
      {
         //long long int count_of_word = 0;
         for (int j = 0; j < sz(allChapters[i].allCharacters); j++)
         {
            string str = allChapters[i].allCharacters[j];
            if (str.length())
            {
               string subs = str.substr(0, sz(str) - 1);
               allC.insert(subs);
            }


         }

      }


      cout << "All the characters in the play are:" << endl;
      cout << "The number of characters in the play are   " << sz(allC) << endl;
      cout << endl;
      for (auto i : allC)
         cout << i << endl;
      string search;

      cout << "Enter the character of the play which you want to  search: " << endl;
      cin >> search;
      transform(all(search), search.begin(), ::tolower);
      cout << "Searching Play... " << endl;
      cout << endl;
      cout << "------------------------" << endl;

      set<string>ans;
      for (int i = 0; i < sz(allChapters); i++)
      {
         set<string>scene;
         for (int j = 0; j < sz(allChapters[i].allCharacters); j++)
         {
            string charac = allChapters[i].allCharacters[j];
            if (sz(charac) == 0)
               continue;
            string subs = charac.substr(0, sz(charac) - 1);
            transform(all(subs), subs.begin(), ::tolower);
            scene.insert(subs);

         }
         if (scene.find(search) != scene.end())
         {
            for (int j = 0; j < sz(allChapters[i].allCharacters); j++)
            {

               ans.insert(allChapters[i].allCharacters[j]);

            }
         }







      }
      cout << "The following is the list of all other characters which appear in at least one scene with the input character." << endl;

      cout << "The number of characters are " << sz(ans) << endl;
      cout << endl;
      for (auto i : ans)
      {
         if (sz(i) == 0)
            continue;
         transform(all(i), i.begin(), ::toupper);
         string str = i.substr(0, sz(i) - 1);
         if (str == ("CHORUS"))
            continue;
         cout << str << endl;
      }
   }
};





inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
   s.erase(0, s.find_first_not_of(t));
   return s;
}
vector<lli> prefix_function(string &s)
{
   lli n = s.size();
   vector<lli>pi(n);
   for (lli i = 1; i < n; i++)
   {
      lli j = pi[i - 1];
      while (j > 0 && s[i] != s[j])
         j = pi[j - 1];
      if (s[i] == s[j])
         j++;
      pi[i] = j;

   }
   return pi;
}
void textgui()
{
   cout << endl;
   cout << endl;
   cout << "LMS Menu" << endl;
   cout << "---------------------------------------------------------------------------------------------------" << endl;
   cout << "---------------------------------------------------------------------------------------------------" << endl;
   cout << "Enter 1 to display all the books in the library (filename,title and authorname).\nEnter 2 to search books by title and display the list\nEnter 3 to search books by author name and display the list\nEnter 4 to display  a selected book\nEnter 5 to perform data analytics on a selected book\n" << endl;
   cout << "Enter -1 to quit LMS" << endl;
   cout << "---------------------------------------------------------------------------------------------------" << endl;
   cout << "---------------------------------------------------------------------------------------------------" << endl;
   cout << endl;
   cout << endl;

}
void list_dir(const char *path, vector<string>&fileInDirectory) //gives the list of all the files in the directories
{
   struct dirent *entry;
   DIR *dir = opendir(path);

   if (dir == NULL) {
      return;
   }
   while ((entry = readdir(dir)) != NULL) {
      string name = entry->d_name;
      lli fileLength = name.length();
      if (fileLength <= 4)
         continue;

      string extension = name.substr(fileLength - 4);
      if (extension == ".txt")
      {
         fileInDirectory.push_back(name);
      }


   }
   closedir(dir);
}
int search(string str, string pattern)//searches if a pattern is present in a string or not
{
   // cout << "search  " << str << endl;
   int patternLength = pattern.length();
   int strLength = str.length();
   if (str.length() == 0 || patternLength == 0)
      return -1;
   for (int i = 0; i <= strLength - patternLength; i++)
   {
      int j;
      for (j = 0; j < patternLength; j++)
      {
         if (str[i + j] != pattern[j])
            break;

      }
      if (j == patternLength)
         return i;
   }
   return -1;

}
void removeSpaces(string &str)
{
   // n is length of the original string
   int n = str.length();

   // i points to next position to be filled in
   // output string/ j points to next character
   // in the original string
   int i = 0, j = -1;

   // flag that sets to true is space is found
   bool spaceFound = false;

   // Handles leading spaces
   while (++j < n && str[j] == ' ');

   // read all characters of original string
   while (j < n)
   {
      // if current characters is non-space
      if (str[j] != ' ')
      {
         // remove preceding spaces before dot,
         // comma & question mark
         if ((str[j] == '.' || str[j] == ',' ||
               str[j] == '?') && i - 1 >= 0 &&
               str[i - 1] == ' ')
            str[i - 1] = str[j++];

         else
            // copy current character at index i
            // and increment both i and j
            str[i++] = str[j++];

         // set space flag to false when any
         // non-space character is found
         spaceFound = false;
      }
      // if current character is a space
      else if (str[j++] == ' ')
      {
         // If space is encountered for the first
         // time after a word, put one space in the
         // output and set space flag to true
         if (!spaceFound)
         {
            str[i++] = ' ';
            spaceFound = true;
         }
      }
   }

   // Remove trailing spaces
   if (i <= 1)
      str.erase(str.begin() + i, str.end());
   else
      str.erase(str.begin() + i - 1, str.end());
}

string findInfo(string nameFile, Book book, string toBeSearched)
{
   // freopen(nameFile,"r",stdin);

   ifstream MyTextFile ;
   MyTextFile.open(nameFile);
   int found = -1;
   string getString = "";
   while (true)
   {
      string str;
      getline(MyTextFile, str, '\n');

      found = search(str, toBeSearched);
      if (found != -1)
      {
         //cout << found << endl;
         getString = str.substr(found + toBeSearched.length());
         break;
      }
      if (MyTextFile.eof())
         break;


   }
   if (found == -1)
   {
      cout << "The text file   " << nameFile << "   is invalid as it has no  " << toBeSearched << endl;
      // book.title = getTitle;
      return getString;
   }

   MyTextFile.close();
   return getString;



}
vector<Book> searchByTitle(vector<Book>&vectorBooks)
{
   cout << "Enter the title to searched" << endl;
   string str2;
   getline(cin, str2);
   string str;
   getline(cin, str);
   // cin >> str;
   removeSpaces(str);
   transform(str.begin(), str.end(), str.begin(), ::tolower);
   // lli patternLength = str.length();

   vector<Book>res;
//  cout << vectorBooks.size() << "p" << endl;
   for (auto i : vectorBooks)
   {
      string titlename = i.title;
      removeSpaces(titlename);
      //cout << titleName << " " << i.filename << endl;
      transform(titlename.begin(), titlename.end(), titlename.begin(), ::tolower);

      if (titlename.find(str) != string::npos)
         res.push_back(i);


   }
   if (res.size() == 0)
   {
      cout << "No book matched with the entered substring as the title" << endl;
   }
   else
   {
      cout << "The following books have the entered substring as title" << endl;
      // for (auto i : res)
      //    i.print(i);
   }
   return res;


}
vector<Book> searchByAuthor(vector<Book>&vectorBooks)
{
   cout << "Enter the author to searched" << endl;
   string str2;
   getline(cin, str2);
   string str;
   getline(cin, str);
   transform(all(str), str.begin(), ::tolower);
   lli patternLength = str.length();

   vector<Book>res;
   for (auto i : vectorBooks)
   {
      string authorname = i.author;
      transform(all(authorname), authorname.begin(), ::tolower);

      if (authorname.find(str) != string::npos)
         res.push_back(i);




   }
   if (res.size() == 0)
   {
      cout << "No book matched with the entered substring as the author" << endl;
   }
   else
   {
      cout << "The following books have the entered substring as author" << endl;
      // for (auto i : res)
      //    i.print(i);
   }
   return res;


}
void printBooks(vector<Book>vec)
{
   for (auto i : vec)
      i.print(i);
}

int main(int argc, char *argv[])
{


   vector<string>fileInDirectory;
   string basePath(argv[1]);
   list_dir(argv[1], fileInDirectory);

   bool flag = false;
   int numOfFiles = 0;
   cout << "Welcome to Library Management System!" << endl;
   cout << "-------------------------------------------------------------------------------" << endl;

   cout << "First you would have to provide the book type for all the new files present in the directory" << endl;
   for (auto i : fileInDirectory)
   {

      if (i == "index.txt")
      {

         flag = true;
      }

   }
   map<string, Book> mp;

   vector<Book>vectorBooks;
   if (flag) //index.txt file is present in the directory imp! fileIndeirectory also contains index.txt
   {
      cout << "The index.txt file is already created" << endl;
      cout << "Updating the index.txt file ......................................" << endl;
      fstream myIndexFile;
      myIndexFile.open("index.txt", ios::in);
      vector<pair<string, string>>oldIndex;
      string word;
      while (myIndexFile >> word)
      {
         string str1 = word;

         myIndexFile >> word;
         oldIndex.push_back({str1, word});
      }
      myIndexFile.close();
      vector<pair<string, string>>newIndex;
      //vector<Book>vectorBooks;
      for (auto i : fileInDirectory)//to check if the ith text file is present in the oldindex or not
      {
         if (i == "index.txt")
            continue;
         bool present = false;
         string type = "";
         for (auto j : oldIndex)
         {
            if (j.first == i) //ith text file is present so no need to prompt the user
            {
               present = true;
               type = j.second;
               break;


            }

         }
         Book bb;
         if (present)
         {
            newIndex.push_back({i, type});
            bb.bookType = type;

         }
         else
         {
            cout << "Found new book of file name   " << i << endl;
            cout << "Enter the type of the book with filename " << i  << endl;
            string bookType;
            cin >> bookType;
            newIndex.push_back({i, bookType});
            bb.bookType = bookType;
            // myIndexFile << i << " " << bookType << endl;
         }
         string title = findInfo(i, bb, "Title:");
         string author = findInfo(i, bb, "Author:");
         string date = findInfo(i, bb, "Release Date:");
         string lang = findInfo(i, bb, "Language:");
         bb.title = ltrim(title);
         bb.author = ltrim(author);
         bb.releaseDate = ltrim(date);
         bb.language = ltrim(lang);
         bb.filename = i;
         bb.filepath = basePath + "\\" + i;
         vectorBooks.push_back(bb);
         mp[i] = bb;






      }
      myIndexFile.open("index.txt", ios::out);
      for (auto i : newIndex)
      {
         myIndexFile << i.first << " " << i.second << endl;

      }



   }
   else
   {
      cout << "The index.txt is not yet created so creating that ..." << endl;
      cout << " Automatically detecting all files in the directory and updating the index.txt so created.........................................................." << endl;

      ofstream myIndexFile("index.txt");
      int index = 0;
      for (auto i : fileInDirectory)
      {
         cout << "Enter the type of the book with filename " + i + " " << endl;
         string bookType;
         cin >> bookType;
         Book bb;
         bb.index = index;
         bb.bookType = bookType;
         string title = findInfo(i, bb, "Title:");
         string author = findInfo(i, bb, "Author:");
         string date = findInfo(i, bb, "Release Date:");
         string lang = findInfo(i, bb, "Language:");
         bb.title = ltrim(title);
         bb.author = ltrim(author);
         bb.releaseDate = ltrim(date);
         bb.language = ltrim(lang);
         bb.filename = i;
         bb.filepath = basePath + "\\" + i;
         vectorBooks.push_back(bb);
         mp[i] = bb;
         //bb.print(bb);
         myIndexFile << i << " " << bookType << endl;
         index++;






      }


   }
   while (1)
   {
      textgui();

      //case 2 -PART 1
      cout << "Enter your choice" << endl;
      int userChoice;
      cin >> userChoice;
      if (userChoice == -1)
      {
         cout << "Exiting from LMS ...." << endl;
         cout << "Thank you for joining us" << endl;
         break;
      }
      if (userChoice == 1)
      {
         printBooks(vectorBooks);

      }
      //case 2-PART 2
      vector<Book> booksFoundBySearchTitle;
      vector<Book>booksFoundBySearchAuthor;
      if (userChoice == 2)
      {
         booksFoundBySearchTitle = searchByTitle(vectorBooks);
         printBooks(booksFoundBySearchTitle);
         cout << "Do you want to display a book from the list of books just displayed?(1 or 0)" << endl;
         int x;
         cin >> x;
         if (x)
         {
            cout << "Enter the file name of the book to be displayed" << endl;
            string fn;
            cin >> fn;
            Book bk = mp[fn];
            bk.displayBook(bk, fn);

         }
         cout << "Do you want to perform data analytics on the list of books displayed? (1 or 0) " << endl;

         int p;
         cin >> p;
         if (p == 1)
         {
            if (booksFoundBySearchTitle.size() + booksFoundBySearchAuthor.size() == 0)
            {
               cout << "No books ready to be displayed because the entered substring by user did not match any collection of books in the library" << endl;
               cout << "Perform task 2 or 3 to have choices available to display the most occurence of an input word" << endl;


            }
            //
            else
            {
               cout << "The list of books available for data analytics are" << endl;
               printBooks(booksFoundBySearchTitle);
               cout << endl;
               cout << endl;
               cout << "Enter the filename which you want to display " << endl;
               string filenameDisplay;
               cin >> filenameDisplay;
               //case 3 -PART 1
               Book bookToDisplay = mp[filenameDisplay];
               string stringBookDisplay = bookToDisplay.bookType;
               transform(all(stringBookDisplay), stringBookDisplay.begin(), ::tolower);
               if (stringBookDisplay == "novel")
               {
                  Novel nov(filenameDisplay, basePath);
                  nov.search_novel();






               }
               else if (stringBookDisplay == "play")
               {
                  Play pl(filenameDisplay, basePath);
                  pl.search_play();


               }

            }
         }

      }

      if (userChoice == 3)
      {
         booksFoundBySearchAuthor = searchByAuthor(vectorBooks);
         printBooks(booksFoundBySearchAuthor);
         cout << "Do you want to display a book from the list of books just displayed?(1 or 0)" << endl;
         int x;
         cin >> x;
         if (x)
         {
            cout << "Enter the file name of the book to be displayed" << endl;
            string fn;
            cin >> fn;
            Book bk = mp[fn];
            bk.displayBook(bk, fn);

         }
         cout << "Do you want to perform data analytics on the list of books displayed? (1 or 0) " << endl;
         int p;
         cin >> p;
         if (p == 1)
         {
            if (booksFoundBySearchTitle.size() + booksFoundBySearchAuthor.size() == 0)
            {
               cout << "No books ready to be displayed because the entered substring by user did not match any collection of books in the library" << endl;
               cout << "Perform task 2 or 3 to have choices available to display the most occurence of an input word" << endl;


            }
            //
            else
            {

               cout << "The list of books available for data analytics are" << endl;
               printBooks(booksFoundBySearchAuthor);
               cout << endl;
               cout << endl;
               cout << "Enter the filename which you want to display " << endl;
               string filenameDisplay;
               cin >> filenameDisplay;
               //case 3 -PART 1
               Book bookToDisplay = mp[filenameDisplay];
               string stringBookDisplay = bookToDisplay.bookType;
               transform(all(stringBookDisplay), stringBookDisplay.begin(), ::tolower);
               if (stringBookDisplay == "novel")
               {
                  Novel nov(filenameDisplay, basePath);
                  nov.search_novel();






               }
               else if (stringBookDisplay == "play")
               {
                  Play pl(filenameDisplay, basePath);
                  pl.search_play();


               }

            }

         }
      }
      if (userChoice == 4)
      {
         cout << "Select a filename from the following list of files to perform data analytics" << endl;
         for (auto i : fileInDirectory)
         {
            // cout << i << " " << "k" << endl;
            if (i == "index.txt")
            {
               //cout << "i" << endl;
               continue;
            }
            cout << i << endl;
         }
         cout << "Enter your choice" << endl;
         string filenameDisplay;
         cin >> filenameDisplay;
         Book bookToDisplay = mp[filenameDisplay];
         bookToDisplay.displayBook(bookToDisplay, filenameDisplay);


      }

      if (userChoice == 5)
      {
         cout << "Select a filename from the following list of files to perform data analytics" << endl;
         for (auto i : fileInDirectory)
         {
            // cout << i << " " << "k" << endl;
            if (i == "index.txt")
            {
               //cout << "i" << endl;
               continue;
            }
            cout << i << endl;
         }
         cout << "Enter your choice" << endl;
         string filenameDisplay;
         cin >> filenameDisplay;
         //case 3 -PART 1
         Book bookToDisplay = mp[filenameDisplay];
         string stringBookDisplay = bookToDisplay.bookType;
         transform(all(stringBookDisplay), stringBookDisplay.begin(), ::tolower);
         if (stringBookDisplay == "novel")
         {
            Novel nov(filenameDisplay, basePath);
            nov.search_novel();






         }
         else if (stringBookDisplay == "play")
         {
            Play pl(filenameDisplay, basePath);
            pl.search_play();


         }

      }





   }
}





