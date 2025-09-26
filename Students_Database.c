/*
"#" means pre-processing directives, tells the compiler to use information from header file
"<>" means file b/w is a header file, that file is to be found in "usual place" which is system dependent 
*/
#include <stdio.h>   // "stdio.h" means standard input and output and "h" means header file 
#include <string.h>  // standard library header file that provides various functions to work with strings and memory  

// Define the maximum number of students and length of each field
#define MAX_STUDENTS 100 // "#define" use to declare constant 
#define NAME_LENGTH 50
#define FATHER_NAME_LENGTH 50
#define DEPARTMENT_LENGTH 50

// Defining a structure to hold student information
typedef struct // (typedef)-->used to create alias for data-types
{
    int id;                                     // student id
    char name[NAME_LENGTH];                     // student name
    char father_name[FATHER_NAME_LENGTH];       // student father name
    char department[DEPARTMENT_LENGTH];         // student depratment
} Student; // structure name 

// Declaring functions 
void Welcome_To_The_Database();                           
void Display_Screen();                                    
void View_Students(Student   students[], int count);          // For viewing students' record 
void Add_Student(Student     students[], int *count);         // For adding new students
void Modify_Student(Student  students[], int count);          // For modifying students' record 
void Search_For_Student(Student students[], int count);       // For searching students' record 
void Save_To_File(Student    students[], int count);          // For saving students' record permanently 
void Load_From_File(Student  students[], int *count);         // For loading students' record from file 

// C-programs must specify one function called main, () indicate to the compiler that it is a function  
int main()
{
    Student students[MAX_STUDENTS]; // array to hold students' records
    int count = 0; // current number of students (using count variable to track number of students)
    
    Welcome_To_The_Database();
    // Load records from file, if file is available (otherwise it create it's own)
    Load_From_File(students, &count);  

    // Display menu options 
    int choice;  // to choose what you want to do
    do
    {
        // display menu options
        Display_Screen();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                Add_Student(students, &count); 
                break;
            case 2:
                View_Students(students, count);
                break;
            case 3:
                Modify_Student(students, count);
                break;
            case 4:
                Search_For_Student(students, count);
                break;
            case 5:
                Save_To_File(students, count); 
                printf("Data saved successfully... Exiting...\n");
                printf("<---------------------------->\n"); 
                break;      
            default:
                printf("Invalid choice! please try again...\n");
        
        }

    } while (choice != 5);

    return 0;
}

// Function to welcome screen
void Welcome_To_The_Database()
{
    printf("\033[1;32m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\033[1;32m\n"); // using escape sequence color for colorful display 
    printf("|                                     |\n");
    printf("| \033[1;32m          WELCOME TO THE       \033[1;32m     |\n");
    printf("| \033[1;32m     COLLEGE DATABASE SYSTEM   \033[1;32m     |\n");
    printf("|                                     |\n");
    printf("\033[1;32m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\033[1;32m\n");
    printf("| \033[1;32m       MANAGE STUDENTS RECORD    \033[1;32m   |\n");
    printf("\033[1;32m^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\033[1;32m\n");

}

// Function to display the main menu
void Display_Screen()
{
    printf("\033[1;32m****************************************  \033[1;32m\n"); // using escape sequence color for colorful display 
    printf("|   \033[1;32m           MAIN MENU:      \033[1;32m        |\n");
    printf("----------------------------------------\n");
    printf("|  \033[1;32m       1. Add New Record     \033[1;32m       |\n");
    printf("|  \033[1;32m       2. View All Records   \033[1;32m       |\n");
    printf("|  \033[1;32m       3. Modify Record      \033[1;32m       |\n");
    printf("|  \033[1;32m       4. Search For Student        \033[1;32m|\n");
    printf("|  \033[1;32m       5. Save & Exit        \033[1;32m       |\n");
    printf("****************************************\n");
}

// Function to view all students that are already stored in files and inforamtion that we are gonna add
void View_Students(Student students[], int count)
{
    printf("\n <--- List of Students ---> \n");
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d\n Name: %s\n Father_Name: %s\n Department: %s\n", students[i].id, students[i].name, students[i].father_name, students[i].department);
        printf("<------------------------>\n");
    }
    
    if (count == 0)
    {
        printf("No students found in the database...\n");
        return;
    }
}

// Function to add a new student
void Add_Student(Student students[], int *count)
{
    if(*count >= MAX_STUDENTS)  // checking if there is any space in database or not
    {
        printf("Database is full! Cannot add more students...\n");
        return;
    }

    Student new_student;
    new_student.id = *count + 1; // assigning a unique id
    printf("\n <--- Adding Student Record ---> \n");
    printf("Enter Student Name: ");
    scanf(" %[^\n]", new_student.name); // reading full name of student

    printf("Enter Student Father's Name: ");
    scanf(" %[^\n]", new_student.father_name); // reading full father name of student

    printf("Enter Student Department: ");
    scanf(" %[^\n]", new_student.department); // reading full department name of student

    students[*count] = new_student;  // adding new student to the array
    (*count)++;                      // increasing the count of students

    printf("Student added successfully!\n");
    
}

