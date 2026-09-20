#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATIENTS 100
#define SPECIALTIES 4

char patientNames[MAX_PATIENTS][50];
int patientAges[MAX_PATIENTS];
int triageLevels[MAX_PATIENTS];
int specialties[MAX_PATIENTS];
int wards[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int dailyPatientCount[SPECIALTIES] =
{
    0,
    0,
    0,
    0
};
int dailyPatientCap[4]=
{
    30,
    20,
    12,
    10
};

int patientCount=0;
int nextPatientID=1000;

float billAmount[MAX_PATIENTS];
int bedOccupancy[4][20]= {0};

void patientIntake();
void viewBedOccupancy();
void displayEmergency();
void systemReport();
void wardDetails(int option);
void registrationSummary();
void calcDailyPatientCount(int specialty);
int calcEstimatedWaitingTime(int count,int specialty);
int setBed(int id);
float calcSurcharge(int urgencyLevel,float fee);
float calcBaseFee(int doctoraId);
float calcWardStayCost(int days,int fee);
float calcAgeDiscount(int age,float total);
void saveBedStatus();
void loadBedStatus();
void savePatientRecord();
void loadNextPatientID();
void mainMenu();
int main()
{
    loadNextPatientID();
    mainMenu();
    return 0;
}
void patientIntake()
{
    system("cls");
    if(patientCount >= MAX_PATIENTS)
    {
        printf("Patient registration limit reached!\n");
        return;
    }
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
        strcspn(patientNames[patientCount],"\n")
    ]='\0';

    do
    {
        printf("\nEnter the age(Year) : ");
        scanf("%d",&patientAges[patientCount]);

        if(patientAges[patientCount] <0 ||
                patientAges[patientCount] >120)
        {
            printf("\n\tInvalid age! Enter an age between 0 and 120.\n");
        }

    }
    while(patientAges[patientCount] <0 ||
            patientAges[patientCount]>120);

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
        printf("Select specialty ID : ");
        scanf("%d",&specialties[patientCount]);

        if(specialties[patientCount]<1 || specialties[patientCount]>4)
        {
            printf("\n\tInvalid Input\n\n");
        }
        else if(dailyPatientCount[specialties[patientCount]-1]>= dailyPatientCap[specialties[patientCount]-1])

        {
            printf("\nDaily patient capacity reached!\n");
        }

    }
    while(specialties[patientCount]<1 ||
            specialties[patientCount]>4 ||
            dailyPatientCount[specialties[patientCount]-1] >=
            dailyPatientCap[specialties[patientCount]-1]);



    printf("\n-----------------------------------------------\n");
    printf("             Ward Addmission                     \n");
    printf("-------------------------------------------------\n\n\n");

    printf("Is the patient admitted to a ward? \n");
    printf("\t1.Yes\n");
    printf("\t2.No\n\n");
    int option;
    do
    {
        printf("Enter the choice : ");
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
    char choice;
    while(1)
    {
        printf("\nBack to main menu (Y/N): ");
        scanf(" %c", &choice);

        if (choice=='Y' || choice=='y')
        {
            system("cls");
            mainMenu();
        }
        else if (choice=='N' ||choice== 'n')
        {
            system("cls");
            printf("=========================================\n");
            printf("         GOOD BYE! HAVE A NICE DAY       \n");
            printf("=========================================\n");
            exit(0);
        }
        else
        {
            printf("\n\tInvalid choice! Please enter Y or N.\n\n");
        }
    }
}


