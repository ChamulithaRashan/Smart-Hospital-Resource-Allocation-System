#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATIENTS 100

char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int triageLevels[MAX_PATIENTS];
int specialties[MAX_PATIENTS];
int wards[MAX_PATIENTS];
int admitted[MAX_PATIENTS];

int patientCount = 0;
void patientIntake();
void viewBedOccupancy();
void displayEmergency();
void systemReport();
void wardDetails(int option);
void registrationSummary();

int main()
{
    printf("\===================================================================\n");
    printf("\t\tHospital Resource Allocating System");
    printf("\n===================================================================\n");
    printf("\n\n\t\t\tMain Menu\n");
    printf("---------------------------------------------------------------------\n\n");
    printf("\t1.Patient Intake & Registration ");
    printf("\n\n\t2.View Bed Occupancy Matrix");
    printf("\n\n\t3.Display Triage Emergency Queue");
    printf("\n\n\t4.System Reports Analytics");
    printf("\n\n\t5.Save and Exit");
    int option = 0;

    do
    {
        printf("\n\nSelect an Option (1-5): ");
        scanf("%d", &option);
        getchar();

        switch(option)
        {
        case 1:
            patientIntake();
            break;

        case 2:
            viewBedOccupancy();
            break;

        case 3:
            displayEmergency();
            break;

        case 4:
            systemReport();
            break;

        case 5:
            printf("Saving data and exiting...\n");
            break;

        default:
            printf("\n\tInvalid Input! Please enter 1-5.\n");
        }

    }
    while(option != 5);


    printf("\n\n");
    return 0;
}
void patientIntake()
{
    system("cls");
    printf("=================================================\n");
    printf("           SMART HOSPITAL SYSTEM                 \n");
    printf("              PATIENT INTAKE                     \n");
    printf("=================================================\n\n\n");
    printf("Patient Registration\n");
    printf("-------------------------------------------------\n\n\n");

    int age;
    printf("Enter the patient name : ");
    fgets(patientNames[patientCount],50,stdin);

    patientNames[patientCount][
        strcspn(patientNames[patientCount], "\n")]='\0';
    printf("\nEnter the age(Year) : ");
    scanf("%d", &patientAges[patientCount]);

    printf("\nEmergency / Triage Level: \n\n");
    printf("\t1.Normal\n");
    printf("\t2.Urgent\n");
    printf("\t3.Critical\n");

    do
    {
        printf("\n Enter the choice : ");
        scanf("%d",&triageLevels[patientCount]);
        if(triageLevels[patientCount]<1 || triageLevels[patientCount]>3)
        {
            printf("\n\tInvalid Input\n");
            continue;
        }
    }
    while(triageLevels[patientCount]<1 || triageLevels[patientCount]>3);

    printf("\n-----------------------------------------------\n");
    printf("             Select Specialty                    \n");
    printf("-------------------------------------------------\n\n\n");

    printf("1.General Practice (OPD)\n");
    printf("2.Paediatrics\n");
    printf("3.Cardiology\n");
    printf("4.Neurology\n\n");
    do
    {
        printf("Select specialty ID:");
        scanf("%d",&specialties[patientCount]);
        if(specialties[patientCount]<1 || specialties[patientCount]>4)
        {
            printf("\n\tInvalid Input\n\n");
            continue;
        }
    }
    while(specialties[patientCount]<1 || specialties[patientCount]>4);



    printf("\n-----------------------------------------------\n");
    printf("             Ward Addmission                     \n");
    printf("-------------------------------------------------\n\n\n");

    printf("Is the patient admitted to a ward?\n");
    printf("\t1.Yes\n");
    printf("\t2.No\n\n");
    int option;
    do
    {
        printf("Enter the choice :");
        scanf("%d",&option);

        if(option<1 || option>2)
        {
            printf("\n\tInvalid Input\n\n");
            continue;
        }
    }
    while(option<1 || option>2);

    switch(option)
    {
    case 1:
        wardDetails(option);

        break;
    case 2:
        registrationSummary();

        break;
    default :
        printf("Invalid Input");

    }
    patientCount++;
}


void viewBedOccupancy()
{
}

void displayEmergency()
{
}

void systemReport()
{
}

void wardDetails(int option)
{
    if(option==2){
        wards[patientCount]=0;
        return;
    }
    printf("\n--------------------------------------------------\n");
    printf("                 WARD DETAILS                     \n");
    printf("--------------------------------------------------\n\n\n");
    printf("\t1.General Ward\n");
    printf("\t2.Paediatric Ward\n");
    printf("\t3.Surgical Ward\n");
    printf("\t4.ICU (Intensive Care Unit\n\n");

    do
    {
        printf("Enter Ward ID (1-4): ");
        scanf("%d",&wards[patientCount]);
        if(wards[patientCount]<1 || wards[patientCount]>4)
        {
            printf("\n\tInvalid Input\n\n");
            continue;
        }
    }
    while(wards[patientCount]<1 || wards[patientCount]>4);
    registrationSummary();

}

void registrationSummary()
{
    printf("\n--------------------------------------------------\n");
    printf("              REGISTRATION SUMMARY\n");
    printf("--------------------------------------------------\n\n");

    printf("Patient Name  : %s\n",patientNames[patientCount]);
    printf("Patient Age   : %d\n",patientAges[patientCount]);

    printf("Triage Level  : ");
    if(triageLevels[patientCount] == 1)
        printf("Normal\n");
    else if(triageLevels[patientCount] == 2)
        printf("Urgent\n");
    else if(triageLevels[patientCount] == 3)
        printf("Critical\n");

    printf("Specialty     : ");
    if(specialties[patientCount] == 1)
        printf("General Practice (OPD)\n");
    else if(specialties[patientCount] == 2)
        printf("Paediatrics\n");
    else if(specialties[patientCount] == 3)
        printf("Cardiology\n");
    else if(specialties[patientCount] == 4)
        printf("Neurology\n");

    printf("Ward          : ");
    if(wards[patientCount] == 0)
        printf("Not Admitted\n");
    else if(wards[patientCount] == 1)
        printf("General Ward\n");
    else if(wards[patientCount] == 2)
        printf("Paediatric Ward\n");
    else if(wards[patientCount] == 3)
        printf("Surgical Ward\n");
    else if(wards[patientCount] == 4)
        printf("ICU\n");
}
