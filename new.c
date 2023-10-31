#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pdfgen.c"
#include "pdfgen.h"
// extra questions thay to next pdf ma jatu reh evu karwanu baki che

// created structure for circular linked list
struct circular_linked_list
{
    char question[100];
    int index;
    struct circular_linked_list *next;
};

// created head pointers for each category
struct circular_linked_list *head_easy = NULL;
struct circular_linked_list *head_medium = NULL;
struct circular_linked_list *head_hard = NULL;

// function to create circular linked list
void create_linked_list(struct circular_linked_list **head, char question[100], int check)
{
    if (*head == NULL)
    {
        *head = (struct circular_linked_list *)malloc(sizeof(struct circular_linked_list));
        strcpy((*head)->question, question);
        (*head)->index = 0;
        (*head)->next = *head;
    }
    else
    {
        struct circular_linked_list *temp = *head;
        while (temp->next != *head)
        {
            temp = temp->next;
        }
        struct circular_linked_list *new_element = (struct circular_linked_list *)malloc(sizeof(struct circular_linked_list));
        strcpy(new_element->question, question);
        new_element->index = temp->index + 1;
        new_element->next = *head;
        temp->next = new_element;
    }
}

// function to open the easy.txt file and create circular linked list 
void create_circular_linked_list_easy()
{
    FILE *file_pointer;
    file_pointer = fopen("easy.txt", "r");
    if (file_pointer == NULL)
    {
        printf("File does not exist\n");
        exit(0);
    }
    else
    {
        for (int i = 1; i <= 25; i++)
        {
            char line[100];
            fgets(line, 100, file_pointer);
            create_linked_list(&head_easy, line, i);
        }
        fclose(file_pointer);
    }
}

// function to open the medium.txt file and create circular linked list
void create_circular_linked_list_medium()
{
    FILE *file_pointer;
    file_pointer = fopen("medium.txt", "r");
    if (file_pointer == NULL)
    {
        printf("File does not exist\n");
        exit(0);
    }
    else
    {
        for (int i = 1; i <= 25; i++)
        {
            char line[100];
            fgets(line, 100, file_pointer);
            create_linked_list(&head_medium, line, i);
        }
        fclose(file_pointer);
    }
}

// function to open the hard.txt file and create circular linked list
void create_circular_linked_list_hard()
{
    FILE *file_pointer;
    file_pointer = fopen("hard.txt", "r");
    if (file_pointer == NULL)
    {
        printf("File does not exist\n");
        exit(0);
    }
    else
    {
        for (int i = 1; i <= 25; i++)
        {
            char line[100];
            fgets(line, 100, file_pointer);
            create_linked_list(&head_hard, line, i);
        }
        fclose(file_pointer);
    }
}

