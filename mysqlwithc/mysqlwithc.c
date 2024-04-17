#include <stdio.h>
#include <mysql.h>
#include <conio.h>
#include <stdlib.h>

void menu();
void getdata();
void display();
void add();
void search();
void update();
void del();

int main()
{
	menu();
	return 0;
}

void menu()
{
	char ch;
	do
	{
		system("cls");
		printf("1. Enter Student Data\n");
		printf("2. Display Student Data\n");
		printf("3. Add Student Data\n");
		printf("4. Search Student Data\n");
		printf("5. Update Stuent Data\n");
		printf("6. Delete Student Data\n");
		printf("7. Exit\n");
		printf("Enter Your Choice: ");
		scanf_s(" %c", &ch);

		switch (ch)
		{
		case '1':
			getdata();
			break;
		case '2':
			display();
			break;
		case '3':
			add();
			break;
		case '4':
			search();
			break;
		case '5':
			update();
			break;
		case '6':
			del();
			break;
		case '7':
			exit(0);
			break;
		default:
			printf("Invalid Choice\n");
		}
	} while (true);
	getchar();
}

void getdata()
{
	system("cls");

	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", NULL, 3306, NULL, 0);

	char name[20], gender, semester, course[10], mobileno[15];
	int rollno;

	char createdatabase[] = "create database mysqlwithc";

	if (mysql_query(conn, createdatabase))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	else
	{
		printf("Enter Student Name: ");
		scanf_s("%s", &name);
		printf("Enter Student Roll No.: ");
		scanf_s(" %d", &rollno);
		printf("Enter Student Mobile No.: ");
		scanf_s(" %s", &mobileno);
		printf("Enter Student Gender: ");
		scanf_s(" %c", &gender);
		printf("Enter Student Course: ");
		scanf_s(" %s", &course);
		printf("Enter Student Semester: ");
		scanf_s(" %c", &semester);

		char usedatabase[] = "use mysqlwithc";

		if (mysql_query(conn,usedatabase))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}
		else
		{
			char createtable[] = "create table students (name varchar(20), rollno int, mobileno bigint, gender char, course varchar(10), semester char)";

			if (mysql_query(conn,createtable))
			{
				fprintf(stderr, "%s\n", mysql_error(conn));
			}
			else
			{
				char query[256];
				sprintf(query, "INSERT INTO students (name, rollno, mobileno, gender, course, semester) VALUES ('%s', %d, '%s', '%c', '%s', '%c')",
					name, rollno, mobileno, gender, course, semester);

				if (mysql_query(conn,query))
				{
					fprintf(stderr, "%s\n", mysql_error(conn));
				}
				else
				{
					printf("Data Inserted Successfully\n");
				}
			}
		}
	}
	getchar();
}

void display()
{
	system("cls");

	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", "mysqlwithc", 3306, NULL, 0);

	char display[] = "select * from students";

	if (mysql_query(conn,display))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);

	if (res == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		mysql_close(conn);
		return;
	}

	int num_fields = mysql_num_fields(res);

	if (num_fields != 6)
	{
		fprintf(stderr, "Unexpected number of fields in result set: %d\n", num_fields);
		mysql_free_result(res); // Free result set memory
		mysql_close(conn); // Close MySQL connection
		getchar(); // Wait for keypress before exiting
		return;
	}

	while ((row = mysql_fetch_row(res)))
	{
		printf("Student Name: %s\n", row[0]);
		printf("Student No.: %s\n", row[1]);
		printf("Student Mobile No. %s\n", row[2]);
		printf("Student Gender: %s\n", row[3]);
		printf("Student Course: %s\n", row[4]);
		printf("Student Semester: %s\n\n", row[5]);
	}

	mysql_free_result(res);

	getchar();
}

