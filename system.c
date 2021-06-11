#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define MAXCREDIT 25
#define MAXSTR 35
#define MAX 100

typedef struct
{
	char id[7];
	char name[MAXSTR];
	char label[MAXSTR];
} academician;

typedef struct
{
	char id[7];
	char name[MAXSTR];
	char credit[3];
	char lecturerId[7];
} lectureType;

typedef struct
{
	char id[7];
	char name[MAXSTR];
	char lecture[3];
	char credit[3];

} student;

typedef struct
{
	char studentId[7];
	char lecture_id[7];
	char point[3];
	char date[MAXSTR];
	char value[2];
} points;

//FONKSIYONLAR
int mainmenu();

int studentMenu();
void addStudent(student *, int);
void updateStudent(student *, int);
void deleteStudent(student *, int);
int addStudentToLecture(student *, int);
int removeStudentFromLecture(student *, int);

int academicianMenu();
void addAcademician(academician *, int);
void updateAcademician(academician *, int);
void deleteAcademician(academician *, int);

int lectureMenu();
void addLecture(lectureType *, int);
void updateLecture(lectureType *, int);
void deleteLecture(lectureType *, int);

void search();
void searchStudent(char *, student *, int, points *, int);
void searchAcademician(char *, academician *, int, lectureType *, int);
void searchLecture(char *, lectureType *, int, points *, int);