int main()
{
    int number_of_papers;
    printf("Enter the number of question papers to create : ");
    scanf("%d", &number_of_papers);
    printf("\n");

    for (int i = 1; i <= number_of_papers; i++)
    {
        int easy_questions, medium_questions, hard_questions;
        printf("Enter the number of easy questions to be included: ");
        scanf("%d", &easy_questions);
        printf("Enter the number of medium level questions to be included: ");
        scanf("%d", &medium_questions);
        printf("Enter the number of hard questions to be included: ");
        scanf("%d", &hard_questions);

        if(easy_questions > 25 || hard_questions>25 || medium_questions>25) {
            printf("ERROR: Number of questions should be less than 25 in each category\n");
            exit(0);
        }

        create_circular_linked_list_easy();
        create_circular_linked_list_medium();
        create_circular_linked_list_hard();

        int indexing = 1;

        // Skipping according to the previous question paper
        FILE *fp1;
        fp1 = fopen("index.txt", "r");
        if (fp1 != NULL)
        {
            int easy_skip, medium_skip, hard_skip;
            fscanf(fp1, "%d", &easy_skip);
            fscanf(fp1, "%d", &medium_skip);
            fscanf(fp1, "%d", &hard_skip);

            for (int i = 0; i < easy_skip; i++)
            {
                head_easy = head_easy->next;
            }

            for (int i = 0; i < medium_skip; i++)
            {
                head_medium = head_medium->next;
            }

            for (int i = 0; i < hard_skip; i++)
            {
                head_hard = head_hard->next;
            }

            fclose(fp1);
        }
       // printf("INFO: e\n");




        // Creating the output file
        char *output_filename = NULL;
        asprintf(&output_filename, "output-%d.pdf", i);

        struct pdf_info info = {
            .creator = "Nirma University",
            .producer = "Nirma University",
            .title = "Nirma University",
            .author = "Nirma University",
            .subject = "Nirma University",
            .date = "Today"};
        struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
        printf("INFO: pdf created\n");
        pdf_set_font(pdf, "Times-Roman");
        pdf_object *page = pdf_append_page(pdf);
        printf("INFO: page added\n");

        pdf_add_text_wrap(
            pdf, page, "Nirma University",
            24, 0, PDF_A4_HEIGHT - 40, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
        pdf_add_text_wrap(
            pdf, page, "Institute of Technology",
            16, 0, PDF_A4_HEIGHT - 54, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
        pdf_add_text_wrap(
            pdf, page, "B. Tech. in Computer Science and Engineering, Semester - III",
            12, 0, PDF_A4_HEIGHT - 66, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
        pdf_add_text_wrap(
            pdf, page, "2CS301 Data Structures and Algorithms",
            12, 0, PDF_A4_HEIGHT - 78, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);

        pdf_add_text_wrap(
            pdf, page, "Roll No: \n\nDate: __/__/___ \n \nTime: 10:30 am to 1:30 pm",
            12, 50, PDF_A4_HEIGHT - 105, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_LEFT, NULL);
        pdf_add_rectangle(pdf, page, 100, PDF_A4_HEIGHT - 110, 70, 20, 1, PDF_BLACK);
        //pdf_add_text(pdf ,page , "---------------------------------------------------------------------------------------------------------------" , 12, 0, PDF_A4_HEIGHT - 120, 0, PDF_A4_WIDTH, PDF_ALIGN_CENTER, NULL);

        pdf_set_font(pdf, "Times-Bold");
        pdf_add_text_wrap(
            pdf, page, "SECTION - I", 14, 0, PDF_A4_HEIGHT - 180, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
        pdf_set_font(pdf, "Times-Roman");

        int offset = 200;
        float temp = 0;
        
        // Adding questions from easy.txt to the pdf
        for (int i = 0; i < easy_questions; i++)
        {
            FILE *fp;
            fp = fopen(output_filename, "a");
            fseek(fp, 3L, SEEK_SET);
            fprintf(fp, "%d %s", indexing, head_easy->question);
            char *question_index = NULL;
            asprintf(&question_index, "Q.%d:    %s ", indexing, head_easy->question);
            pdf_add_text_wrap(pdf, page, question_index, 12, 50, PDF_A4_HEIGHT - offset, 0, PDF_BLACK, PDF_A4_WIDTH, PDF_ALIGN_LEFT, &temp);
            offset += 13;
            temp = 0;
            fclose(fp);
            indexing++;
            head_easy = head_easy->next;
            free(question_index);
        }
          pdf_set_font(pdf, "Times-Bold");
        pdf_add_text_wrap(
            pdf, page, "SECTION - II", 14, 0, PDF_A4_HEIGHT - offset, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
pdf_set_font(pdf, "Times-Roman");
        offset += 20;

        // Adding questions from hard.txt to the pdf
        for (int i = 0; i < hard_questions; i++)
        {
            FILE *fp;
            fp = fopen(output_filename, "a");
            fprintf(fp, "%d %s", indexing, head_hard->question);
            char *question_index = NULL;
            asprintf(&question_index, "Q.%d:   %s ", indexing, head_hard->question);
            pdf_add_text_wrap(pdf, page, question_index, 12, 50, PDF_A4_HEIGHT - offset, 0, PDF_BLACK, PDF_A4_WIDTH, PDF_ALIGN_LEFT, &temp);
            offset += 13;
            temp = 0;
            fclose(fp);
            indexing++;
            head_hard = head_hard->next;
            offset += 3;
            free(question_index);
        }
          pdf_set_font(pdf, "Times-Bold");
        pdf_add_text_wrap(
            pdf, page, "SECTION - III", 14, 0, PDF_A4_HEIGHT - offset, 0, PDF_BLACK, PDF_A4_WIDTH,
            PDF_ALIGN_CENTER, NULL);
pdf_set_font(pdf, "Times-Roman");
        offset += 20;

        // Adding questions from medium.txt to the pdf
        for (int i = 0; i < medium_questions; i++)
        {
            FILE *fp;
            fp = fopen(output_filename, "a");
            fprintf(fp, "%d %s", indexing, head_medium->question);
            char *question_index = NULL;

            asprintf(&question_index, "Q.%d:   %s ", indexing, head_medium->question);
            pdf_add_text_wrap(pdf, page, question_index, 12, 50, PDF_A4_HEIGHT - offset, 0, PDF_BLACK, PDF_A4_WIDTH, PDF_ALIGN_LEFT, &temp);
            offset += 13;
            temp = 0;
            fclose(fp);
            indexing++;
            head_medium = head_medium->next;
        }
        pdf_save(pdf, output_filename);
        pdf_destroy(pdf);

        FILE *fp;
        fp = fopen("index.txt", "w");
        fseek(fp, 0L, SEEK_SET);
        fprintf(fp, "%d\n", easy_questions%26);
        fprintf(fp, "%d\n", medium_questions %26);
        fprintf(fp, "%d\n", hard_questions%26);
        fclose(fp);
    }

    return 0;
}