// Function to modify an existing students' record
void Modify_Student(Student students[], int count)
{
    int id;
    printf("<--- Modifyiny Student Record --->\n");
    printf("Enter the student ID to modify: ");
    scanf("%d", &id);

    if (id <= 0 || id > count) // checking for invalid id  
    {
        printf("Invalid ID! No student found with that ID...\n");
        return;
    }
    
    // Using index variable to keep track of the specific record, that we want to modify within an array
    int index = id - 1;   // suppose we want to access the teacher with ID 3, this gives us index = 2
    printf("Enter New Name for Student (ID: %d): ", id);
    scanf(" %[^\n]", students[index].name);

    printf("Enter New Father Name for Student (ID: %d): ", id);
    scanf(" %[^\n]", students[index].father_name);

    printf("Enter New Department for Student (ID: %d): ", id);
    scanf(" %[^\n]", students[index].department);

    printf("Student record modified successfully!\n");
    printf("<-------------------------------->\n");

}  

// Function to search for students by ID or Department
void Search_For_Student(Student students[], int count)
{
    if (count == 0) 
    {
        printf("No students in the database to search...\n"); // to check student exists or not 
        return;
    }
    else 
    {
        printf("Invalid choice! Please try again...\n");
    }

    int choice;
    printf("\n<--- Search For Student --->\n");
    printf("Search by:\n 1. ID\n 2. Department\nEnter your choice: "); // searching for student by ID or department
    scanf("%d", &choice);

    if (choice == 1) // searching for student by ID 
    {
        int search_id;
        printf("Enter Student ID to search: ");
        scanf("%d", &search_id);

        for (int i = 0; i < count; i++) 
        {
            if (students[i].id == search_id)
            {
                printf("\nStudent Found:\n");
                printf("ID: %d\n Name: %s\n Father Name: %s\n Department: %s\n",
                students[i].id, students[i].name, students[i].father_name, students[i].department);
                return;
            }
        }
        printf("Student with ID %d not found...\n", search_id); // if student with specific ID not found 

    } 
    
    else if (choice == 2) // searching for student by department
    {
        char search_department[DEPARTMENT_LENGTH];
        printf("Enter Department to search: ");
        scanf(" %[^\n]", search_department);

        int found = 0; 
        printf("\nStudents in Department '%s':\n", search_department);
        for (int i = 0; i < count; i++) 
        {
            if (strcmp(students[i].department, search_department) == 0) 
            {
                printf("ID: %d\n Name: %s\n Father Name: %s\n",
                students[i].id, students[i].name, students[i].father_name);
                printf("<------------------------>\n");
                found = 1;
            }
        }

        if (!found) 
        {
            printf("No students found in Department '%s'...\n", search_department); // if student with specific department not found
        }

    } 
    
    else 
    {
        printf("Invalid choice! Please try again...\n");
    }
}

// Function to save students record to a file
void Save_To_File(Student students[], int count)
{
    FILE *file = fopen("Students_Database_File.txt", "w"); // opening file to write students' records 

    if (file == NULL) // checking for errors
    {
        printf("Error opening file for writing...\n");
        return;
    }

    for (int i = 0; i < count; i++) // writing each piece of data on a new line
    {
        fprintf(file, "Student ID: %d\n Student Name: %s\n Student's Father Name: %s\n Department: %s\n", 
                students[i].id, 
                students[i].name, 
                students[i].father_name, 
                students[i].department);
    }
    
    fclose(file); // closing file after writing students' records
}

// Function to load students records from the file 
void Load_From_File(Student students[], int *count)
{
    FILE *file = fopen("Students_Database_File.txt", "r"); // opening file for reading students' records

    if (file == NULL) // checking for errors
    {
        printf("File not found or unable to open...\n");
        return;
    }

    *count = 0;
    while (!feof(file)) // Loop until end of file
    {
        Student temp; // Temporary student to read data into

        // Read and parse each field line by line
        if (fscanf(file, " Student ID: %d\n", &temp.id) != 1)
            break;

        fgets(temp.name, NAME_LENGTH, file);
        fgets(temp.father_name, FATHER_NAME_LENGTH, file);
        fgets(temp.department, DEPARTMENT_LENGTH, file);

        // Remove the newline characters from strings
        temp.name[strcspn(temp.name, "\n")] = '\0';
        temp.father_name[strcspn(temp.father_name, "\n")] = '\0';
        temp.department[strcspn(temp.department, "\n")] = '\0';
        
        // to find where the actual data (e.g., name or department) begins after the label (e.g., Student field:)
        // strchr returns a pointer to the colon's position in the string or NULL if no colon is found
        char *name_start = strchr(temp.name, ':');
        char *father_name_start = strchr(temp.father_name, ':');
        char *department_start = strchr(temp.department, ':');
        
        // this code checks if the colon (:) was found in each string
        // if found, it moves the pointer 2 positions forward to skip the colon and the space (: ), so it points directly to the actual data
        // if not found, it does nothing 
        if (name_start) name_start += 2; 
        if (father_name_start) father_name_start += 2; 
        if (department_start) department_start += 2; 

        // if there is text after the colon, it copies that text into temp.variable
        // if there is no text after the colon (or no colon), it sets temp.variable to an empty string 
        strcpy(temp.name, name_start ? name_start : ""); 
        strcpy(temp.father_name, father_name_start ? father_name_start : ""); 
        strcpy(temp.department, department_start ? department_start : ""); 

        // Add the information from temp to the student array
        students[*count] = temp;
        (*count)++;
    }

    fclose(file); // close the file
    printf("Data loaded successfully! %d records found...\n", *count);
}

    
