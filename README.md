# BTree-For-BookManager
This is my data structure‘s course design project.It uses BTree to build this system for improving the query's speed.
This project contains these function as list:

1. storage books: buy a new book, after the classification and determination to register accounts to books isbn.
If the book is already in the account, it will only increase the total stock.
2. delete books: if a book has no reserved value, it is written off from the book's account.

3. borrowing books: if the existing volume of a book is greater than zero, a book is borrowed and
the book number and the return period of the borrower are registered. If less than 0, ask if an appointment is made.

4.return the book: write off the registration of the borrower and change the amount of the book.

5.show : the B tree is displayed in the form of a concave table. This operation is set up for the purpose of debugging and maintenance.

6. view the author's work: by inputting the name of the author, output its name

7. see the book state: the input view ISBN, book information, including the book itself, and the borrower and booking information.

8. view the library situation: the information of all books in the output library

1.入库图书：新购入一种书，经分类和确定书号之后登记到图书账目中去。如果这种书在帐中已有，则只将总库存量增加。
2.删除图书：某种书已无保留价值，将它从图书账目中注销。
3.借阅图书：如果一种书的现存量大于零，则借出一本，登记借阅者的图书证号和归还期限。如果小于等于0，则询问是否进行预约。
4.归还图书：注销对借阅者的登记，改变该书的现存量。
5.显示：以凹入表的形式显示B树。这个操作是为了调试和维护的目的而设置。
6.查看著者著作：通过输入著者的名字，输出其名下的著作
7.查看图书状态：通过输入书号，查看书本的信息，包括书本本身的信息，与借阅者和预约者的信息。
8.查看书库情况：输出书库中所有图书的信息

This project is a memory system that can't save data after close it.
Last but not least,you can see your option's log in the log file which is located in the current dir.