void viewBedOccupancy()
{
    system("cls");
    int capacity[4] = {20, 10, 10, 5};

    char *wardNames[4] =
    {
        "General Ward",
        "Paediatric Ward",
        "Surgical Ward",
        "ICU"
    };
    printf("=================================================\n");
    printf("           SMART HOSPITAL SYSTEM                 \n");
    printf("           BED OCCUPANCY MATRIX                  \n");
    printf("=================================================\n\n\n");
    printf("Bed Occupancy Matrix\n");
    printf("-------------------------------------------------\n\n\n");

    printf("Hospital Ward Data\n");
    printf("+---------+---------------------------+---------------------------+--------------------+\n");
    printf("| Ward ID | Ward Name                 | Daily Bed Rate (LKR/Day)  | Total Bed Capacity |\n");
    printf("+---------+---------------------------+---------------------------+--------------------+\n");
    printf("|    1    | General Ward              |                   3000.00 |         20         |\n");
    printf("|    2    | Paediatric Ward           |                   6000.00 |         10         |\n");
    printf("|    3    | Surgical Ward             |                  12000.00 |         10         |\n");
    printf("|    4    | ICU (Intensive Care Unit) |                  25000.00 |         05         |\n");
    printf("+---------+---------------------------+---------------------------+--------------------+\n");

    printf("\n\nLegend : [0] = Available | [1] = Occupied | [--] = N/A (Exceeds Ward Capacity)");
    printf("\n---------------------------------------------------------------------------------\n\n");

    printf("+------------------------+---------------------------------------------------------------------------------+\n");

    printf("| %-22s | ","Ward Name / Bed ");
    for (int i = 1; i <= 20; i++)
    {
        printf("%03d ",i);
    }
    printf("|\n");
    printf("+------------------------+---------------------------------------------------------------------------------+\n");
    for(int ward=0; ward<4; ward++)
    {
        printf("| %-22s | ",wardNames[ward]);

        for(int bed=0; bed<20; bed++)
        {
            if(bed<capacity[ward])
            {
                printf("[%d] ",bedOccupancy[ward][bed]);
            }
            else
            {
                printf("[-] ");
            }
        }

        printf("|\n");
    }
    printf("+------------------------+---------------------------------------------------------------------------------+\n");
    char choice;
    while(1)
    {
        printf("\nBack to main menu (Y/N): ");
        scanf(" %c", &choice);

        if (choice=='Y' || choice=='y')
        {
            system("cls");
            mainMenu();
        }
        else if (choice=='N' ||choice== 'n')
        {
            system("cls");
            printf("=========================================\n");
            printf("         GOOD BYE! HAVE A NICE DAY       \n");
            printf("=========================================\n");
            exit(0);
        }
        else
        {
            printf("\n\tInvalid choice! Please enter Y or N.\n\n");
        }
    }
}

void displayEmergency()
{
    system("cls");
    int critical=0;
    int urgent=0;
    int normal=0;
    printf("===================================================\n");
    printf("           SMART HOSPITAL SYSTEM                 \n");
    printf("           TRIAGE EMERGENCY QUEUE                  \n");
    printf("===================================================\n\n\n");

    printf("Total Patients Registerd : %d",patientCount);
    printf("\n\n Urgency Level Summary \n");
    printf("---------------------------------------------------\n");
    for(int i=0 ; i < patientCount ; i++)
    {
        if(triageLevels[i]==1)
            normal++;
        else if(triageLevels[i]==2)
            urgent++;
        else if(triageLevels[i]==3)
            critical++;
    }
    printf(" Level 3 - Critical       : %d",critical);
    printf("\n Level 2 - Urgent         : %d",urgent);
    printf("\n Level 1 - Normal         : %d",normal);
    printf("\n---------------------------------------------------\n\n");

    printf("                  EMERGENCY QUEUE                   \n");
    printf("-----------------------------------------------------------\n");
    printf("%-10s %-30s %-20s\n", "Priority", "Patient Name", "Urgency Level");
    printf("\n-----------------------------------------------------------\n");
    int count=0;
    for(int i=0 ; i < patientCount; i++)
    {
        if(triageLevels[i]==3)
        {
            printf("%-10d %-30s %-20s\n",count+1,patientNames[i],"Level 3 - Critical");
            count++;
        }
    }
    //printf("\n");
    for(int i=0 ; i < patientCount; i++)
    {
        if(triageLevels[i]==2)
        {
           printf("%-10d %-30s %-20s\n",count+1,patientNames[i],"Level 2 - Urgent");
            count++;
        }
    }
   // printf("\n");
    for(int i=0 ; i < patientCount; i++)
    {
        if(triageLevels[i]==1)
        {
            printf("%-10d %-30s %-20s\n",count+1,patientNames[i],"Level 1 - Normal");
            count++;
        }
    }
    //printf("\n");
    printf("\n-----------------------------------------------------------\n");

    printf("\n Critical Patient : %d",critical);
    printf("\n Urgent Patient   : %d",urgent);
    printf("\n Normal Patient   : %d",normal);
    printf("\n\n===================================================");
    char choice;
    while(1)
    {
        printf("\nBack to main menu (Y/N): ");
        scanf(" %c", &choice);

        if (choice=='Y' || choice=='y')
        {
            system("cls");
            mainMenu();
        }
        else if (choice=='N' ||choice== 'n')
        {
            system("cls");
            printf("=========================================\n");
            printf("         GOOD BYE! HAVE A NICE DAY       \n");
            printf("=========================================\n");
            exit(0);
        }
        else
        {
            printf("\n\tInvalid choice! Please enter Y or N.\n\n");
        }
    }
}

