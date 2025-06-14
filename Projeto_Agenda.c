#include <stdio.h>
#include <string.h>

//Struct of the agenda
typedef struct agenda{
    char event[251];
    int iday, imonth, iyear;
    int initial_hour, initial_minute;
    int fday, fmonth, fyear;
    int final_hour, final_minute;
} commitments;

//Function to create appointments
char create_appointment(commitments events[], int *count) {

    int i = *count;
//Put the name of the event
    printf("Enter the name of the event:\n");
    fgets(events[i].event, sizeof(events[i].event), stdin);

//Event start date and time
    printf("Enter the start date of the event (day/month/year):\n");
    scanf("%d %d %d", &events[i].iday, &events[i].imonth, &events[i].iyear);

    printf("Set the starting hour and minute (00:00):\n");
    scanf("%d %d", &events[i].initial_hour, &events[i].initial_minute);

//Date and end time of the event
    printf("Enter the end date of the event (day/month/year):\n");
    scanf("%d %d %d", &events[i].fday, &events[i].fmonth, &events[i].fyear);

    printf("Set the final hour and minute (00:00):\n");
    scanf("%d %d", &events[i].final_hour, &events[i].final_minute);
       
    (*count)++;

    char next;
    printf("Type (s) to stop and save; (c) to create another appointment; (d) to delete an appointment; (v) to view appointments.\n");
    scanf(" %c", &next);

//cleaning buffer
    getchar();
           
    return next;
}


//Function to delete appointments
int delete_commitments(commitments events[], int *count, int index) {
    if(index < 0 || index >= *count) {
        return 0;
    }

    for(int i = index; i < *count - 1; i++) {
        events[i] = events[i + 1];
    }

    (*count)--;
    
    return 1;
}

//Function to view appointments
void viwer(commitments events[], int count){
    printf("\n--- Commitments ---\n");
    for(int i = 0; i < count; i++) {
        printf("Event %d:\n", i + 1);
        printf("Name: %s\n", events[i].event);
        printf("Start: %02d/%02d/%04d às %02d:%02d\n",
               events[i].iday, events[i].imonth, events[i].iyear,
               events[i].initial_hour, events[i].initial_minute);
        printf("End: %02d/%02d/%04d às %02d:%02d\n",
               events[i].fday, events[i].fmonth, events[i].fyear,
               events[i].final_hour, events[i].final_minute);
    }
    printf("\n--- Commitments ---\n");
    printf("\n");
}

//Function to save appointments
void save_appointments(commitments events[], int count) {
    FILE *f = fopen("agenda.txt", "w");
    if(!f) {
        printf("Error opening file to save.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        fprintf(f, "%s\n%d %d %d\n%d %d\n%d %d %d\n%d %d\n",
                events[i].event,
                events[i].iday, events[i].imonth, events[i].iyear,
                events[i].initial_hour, events[i].initial_minute,
                events[i].fday, events[i].fmonth, events[i].fyear,
                events[i].final_hour, events[i].final_minute);
    }

    fclose(f);
}

//Function to load appointments
int load_appointments(commitments events[]) {
    FILE *f = fopen("agenda.txt", "r");
    if(!f) {
        return 0;
    } 

    int count = 0;
    while (fgets(events[count].event, sizeof(events[count].event), f)) {
        events[count].event[strcspn(events[count].event, "\n")] = '\0';
        fscanf(f, "%d %d %d", &events[count].iday, &events[count].imonth, &events[count].iyear);
        fscanf(f, "%d %d", &events[count].initial_hour, &events[count].initial_minute);
        fscanf(f, "%d %d %d", &events[count].fday, &events[count].fmonth, &events[count].fyear);
        fscanf(f, "%d %d", &events[count].final_hour, &events[count].final_minute);
        fgetc(f);
        count++;
    }

    fclose(f);
    return count;
}

int main() {
    commitments events[500];
    
    int count = load_appointments(events);
    char set;

    printf("Type (c) to create an appointment; (d) to delete an appointment; (v) to view appointments.\n");
    scanf(" %c", &set);
//cleaning buffer
    getchar();
    if(set == 'c') {
        while(1) {
            set = create_appointment(events, &count);

            if(set == 'v') {
                save_appointments(events, count);
                viwer(events, count);              
            }
            else if(set == 'c') {
                continue;
            }
            else if(set == 'd') {

                int index;
                viwer(events, count);

                printf("Enter the appointment number you want to delete: ");
                scanf("%d", &index);
                getchar();

                index--;
                if(delete_commitments(events, &count, index)) {
                    printf("Appointment deleted successfully!\n");
                }
                else {
                    printf("Invalid index. No appointments were deleted.\n");
                }
                save_appointments(events, count);
            }
            else if(set == 's') {
                save_appointments(events, count);
                return 0;
                
            }

            printf("Type (s) to stop and save; (c) to create another appointment; (d) to delete an appointment; (v) to view appointments.\n");

        }
    }

    else if(set == 'd') {
        int index;
        viwer(events, count);

        printf("Enter the appointment number you want to delete: ");
        scanf("%d", &index);
        getchar();

        index--;
        if(delete_commitments(events, &count, index)) {
            printf("Appointment deleted successfully!\n");
        }
        else {
            printf("Invalid index. No appointments were deleted.\n");
        }

        save_appointments(events, count);
    }

    else {
        viwer(events, count);
        printf("Type (c) to create an appointment; (d) to delete an appointment; (r) to stop.\n");
        scanf(" %c", &set);

        if(set == 'c') {
            create_appointment(events, &count);
            save_appointments(events, count);

        }

        else if(set == 'd') {
            int index;
            viwer(events, count);

            printf("Enter the appointment number you want to delete: ");
            scanf("%d", &index);
            getchar();

            index--;
            if(delete_commitments(events, &count, index)) {
                printf("Appointment deleted successfully!\n");
            }
            else {
                printf("Invalid index. No appointments were deleted.\n");
            }
            
            save_appointments(events, count);
        }
        
        else {
            return 0;
        }

    }

    return 0;
}
