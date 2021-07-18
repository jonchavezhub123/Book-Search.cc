#include <iostream>
#include <mysql.h>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

    const char* MY_HOSTNAME = "courses";
    const char* MY_DATABASE = "z1866268";
    const char* MY_USERNAME = "z1866268";
    const char* MY_PASSWORD = "2001Feb25";

//bool connect(MYSQL*, const char*, const char*, const char*, const char*, const char*);

int main()
{
	string input;
	cout <<"Choose an option to run (q to quit, B to Book List, A to Auto Search, T to Title Search): ";  cin >> input;

	while( input != "q")
	{

	if( input == "B")
	{
	MYSQL *ql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	ql = mysql_init(NULL);

	if(!mysql_real_connect(ql, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 0, NULL, 0)) 
	cerr << mysql_error(ql) << endl;
 
	 if (mysql_query(ql, "SELECT DISTINCT Title,Price ,AuthorLast, AuthorFirst FROM Book,Wrote,Author WHERE Book.BookCode = Wrote.BookCode AND Author.AuthorNum = Wrote.AuthorNum ORDER BY Sequence;")) 
	{
            cerr << mysql_error(ql) << endl;
            return false;
        }

	int i = 0;
	 // Get a result set
        res = mysql_use_result(ql);
        // Fetch a result set
        while ((row = mysql_fetch_row(res)) != NULL )
	{
            i++;
	    cout << i << ".) " << row[0] << ", $"<< row[1] << ", "<< row[2] << ", " << row[3]<< endl;
	  
	}
}

	else if(input == "A")
	{
		string first;
		string last;

		cout << "Name an author: "; cin >> first >> last;
		
		MYSQL  *sql1;
		MYSQL_RES *res;
		MYSQL_ROW row;

		sql1 = mysql_init(NULL);

		if(!mysql_real_connect(sql1, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 0, NULL, 0)) 
        	cerr << mysql_error(sql1) << endl;
		
		if (mysql_query(sql1, "SELECT DISTINCT AuthorLast, AuthorFirst FROM Author")) 
        	{
            	cerr << mysql_error(sql1) << endl;
            	return false;
        	}

			 res = mysql_use_result(sql1);

			 string first2;
                         string last2;
			while ((row = mysql_fetch_row(res)) != NULL)
			{
		
				if(row[0] == last && row[1] == first)
				{
					last2 = row[0];
					first2 = row[1];
					break;
				}
			}
	
		if(last == last2 && first == first2)
		{
                	MYSQL_RES *res2;
                	MYSQL_ROW row2;

                	sql1 = mysql_init(NULL);

                if(!mysql_real_connect(sql1, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 0, NULL, 0)) 
                cerr << mysql_error(sql1) << endl;

		std::ostringstream oss;
		oss << "SELECT DISTINCT Title, Book.BookCode, AuthorFirst, AuthorLast, Price,Branch.BranchNum,OnHand  FROM Book, Wrote,Author, Inventory, Branch WHERE Author.AuthorFirst = '"
			<< first  << "' AND Author.AuthorLast = '" 
			<< last << "' AND Wrote.AuthorNum = Author.AuthorNum AND Wrote.BookCode = Book.BookCode AND Branch.BranchNum = Inventory.BranchNum AND Inventory.BookCode = Book.BookCode BR";
		string var = oss.str();
	
		const char *C = var.c_str();	
                  
                if (mysql_query(sql1, C)) 
                {
                cerr << mysql_error(sql1) << endl;
                return false;
                }
                         res2 = mysql_use_result(sql1);

			int x =0;
                        while ((row2 = mysql_fetch_row(res2)) != NULL)
			{
				x++;
				cout << "Book "<< x << ": " << "Title-> " 
				<<  row2[0] << " BookCode-> " <<row2[1] << " AuthorFirst-> " <<row2[2] << " AuthorLast-> "<<  row2[3] << " Price-> " << row2[4] <<endl; 
				cout << "Branch " << row2[5] << ": OnHand-> " << row2[6] << endl; 
			}
	}

	else 
		cout << "Couldn't find person" << endl;
}
	else if(input == "T")
	{
		string title;
		cout << "Name a book: ";cin >> title;

		MYSQL  *sql1;
                MYSQL_RES *res;
                MYSQL_ROW row;

                sql1 = mysql_init(NULL);

                if(!mysql_real_connect(sql1, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 0, NULL, 0)) 
                cerr << mysql_error(sql1) << endl;

		 if (mysql_query(sql1, "SELECT Title FROM Book")) 
                {
                cerr << mysql_error(sql1) << endl;
                return false;
                }

		res = mysql_use_result(sql1);
                string title2;

		 while ((row = mysql_fetch_row(res)) != NULL)
                        {
                
                                if(row[0] == title )
                                {
                                        title2 = row[0];
                                        break;
                                }
                        }

		if(title2 == title)
		{
			MYSQL_RES *res2;
                        MYSQL_ROW row2;

                        sql1 = mysql_init(NULL);

                if(!mysql_real_connect(sql1, MY_HOSTNAME, MY_USERNAME, MY_PASSWORD, MY_DATABASE, 0, NULL, 0)) 
                cerr << mysql_error(sql1) << endl;

                std::ostringstream oss;
                oss << "SELECT DISTINCT Title, Book.BookCode, AuthorFirst, AuthorLast, Price,Branch.BranchNum,OnHand  FROM Book, Wrote,Author, Inventory, Branch WHERE  Title = '" 
	<< title << "' AND Wrote.BookCode = Book.BookCode AND Branch.BranchNum = Inventory.BranchNum AND Inventory.BookCode = Book.BookCode AND Wrote.AuthorNum = Author.AuthorNum";
                string var = oss.str();
        
                const char *C = var.c_str();    
                  
                if (mysql_query(sql1, C)) 
                {
                cerr << mysql_error(sql1) << endl;
                return false;
                }
                         res2 = mysql_use_result(sql1);

                        int x =0;
                        while ((row2 = mysql_fetch_row(res2)) != NULL)
                        {
                                x++;
                                cout << "Book "<< x << ": " << "Title-> " 
                                <<  row2[0] << " BookCode-> " <<row2[1] << " AuthorFirst-> " <<row2[2] << " AuthorLast-> "<<  row2[3] << " Price-> " << row2[4] <<endl; 
                                cout << "Branch " << row2[5] << ": OnHand-> " << row2[6] << endl; 
                        }
	        }


		else
		cout << "Could not find book" << endl;
	}
	cout << "Choose another option: "; cin >> input;
}
}