int countLine(char *);
char *stringCalculate(char *, char *, int);
char *date();
int main()
{
	mainmenu();
	printf("\n=Exit");
	return 0;
}
int mainmenu()
{
	int i, j = 0;
	int state = 0;
	char c;
	int line;
	system("@cls||clear");
	printf("Lecture Management System\nUmutcan Sevdi\nStructural Programming Project");
	printf("\n\n__________________________________________________________________________________\n"
		   "Options=\n__________________________________________________________________________________\n"
		   "1)Search\t\t| Inspect a lecture, student or an academician.\n"
		   "2)Student Management\t| Displays students.\n"
		   "3)Academician Management| Displays academicians.\n"
		   "4)Lecture Management\t| Displays avaliable lectures.\n"
		   "\n-------------------------------------------------------------------------------\nUse Backspace to exit\n-------------------------------------------------------------------------------\n");
	switch (getch())
	{
	case '1':
		search();
		break;
	case '2':
		studentMenu();
		break;
	case '3':
		academicianMenu();
		break;
	case '4':
		lectureMenu();
		break;
	case 8:
		printf("\n=mainMenuExit");
		exit(0);
	default:
		printf("Invalid Command\n\n-------------------------------------------------------------------------------\nPress any key to try again");
		getch();
		mainmenu();
	}
	mainmenu();
	return;
}
int studentMenu()
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n");
	int i, j = 0, state = 0;
	char c;
	int line = countLine("student.txt");
	student *stud = (student *)malloc((line) * sizeof(student));
	if (stud == NULL)
	{
		printf("error");
		return;
	}
	FILE *data = fopen("student.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				stud[i].credit[j] = '\0';
				state = 3;
			}
			else if (state == 0)
			{
				stud[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case ',':
			state = 2;
			stud[i].lecture[j] = '\0';
			j = 0;
			break;
		case '\n':
			stud[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			stud[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				stud[i].id[j] = c;
				break;
			case 1:
				stud[i].lecture[j] = c;
				break;
			case 2:
				stud[i].credit[j] = c;
				break;
			case 3:
				stud[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	printf("\nStudent List\n_________________________________________"
		   "\n|ID\t|Name\t\t|Lecture|Credit");
	for (i = 0; i < line; i++)
	{
		printf("\n|%s\t|%s\t|%s\t|%s", stud[i].id, stud[i].name, stud[i].lecture, stud[i].credit);
	}
	printf("\n|Total\t|%d\n_________________________________________________________", line);
	printf("\nOptions=\n__________________________________________________________________________________\n"
		   "1)Add\t\t| Add a student to the system.\n"
		   "2)Update\t| Updates a student's properties.\n"
		   "3)Delete\t| Deletes a student.\n"
		   "4)Add Student to Lecture\t| Adds a student to a lecture.\n"
		   "5)Delete Student from Lecture\t| Removes a student from the lecture.\n"
		   "\n-------------------------------------------------------------------------------\nUse Backspace to return\n-------------------------------------------------------------------------------\n");
	printf("\n=\t");
	switch (c = getch())
	{
	case '1':
		printf("\nAdd Student");
		addStudent(stud, line);
		getch();
		break;
	case '2':
		printf("Update Student");
		updateStudent(stud, line);
		getch();
		break;
	case '3':
		printf("Delete Student");
		deleteStudent(stud, line);
		getch();
		break;
	case '4':
		printf("Add Student to Lecture");
		addStudentToLecture(stud, line);
		break;
	case '5':
		printf("Delete Student from Lecture");
		removeStudentFromLecture(stud, line);
		break;
	case 8:
		printf("Back");
		mainmenu();
		break;
	default:
		printf("Invalid Command\n\n-------------------------------------------------------------------------------\nPress any key to try again");
		getch();
		studentMenu();
	}
	free(stud);
	fclose(data);
	printf("\n=back");
	mainmenu();
	return;
}
void addStudent(student *stud, int line)
{
	int i, extraSize;
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n"
		   "\nAdd Student=\n__________________________________________________________________________________\n");
	printf("\nEnter the number of  student .\n=");
	scanf("%d", &extraSize);
	printf("\n-------------------------------------------------------------------------------");
	student *extra = (student *)malloc((extraSize + 1) * sizeof(student));
	gets(extra[0].name);
	for (i = 0; i < extraSize; i++)
	{
		printf("\n%d. enter the name of the student\n=", i + 1);
		gets(extra[i].name);
		extra[i].lecture[0] = '0';
		extra[i].lecture[1] = '0';
		extra[i].lecture[2] = '\0';
		sprintf(extra[i].credit, "%d", MAXCREDIT);
		sprintf(extra[i].id, "%d", 101000 + line + i + 1);
		printf("\n-------------------------------------------------------------------------------");
	}
	FILE *fp = fopen("student.txt", "w");
	if (fp == NULL)
	{
		printf("\nError: File not found\n");
	}
	else
	{
		for (i = 0; i < line; i++)
		{
			fprintf(fp, "%s\t%s,%s\t%s\n", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
		}
		for (i = 0; i < extraSize; i++)
		{
			if (i != extraSize - 1)
			{
				fprintf(fp, "%s\t%s,%s\t%s\n", extra[i].id, extra[i].lecture, extra[i].credit, extra[i].name);
			}
			else
			{
				fprintf(fp, "%s\t%s,%s\t%s", extra[i].id, extra[i].lecture, extra[i].credit, extra[i].name);
			}
		}
		printf("\nstudentler added successfully \n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
	}
	fclose(fp);
	free(extra);
}
void deleteStudent(student *stud, int line)
{
	int i = 0, counter = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n"
		   "\nDelete Student=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of the student .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(stud[i].id, number) == 0)
		{
			stud[i].id[0] = '-';
			counter++;
		}
		else
		{
			i++;
		}
	}

	if (counter)
	{
		FILE *fp = fopen("student.txt", "w");
		if (fp == NULL)
		{
			printf("\nError: File not found\n");
		}
		else
		{
			for (i = 0; i < line; i++)
			{
				if (stud[i].id[0] != '-')
				{
					if (i != line - 1)
					{
						fprintf(fp, "%s\t%s,%s\t%s\n", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
					}
					else
					{
						fprintf(fp, "%s\t%s,%s\t%s", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
					}
				}
				else
				{
					printf("\n%s  deleted successfully\n__________________________________________________________________________________\nBackmek icin bir tusa basin...", stud[i].name);
				}
			}
		}

		fclose(fp);
	}
	else
	{
		printf("\nError: student with given ID does not exists.");
	}
}
void updateStudent(student *stud, int line)
{
	int i = 0, counter = 0;
	int j = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n"
		   "\nUpdate Student=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of  student .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(stud[i].id, number) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("Enter the new information for student ."
			   "\nAdi=",
			   stud[i].name, stud[i].id);
		gets(stud[i].name);
		gets(stud[i].name);
		printf("\nNumarasi=");
		gets(number);
		counter = 0;
		while (j < line && counter == 0)
		{
			if (strcmp(stud[j].id, number) == 0)
			{
				counter++;
			}
			else
			{
				j++;
			}
		}
		if (counter)
		{
			printf("\nError: number already exists.\n");
		}
		else
		{
			strcpy(stud[i].id, number);
			FILE *fp = fopen("student.txt", "w");
			if (fp == NULL)
			{
				printf("\nError: File not found\n");
			}
			else
			{
				for (i = 0; i < line; i++)
				{
					if (i != line - 1)
					{
						fprintf(fp, "%s\t%s,%s\t%s\n", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
					}
					else
					{
						fprintf(fp, "%s\t%s,%s\t%s", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
					}
				}
			}
			printf("\nstudent information updated successfully.\n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
			fclose(fp);
		}
	}
	else
	{
		printf("\nError: student with given ID does not exists.");
	}
}
int addStudentToLecture(student *stud, int line)
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n"
		   "\nAdd Student to Lecture=\n__________________________________________________________________________________\n");
	int i, j = 0, k = 0, counter = 0, state = 0;
	char lecture_credit[3];
	char number[7], c;
	char lecture_id[MAXSTR];
	printf("Enter the Lecture ID\n=");
	scanf("%s", lecture_id);
	FILE *lectureler = fopen("lecture.txt", "r");
	int line_lecture = countLine("lecture.txt");
	if (lectureler == NULL)
	{
		printf("error");
		return 1;
	}
	lectureType *lecture = (lectureType *)malloc((line_lecture) * sizeof(lectureType));

	while (!feof(lectureler))
	{
		c = fgetc(lectureler);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				lecture[i].lecturerId[j] = '\0';
				state = 3;
			}
			else if (state == 1)
			{
				lecture[i].credit[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecture[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecture[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecture[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecture[i].id[j] = c;
				break;
			case 1:
				lecture[i].credit[j] = c;
				break;
			case 2:
				lecture[i].lecturerId[j] = c;
				break;
			case 3:
				lecture[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	i = 0, j = 0, state = 0;
	int linePoint = countLine("points.txt");
	FILE *data = fopen("points.txt", "r");
	if (data == NULL)
	{
		printf("error");
		return 1;
	}
	points *grade = (points *)malloc((linePoint) * sizeof(points));
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = '\0';
				state = 1;
				break;
			case 1:
				grade[i].lecture_id[j] = '\0';
				state = 2;
				break;
			case 2:
				grade[i].point[j] = '\0';
				state = 3;
				break;
			case 3:
				grade[i].value[j] = '\0';

				state = 4;
				break;
			}
			j = 0;
			break;
		case '\n':
			grade[i].date[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			grade[i].date[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = c;
				break;
			case 1:
				grade[i].lecture_id[j] = c;
				break;
			case 2:
				grade[i].point[j] = c;
				break;
			case 4:
				grade[i].date[j] = c;
				break;
			case 3:
				grade[i].value[j] = c;
				break;
			}
			j++;
		}
	}
	fclose(data);
	i = 0, j = 0, state = 0;
	while (i < line_lecture && counter == 0)
	{
		if (strcmp(lecture[i].id, lecture_id) == 0)
		{
			counter++;
			lecture_credit[0] = lecture[i].credit[0];
			lecture_credit[1] = lecture[i].credit[1];
			lecture_credit[2] = '\0';
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		counter = 0;
		printf("Student ID that you would like to add lecture.\n=");
		scanf("%d", &j);
		points *eknot = (points *)malloc((j) * sizeof(points));
		for (k = 0; k < j; k++)
		{
			eknot[k].studentId[0] = '-';
			eknot[k].lecture_id[0] = '-';
			eknot[k].point[0] = '-';
		}
		for (k = 0; k < j; k++)
		{
			counter = 0;
			printf("\nEnter %d. student ID\n=", k + 1);
			scanf("%s", number);
			i = 0;
			while (i < line && counter == 0)
			{
				if (strcmp(stud[i].id, number) == 0)
				{
					printf("\n%s\t%s\t%s\t%d\t%d\t%s", stud[i].name, stud[i].id, stud[i].credit, i, counter, stringCalculate(stud[i].credit, lecture_credit, 0));
					if (stringCalculate(stud[i].credit, lecture_credit, 0)[0] == '-')
					{
						printf("\nError: Student does not have enough credits.\n\tStudent's Credit:\t%s\n\tRequired credit:\t%s", stud[i].credit, lecture_credit);
						i++;
					}
					else
					{
						strcpy(stud[i].lecture, stringCalculate(stud[i].lecture, "01", 1));
						strcpy(stud[i].credit, stringCalculate(stud[i].credit, lecture_credit, 0));
						counter++;
					}
				}
				else
				{
					i++;
				}

				if (counter)
				{
					strcpy(eknot[k].studentId, stud[i].id);
					strcpy(eknot[k].lecture_id, lecture_id);
					strcpy(eknot[k].point, "1");
					printf("\n%s added successfully to the Lecture.", stud[i].name);
				}
				else if (i >= line)
				{
					printf("\nNo student was found with given ID.");
				}
			}
		}
		data = fopen("points.txt", "a");
		state = 0;
		for (i = 0; i < j; i++)
		{
			strcpy(grade[i].date, date());
			if (eknot[i].studentId[0] != '-')
			{
				state++;
				printf("%s\t%s\t%s\n", eknot[i].studentId, eknot[i].lecture_id, eknot[i].point);
				fprintf(data, "%s\t%s\t%s\t%d\t%s", eknot[i].studentId, eknot[i].lecture_id, eknot[i].point, linePoint + state + 1, grade[i].date);
			}
		}
		FILE *fp = fopen("student.txt", "w");
		for (i = 0; i < line; i++)
		{
			if (i != line - 1)
			{
				fprintf(fp, "%s\t%s,%s\t%s\n", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
			}
			else
			{
				fprintf(fp, "%s\t%s,%s\t%s", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
			}
		}
		free(eknot);
		fclose(fp);
		fclose(data);
		printf("\n%d/%d student added successfully to the Lecture \n\n-------------------------------------------------------------------------------\nPress any key to return Main Menu", state, j);
		getch();
	}
	else
	{
		printf("\nError: No lecture was found with given ID.\n\n-------------------------------------------------------------------------------\nPress any key to return Main Menu");
		getch();
	}
	free(grade);
	free(lecture);
	fclose(lectureler);
	return 0;
}
int removeStudentFromLecture(student *stud, int line)
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nStudent Management\n__________________________________________________________________________________\n"
		   "\nDelete Student from Lecture=\n__________________________________________________________________________________\n");
	int i, j = 0, counter = 0, state = 0, index;
	char lecture_credit[3];
	char number[7], c;
	char lecture_id[MAXSTR];

	int linePoint = countLine("points.txt");
	FILE *data = fopen("points.txt", "r");
	if (data == NULL)
	{
		printf("error");
		return 1;
	}
	points *grade = (points *)malloc((linePoint) * sizeof(points));
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = '\0';
				state = 1;
				break;
			case 1:
				grade[i].lecture_id[j] = '\0';
				state = 2;
				break;
			case 2:
				grade[i].point[j] = '\0';
				state = 3;
				break;
			case 3:
				grade[i].value[j] = '\0';

				state = 4;
				break;
			}
			j = 0;
			break;
		case '\n':
			grade[i].date[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			grade[i].date[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = c;
				break;
			case 1:
				grade[i].lecture_id[j] = c;
				break;
			case 2:
				grade[i].point[j] = c;
				break;
			case 4:
				grade[i].date[j] = c;
				break;
			case 3:
				grade[i].value[j] = c;
				break;
			}
			j++;
		}
	}
	i = 0, j = 0, state = 0;
	fclose(data);
	int line_lecture = countLine("lecture.txt");
	FILE *lectureler = fopen("lecture.txt", "r");
	if (lectureler == NULL)
	{
		printf("error");
		return 1;
	}
	lectureType *lecture = (lectureType *)malloc((line_lecture) * sizeof(lectureType));
	while (!feof(lectureler))
	{
		c = fgetc(lectureler);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				lecture[i].lecturerId[j] = '\0';
				state = 3;
			}
			else if (state == 1)
			{
				lecture[i].credit[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecture[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecture[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecture[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecture[i].id[j] = c;
				break;
			case 1:
				lecture[i].credit[j] = c;
				break;
			case 2:
				lecture[i].lecturerId[j] = c;
				break;
			case 3:
				lecture[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	printf("\nEnter the Lecture ID\n=");
	scanf("%s", lecture_id);
	printf("\nStudent ID\n=");
	scanf("%s", number);
	i = 0, j = 0;
	while (j < linePoint && counter == 0)
	{
		if (strcmp(grade[j].lecture_id, lecture_id) == 0 && strcmp(grade[j].studentId, number) == 0)
		{
			counter++;
			lecture_credit[0] = lecture[j].credit[0];
			lecture_credit[1] = lecture[j].credit[1];
			lecture_credit[2] = '\0';
		}
		else
		{
			j++;
		}
	}
	if (counter)
	{
		data = fopen("points.txt", "w");
		for (i = 0; i < linePoint; i++)
		{
			if (i != j)
			{
				if (i != linePoint - 1)
					fprintf(data, "%s\t%s\t%s\t%d\t%s\n", grade[i].studentId, grade[i].lecture_id, grade[i].point, i + 1, grade[i].date);
				else
					fprintf(data, "%s\t%s\t%s\t%d\t%s", grade[i].studentId, grade[i].lecture_id, grade[i].point, i + 1, grade[i].date);
			}
			else
			{
				strcpy(grade[i].date, date());
				if (i != linePoint - 1)
					fprintf(data, "%s\t%s\t0\t%d\t%s\n", grade[i].studentId, grade[i].lecture_id, i + 1, grade[i].date);
				else
					fprintf(data, "%s\t%s\t0\t%d\t%s", grade[i].studentId, grade[i].lecture_id, i + 1, grade[i].date);
			}
		}
		FILE *fp = fopen("student.txt", "w");
		for (i = 0; i < line; i++)
		{
			if (strcmp(stud[i].id, number) == 0)
			{
				strcpy(stud[i].lecture, stringCalculate(stud[i].lecture, "01", 0));
				strcpy(stud[i].credit, stringCalculate(stud[i].credit, lecture_credit, 1));
			}
			if (i != line - 1)
				fprintf(fp, "%s\t%s,%s\t%s\n", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
			else
				fprintf(fp, "%s\t%s,%s\t%s", stud[i].id, stud[i].lecture, stud[i].credit, stud[i].name);
		}
		fclose(fp);
		fclose(data);
		printf("\n%s deleted successfully from the lecture. \n\n-------------------------------------------------------------------------------\nDevam etmek icin herhangi bir tusa basin", grade[j].studentId);
		getch();
	}
	else
	{
		printf("\nError: Given student-lecture link does not exist.\n\n-------------------------------------------------------------------------------\nPress any key to try again");
		getch();
	}
	fclose(lectureler);
	free(grade);
	return 0;
}
int academicianMenu()
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nAcademician Management\n__________________________________________________________________________________\n");
	int i, j = 0, state = 0;
	char c;
	int line = countLine("academician.txt");
	academician *lecturer = (academician *)malloc((line) * sizeof(academician));
	if (lecturer == NULL)
	{
		printf("error");
		return;
	}
	FILE *data = fopen("academician.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 1)
			{
				lecturer[i].label[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecturer[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecturer[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecturer[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecturer[i].id[j] = c;
				break;
			case 1:
				lecturer[i].label[j] = c;
				break;
			case 2:
				lecturer[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	printf("\nAcademician List\n_________________________________________"
		   "\n|ID\t|name\t\t|label");
	for (i = 0; i < line; i++)
	{
		printf("\n|%s\t|%s\t|%s", lecturer[i].id, lecturer[i].name, lecturer[i].label);
	}
	printf("\n|Total\t|%d\n_________________________________________________________", line);
	printf("\nOptions=\n__________________________________________________________________________________\n"
		   "1)Academician Add\t| Adds an academician to the system.\n"
		   "2)Academician Update\t| Updates the Academician information.\n"
		   "3)Academician Delete\t| Deletes the Academician from system.\n"
		   "\n-------------------------------------------------------------------------------\nUse Backspace to return\n-------------------------------------------------------------------------------\n");
	printf("\n=\t");
	switch (c = getch())
	{
	case '1':
		printf("\nAcademician Add");
		addAcademician(lecturer, line);
		getch();
		break;
	case '2':
		printf("\nAcademician Update");
		updateAcademician(lecturer, line);
		getch();
		break;
	case '3':
		printf("\nAcademician Delete");
		deleteAcademician(lecturer, line);
		getch();
		break;
	case 8:
		printf("Back");
		mainmenu();
		break;
	default:
		printf("Invalid Command\n\n-------------------------------------------------------------------------------\nPress any key to try again");
		getch();
		studentMenu();
	}
	free(lecturer);
	fclose(data);
	printf("\n=back");
	mainmenu();
	return;
}
void addAcademician(academician *lecturer, int line)
{
	int i, extraSize;
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nAcademician Management\n__________________________________________________________________________________\n"
		   "\nAcademician Add=\n__________________________________________________________________________________\n");
	printf("\nEnter the number of  Academician .\n=");
	scanf("%d", &extraSize);
	academician *extra = (academician *)malloc((extraSize + 1) * sizeof(academician));
	gets(extra[0].name);
	printf("\n-------------------------------------------------------------------------------");
	for (i = 0; i < extraSize; i++)
	{
		printf("\n%d. enter the name of the Academician\n=", i + 1);
		gets(extra[i].name);
		printf("\nLabel:\n=");
		gets(extra[i].label);
		sprintf(extra[i].id, "%d", 121000 + line + i + 1);
		printf("\n-------------------------------------------------------------------------------");
	}
	FILE *fp = fopen("academician.txt", "w");
	if (fp == NULL)
	{
		printf("\nError: File not found\n");
	}
	else
	{
		for (i = 0; i < line; i++)
		{
			fprintf(fp, "%s\t%s\t%s\n", lecturer[i].id, lecturer[i].label, lecturer[i].name);
		}
		for (i = 0; i < extraSize; i++)
		{
			if (i != extraSize - 1)
				fprintf(fp, "%s\t%s\t%s\n", extra[i].id, extra[i].label, extra[i].name);
			else
				fprintf(fp, "%s\t%s\t%s", extra[i].id, extra[i].label, extra[i].name);
		}
		printf("\nAcademicians were added successfully \n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
	}
	fclose(fp);
	free(extra);
}
void deleteAcademician(academician *lecturer, int line)
{
	int i = 0, counter = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nAcademician Management\n__________________________________________________________________________________\n"
		   "\nAcademician Delete=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of the Academician .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(lecturer[i].id, number) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		counter = i;
		FILE *fp = fopen("academician.txt", "w");
		if (fp == NULL)
		{
			printf("\nError: File not found\n");
		}
		else
		{
			for (i = 0; i < line; i++)
			{
				if (i != counter)
				{
					if (i != line - 1)
						fprintf(fp, "%s\t%s\t%s\n", lecturer[i].id, lecturer[i].label, lecturer[i].name);
					else
						fprintf(fp, "%s\t%s\t%s", lecturer[i].id, lecturer[i].label, lecturer[i].name);
				}
				else
				{
					printf("\n%s  deleted successfully\n__________________________________________________________________________________\nBackmek icin bir tusa basin...", lecturer[i].name);
				}
			}
		}
		fclose(fp);
	}
	else
	{
		printf("\nError: Academician with given ID does not exists.");
	}
}
void updateAcademician(academician *lecturer, int line)
{
	int i = 0, counter = 0;
	int j = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nAcademician Management\n__________________________________________________________________________________\n"
		   "\nAcademician Update=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of  Academician .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(lecturer[i].id, number) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("Enter the new information for Academician ."
			   "\n-------------------------------------------------------------------------------"
			   "\nAdi=",
			   lecturer[i].name, lecturer[i].id);
		gets(lecturer[i].name);
		gets(lecturer[i].name);
		printf("\nNumarasi=");
		gets(number);
		counter = 0;
		while (j < line && counter == 0)
		{
			if (strcmp(lecturer[j].id, number) == 0)
			{
				counter++;
			}
			else
			{
				j++;
			}
		}
		if (counter)
		{
			printf("\nError: number already exists.\n");
		}
		else
		{
			strcpy(lecturer[i].id, number);
			printf("\nLabeli=");
			gets(lecturer[i].label);
			FILE *fp = fopen("academician.txt", "w");
			if (fp == NULL)
			{
				printf("\nError: File not found\n");
			}
			else
			{
				for (i = 0; i < line; i++)
				{
					if (i != line - 1)
						fprintf(fp, "%s\t%s\t%s\n", lecturer[i].id, lecturer[i].label, lecturer[i].name);
					else
						fprintf(fp, "%s\t%s\t%s", lecturer[i].id, lecturer[i].label, lecturer[i].name);
				}
			}

			printf("\nAcademician information updated successfully.\n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
			fclose(fp);
		}
	}
	else
	{
		printf("\nError: Academician with given ID does not exists.");
	}
}

int lectureMenu()
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nLecture Management\n__________________________________________________________________________________\n");
	int i, j = 0, state = 0;
	char c;
	int line = countLine("lecture.txt");
	lectureType *lecture = (lectureType *)malloc((line) * sizeof(lectureType));
	if (lecture == NULL)
	{
		printf("error");
		return;
	}
	FILE *data = fopen("lecture.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				lecture[i].lecturerId[j] = '\0';
				state = 3;
			}
			else if (state == 1)
			{
				lecture[i].credit[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecture[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecture[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecture[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecture[i].id[j] = c;
				break;
			case 1:
				lecture[i].credit[j] = c;
				break;
			case 2:
				lecture[i].lecturerId[j] = c;
				break;
			case 3:
				lecture[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	printf("\nLecture List\n_________________________________________________________"
		   "\n|ID\t|Academician ID\t|Credit\t|name");
	for (i = 0; i < line; i++)
	{
		printf("\n|%s\t|%s\t\t|%s\t|%s", lecture[i].id, lecture[i].lecturerId, lecture[i].credit, lecture[i].name);
	}
	printf("\n|Total\t|%d\n_________________________________________________________", line);
	printf("\nOptions=\n__________________________________________________________________________________\n"
		   "1)Add\t| Adds lecture to the system.\n"
		   "2)Update\t| Updates the lecture information\n"
		   "3)Delete\t| Deletes the lecture.\n"
		   "\n-------------------------------------------------------------------------------\nUse Backspace to return\n-------------------------------------------------------------------------------\n");
	printf("\n=\t");
	switch (c = getch())
	{
	case '1':
		printf("\nlecture Add");
		addLecture(lecture, line);
		getch();
		break;
	case '2':
		printf("\nlecture Update");
		updateLecture(lecture, line);
		getch();
		break;
	case '3':
		printf("\nlecture Delete");
		deleteLecture(lecture, line);
		getch();
		break;
	case 8:
		printf("Back");
		mainmenu();
		break;
	default:
		printf("Invalid Command\n\n-------------------------------------------------------------------------------\nPress any key to try again");
		getch();
		lectureMenu();
	}
	free(lecture);
	fclose(data);
	printf("\n=back");
	mainmenu();
	return;
}
void addLecture(lectureType *lecture, int line)
{
	int i, extraSize;
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nLecture Management\n__________________________________________________________________________________\n"
		   "\nlecture Add=\n__________________________________________________________________________________\n");
	printf("\nEnter the number of Lecture Type .\n=");
	scanf("%d", &extraSize);
	lectureType *extra = (lectureType *)malloc((extraSize + 1) * sizeof(lectureType));
	gets(extra[0].name);
	printf("\n-------------------------------------------------------------------------------");
	for (i = 0; i < extraSize; i++)
	{
		printf("\n%d. Enter the name of the Lecture\n=", i + 1);
		gets(extra[i].name);
		printf("\nCredit of the Lecture\n=");
		gets(extra[i].credit);
		printf("\nAcademician ID\n=");
		gets(extra[i].lecturerId);
		sprintf(extra[i].id, "%d", 201000 + line + i + 1);
		printf("\n-------------------------------------------------------------------------------\n");
	}
	FILE *fp = fopen("lecture.txt", "w");
	if (fp == NULL)
	{
		printf("\nError: File not found\n");
	}
	else
	{
		for (i = 0; i < line; i++)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\n", lecture[i].id, lecture[i].credit, lecture[i].lecturerId, lecture[i].name);
		}
		for (i = 0; i < extraSize; i++)
		{
			printf("%s\t%s\t%s\t%s\n", extra[i].id, extra[i].credit, extra[i].lecturerId, extra[i].name);
			if (i != extraSize - 1)
				fprintf(fp, "%s\t%s\t%s\t%s\n", extra[i].id, extra[i].credit, extra[i].lecturerId, extra[i].name);
			else
				fprintf(fp, "%s\t%s\t%s\t%s", extra[i].id, extra[i].credit, extra[i].lecturerId, extra[i].name);
		}

		printf("\nlectureler added successfully \n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
	}
	fclose(fp);
	free(extra);
}
void deleteLecture(lectureType *lecture, int line)
{
	int i = 0, counter = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nLecture Management\n__________________________________________________________________________________\n"
		   "\nlecture Delete=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of the lecture .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(lecture[i].id, number) == 0)
		{
			lecture[i].id[0] = '-';
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		FILE *fp = fopen("lecture.txt", "w");
		if (fp == NULL)
		{
			printf("\nError: File not found\n");
		}
		else
		{
			for (i = 0; i < line; i++)
			{
				if (lecture[i].id[0] != '-')
				{
					if (i != line - 1)
						fprintf(fp, "%s\t%s\t%s\t%s\n", lecture[i].id, lecture[i].credit, lecture[i].lecturerId, lecture[i].name);
					else
						fprintf(fp, "%s\t%s\t%s\t%s", lecture[i].id, lecture[i].credit, lecture[i].lecturerId, lecture[i].name);
				}
				else
				{
					printf("\n%s  deleted successfully\n__________________________________________________________________________________\nBackmek icin bir tusa basin...", lecture[i].name);
				}
			}
		}

		fclose(fp);
	}
	else
	{
		printf("\nError: lecture type with given ID  does not exists.");
	}
}
void updateLecture(lectureType *lecture, int line)
{
	int i = 0, counter = 0;
	int j = 0;
	char number[7];
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nLecture Management\n__________________________________________________________________________________\n"
		   "\nlecture Update=\n__________________________________________________________________________________\n");
	printf("\nEnter the ID of  the Lecture .\n=");
	scanf("%s", number);
	while (i < line && counter == 0)
	{
		if (strcmp(lecture[i].id, number) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("Enter the new information for the Lecture ."
			   "\nAdi=",
			   lecture[i].name, lecture[i].id);
		gets(lecture[i].name);
		gets(lecture[i].name);
		printf("\nNumarasi=");
		gets(number);
		counter = 0;
		while (j < line && counter == 0)
		{
			if (strcmp(lecture[j].id, number) == 0)
			{
				counter++;
			}
			else
			{
				j++;
			}
		}
		if (counter)
		{
			printf("\nError: number already exists.\n");
		}
		else
		{
			strcpy(lecture[i].id, number);
			printf("\ncreditsi=");
			gets(lecture[i].credit);
			FILE *fp = fopen("lecture.txt", "w");
			if (fp == NULL)
			{
				printf("\nError: File not found\n");
			}
			else
			{
				for (i = 0; i < line; i++)
				{
					if (i != line - 1)
						fprintf(fp, "%s\t%s\t%s\t%s\n", lecture[i].id, lecture[i].credit, lecture[i].lecturerId, lecture[i].name);
					else
						fprintf(fp, "%s\t%s\t%s\t%s", lecture[i].id, lecture[i].credit, lecture[i].lecturerId, lecture[i].name);
				}
			}

			printf("\nlecture information updated successfully.\n__________________________________________________________________________________\nBackmek icin bir tusa basin...");
			fclose(fp);
		}
	}
	else
	{
		printf("\nError: lecture type with given ID  does not exists.");
	}
}
void search()
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nSearch Profile\n__________________________________________________________________________________\n"
		   "Enter the ID of a student, lecture veya an Academician that you would like to inspect\n=");
	int i, j = 0, state = 0;
	char c;
	int line = countLine("student.txt");
	student *stud = (student *)malloc((line) * sizeof(student));
	if (stud == NULL)
	{
		printf("error");
		return;
	}
	FILE *data = fopen("student.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				stud[i].credit[j] = '\0';
				state = 3;
			}
			else if (state == 0)
			{
				stud[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case ',':
			state = 2;
			stud[i].lecture[j] = '\0';
			j = 0;
			break;
		case '\n':
			stud[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			stud[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				stud[i].id[j] = c;
				break;
			case 1:
				stud[i].lecture[j] = c;
				break;
			case 2:
				stud[i].credit[j] = c;
				break;
			case 3:
				stud[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	fclose(data);
	i = 0;
	j = 0;
	state = 0;
	int line_uye = countLine("academician.txt");
	academician *lecturer = (academician *)malloc((line_uye) * sizeof(academician));
	if (lecturer == NULL)
	{
		printf("error");
		return;
	}
	data = fopen("academician.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 1)
			{
				lecturer[i].label[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecturer[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecturer[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecturer[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecturer[i].id[j] = c;
				break;
			case 1:
				lecturer[i].label[j] = c;
				break;
			case 2:
				lecturer[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	fclose(data);
	i = 0;
	j = 0, state = 0;
	int line_lecture = countLine("lecture.txt");
	lectureType *lecture = (lectureType *)malloc((line_lecture) * sizeof(lectureType));
	if (lecture == NULL)
	{
		printf("error");
		return;
	}
	data = fopen("lecture.txt", "r");
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			if (state == 2)
			{
				lecture[i].lecturerId[j] = '\0';
				state = 3;
			}
			else if (state == 1)
			{
				lecture[i].credit[j] = '\0';
				state = 2;
			}
			else if (state == 0)
			{
				lecture[i].id[j] = '\0';
				state = 1;
			}
			j = 0;
			break;
		case '\n':
			lecture[i].name[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			lecture[i].name[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				lecture[i].id[j] = c;
				break;
			case 1:
				lecture[i].credit[j] = c;
				break;
			case 2:
				lecture[i].lecturerId[j] = c;
				break;
			case 3:
				lecture[i].name[j] = c;
				break;
			}
			j++;
		}
	}
	fclose(data);
	i = 0;
	j = 0;
	state = 0;
	int linePoint = countLine("points.txt");
	data = fopen("points.txt", "r");
	if (data == NULL)
	{
		printf("error");
	}
	points *grade = (points *)malloc((linePoint) * sizeof(points));
	while (!feof(data))
	{
		c = fgetc(data);
		switch (c)
		{
		case '\t':
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = '\0';
				state = 1;
				break;
			case 1:
				grade[i].lecture_id[j] = '\0';
				state = 2;
				break;
			case 2:
				grade[i].point[j] = '\0';
				state = 3;
				break;
			case 3:
				grade[i].value[j] = '\0';
				state = 4;
				break;
			}
			j = 0;
			break;
		case '\n':
			grade[i].date[j] = '\0';
			state = 0;
			i++;
			j = 0;
			break;
		case EOF:
			grade[i].date[j] = '\0';
			break;
		default:
			switch (state)
			{
			case 0:
				grade[i].studentId[j] = c;
				break;
			case 1:
				grade[i].lecture_id[j] = c;
				break;
			case 2:
				grade[i].point[j] = c;
				break;
			case 4:
				grade[i].date[j] = c;
				break;
			case 3:
				grade[i].value[j] = c;
				break;
			}
			j++;
		}
	}
	fclose(data);
	char text[MAXSTR];
	scanf("%s", text);

	if (text[0] == '1' && text[1] == '0')
	{
		searchStudent(text, stud, line, grade, linePoint);
	}
	else if (text[0] == '1' && text[1] == '2')
	{
		searchAcademician(text, lecturer, line_uye, lecture, line_lecture);
	}
	else if (text[0] == '2' && text[1] == '0')
	{
		searchLecture(text, lecture, line_lecture, grade, linePoint);
	}

	free(lecture);
	free(stud);
	free(lecturer);
	free(grade);
}
void searchStudent(char *text, student *stud, int line, points *grade, int linePoint)
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nSearch Profile\n__________________________________________________________________________________\n"
		   "\nSearching Student=\n__________________________________________________________________________________\n");
	int i = 0, j = 0, state = 0, counter = 0;
	while (i < line && counter == 0)
	{
		if (strcmp(stud[i].id, text) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("%s  is found.\n"
			   "Press 1 to save on a file,\nPress any key to inspect only.\n",
			   stud[i].name);
		counter = i;
		if (getch() == '1')
		{
			char filename[MAXSTR];
			strcpy(filename, text);
			strcat(filename, ".txt");
			FILE *data = fopen(filename, "w");
			fprintf(data, "\n%s\t%s\n_________________________________________"
						  "\nLecture Taken:\t%s\nRemaining Credit:\t%s\n_________________________________________"
						  "\n|lecture ID\t|Lecture State\t|Update Date\n",
					stud[counter].name, stud[counter].id, stud[counter].lecture, stud[counter].credit);
			for (i = 0; i < linePoint; i++)
			{
				if (strcmp(text, grade[i].studentId) == 0)
				{
					if (grade[i].point[0] == '1')
						fprintf(data, "|%s\t\t|SAVED\t|%s\n", grade[i].lecture_id, grade[i].date);
					else
						fprintf(data, "|%s\t\t|LEFT\t|%s\n", grade[i].lecture_id, grade[i].date);
				}
			}
			fclose(data);
			printf("\nlecture information added successfully to %s .", filename);
		}
		printf("\n\n%s\t%s\n_________________________________________"
			   "\nLecture Taken:\t%s\nRemaining Credit:\t%s\n_________________________________________"
			   "\n|lecture ID\t|Lecture State\t|Update Date\n",
			   stud[counter].name, stud[counter].id, stud[counter].lecture, stud[counter].credit);
		for (i = 0; i < linePoint; i++)
		{
			if (strcmp(text, grade[i].studentId) == 0)
			{
				if (grade[i].point[0] == '1')
					printf("|%s\t\t|SAVED\t|%s\n", grade[i].lecture_id, grade[i].date);
				else
					printf("|%s\t\t|LEFT\t|%s\n", grade[i].lecture_id, grade[i].date);
			}
		}
	}
	else
	{
		printf("\nError: student does not exists.");
	}
	printf("\n\n-------------------------------------------------------------------------------\nPress any key to return Main Menu");
	getch();
}
void searchAcademician(char *text, academician *lecturer, int line, lectureType *lecture, int line_lecture)
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nSearch Profile\n__________________________________________________________________________________\n"
		   "\nSearching Academician=\n__________________________________________________________________________________\n");
	int i = 0, j = 0, state = 0, counter = 0;
	while (i < line && counter == 0)
	{
		if (strcmp(lecturer[i].id, text) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("%s  is found.\n"
			   "Press 1 to save on a file,\nPress any key to inspect only.\n",
			   lecturer[i].name);
		counter = i;
		if (getch() == '1')
		{
			char filename[MAXSTR];
			strcpy(filename, text);
			strcat(filename, ".txt");
			FILE *data = fopen(filename, "w");
			fprintf(data, "\n%s\t%s\n_________________________________________"
						  "\nLabel:\t%s\n_________________________________________"
						  "\n|lecture Adi\t\t\t|lecture ID\t|creditsi\n",
					lecturer[counter].name, lecturer[counter].id, lecturer[counter].label);
			for (i = 0; i < line_lecture; i++)
			{
				if (strcmp(text, lecture[i].lecturerId) == 0)
				{
					fprintf(data, "|%s\t|%s\t|%s\n", lecture[i].name, lecture[i].id, lecture[i].credit);
				}
			}
			fclose(data);
			printf("\nAcademician information added successfully to %s .", filename);
		}
		printf("\n%s\t%s\n_________________________________________"
			   "\nLabel:\t%s\n_________________________________________"
			   "\n|Lecture Name\t|Lecture ID\t|Credit\n",
			   lecturer[counter].name, lecturer[counter].id, lecturer[counter].label);
		for (i = 0; i < line_lecture; i++)
		{
			if (strcmp(text, lecture[i].lecturerId) == 0)
			{
				printf("|%s\t|%s\t|%s\n", lecture[i].name, lecture[i].id, lecture[i].credit);
			}
		}
	}
	else
	{
		printf("\nError: Academician does not exists.");
	}
	printf("\n\n-------------------------------------------------------------------------------\nPress any key to return Main Menu");
	getch();
}
void searchLecture(char *text, lectureType *lecture, int line, points *grade, int linePoint)
{
	system("@cls||clear");
	printf("__________________________________________________________________________________"
		   "\nSearch Profile\n__________________________________________________________________________________\n"
		   "\nSearching Lecture=\n__________________________________________________________________________________\n");
	int i = 0, j = 0, state = 0, counter = 0;
	while (i < line && counter == 0)
	{
		if (strcmp(lecture[i].id, text) == 0)
		{
			counter++;
		}
		else
		{
			i++;
		}
	}
	if (counter)
	{
		printf("%s  was found.\n"
			   "Press 1 to save on a file,\nPress any key to inspect only.\n",
			   lecture[i].name);
		counter = i;
		if (getch() == '1')
		{
			char filename[MAXSTR];
			strcpy(filename, text);
			strcat(filename, ".txt");
			FILE *data = fopen(filename, "w");
			fprintf(data, "\n%s\t%s\n_________________________________________"
						  "\nAcademician ID:\t%s\nLecture Credit:\t%s\n_________________________________________"
						  "\n|Student ID\t|Lecture State\t|Update Date\n",
					lecture[counter].name, lecture[counter].id, lecture[counter].lecturerId, lecture[counter].credit);
			for (i = 0; i < linePoint; i++)
			{
				if (strcmp(lecture[counter].id, grade[i].lecture_id) == 0)
				{
					if (grade[i].point[0] == '1')
						fprintf(data, "|%s\t\t|SAVED\t|%s\n", grade[i].studentId, grade[i].date);
					else
						fprintf(data, "|%s\t\t|LEFT\t|%s\n", grade[i].studentId, grade[i].date);
				}
			}
			fclose(data);
			printf("\nlecture information added successfully to %s .", filename);
		}
		printf("\n%s\t%s\n_________________________________________"
			   "\nAcademician ID:\t%s\nLecture Credit:\t%s\n_________________________________________"
			   "\n|Student ID\t|Lecture State\t|Update Date\n",
			   lecture[counter].name, lecture[counter].id, lecture[counter].lecturerId, lecture[counter].credit);
		for (i = 0; i < linePoint; i++)
		{
			if (strcmp(text, grade[i].lecture_id) == 0)
			{
				if (grade[i].point[0] == '1')
					printf("|%s\t\t|SAVED\t|%s\n", grade[i].studentId, grade[i].date);
				else
					printf("|%s\t\t|LEFT\t|%s\n", grade[i].studentId, grade[i].date);
			}
		}
	}
	else
	{
		printf("\nError: lecture does not exists.");
	}
	printf("\n\n-------------------------------------------------------------------------------\nPress any key to return Main Menu");
	getch();
}
int countLine(char *fileName)
{ //Sinif haric satir sayisini bulur
	FILE *adress = fopen(fileName, "r");
	char c;
	int n = 1;
	while (!feof(adress))
	{
		c = fgetc(adress);
		if (c == '\n')
			n++;
	}
	fclose(adress);
	return n;
}
char *stringCalculate(char *num1, char *num2, int sum)
{
	char *result = malloc(3 * sizeof(char));
	result[2] = '\0';
	if (sum)
	{
		if ((num1[1] - '0' + num2[1] - '0') >= 10)
		{
			result[1] = (num1[1] - '0' + num2[1] - '0') % 10 + '0';
			result[0] = num1[0] + num2[0] + 1 - '0';
		}
		else
		{
			result[1] = num1[1] + num2[1] - '0';
			result[0] = num1[0] + num2[0] - '0';
		}
	}
	else
	{
		if ((num1[0] > num2[0]) || ((num1[0] == num2[0]) && num1[1] >= num2[1]))
		{
			if ((num1[1] - num2[1]) < 0)
			{
				result[1] = 10 + num1[1] - num2[1] + '0';
				result[0] = num1[0] - num2[0] - 1 + '0';
			}
			else
			{
				result[1] = num1[1] - num2[1] + '0';
				result[0] = num1[0] - num2[0] + '0';
			}
		}
		else
		{
			result[0] = '-';
			result[1] = '1';
		}
	}
	return result;
}
char *date()
{
	char *t = (char *)malloc((MAXSTR) * sizeof(char));
	if (t != NULL)
	{
		time_t dateTime;
		time(&dateTime);
		sprintf(t, ctime(&dateTime));
		printf("\t%s", t);
	}
	return t;
}
