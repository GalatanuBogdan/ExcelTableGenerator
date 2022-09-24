#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


#define STARTING_DAY 12
#define STARTING_MONTH 9
#define STARTING_YEAR 2022
#define ENDING_YEAR 2025

vector<string> persons = { "Beatrice", "Mariana", "Irina", "Carmen", "Alina"};
vector<string> availableHours = { "07:00","07:30","08:00","08:30","09:00","09:30","10:00","10:30","11:00","11:30","12:00","12:30","13:00","13:30","14:00","14:30","15:00","15:30","16:00","16:30","17:00","17:30","18:00","18:30","19:00","19:30","20:00","20:30","21:00","21:30","22:00" };

int dayNumber(int day, int month, int year)
{
	/*Index     Day
		0         Sunday
		1         Monday
		2         Tuesday
		3         Wednesday
		4         Thursday
		5         Friday
		6         Saturday* /
	*/

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
					   4, 6, 2, 4 };
	year -= month < 3;
	return (year + year / 4 - year / 100 +
		year / 400 + t[month - 1] + day) % 7;
}

/*
  A Function that returns the name of the month
  with a given month number

  Month Number     Name
  0                January
  1                February
  2                March
  3                April
  4                May
  5                June
  6                July
  7                August
  8                September
  9                October
  10               November
  11               December */
string getDayName(int dayIndex)
{
	/*Index     Day
		0         Sunday
		1         Monday
		2         Tuesday
		3         Wednesday
		4         Thursday
		5         Friday
		6         Saturday* /
	*/
	//add some spaces to be sure that the text will be aligned in center
	std::vector<string> days = 
	{ 
		"  Duminica  ",
		"    Luni    ",
		"    Marti   ",
		"  Miercuri  ",
		"    Joi     ",
		"   Vineri   ",
		"  Sambata   " 
	};

	return (days[dayIndex]);
}

string getMonthName(int monthNumber)
{
	string months[] = { "January", "February", "March",
					   "April", "May", "June",
					   "July", "August", "September",
					   "October", "November", "December"
	};

	return (months[monthNumber]);
}