void add()
{
	system("cls");

	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", NULL, 3306, NULL, 0);

	char usedatabase[] = "use mysqlwithc";

	if (mysql_query(conn,usedatabase))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	else
	{
		char name[20], gender, semester, course[10], mobileno[15];
		int rollno;

		printf("Enter Student Name: ");
		scanf_s("%s", &name);
		printf("Enter Student Roll No.: ");
		scanf_s(" %d", &rollno);
		printf("Enter Student Mobile No.: ");
		scanf_s(" %s", &mobileno);
		printf("Enter Student Gender: ");
		scanf_s(" %c", &gender);
		printf("Enter Student Course: ");
		scanf_s(" %s", &course);
		printf("Enter Student Semester: ");
		scanf_s(" %c", &semester);

		char query[256];
		sprintf(query, "INSERT INTO students (name, rollno, mobileno, gender, course, semester) VALUES ('%s', %d, '%s', '%c', '%s', '%c')",
			name, rollno, mobileno, gender, course, semester);

		if (mysql_query(conn,query))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}
		else
		{
			printf("Student Added Successfully\n");
		}
	}
	getchar();
}

void search()
{
	system("cls");

	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", NULL, 3306, NULL, 0);

	int srollno;

	printf("Enter Student Roll No. That You Want To Search: ");
	scanf_s("%d", &srollno);

	char usedatabase[] = "use mysqlwithc";

	if (mysql_query(conn, usedatabase))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	else
	{
		char searchquery[300];
		sprintf(searchquery, "select * from students where rollno = %d", srollno);

		if (mysql_query(conn, searchquery))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}
		else
		{
			res = mysql_store_result(conn);

			if (res == NULL)
			{
				fprintf(stderr, "%s\n", mysql_error(conn));
				mysql_close(conn);
				return;
			}

			int num_fields = mysql_num_fields(res);

			if (num_fields != 6)
			{
				fprintf(stderr, "Unexpected number of fields in result set: %d\n", num_fields);
				mysql_free_result(res); // Free result set memory
				mysql_close(conn); // Close MySQL connection
				getchar(); // Wait for keypress before exiting
				return;
			}

			while ((row = mysql_fetch_row(res)))
			{
				printf("Student Name: %s\n", row[0]);
				printf("Student No.: %s\n", row[1]);
				printf("Student Mobile No. %s\n", row[2]);
				printf("Student Gender: %s\n", row[3]);
				printf("Student Course: %s\n", row[4]);
				printf("Student Semester: %s\n\n", row[5]);
			}

			mysql_free_result(res);
		}
	}
	getchar();
}

void update()
{
	system("cls");

	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", NULL, 3306, NULL, 0);

	char usedatabase[] = "use mysqlwithc";

	if (mysql_query(conn, usedatabase))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	else
	{
		char name[20], gender, semester, course[10], mobileno[15];
		int rollno;

		int srollno;

		printf("Enter Roll No. That You Want To Update: ");
		scanf_s("%d", &srollno);

		printf("Enter Student Name: ");
		scanf_s(" %s", name, sizeof(name));
		printf("Enter Student Roll No.: ");
		scanf_s(" %d", &rollno);
		printf("Enter Student Mobile No.: ");
		scanf_s(" %s", &mobileno);
		printf("Enter Student Gender: ");
		scanf_s(" %c", &gender);
		printf("Enter Student Course: ");
		scanf_s(" %s", &course);
		printf("Enter Student Semester: ");
		scanf_s(" %c", &semester);

		char updatequery[300];
		sprintf(updatequery, "update students set name = '%s',mobileno = '%s',gender = '%c',course = '%s',semester = '%c' where rollno = %d", name, mobileno, gender, course, semester, srollno);

		if (mysql_query(conn, updatequery))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}
		else
		{
			printf("Data Updated Successfully\n");
		}
	}
	getchar();
}

void del()
{
	system("cls");

	MYSQL* conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "Mangesh@2006", NULL, 3306, NULL, 0);

	char usedatabase[] = "use mysqlwithc";

	if (mysql_query(conn, usedatabase))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
	}
	else
	{
		int srollno;

		printf("Enter Roll No. That You Want To Delete: ");
		scanf_s("%d", &srollno);

		char deletequery[300];
		sprintf(deletequery, "delete from students where rollno = %d", srollno);

		if (mysql_query(conn,deletequery))
		{
			fprintf(stderr, "%s\n", mysql_error(conn));
		}
		else
		{
			printf("Student Data Deleted Successfully\n");
		}
	}
	getchar();
}