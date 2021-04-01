# LMS

A library of books contains many books. Each book is stored in a text file in a given directory,
which contains the library. Each book has a title, an author, a release date, and a Language. These
can be read from the Project Gutenberg file header, see for example the novel Mobi Dick by
Herman Hesse:
https://www.gutenberg.org/files/2701/2701-0.txt
The file header is given below for reference.
A book can contain many types of content, e.g. a novel, a play, etc. For this assignment, you need
to implement a novel and play, but your software design should be such that other types of books
can be easily added. A novel can contain many chapters. Each chapter has a title followed by
many paragraphs. Each paragraph contains many sentences, and each sentence is a sequence of
words. A play has a optional prologue followed by many acts. Each act has many scenes, and each
scene is a sequence of dialogues. Additionally, a play also has a list of characters or personae,
where each dialogue is spoken by a character.