/* A Function to return the number of days in
   a month

  Month Number     Name        Number of Days
  0                January     31
  1                February    28 (non-leap) / 29 (leap)
  2                March       31
  3                April       30
  4                May         31
  5                June        30
  6                July        31
  7                August      31
  8                September   30
  9                October     31
  10               November    30
  11               December    31

*/
int numberOfDays(int monthNumber, int year)
{
	// January
	if (monthNumber == 0)
		return (31);

	// February
	if (monthNumber == 1)
	{
		// If the year is leap then February has
		// 29 days
		if (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March
	if (monthNumber == 2)
		return (31);

	// April
	if (monthNumber == 3)
		return (30);

	// May
	if (monthNumber == 4)
		return (31);

	// June
	if (monthNumber == 5)
		return (30);

	// July
	if (monthNumber == 6)
		return (31);

	// August
	if (monthNumber == 7)
		return (31);

	// September
	if (monthNumber == 8)
		return (30);

	// October
	if (monthNumber == 9)
		return (31);

	// November
	if (monthNumber == 10)
		return (30);

	// December
	if (monthNumber == 11)
		return (31);
}

// Function to print the calendar of the given year
void printCalendar(int year)
{
	printf("         Calendar - %d\n\n", year);
	int days;

	// Index of the day from 0 to 6
	int current = dayNumber(1, 1, year);

	// i --> Iterate through all the months
	// j --> Iterate through all the days of the
	//       month - i
	for (int i = 0; i < 12; i++)
	{
		days = numberOfDays(i, year);

		// Print the current month name
		printf("\n  ------------%s-------------\n",
			getMonthName(i).c_str());

		// Print the columns
		//printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		for (int j = 1; j <= days; j++)
		{
			//printf("%5d", j);

			int dayIndex = dayNumber(j, i + 1, year);
			std::string dayName = getDayName(dayIndex);

			printf("%d.%d.%d %s\n", j, i + 1, year, dayName.c_str());

			if (dayIndex == 0) //duminica
			{
				printf("\n");
			}
		}
	}

	return;
}

int getNumOfDaysFromYear(int year)
{
	int numOfDaysInAYear = 0;
	for(int i=0;i<12;i++)
		numOfDaysInAYear += numberOfDays(i, year);

	return numOfDaysInAYear;
}

int main()
{
	//printCalendar(STARTING_YEAR);

	ofstream out("output2.xml");

	std::string document;

	std::string xmlVersion = "<?xml version=\"1.0\"?>";
	
	document.append(xmlVersion);
	
	std::string workbook;

	workbook.append("<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\"\n");
	workbook.append("xmlns:o=\"urn:schemas-microsoft-com:office:office\"\n");
	workbook.append("xmlns:x=\"urn:schemas-microsoft-com:office:excel\"\n");
	workbook.append("xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"\n");
	workbook.append("xmlns:html=\"http://www.w3.org/TR/REC-html40\">\n");
	
	for (int i = 0;i < persons.size();i++)
	{
		std::string workSheet = "<Worksheet ss:Name=\"" + persons[i] + "\">";

		int numOfYears = ENDING_YEAR - STARTING_YEAR + 1;

		//get total number of columns needed
		int columnCount = 1; //extra 1 for description
		
		//count for each year, how many days we have
		for (int currentYear = STARTING_YEAR; currentYear <= ENDING_YEAR; currentYear++)
			columnCount += getNumOfDaysFromYear(currentYear);
		
		std::string columnCountString = std::to_string(columnCount);

		int rowCount = 2 + availableHours.size();//extra 2 for description
		std::string rowCountString = std::to_string(rowCount);

		std::string table = "<Table ss:ExpandedColumnCount=\"" + columnCountString + "\" ss:ExpandedRowCount=\"" + rowCountString + "\">";
		std::string rowWithDayNames;
		std::string rowWithExactDateName;

		rowWithDayNames.append("<Row>");
		rowWithExactDateName.append("<Row>");

		//first add one empty cell and one cell with "hours" name
		rowWithDayNames.append("<Cell><Data ss:Type=\"String\"></Data></Cell>");
		rowWithExactDateName.append("<Cell><Data ss:Type=\"String\">Ora</Data></Cell>");

		for (int currentYear = STARTING_YEAR; currentYear <= ENDING_YEAR; currentYear++)
		{
			//go over all the months
			for (int j = 0;j < 12;j++)
			{
				//go over all the days
				int daysNumber = numberOfDays(j, currentYear);
				for (int k = 1;k <= daysNumber;k++)
				{
					int dayIndex = dayNumber(k, j + 1, currentYear);
					std::string dayName = getDayName(dayIndex);

					std::string dayNameCell =
						string("<Cell>") +
						string("<Data ss:Type=\"String\">") +
						dayName +
						string("</Data>") +
						string("</Cell>");

					rowWithDayNames.append(dayNameCell);

					std::string exactDateCell =
						string("<Cell>") +
						string("<Data ss:Type=\"String\">") +
						std::string(to_string(k) + "." + to_string(j + 1) + "." + to_string(currentYear)) +
						string("</Data>") +
						string("</Cell>");
					rowWithExactDateName.append(exactDateCell);
				}
			}
		}

		rowWithDayNames.append("</Row>");
		rowWithExactDateName.append("</Row>");
		table.append(rowWithDayNames);
		table.append(rowWithExactDateName);

		for (int j = 0;j < availableHours.size();j++)
		{
			std::string rowWithAvailableHours("<Row>");

			std::string availableHour =
				string("<Cell>") +
				string("<Data ss:Type=\"String\">") +
				availableHours[j] +
				string("</Data>") +
				string("</Cell>");

			rowWithAvailableHours.append(availableHour);

			for (int currentYear = STARTING_YEAR; currentYear <= ENDING_YEAR; currentYear++)
			{
				//go over all the months
				for (int j = 0;j < 12;j++)
				{
					//go over all the days
					int daysNumber = numberOfDays(j, currentYear);
					for (int k = 1;k <= daysNumber;k++)
					{
						std::string emptyCell =
							string("<Cell>") +
							string("<Data ss:Type=\"String\">") +
							string("</Data>") +
							string("</Cell>");

						rowWithAvailableHours.append(emptyCell);
					}
				}
			}

			rowWithAvailableHours.append("</Row>");

			table.append(rowWithAvailableHours);
		}

		table.append("</Table>");

		workSheet.append(table);

		workSheet.append("</Worksheet>");

		workbook.append(workSheet);
	}

	workbook.append("</Workbook>");

	document.append(workbook);

	std::cout << document;

	out << document;
}