#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void patientIntake();
void viewBedOccupancy();
void displayEmergency();
void systemReport();
void wardDetails();
void registrationSummary();

char patienDetails[100][2][50];

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
    int option=1;
    while(option)
    {
        printf("\n\nSelect an Option(1-5) : ");
        scanf("%d",&option);
        getchar();
        printf("\n");
        switch(option)
        {
        case 1:
            patientIntake();
            option=0;
            break;
        case 2:
            viewBedOccupancy();
            option=0;
            break;
        case 3:
            displayEmergency();
            option=0;
            break;
        case 4:
            systemReport();
            option=0;
            break;
        default:
            printf("\tInvalid Input");
            option=1;
            continue;

        }
    }

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

    char name[30];
    int len=sizeof(patienDetails)/sizeof(patienDetails[0]);
    int age,option;
    printf("Enter the patient name : ");
    fgets(patienDetails[len][0],50,stdin);
    printf("\nEnter the age(Year) : ");
    scanf("%s",&patienDetails[len][1]);
    printf("\nEmergency / Triage Level: \n\n");
    printf("\t1.Normal\n");
    printf("\t2.Urgent\n");
    printf("\t3.Critical\n");
    printf("\n Enter the choice : ");
    scanf("%d",&option);
    printf("\n-----------------------------------------------\n");
    printf("             Select Specialty                    \n");
    printf("-------------------------------------------------\n\n\n");

    printf("1.General Practice (OPD)\n");
    printf("2.Paediatrics\n");
    printf("3.Cardiology\n");
    printf("4.Neurology\n\n");
    int option2,option3;
    printf("Select specialty ID:");
    scanf("%d",&option2);

    printf("\n-----------------------------------------------\n");
    printf("             Ward Addmission                     \n");
    printf("-------------------------------------------------\n\n\n");

    printf("Is the patient admitted to a ward?\n");
    printf("\t1.Yes\n");
    printf("\t2.No\n\n");
    printf("Enter the choice :");
    scanf("%d",&option3);
    switch(option3){
        case 1:wardDetails();
                break;
        case 2:registrationSummary();
                break;
        default :printf("Invalid Input");
    }



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

void wardDetails(){
    printf("\n--------------------------------------------------\n");
    printf("                 WARD DETAILS                     \n");
    printf("--------------------------------------------------\n\n\n");
    printf("\t1.General Ward\n");
    printf("\t2.Paediatric Ward\n");
    printf("\t3.Surgical Ward\n");
    printf("\t4.ICU (Intensive Care Unit\n\n");

    int option;
    printf("Enter Ward ID : ");
    scanf("%d",&option);
    registrationSummary();

}

void registrationSummary(){
    printf("\n--------------------------------------------------\n");
    printf("               REGISTRATION SUMMARY                 \n");
    printf("--------------------------------------------------\n\n\n");

    printf("Patient Name  : \n");
    printf("Patient Age   : \n");
    printf("Triage Level  : \n");
    printf("Specialty     : \n");
    printf("Ward          : \n");

}