void systemReport()
{
    system("cls");
    int admittedPatients=0;
    int normalPatients=0;
    int urgentPatients=0;
    int criticalPatients=0;

    int generalOccupied=0;
    int paediatricOccupied=0;
    int surgicalOccupied=0;
    int icuOccupied=0;

    int totalBeds = 20+10+10+5;
    int occupiedBeds =0;

    for(int i=0; i < patientCount; i++)
    {

        if(wards[i] >0)
        {
            admittedPatients++;
        }

        if(triageLevels[i]==1)
        {
            normalPatients++;
        }
        else if(triageLevels[i]==2)
        {
            urgentPatients++;
        }
        else if(triageLevels[i]==3)
        {
            criticalPatients++;
        }
    }
    for(int i=0; i<20; i++)
    {
        if(bedOccupancy[0][i]==1)
        {
            generalOccupied++;
        }
    }

    for(int i=0; i<10; i++)
    {
        if(bedOccupancy[1][i]==1)
        {
            paediatricOccupied++;
        }
    }

    for(int i=0; i<10; i++)
    {
        if(bedOccupancy[2][i]==1)
        {
            surgicalOccupied++;
        }
    }

    for(int i=0; i < 5; i++)
    {
        if(bedOccupancy[3][i]==1)
        {
            icuOccupied++;
        }
    }

    occupiedBeds = generalOccupied+paediatricOccupied+surgicalOccupied+icuOccupied;

    printf("===============================================================\n");
    printf("                  SMART HOSPITAL SYSTEM\n");
    printf("                       SYSTEM REPORT\n");
    printf("===============================================================\n\n");

    printf("                    SYSTEM OVERVIEW\n");
    printf("---------------------------------------------------------------\n");

    printf("Total Registered Patients : %d\n",patientCount);
    printf("Total Admitted Patients   : %d\n",admittedPatients);
    printf("Total Outpatients         : %d\n",
           patientCount-admittedPatients);

    printf("\n---------------------------------------------------------------\n");
    printf("                     TRIAGE SUMMARY\n");
    printf("---------------------------------------------------------------\n");

    printf("Triage Level                 Patients\n");
    printf("--------------------------------------\n");
    printf("1. Normal                       %d\n",normalPatients);
    printf("2. Urgent                       %d\n",urgentPatients);
    printf("3. Critical                     %d\n",criticalPatients);

    printf("\n---------------------------------------------------------------\n");
    printf("                   SPECIALTY SUMMARY\n");
    printf("---------------------------------------------------------------\n");

    printf("Specialty                     Patients\n");
    printf("--------------------------------------\n");
    printf("1. General Practice (OPD)        %d\n",dailyPatientCount[0]);
    printf("2. Paediatrics                   %d\n",dailyPatientCount[1]);
    printf("3. Cardiology                    %d\n",dailyPatientCount[2]);
    printf("4. Neurology                     %d\n",dailyPatientCount[3]);
    printf("\n---------------------------------------------------------------\n");
    printf("                    WARD OCCUPANCY\n");
    printf("---------------------------------------------------------------\n");

    printf("Ward                  Occupied    Capacity\n");
    printf("--------------------------------------------\n");

    printf("General Ward             %2d          20\n",generalOccupied);
    printf("Paediatric Ward          %2d          10\n",paediatricOccupied);
    printf("Surgical Ward            %2d          10\n",surgicalOccupied);
    printf("ICU                      %2d           5\n",icuOccupied);

    printf("--------------------------------------------\n");

    printf("Total Beds Occupied      : %d\n",occupiedBeds);
    printf("Total Bed Capacity       : %d\n",totalBeds);
    printf("Available Beds           : %d\n",totalBeds-occupiedBeds);

    printf("\n===============================================================\n");
    printf("                  END OF SYSTEM REPORT\n");
    printf("===============================================================\n");
    char choice;
    while(1)
    {
        printf("Back to main menu (Y/N): ");
        scanf(" %c", &choice);

        if (choice=='Y' || choice=='y')
        {
            system("cls");
            mainMenu();
        }
        else if (choice=='N' ||choice== 'n')
        {
            system("cls");
            printf("=========================================\n");
            printf("         GOOD BYE! HAVE A NICE DAY       \n");
            printf("=========================================\n");
            exit(0);
        }
        else
        {
            printf("\n\tInvalid choice! Please enter Y or N.\n\n");
        }
    }
}


