#include <stdio.h>
#include <stdlib.h>
void patientIntake();
void viewBedOccupancy();
void displayEmergency();
void systemReport();

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