void wardDetails(int option)
{
    if(option==2)
    {
        wards[patientCount]=0;

        return;
    }
    printf("\n--------------------------------------------------\n");
    printf("                 WARD DETAILS                     \n");
    printf("--------------------------------------------------\n\n\n");
    printf("\t1.General Ward\n");
    printf("\t2.Paediatric Ward\n");
    printf("\t3.Surgical Ward\n");
    printf("\t4.ICU (Intensive Care Unit)\n\n");

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
    if(setBed(wards[patientCount]))
    {
        printf("\nEnter number of admitted days: ");
        scanf("%d", &daysAdmitted[patientCount]);

        registrationSummary();
    }
    else
    {
        wards[patientCount]=0;
        daysAdmitted[patientCount]=0;

        printf("\nPatient cannot be admitted to this ward.\n");
        registrationSummary();
    }

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
    if(specialties[patientCount] ==1)
        printf("General Practice (OPD)\n");
    else if(specialties[patientCount] ==2)
        printf("Paediatrics\n");
    else if(specialties[patientCount] ==3)
        printf("Cardiology\n");
    else if(specialties[patientCount] ==4)
        printf("Neurology\n");

    printf("Ward          : ");
    if(wards[patientCount] ==0)
        printf("Not Admitted\n");
    else if(wards[patientCount] ==1)
        printf("General Ward\n");
    else if(wards[patientCount] ==2)
        printf("Paediatric Ward\n");
    else if(wards[patientCount] ==3)
        printf("Surgical Ward\n");
    else if(wards[patientCount] ==4)
        printf("ICU\n");
    if (wards[patientCount] >0)
    {
        printf("Admitted Days : %d\n",daysAdmitted[patientCount]);
    }
    else
    {
        printf("Admitted Days : 0\n");
    }
    printf("\n-----------------------------------------------------\n");
    printf("Base Consulation Fee  : LKR %.2f",calcBaseFee(specialties[patientCount]));
    printf("\nEmergency Surcharge   : LKR %.2f",calcSurcharge(triageLevels[patientCount],calcBaseFee(specialties[patientCount])));
    printf("\nWard Stay Cost(%d Days): LKR %.2f",daysAdmitted[patientCount],calcWardStayCost(daysAdmitted[patientCount],wards[patientCount]));

    printf("\n-----------------------------------------------------\n\n");

    float bill = calcBaseFee(specialties[patientCount])
                 + calcSurcharge(triageLevels[patientCount],
                                 calcBaseFee(specialties[patientCount]))
                 + calcWardStayCost(daysAdmitted[patientCount],
                                    wards[patientCount]);
    printf("\nGross Total Bill        : LKR %.2f",bill);
    printf("\nAge Subsidy Discount    : LKR %.2f",calcAgeDiscount(patientAges[patientCount],bill));
    float finalBill=bill-calcAgeDiscount(patientAges[patientCount],bill);
    billAmount[patientCount]=finalBill;
    savePatientRecord();
    printf("\nFinal Payable Amount    : LKR %.2f",finalBill);
    printf("\n\n-------------------------------------------------");
    printf("\n         Patient Registered Successfully           ");
    printf("\n---------------------------------------------------");
    printf("\n\nPatient ID              : PAT-%d",nextPatientID);
    printf("\nEstiimated Waiting time : %d mins",calcEstimatedWaitingTime(dailyPatientCount[specialties[patientCount]-1],specialties[patientCount]));
    calcDailyPatientCount(specialties[patientCount]);

}
void calcDailyPatientCount(int specialty)
{
    if(specialty==1)
        dailyPatientCount[0]++;
    else if(specialty==2)
        dailyPatientCount[1]++;
    else if(specialty==3)
        dailyPatientCount[2]++;
    else if(specialty==4)
        dailyPatientCount[3]++;
}
int calcEstimatedWaitingTime(int count,int specialty)
{
    int result;
    if(specialty==1)
        result=(count)*15;
    else if(specialty==2)
        result=(count)*20;
    else if(specialty==3)
        result=(count)*30;
    else if(specialty==4)
        result=(count)*30;
    return result;
}
int setBed(int id)
{
    int capacity;

    if(id ==1)
        capacity=20;
    else if(id==2)
        capacity=10;
    else if(id==3)
        capacity=10;
    else if(id==4)
        capacity=5;
    else
        return 0;

    int wardIndex =id-1;

    for(int i=0; i < capacity; i++)
    {
        if(bedOccupancy[wardIndex][i] ==0)
        {
            bedOccupancy[wardIndex][i]=1;
            saveBedStatus();
            printf("\nBed %02d assigned successfully.\n",i+1);

            return 1;
        }

    }

    printf("\nNo available beds in this ward!\n");
    return 0;
}
float calcSurcharge(int urgencyLevel,float fee)
{
    float charge;
    if(urgencyLevel==1)
        charge=0;
    else if (urgencyLevel==2)
        charge=(fee*20)/100;
    else if (urgencyLevel==3)
        charge=(fee*50)/100;
    return charge;
}
float calcBaseFee(int doctorId)
{
    float fee;
    if(doctorId==1)
        fee=1500.0;
    else if(doctorId==2)
        fee=2500.0;
    else if(doctorId==3)
        fee=4500.0;
    else if(doctorId==4)
        fee=5000.0;
    return fee;

}
float calcWardStayCost(int days,int wardId)
{
    float result;
    if(wardId==1)
        result=days*3000.0;
    else if(wardId==2)
        result=days*6000.0;
    else if(wardId==3)
        result=days*12000.0;
    else if(wardId==4)
        result=days*25000.0;
    else
        result=0.0;
    return result;

}
float calcAgeDiscount(int age,float total)
{
    float result=0;
    if(age<5 || age>65)
        result=total*15/100;
    return result;
}
void saveBedStatus()
{
    FILE *file=fopen("beds_status.txt", "w");

    if(file==NULL)
    {
        printf("Error opening beds_status.txt\n");
        return;
    }

    for(int ward=0; ward<4; ward++)
    {
        for(int bed=0; bed < 20; bed++)
        {
            fprintf(file, "%d ",bedOccupancy[ward][bed]);
        }

        fprintf(file,"\n");
    }

    fclose(file);
}
void savePatientRecord()
{
    FILE *file=fopen("patient_records.txt","a");

    if(file == NULL)
    {
        printf("Error opening patient_records.txt\n");
        return;
    }

    fprintf(file,
            "Patient ID: PAT-%d | "
            "Name: %s | "
            "Age: %d | "
            "Specialty: %d | "
            "Triage: %d | "
            "Ward: %d | "
            "Days: %d | "
            "Final Bill: LKR %.2f\n",
            nextPatientID,
            patientNames[patientCount],
            patientAges[patientCount],
            specialties[patientCount],
            triageLevels[patientCount],
            wards[patientCount],
            daysAdmitted[patientCount],
            billAmount[patientCount]);
    fclose(file);
    nextPatientID++;
}
void loadNextPatientID()
{
    FILE *file=fopen("patient_records.txt","r");

    if(file==NULL)
    {
        nextPatientID=1000;
        return;
    }

    char line[300];
    int id;
    int lastID = 999;

    while(fgets(line,sizeof(line),file))
    {
        if(sscanf(line,"Patient ID: PAT-%d",&id)==1)
        {
            if(id>lastID)
            {
                lastID=id;
            }
        }
    }

    nextPatientID=lastID+1;

    fclose(file);
}
void mainMenu()
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
            saveBedStatus();
            printf("Saving data and exiting...\n");
            return;

        default:
            printf("\n\tInvalid Input! Please enter 1-5.\n");
        }
    }
    while(option != 5);
    printf("\n\n");
}
